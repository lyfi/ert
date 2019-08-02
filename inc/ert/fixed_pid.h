#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	Fixed32 Dt;
	Fixed32 Max;
	Fixed32 Min;
	Fixed32 Kp;
	Fixed32 Kd;
	Fixed32 Ki;
	Fixed32 PrevError;
	Fixed32 Integral;
} FixedPid;


void FixedPid_Init(FixedPid* self, Fixed32 dt, Fixed32 pidMin, Fixed32 pidMax, Fixed32 kp, Fixed32 kd, Fixed32 ki);
Fixed32 FixedPid_Calculate(FixedPid* self, Fixed32 setpoint, Fixed32 pv); 


#ifdef __cplusplus
}
#endif