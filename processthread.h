#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H
#include <QThread>
#include <QTime>
#include <QDebug>
#include <windows.h>
#include "cdatacontrol.h"
extern "C"
{
    //#include "dll.h"
    #include "VMC_API.h"
}
class ProcessThread : public QThread
{
    Q_OBJECT
public:
    ProcessThread();
    void run();//线程周期函数

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

    void Process();//周期执行dll函数

signals:
    void running(QVariant var);//接口程序运行信号,此信号通知cdatacontrol更新输出数据
    void updateCount(QString,bool);//通知主窗口更新拍数

private slots:
    void getNewInpoputData();//获取新的输入数据

private:
    bool bRun;
    //bool bNewdata;
    Input_vmc indata;
    Output_vmc outdata;
    Output_vmc lastoutdata;
    unsigned int TimerCount;//连续执行时的计时
    bool bConstant;//T连续执行;F按照指定的拍数执行
    bool ConstantCountStart;//
    unsigned int ConstantTarget;//需要指定执行的拍数
    unsigned int ConstantCount;//非连续执行时的拍数
};

#endif // PROCESSTHREAD_H
