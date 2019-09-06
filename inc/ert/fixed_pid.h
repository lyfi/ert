#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    Fixed32 SetPoint;
    Fixed32 Kp;
    Fixed32 Ki;
    Fixed32 Kd;
    Fixed32 Derivator;
    Fixed32 Integrator;
    Fixed32 IntegratorMax;
    Fixed32 IntegratorMin;
    Fixed32 PrevError;
} FixedPid;


RESULT FixedPid_Init(FixedPid* self, Fixed32 setPoint, Fixed32 kp, Fixed32 ki, Fixed32 kd, Fixed32 derivator, 
                     Fixed32 integratorMax, Fixed32 integratorMin);
Fixed32 FixedPid_Calculate(FixedPid* self, Fixed32 pv); 


#ifdef __cplusplus
}
#endif