
#include <stdint.h>

#include <ert/ert.h>
#include <ert/fixed_point.h>
#include <ert/fixed_pid.h>


RESULT
FixedPid_Init(FixedPid* self, Fixed32 setPoint, Fixed32 kp, Fixed32 ki, Fixed32 kd, Fixed32 derivator, 
              Fixed32 integratorMax, Fixed32 integratorMin) {

    if(derivator == 0) {
        return RESULT_ERROR;
    }

    self->SetPoint = setPoint;
    self->Kp = kp;
    self->Ki = ki;
    self->Kd = kd;
    self->Derivator = derivator;
    self->IntegratorMax = integratorMax;
    self->IntegratorMin = integratorMin;
    self->Integrator = 0;
    self->PrevError = 0;

    return RESULT_OK;
}


Fixed32 
FixedPid_Calculate(FixedPid* self, Fixed32 pv) {
    // Calculate error
    Fixed32 error = self->SetPoint - pv;

    // Proportional term
    Fixed32 Pout = Fixed32_Mul(self->Kp, error);

    // Integral term
    self->Integrator += Fixed32_Mul(error, self->Derivator);
    Fixed32 Iout = Fixed32_Mul(self->Ki, self->Integrator);

    // Derivative term
    Fixed32 derivative = Fixed32_Div(error - self->PrevError, self->Derivator);
    Fixed32 Dout = Fixed32_Mul(self->Kd,  derivative);

    // Calculate total output
    Fixed32 output = Pout + Iout + Dout;

    // Restrict to max/min
    if(output > self->IntegratorMax) {
        output = self->IntegratorMax;
    }
    else if(output < self->IntegratorMin) {
        output = self->IntegratorMin;
    }

    // Save error to previous error
    self->PrevError = error;

    return output;

}