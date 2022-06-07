#ifndef CDATACONTROL_H
#define CDATACONTROL_H

#include <QDebug>
#include <QString>
#include "def.h"

class CDataControl:public QObject
{
    Q_OBJECT
public:
    CDataControl(int b,int e,int o,int datatype,bool io, int length);
    bool isVaild();

    static void* intputdata;

    static void* getIntputdata();
    static void setIntputdata(int value);

    bool getIo() const;
    void setIo(bool value);

    static int getDatalength();
    static void setDatalength(int value);
signals:
    void updatedata();

private slots:
    void slot_onInputDataFinished();
    void slot_onInputDataChange(QString txt);
    void slot_updateOutputData();
    void slot_clearalldata();
    void slot_updatedata();

private:
    void setbitsdata();
    int beginbit;
    int endbit;
    unsigned int offset;
    int datatype;
    QString inputstr;
    bool io;
    static int inputdatalength;
};

#endif // CDATACONTROL_H
