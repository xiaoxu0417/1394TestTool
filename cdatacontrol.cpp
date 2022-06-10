#include "cdatacontrol.h"

void* CDataControl::intputdata = nullptr;
int CDataControl::inputdatalength = 0;

CDataControl::CDataControl(int b, int e, int o,int datatype,bool io,int length)
{
    beginbit = b;
    endbit = e;
    offset = o;
    this->datatype = datatype;
    this->io = io;
    if(!intputdata)
    {
        intputdata = (void*)malloc(sizeof(int)*length);
        memset(intputdata,0x0,sizeof(int)*length);
    }

    if(io == false)
    {
        //解析数据
    }
}

void CDataControl::slot_onInputDataFinished()
{
    qDebug()<<beginbit <<" "<<endbit <<" "<< offset <<" data finish";
    //if(inputstr != "0")
    {
        bool ret = isVaild();
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
    //更新输出端数据
    qDebug()<<"update output! "<<io;
    struct testdata_out data = var.value<struct testdata_out>();
    int *p = (int *)&data;
    unsigned int bits = endbit - beginbit + 1;
    unsigned int left = ((0x1 << bits) - 1);
    unsigned int right = beginbit;
    printf("%d %d %d \n",((*p) & left) >> right,left,right);
    //ret = ((*p) & right) >> right;
    ret = ((*p) >> right) & left;

    //当process程序运行起来时,每拍让输出数据更新
    emit testsetOutPutdata(QString::number(ret));
}

//清除所有数据
void CDataControl::slot_clearalldata()
{
    //struct testdata *data = (struct testdata *)intputdata;

    memset(intputdata,  0x0,    sizeof(int)* inputdatalength);


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

bool CDataControl::getIo() const
{
    return io;
}

void CDataControl::setIo(bool value)
{
    io = value;
}

bool CDataControl::isVaild()
{
    bool ret = false;
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
            qDebug()<<"SINT 数值越界";
            ret_int = 0;
        }
        //根据begin end offset 和ret_int 修改总线数据
        p2 = (int *)intputdata + offset;
        head = (0x1 <<(32 - endbit - 1)) - 1;
        head = head << (endbit + 1);

        tail1 = (0x1 << (beginbit)) - 1;
        head = head | tail1;
        *p2 = (*p2) & head;
        *p2 = (*p2)|(ret_int << beginbit);
        break;
   //unsigned int
    case 1:
        ret_unint = inputstr.toUInt();

        if((ret_unint > (0x1<<bits)) || (ret_unint < 0))
        {
            qDebug()<<"UINT 数值越界";
            ret_unint = 0;
        }
        p = (unsigned int *)intputdata + offset;
        head = (0x1 <<(32 - endbit - 1)) - 1;
        head = head << (endbit + 1);

        tail1 = (0x1 << (beginbit)) - 1;
        head = head | tail1;
        *p = (*p) & head;
        *p = (*p)|(ret_unint << beginbit);
        break;

   //float
    case 3:
        if(bits != 32)
        {
            qDebug()<<"FLOAT 位数错误";
        }
        ret_float = inputstr.toFloat();
        pf = (float *)intputdata + offset;
        *pf = ret_float;
        ret = true;
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


