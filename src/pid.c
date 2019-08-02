

#include <ert/pid.h>


void 
Pid_Init(Pid* self, float setPoint, float kp, float ki, float kd, float derivator, 
         float integrator, float integratorMax, float integratorMin) {
    self->SetPoint = setPoint;
    self->Kp = kp;
    self->Kd = kd;
    self->Ki = ki;
    self->Derivator = derivator;
    self->Integrator = integrator;
    self->IntegratorMax = integratorMax;
    self->IntegratorMin = integratorMin;
    self->Error = 0.0;
}

float 
Pid_Calculate(Pid* self, float pv) {
    self->Error = self->SetPoint - pv;
    float P_value = self->Kp * self->Error;
    float D_value = self->Kd * ( self->Error - self->Derivator);
    self->Derivator = self->Error;

    self->Integrator = self->Integrator + self->Error;

    if(self->Integrator > self->IntegratorMax){
        self->Integrator = self->IntegratorMax;
    }
    else if(self->Integrator < self->IntegratorMin) {
        self->Integrator = self->IntegratorMin;
    }

    float I_value = self->Integrator * self->Ki;

    return P_value + I_value + D_value;
}
