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
    void running(QVariant var);//�ӿڳ��������ź�,���ź�֪ͨcdatacontrol�����������

private slots:
    void getNewInpoputData();//��ȡ�µ���������

private:
    bool bRun;
    bool bNewdata;
    struct testdata indata;
    struct testdata_out outdata;
    struct testdata_out lastoutdata;
};

#endif // PROCESSTHREAD_H
