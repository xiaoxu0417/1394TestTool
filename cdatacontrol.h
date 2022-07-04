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
    ~CDataControl();
    bool isVaild();

    static void* intputdata;

    static void* getIntputdata();
    static void setIntputdata(int value);

    bool getIo() const;
    void setIo(bool value);

    static int getDatalength();
    static void setDatalength(int value);

    void updateStyle(QString mean);

signals:
    void updateDllInPutdata();
    void testsetOutPutdata(QString);
    void updateMeaning(QString);
    void updateMeaningstyle(QString);
    void updateLineEdit(QString);

private slots:
    void slot_onInputDataFinished();
    void slot_onInputDataChange(QString txt);
    void slot_updateOutputData(QVariant var);
    void slot_clearalldata();

private:
    void setbitsdata();
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
