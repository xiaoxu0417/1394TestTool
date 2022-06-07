#include "TreeWidgetItemEx.h"


TreeWidgetItemEx::TreeWidgetItemEx()
{

}

TreeWidgetItemEx::TreeWidgetItemEx(int a, int b, int c,enum datatype type)
{
    bitbegin = a;
    bitend = b;
    offset = c;
    datatype = type;
}

TreeWidgetItemEx::~TreeWidgetItemEx()
{

}

int TreeWidgetItemEx::getBitbegin() const
{
    return bitbegin;
}

void TreeWidgetItemEx::setBitbegin(int value)
{
    bitbegin = value;
}

int TreeWidgetItemEx::getBitend() const
{
    return bitend;
}

void TreeWidgetItemEx::setBitend(int value)
{
    bitend = value;
}

int TreeWidgetItemEx::getOffset() const
{
    return offset;
}

void TreeWidgetItemEx::setOffset(int value)
{
    offset = value;
}

int TreeWidgetItemEx::getDatatype() const
{
    return datatype;
}

void TreeWidgetItemEx::setDatatype(const QString &value)
{
    if(value == "UINT")
        datatype = 1;
    else if(value == "SINT")
        datatype = 2;
    else if(value == "FLOAT")
        datatype = 3;
    else
        datatype = 1;
}

bool TreeWidgetItemEx::getB_io() const
{
    return b_io;
}

void TreeWidgetItemEx::setB_io(bool value)
{
    b_io = value;
}
