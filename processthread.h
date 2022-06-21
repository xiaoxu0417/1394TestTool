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
    void running(QVariant var);//�ӿڳ��������ź�,���ź�֪ͨcdatacontrol�����������
    void updateCount(int);//֪ͨ�����ڸ�������

private slots:
    void getNewInpoputData();//��ȡ�µ���������

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
