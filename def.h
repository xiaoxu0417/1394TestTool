#ifndef DEF_H
#define DEF_H
//��ʵ���������ݽṹ�嶨��,��Ҫ��xml����һ��,�������������ṹ��
#include <QVariant>
#include <QMetaType>

struct testdata
{
    unsigned int a:1;
    unsigned int b:1;
    unsigned int c:30;

    int e1 :16;
    int e2 :16;

    float f;
};

struct testdata_out
{
    unsigned int a:1;
    unsigned int b:16;
    unsigned int c:15;

    int d;
};

Q_DECLARE_METATYPE(testdata_out)
#endif // DEF_H
