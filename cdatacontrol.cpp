#include "cdatacontrol.h"

int CDataControl::intputdata[] = {0};

CDataControl::CDataControl(int b, int e, int o,int datatype)
{
    beginbit = b;
    endbit = e;
    offset = o;
    this->datatype = datatype;
}

void CDataControl::onInputDataFinished()
{
    qDebug()<<beginbit <<" "<<endbit <<" "<< offset <<" data finish";
    bool ret = isVaild();
}

void CDataControl::onInputDataChange(QString txt)
{
    qDebug()<<beginbit <<" "<<endbit <<" "<< offset <<" data change"<<txt;
    inputstr = txt;
}

bool CDataControl::isVaild()
{
    bool ret = false;
    //�Ȳ����Ǵ�С��
    int bits = endbit - beginbit;
    if(bits < 0)
    {
        qDebug()<<"λ�����!"<<endbit<<" "<<beginbit;
        return false;
    }

    int ret_int = 0;
    unsigned int temp = 0;
    unsigned int filter = 0;

    unsigned int ret_unint = 0;
    unsigned int *p;
    int *p2;
    unsigned int head = 0;
    unsigned int tail1 = 0;
    switch(datatype)
    {
    //int
    case 2:
        ret_int = inputstr.toInt();
        if(ret_int > 0x1<<bits)
        {
            qDebug()<<"��ֵԽ��";
            ret_int = 0;
        }
        //����0
        if(ret_int >= 0)
        {
            //����begin end offset ��ret_int �޸���������
            p2 = (int *)intputdata + offset;
            head = (0x1 <<(32 - endbit - 1)) - 1;
            head = head << (endbit + 1);

            tail1 = (0x1 << (beginbit)) - 1;
            head = head | tail1;
            *p2 = (*p2) & head;

            *p2 = (*p2)|(ret_int << beginbit);
        }
        else
        {
            filter = (0x1 <<(endbit - beginbit)) - 1;
            temp = ret_int &(filter) - 1;
            temp = ~(temp);//����λ
        }
        break;
   //unsigned int
    case 1:
        ret_unint = inputstr.toUInt();

        if((ret_unint > (0x1<<bits)) || (ret_unint < 0))
        {
            qDebug()<<"��ֵԽ��";
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
        ret = true;
        break;
    }

    return ret;
}

int* CDataControl::getIntputdata()
{
    return intputdata;
}

void CDataControl::setIntputdata(int value)
{
    intputdata[0] = value;
}


