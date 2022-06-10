#include "processthread.h"

ProcessThread::ProcessThread()
{
    bRun = true;
    bNewdata = false;
    memset(&data,0x0,sizeof(data));
}

void ProcessThread::run()
{
    while(bRun)
    {
        if(data.e1 != 0)
        {
            //qDebug()<<"输入"<<data.e1;
        }

        QTime begin;
        begin = QTime::currentTime();
        //qDebug()<<begin;
        // call dll,并传递参数,返回调用参数
        QTime end = QTime::currentTime();
        int m_iTestTime = begin.msecsTo(end);
        if(m_iTestTime < 12.5)
        {
            Sleep(12.5 - m_iTestTime);//毫秒
        }
        emit running();
    }
}

bool ProcessThread::getBNewdata() const
{
    return bNewdata;
}

void ProcessThread::setBNewdata(bool value)
{
    bNewdata = value;
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
        memcpy(&data,p,sizeof(data));
    }
}
