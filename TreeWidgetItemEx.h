#ifndef MYTREEITEM_H
#define MYTREEITEM_H
#include <QTreeWidgetItem>
#include <QObject>

class TreeWidgetItemEx :public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    TreeWidgetItemEx();
    TreeWidgetItemEx(int a,int b, int c);
    ~TreeWidgetItemEx();
    int getBitbegin() const;
    void setBitbegin(int value);

    int getBitend() const;
    void setBitend(int value);

    int getOffset() const;
    void setOffset(int value);

private:
    int bitbegin;
    int bitend;
    int offset;
};

#endif // MYTREEITEM_H
