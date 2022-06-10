#ifndef DEF_H
#define DEF_H
//真实环境下数据结构体定义,需要与xml保持一致,包含输入和输出结构体
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
