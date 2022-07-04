#ifndef DEF_H
#define DEF_H
//真实环境下数据结构体定义,需要与xml保持一致,包含输入和输出结构体
#include <QVariant>
#include <QMetaType>

struct testdata
{
    //共10个int
    unsigned int a:1;
    unsigned int b:1;
    unsigned int c:30;

    int e1 :16;
    int e2 :16;

    float f;

    int back[7];
};

struct testdata_out
{
    //共5个int
    unsigned int a:1;
    unsigned int b:16;
    unsigned int c:15;

    int d;
    float e;

    int back[2];
};

Q_DECLARE_METATYPE(testdata_out)
#endif // DEF_H
