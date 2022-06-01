#include "TreeWidgetItemEx.h"


TreeWidgetItemEx::TreeWidgetItemEx()
{

}

TreeWidgetItemEx::TreeWidgetItemEx(int a, int b, int c)
{
    bitbegin = a;
    bitend = b;
    offset = c;
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
