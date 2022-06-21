#include "processthread.h"

ProcessThread::ProcessThread()
{
    bRun = true;
    memset(&indata,0x0,sizeof(indata));
    memset(&outdata,0x0,sizeof (outdata));
    memset(&lastoutdata,0x0,sizeof(lastoutdata));
    TimerCount = 0;
    bConstant = true;
    ConstantCount = 0;
    ConstantTarget = 0;
    ConstantCountStart = false;
}

void ProcessThread::run()
{
    //测试下,线程启动后,设置run false,之后为什么不run 了?
    while(bRun)
    {
        if(indata.e1 != 0)
        {
            //qDebug()<<"输入"<<data.e1;
        }
        if(bConstant)
        {

        }
        else if(ConstantCountStart == true)
        {
            //计算拍数
            if(ConstantCount > ConstantTarget)
            {
                //结束
                bRun = false;
            }
            else
            {
                ConstantCount++;
                emit updateCount(ConstantCount);
            }
        }

//        QTime begin;
//        begin = QTime::currentTime();
//        //qDebug()<<begin;
//        // call dll,并传递参数,返回调用参数
//        QTime end = QTime::currentTime();
//        int m_iTestTime = begin.msecsTo(end);
//        if(m_iTestTime < 12.5)
//        {
//            Sleep(12.5 - m_iTestTime);//毫秒
//        }
        //indata入参
        outdata.a = indata.a;
        outdata.b = indata.e1*10;
        outdata.c = indata.e2*10;

        //运行
        TimerCount++;
        Sleep(8);
        //qDebug()<<"thread"<<count;


        outdata.d = indata.f*10;
        //outdata出参

        if(memcmp(&lastoutdata,&outdata,sizeof (outdata)))
        {
            memcpy(&lastoutdata,&outdata,sizeof (outdata));
            QVariant data;
            data.setValue(outdata);
            emit running(data);
        }
    }
}

void ProcessThread::getNewInpoputData()
{
    //调用接口前,获取输入数据,并拷贝到data中
    void *p = CDataControl::getIntputdata();
    if(!p)
    {
        qDebug()<<"process no data";
    }
    else
    {
        memcpy(&indata,p,sizeof(indata));
    }
}

bool ProcessThread::getConstantCountStart() const
{
    return ConstantCountStart;
}

void ProcessThread::setConstantCountStart(bool value)
{
    ConstantCountStart = value;
}

bool ProcessThread::getBRun() const
{
    return bRun;
}

void ProcessThread::setBRun(bool value)
{
    bRun = value;
}

unsigned int ProcessThread::getConstantTarget() const
{
    return ConstantTarget;
}

void ProcessThread::setConstantTarget(unsigned int value)
{
    ConstantTarget = value;
}

bool ProcessThread::getBConstant() const
{
    return bConstant;
}

void ProcessThread::setBConstant(bool value)
{
    bConstant = value;
}

unsigned int ProcessThread::getTimeCount() const
{
    return TimerCount;
}

void ProcessThread::setTimeCount(unsigned int value)
{
    TimerCount = value;
}
