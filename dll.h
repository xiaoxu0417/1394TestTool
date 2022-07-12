#include "def.h"
#include "Break.h"

#define API_DEC __declspec(dllexport)

API_DEC void initdata(int d);
API_DEC void process();
API_DEC int output();

API_DEC void API_VMC_In(int* data, int Len);
API_DEC void API_VMC_Process();
API_DEC void* API_VMC_Out(int *len);
