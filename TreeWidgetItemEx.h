#ifndef MYTREEITEM_H
#define MYTREEITEM_H
#include <QTreeWidgetItem>
#include <QObject>
#include "cdatacontrol.h"

class TreeWidgetItemEx : public QTreeWidgetItem,public QObject
{
    enum datatype
    {
        UINT = 1,
        SINT ,
        FLOAT
    };
    //Q_OBJECT
public:
    TreeWidgetItemEx();
    TreeWidgetItemEx(int a,int b, int c, enum datatype type);
    ~TreeWidgetItemEx();

    int getBitbegin() const;
    void setBitbegin(int value);

    int getBitend() const;
    void setBitend(int value);

    int getOffset() const;
    void setOffset(int value);

    int getDatatype() const;
    void setDatatype(const QString &value);

    bool getB_io() const;
    void setB_io(bool value);

    unsigned int getNo() const;
    void setNo(unsigned int value);

private:
    int bitbegin;
    int bitend;
    int offset;
    int datatype;
    bool b_io;

    //标记当前信号是哪个子系统,第几个信号
    //unsigned int Level;
    unsigned int No;
};

#endif // MYTREEITEM_H
