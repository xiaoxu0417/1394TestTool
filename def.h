#ifndef DEF_H
#define DEF_H
//数据结构体定义,需要与xml保持一致
struct testdata
{
    unsigned int a:1;
    unsigned int b:1;
    unsigned int c:30;

    int e1 :16;
    int e2 :16;

    float f;
};
#endif // DEF_H
