#ifndef CDATACONTROL_H
#define CDATACONTROL_H

#include <QDebug>
#include <QString>

class CDataControl:public QObject
{
    Q_OBJECT
public:
    CDataControl(int b,int e,int o,int datatype);
    bool isVaild();

    static int intputdata[3];

    static int* getIntputdata();
    static void setIntputdata(int value);

private slots:
    void onInputDataFinished();
    void onInputDataChange(QString txt);


private:
    int beginbit;
    int endbit;
    unsigned int offset;
    int datatype;
    QString inputstr;

};

#endif // CDATACONTROL_H
