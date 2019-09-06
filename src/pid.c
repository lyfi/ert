/* PID 计算 */
/* Port from https://gist.github.com/bradley219/5373998
*/

#ifdef FLOAT_ENABLED

#include <ert/ert.h>
#include <ert/pid.h>


RESULT 
Pid_Init(Pid* self, float setPoint, float kp, float ki, float kd, float derivator, 
         float integratorMax, float integratorMin) {

    if(derivator == 0.0) {
        return RESULT_ERROR;
    }

    self->SetPoint = setPoint;
    self->Kp = kp;
    self->Kd = kd;
    self->Ki = ki;
    self->Derivator = derivator;
    self->IntegratorMax = integratorMax;
    self->IntegratorMin = integratorMin;

    self->Integrator = 0;
    self->PrevError = 0.0;

    return RESULT_OK;
}

float 
Pid_Calculate(Pid* self, float pv) {
    // Calculate error
    float error = self->SetPoint - pv;

    // Proportional term
    float Pout = self->Kp * error;

    // Integral term
    self->Integrator += error * self->Derivator;
    double Iout = self->Ki * self->Integrator;

    // Derivative term
    double derivative = (error - self->PrevError) / self->Derivator;
    double Dout = self->Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

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

#endif //FLOAT_ENABLED