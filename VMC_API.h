#ifndef VMC_API_h__
#define VMC_API_h__
#include "Break.h"

#define RIU_API __declspec(dllexport)

RIU_API void API_VMC_In(int* data, int Len);
RIU_API void API_VMC_Process();
RIU_API Output_vmc API_VMC_Out(int *len);

#endif // VMC_API_h__
