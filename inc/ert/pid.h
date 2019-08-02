#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    float SetPoint;
    float Kp;
    float Ki;
    float Kd;
    float Derivator;
    float Integrator;
    float IntegratorMax;
    float IntegratorMin;
    float Error;
} Pid;

void Pid_Init(Pid* self, float setPoint, float kp, float ki, float kd, float derivator, float integrator, float integratorMax, float integratorMin);
float Pid_Calculate(Pid* self, float pv); 

#ifdef __cplusplus
}
#endif