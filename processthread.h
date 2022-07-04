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
    void run();//�߳����ں���

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

    void Process();//����ִ��dll����

signals:
    void running(QVariant var);//�ӿڳ��������ź�,���ź�֪ͨcdatacontrol�����������
    void updateCount(QString,bool);//֪ͨ�����ڸ�������

private slots:
    void getNewInpoputData();//��ȡ�µ���������

private:
    bool bRun;
    //bool bNewdata;
    Input_vmc indata;
    Output_vmc outdata;
    Output_vmc lastoutdata;
    unsigned int TimerCount;//����ִ��ʱ�ļ�ʱ
    bool bConstant;//T����ִ��;F����ָ��������ִ��
    bool ConstantCountStart;//
    unsigned int ConstantTarget;//��Ҫָ��ִ�е�����
    unsigned int ConstantCount;//������ִ��ʱ������
};

#endif // PROCESSTHREAD_H
