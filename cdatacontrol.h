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
    bool isVaild();//根据UI输出字符串,判断是否有效,有效则保存到input数据中,并通知process线程更新数据

    static Input_vmc* inputdata;

    static void* getIntputdata();
    static void setIntputdata(int value);

    bool getIo() const;
    void setIo(bool value);

    static int getDatalength();
    static void setDatalength(int value);

    void updateStyle(QString mean);

    //根据ini load 数据,更新UI页面上的显示
    void updateInputUIFormIni();

    int getBeginbit() const;
    void setBeginbit(int value);

    int getEndbit() const;
    void setEndbit(int value);

    unsigned int getOffset() const;
    void setOffset(unsigned int value);

signals:
    void updateDllInPutdata();//通知process线程更新输入数据
    void testsetOutPutdata(QString);
    void updateMeaning(QString);
    void updateMeaningstyle(QString);
    void updateLineEdit(QString);

private slots:
    void slot_onInputDataFinished();//UI完成输入数据,校验并显示数据
    void slot_onInputDataChange(QString txt);//UI正在 输入数据,保存数据
    void slot_updateOutputData(QVariant var);//process线程更新输出结果
    void slot_clearalldata();//清空数据
    void slot_onLoadInputData(QVariant var);//更新从ini load的数据

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
