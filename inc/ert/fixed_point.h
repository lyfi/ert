#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#define FIXED32_Q (16)
#define FIXED32_FMASK (((Fixed32)1 << FIXED32_Q) - 1)

typedef int32_t Fixed32;
typedef int64_t Fixed64;

enum  {
    Fixed32_ONE = 0x00010000
};

// Optional
static inline Fixed32 Fixed32_FromFloat(float f) {
    float temp = f * Fixed32_ONE;
    temp += (temp >= 0) ? 0.5f : -0.5f;
    return (Fixed32)temp;
}

// Optional
static inline Fixed32 Fixed32_ToFloat(float T) {
	return (float)((T)*((float)(1)/(float)(1 << FIXED32_Q)));
}

static inline Fixed32 Fixed32_FromInt(int32_t n) {
	return (Fixed32)(n * Fixed32_ONE);
}

static inline int32_t Fixed32_ToInt(Fixed32 a) {
    return a >= 0 ? (a + (Fixed32_ONE >> 1)) / Fixed32_ONE : (a - (Fixed32_ONE >> 1)) / Fixed32_ONE;
}


static inline int32_t Fixed32_Frac(Fixed32 a){
	return a & FIXED32_FMASK;
}

static inline Fixed32 Fixed32_Add(Fixed32 a, Fixed32 b) {
	return a + b;
}

static inline Fixed32 Fixed32_Minus(Fixed32 a, Fixed32 b) {
	return a - b;
}

static inline Fixed32 Fixed32_Mul(Fixed32 a, Fixed32 b) {
	return (Fixed32)(((Fixed64)a * (Fixed64)b) >> FIXED32_Q);	
}

static inline Fixed32 Fixed32_Div(Fixed32 a, Fixed32 b) {
	return (Fixed32)(((Fixed64)a << FIXED32_Q) / (Fixed64)b);
}


#ifdef __cplusplus
}
#endif