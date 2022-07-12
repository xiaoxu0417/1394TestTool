#ifndef CDATACONTROL_H
#define CDATACONTROL_H

#include <QDebug>
#include <QString>
//#include "def.h"
#include "vmc_def.h"
#include <QMessageBox>
#include <QMutex>

#define VAILD_STYLE     ("QLabel{background:#00CC00;}")
#define INVAILD_STYLE   ("QLabel{background:#FF6666;}")
#define NULL_STYLE      ("QLabel{background:#FFFFFF;}")
class CDataControl:public QObject
{
    Q_OBJECT
public:
    CDataControl(int b,int e,int o,int datatype,bool m_io, int length, QMap <int,QString> meaning);
    CDataControl();
    ~CDataControl();
    bool isVaild();//����UI����ַ���,�ж��Ƿ���Ч,��Ч�򱣴浽input������,��֪ͨprocess�̸߳�������

    static Input_vmc* inputdata;

    static void* getIntputdata();
    static void setIntputdata(int value);

    bool getIo() const;
    void setIo(bool value);

    static int getDatalength();
    static void setDatalength(int value);

    void updateStyle(QString mean);

    //����ini load ����,����UIҳ���ϵ���ʾ
    void updateInputUIFormIni();

    int getBeginbit() const;
    void setBeginbit(int value);

    int getEndbit() const;
    void setEndbit(int value);

    unsigned int getOffset() const;
    void setOffset(unsigned int value);

signals:
    void updateDllInPutdata();//֪ͨprocess�̸߳�����������
    void testsetOutPutdata(QString);
    void updateMeaning(QString);
    void updateMeaningstyle(QString);
    void updateLineEdit(QString);

private slots:
    void slot_onInputDataFinished();//UI�����������,У�鲢��ʾ����
    void slot_onInputDataChange(QString txt);//UI���� ��������,��������
    void slot_updateOutputData(QVariant var);//process�̸߳���������
    void slot_clearalldata();//�������
    void slot_onLoadInputData(QVariant var);//���´�ini load������

private:
    int beginbit;
    int endbit;
    unsigned int offset;
    int datatype;
    QString inputstr;
    bool m_io;
    static int inputdatalength;
    QMap <int,QString> m_meaning;
    QMutex mutex;
};

#endif // CDATACONTROL_H
