#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H
#include <QThread>
#include <QTime>
#include <QDebug>
#include <windows.h>
#include "cdatacontrol.h"

class ProcessThread : public QThread
{
    Q_OBJECT
public:
    ProcessThread();
    void run();

    unsigned int getTimeCount() const;
    void setTimeCount(unsigned int value);

    bool getBConstant() const;
    void setBConstant(bool value);

    unsigned int getConstantTarget() const;
    void setConstantTarget(unsigned int value);

    bool getBRun() const;
    void setBRun(bool value);

    bool getConstantCountStart() const;
    void setConstantCountStart(bool value);

signals:
    void running(QVariant var);//接口程序运行信号,此信号通知cdatacontrol更新输出数据
    void updateCount(int);//通知主窗口更新拍数

private slots:
    void getNewInpoputData();//获取新的输入数据

private:
    bool bRun;
    //bool bNewdata;
    struct testdata indata;
    struct testdata_out outdata;
    struct testdata_out lastoutdata;
    unsigned int TimerCount;
    bool bConstant;
    bool ConstantCountStart;
    unsigned int ConstantTarget;
    unsigned int ConstantCount;
};

#endif // PROCESSTHREAD_H
