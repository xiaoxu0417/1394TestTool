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

    bool getBNewdata() const;
    void setBNewdata(bool value);

signals:
    void running();//接口程序运行信号,此信号通知cdatacontrol更新输出数据

private slots:
    void getNewInpoputData();//获取新的输入数据

private:
    bool bRun;
    bool bNewdata;
    struct testdata data;
};

#endif // PROCESSTHREAD_H
