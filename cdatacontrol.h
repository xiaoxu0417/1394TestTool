#ifndef CDATACONTROL_H
#define CDATACONTROL_H

#include <QDebug>
#include <QString>
#include "def.h"
#include <QMessageBox>

class CDataControl:public QObject
{
    Q_OBJECT
public:
    CDataControl(int b,int e,int o,int datatype,bool m_io, int length, QMap <int,QString> meaning);
    bool isVaild();

    static void* intputdata;

    static void* getIntputdata();
    static void setIntputdata(int value);

    bool getIo() const;
    void setIo(bool value);

    static int getDatalength();
    static void setDatalength(int value);

signals:
    //void updatedata();
    void testsetOutPutdata(QString);
    void updateMeaning(QString);
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
};

#endif // CDATACONTROL_H
