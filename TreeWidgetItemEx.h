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

private:
    int bitbegin;
    int bitend;
    int offset;
    int datatype;
};

#endif // MYTREEITEM_H
