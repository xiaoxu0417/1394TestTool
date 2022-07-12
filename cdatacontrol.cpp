#include "cdatacontrol.h"

Input_vmc* CDataControl::inputdata = nullptr;
int CDataControl::inputdatalength = 0;

CDataControl::CDataControl(int b, int e, int o,int datatype,bool io,int length,QMap <int,QString> meaning)
{
    beginbit = b;
    endbit = e;
    offset = o;
    this->datatype = datatype;
    this->m_io = io;
    if(!inputdata)
    {
        inputdata = (Input_vmc*)malloc(sizeof(Input_vmc));
        memset(inputdata,0x0,sizeof(Input_vmc));
    }

    m_meaning = meaning;

    if(io == false)
    {

    }
}

CDataControl::~CDataControl()
{
    if(inputdata)
    {
        delete inputdata;
        inputdata = nullptr;
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
    //应该按照类型处理下,比如float类型,现在统一按照整型处理debug
    int ret = 10;
    QString mean;

    qDebug()<<"update output! "<<m_io;
    Output_vmc data = var.value<Output_vmc>();
    unsigned int *p = (unsigned int *)&data + offset;
    unsigned int bits = endbit - beginbit + 1;
    unsigned int left = ((0x1 << bits) - 1);
    unsigned int right = beginbit;
    printf("%d %d %d \n",((*p) & left) >> right,left,right);
    //ret = ((*p) & right) >> right;
    ret = ((*p) >> right) & left;

    emit testsetOutPutdata(QString::number(ret));

    if(datatype == 1 || datatype == 2)
    {
        mean = m_meaning[ret];

        updateStyle(mean);
    }
}

//清除输入数据
void CDataControl::slot_clearalldata()
{
    memset(inputdata,  0x0,    sizeof(Input_vmc));

    //0 is invaild
    emit updateStyle(m_meaning[0]);
    emit updateDllInPutdata();//
}

void CDataControl::slot_onLoadInputData(QVariant var)
{
    Input_vmc data = var.value<Input_vmc>();
    //qDebug()<<"load"<<endbit<<" "<<beginbit<<" "<<offset;
    memcpy(inputdata,&data,sizeof (data));
    updateInputUIFormIni();
}

unsigned int CDataControl::getOffset() const
{
    return offset;
}

void CDataControl::setOffset(unsigned int value)
{
    offset = value;
}

int CDataControl::getEndbit() const
{
    return endbit;
}

void CDataControl::setEndbit(int value)
{
    endbit = value;
}

int CDataControl::getBeginbit() const
{
    return beginbit;
}

void CDataControl::setBeginbit(int value)
{
    beginbit = value;
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
    if( mean == QString::fromLocal8Bit("正常") || mean == QString::fromLocal8Bit("有效"))
    {
        emit updateMeaningstyle(VAILD_STYLE);
    }
    else if(mean == QString::fromLocal8Bit("故障") || mean == QString::fromLocal8Bit("无效"))
    {
        emit updateMeaningstyle(INVAILD_STYLE);
    }
    else
    {
        emit updateMeaningstyle(NULL_STYLE);
    }
    emit updateMeaning(mean);
}

void CDataControl::updateInputUIFormIni()
{
    int ret = 10;
    QString mean;

    qDebug()<<"updateInputUIFormIni! "<<m_io<<beginbit<<endbit<<offset;
    //整型
    if(1 == datatype || 2 == datatype)
    {
        unsigned int *p = (unsigned int *)inputdata + offset;
        unsigned int bits = endbit - beginbit + 1;
        unsigned int left = ((0x1 << bits) - 1);
        unsigned int right = beginbit;
        printf("%d %d %d \n",((*p) & left) >> right,left,right);
        //ret = ((*p) & right) >> right;
        ret = ((*p) >> right) & left;

        mean = m_meaning[ret];
        updateStyle(mean);

        emit updateLineEdit(QString::number(ret));
        qDebug()<<"emit "<<ret;
    }
    //float
    else
    {
        //
    }

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

    int bits = endbit - beginbit + 1;
    if(bits < 0)
    {
        qDebug()<<"位数错误"<<endbit<<" "<<beginbit;
        return false;
    }

    int ret_int = 0;

    unsigned int ret_unint = 0;
    float ret_float = 0.0;
    unsigned int *p;
    float *pf;
    int *p2;
    unsigned int head = 0;
    unsigned int tail1 = 0;
    switch(datatype)
    {
    //int
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

        mutex.lock();
        p2 = (int *)inputdata + offset;
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
        p = (unsigned int *)inputdata + offset;
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
            qDebug()<<"FLOAT err";
            meaning = "Float err";
            emit updateMeaning(meaning);
            ret = false;
        }
        else
        {
            ret = true;
        }
        ret_float = inputstr.toFloat();

        mutex.lock();
        pf = (float *)inputdata + offset;
        *pf = ret_float;
        mutex.unlock();
        break;
    }

    return ret;
}

void* CDataControl::getIntputdata()
{
    return inputdata;
}

void CDataControl::setIntputdata(int value)
{
    inputdata = nullptr;
}


