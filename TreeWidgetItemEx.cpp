#include "TreeWidgetItemEx.h"


TreeWidgetItemEx::TreeWidgetItemEx()
{

}

TreeWidgetItemEx::TreeWidgetItemEx(int a, int b, int c,enum m_datatype type)
{
    m_bitbegin = a;
    m_bitend = b;
    m_offset = c;
    m_datatype = type;
}

TreeWidgetItemEx::~TreeWidgetItemEx()
{

}

int TreeWidgetItemEx::getBitbegin() const
{
    return m_bitbegin;
}

void TreeWidgetItemEx::setBitbegin(int value)
{
    m_bitbegin = value;
}

int TreeWidgetItemEx::getBitend() const
{
    return m_bitend;
}

void TreeWidgetItemEx::setBitend(int value)
{
    m_bitend = value;
}

int TreeWidgetItemEx::getOffset() const
{
    return m_offset;
}

void TreeWidgetItemEx::setOffset(int value)
{
    m_offset = value;
}

int TreeWidgetItemEx::getDatatype() const
{
    return m_datatype;
}

void TreeWidgetItemEx::setDatatype(const QString &value)
{
    if(value == "UINT")
        m_datatype = 1;
    else if(value == "SINT")
        m_datatype = 2;
    else if(value == "FLOAT")
        m_datatype = 3;
    else
        m_datatype = 1;
}

bool TreeWidgetItemEx::getB_io() const
{
    return m_b_io;
}

void TreeWidgetItemEx::setB_io(bool value)
{
    m_b_io = value;
}

unsigned int TreeWidgetItemEx::getNo() const
{
    return No;
}

void TreeWidgetItemEx::setNo(unsigned int value)
{
    No = value;
}

void TreeWidgetItemEx::setMeaning(QString value, QString meaning)
{
    m_meaning.insert(value.toInt(),meaning);
}

QString TreeWidgetItemEx::getInitMeaning()
{
    QString ret;
    if(m_meaning.size() > 0)
    {
        QMap<int, QString>::const_iterator i;
        for( i=m_meaning.constBegin(); i!=m_meaning.constEnd(); ++i)
        {
            if(m_datatype == 1 || m_datatype == 2)
            {
                ret += QString::number(i.key()) + ":" + i.value() + ";";
            }
            else
            {
                ret += i.value() + ";";
            }
        }
    }
    else
    {

    }

    return ret;
}

QMap<int, QString> TreeWidgetItemEx::getMeaningMap()
{
    return m_meaning;
}

void TreeWidgetItemEx::slot_onupdateMeaning()
{

}


