#include "processthread.h"

ProcessThread::ProcessThread()
{
    bRun = false;
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
    while(1)
    {
        if(!bRun)
        {
            continue;
        }
#ifdef DEBUG_DATA
        if(indata.e1 != 0)
        {
            //qDebug()<<"输入"<<data.e1;
        }
#endif
        if(bConstant)
        {
            qDebug()<<"连续"<<TimerCount;
            Process();
            emit updateCount(QString::number(TimerCount),false);
        }
        else if(ConstantCountStart == true)
        {
            //计算拍数
            if(ConstantCount >= ConstantTarget)
            {
                //结束
                bRun = false;
                qDebug()<<"结束"<<QTime::currentTime()<<ConstantCount<<ConstantTarget;
                emit updateCount(QString::number(ConstantCount),true);
                ConstantTarget = 0;
                ConstantCount = 0;
            }
            else
            {
                ConstantCount++;                
                emit updateCount(QString::number(ConstantCount),false);

                qDebug()<<"run"<<ConstantCount<<QTime::currentTime();

                Process();
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

    }
}

void ProcessThread::getNewInputDataFromUI()
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

//从配置文件获取输入数据
void ProcessThread::getNewInputDataFromIni(QVariant var)
{
    Input_vmc in = var.value<Input_vmc>();
    memcpy(&indata,&in,sizeof(indata));
}

bool ProcessThread::getConstantCountStart() const
{
    return ConstantCountStart;
}

void ProcessThread::setConstantCountStart(bool value)
{
    ConstantCountStart = value;
}

void ProcessThread::Process()
{

#ifdef DEBUG_DATA
    //indata入参
    outdata.a = indata.a;
    outdata.b = indata.e1*10;
    outdata.c = indata.e2*10;
#endif
    //运行
    TimerCount++;

#ifdef DEBUG_DATA
    sleep(1);//debug
    outdata.d = indata.f*10;
#else
    int len = 0;

    API_VMC_In((int*)&indata,sizeof (indata));
    API_VMC_Process();
    outdata = API_VMC_Out(&len);
    msleep(8);//qt thread sleep
    qDebug()<<indata.brk.riu3.left_wheel_speed;
#endif
    //outdata出参

    if(memcmp(&lastoutdata,&outdata,sizeof (outdata)))
    {
        memcpy(&lastoutdata,&outdata,sizeof (outdata));
        QVariant data;
        data.setValue(outdata);
        emit running(data);
    }
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
