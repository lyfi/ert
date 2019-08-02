#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#define FIXED32_Q (16)
#define FIXED32_FMASK (((Fixed32)1 << FIXED32_Q) - 1)

typedef int32_t Fixed32;
typedef int64_t Fixed64;


Fixed32 Fixed32_FromInt(int32_t n);
int32_t Fixed32_Frac(Fixed32 a);

/* 
Fixed32 Fixed32_FromFloat(float f);
Fixed32 Fixed32_ToFloat(float T);
*/

Fixed32 Fixed32_Mul(Fixed32 a, Fixed32 b);
Fixed32 Fixed32_Div(Fixed32 a, Fixed32 b);

#ifdef __cplusplus
}
#endif