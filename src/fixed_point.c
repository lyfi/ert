#include <stdint.h>

#include <ert/fixed_point.h>

inline Fixed32 Fixed32_FromInt(int32_t n) {
	return (Fixed32)((Fixed32)n << FIXED32_Q);
}

inline int32_t Fixed32_Frac(Fixed32 a){
	return a & FIXED32_FMASK;
}

#ifdef FLOAT_ENABLED
// Optional
inline Fixed32 Fixed32_FromFloat(float f) {
	return (Fixed32)((f) * (((Fixed64)1 << FIXED32_Q) + ((f) >= 0 ? 0.5 : -0.5)));
}

// Optional
inline Fixed32 Fixed32_ToFloat(float T) {
	return (float)((T)*((float)(1)/(float)(1 << FIXED32_Q)));
}
#endif

inline Fixed32 Fixed32_Mul(Fixed32 a, Fixed32 b) {
	return (Fixed32)(((Fixed64)a * (Fixed64)b) >> FIXED32_Q);	
}

inline Fixed32 Fixed32_Div(Fixed32 a, Fixed32 b) {
	return (Fixed32)(((Fixed64)a << FIXED32_Q) / (Fixed64)b);
}
