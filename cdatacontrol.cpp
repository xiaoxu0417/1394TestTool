#include "cdatacontrol.h"

void* CDataControl::intputdata = nullptr;
int CDataControl::inputdatalength = 0;

CDataControl::CDataControl(int b, int e, int o,int datatype,bool io,int length,QMap <int,QString> meaning)
{
    beginbit = b;
    endbit = e;
    offset = o;
    this->datatype = datatype;
    this->m_io = io;
    if(!intputdata)
    {
        intputdata = (void*)malloc(sizeof(int)*length);
        memset(intputdata,0x0,sizeof(int)*length);
    }

    m_meaning = meaning;

    if(io == false)
    {
        //解析数据
    }
}

CDataControl::~CDataControl()
{
    if(intputdata)
    {
        delete intputdata;
        intputdata = nullptr;
        qDebug()<<"exit";
    }
}
void CDataControl::slot_onInputDataFinished()
{
    qDebug()<<beginbit <<" "<<endbit <<" "<< offset <<" data finish";
    //if(inputstr != "0")

    bool ret = isVaild();
    if(!ret)
    {
        emit updateLineEdit("0");
    }
    else
    {
        emit updateDllInPutdata();
    }
}

void CDataControl::slot_onInputDataChange(QString txt)
{
    qDebug()<<beginbit <<" "<<endbit <<" "<< offset <<" data change"<<txt;
    inputstr = txt;
}

void CDataControl::slot_updateOutputData(QVariant var)
{
    int ret = 10;
    QString mean;
    //更新输出端数据
    qDebug()<<"update output! "<<m_io;
    Output_vmc data = var.value<Output_vmc>();
    unsigned int *p = (unsigned int *)&data;
    unsigned int bits = endbit - beginbit + 1;
    unsigned int left = ((0x1 << bits) - 1);
    unsigned int right = beginbit;
    printf("%d %d %d \n",((*p) & left) >> right,left,right);
    //ret = ((*p) & right) >> right;
    ret = ((*p) >> right) & left;

    //当process程序运行起来时,每拍让输出数据更新
    emit testsetOutPutdata(QString::number(ret));

    if(datatype == 1 || datatype == 2)
    {
        mean = m_meaning[ret];

        updateStyle(mean);
        //float类型 还是使用初始化meaning,更新是不变
    }
}

//清除所有数据
void CDataControl::slot_clearalldata()
{
    memset(intputdata,  0x0,    sizeof(int)* inputdatalength);
    //每一个item都弹出,效果不好
//    QMessageBox message(QMessageBox::NoIcon,  "注意",  "已清零!");
//    message.exec();
    //0 is invaild
    emit updateStyle(m_meaning[0]);
    emit updateDllInPutdata();//
}

void CDataControl::setbitsdata()
{

}

int CDataControl::getDatalength()
{
    return inputdatalength;
}

void CDataControl::setDatalength(int value)
{
    inputdatalength = value;
}

void CDataControl::updateStyle(QString mean)
{
    if( mean == QString::fromLocal8Bit("有效") || mean == QString::fromLocal8Bit("正常"))
    {
        emit updateMeaningstyle(VAILD_STYLE);
    }
    else if(mean == QString::fromLocal8Bit("无效") || mean == QString::fromLocal8Bit("故障"))
    {
        emit updateMeaningstyle(INVAILD_STYLE);
    }
    else
    {
        emit updateMeaningstyle(NULL_STYLE);
    }
    emit updateMeaning(mean);
}

bool CDataControl::getIo() const
{
    return m_io;
}

void CDataControl::setIo(bool value)
{
    m_io = value;
}

bool CDataControl::isVaild()
{
    bool ret = false;
    QString meaning = "";
    //先不考虑大小端
    int bits = endbit - beginbit + 1;
    if(bits < 0)
    {
        qDebug()<<"位域错误!"<<endbit<<" "<<beginbit;
        return false;
    }

    int ret_int = 0;
    unsigned int temp = 0;
    unsigned int filter = 0;

    unsigned int ret_unint = 0;
    float ret_float = 0.0;
    unsigned int *p;
    float *pf;
    int *p2;
    unsigned int head = 0;
    unsigned int tail1 = 0;
    switch(datatype)
    {
    //int,有符号数和无符号数算法一致
    case 2:
        ret_int = inputstr.toInt();
        if(ret_int > (0x1<<bits)-1 || (ret_int < -1 * (0x1 << (bits))))
        {
            qDebug()<<"SINT error";
            ret_int = 0;
            meaning = "SINT error";
            ret = false;
        }
        else
        {
            ret = true;
        }
        meaning = m_meaning[ret_int];
        updateStyle(meaning);

        //根据begin end offset 和ret_int 修改总线数据
        mutex.lock();
        p2 = (int *)intputdata + offset;
        head = (0x1 <<(32 - endbit - 1)) - 1;
        head = head << (endbit + 1);

        tail1 = (0x1 << (beginbit)) - 1;
        head = head | tail1;
        *p2 = (*p2) & head;
        *p2 = (*p2)|(ret_int << beginbit);
        mutex.unlock();
        break;
   //unsigned int
    case 1:
        ret_unint = inputstr.toUInt();

        //32 uint容错,按照移位操作为0
        if(bits == 32)
        {
            if(ret_unint > ((0x1 << 32)-1))
            {
                qDebug()<<"32 UINT err";
                ret_unint = 0;
                meaning = "UINT error";
                ret = false;
            }
            else
            {
                meaning = m_meaning[ret_unint];
                ret = true;
            }
        }
        else if(ret_unint > ((0x1<<(int)bits)-1) /*|| (ret_unint < 0)*/)
        {
            qDebug()<<"UINT error";
            ret_unint = 0;
            meaning = "UINT error";
            ret = false;
        }
        else
        {
            meaning = m_meaning[ret_unint];
            ret = true;
        }
        updateStyle(meaning);

        mutex.lock();
        p = (unsigned int *)intputdata + offset;
        head = (0x1 <<(32 - endbit - 1)) - 1;
        head = head << (endbit + 1);

        tail1 = (0x1 << (beginbit)) - 1;
        head = head | tail1;
        *p = (*p) & head;
        *p = (*p)|(ret_unint << beginbit);
        mutex.unlock();
        break;

   //float
    case 3:
        if(bits != 32)
        {
            qDebug()<<"FLOAT 位数错误";
            meaning = "Float越界";
            emit updateMeaning(meaning);
            ret = false;
        }
        else
        {
            ret = true;
        }
        ret_float = inputstr.toFloat();

        mutex.lock();
        pf = (float *)intputdata + offset;
        *pf = ret_float;
        mutex.unlock();
        break;
    }

    return ret;
}

void* CDataControl::getIntputdata()
{       
    return intputdata;
}

void CDataControl::setIntputdata(int value)
{
    intputdata = nullptr;
}


