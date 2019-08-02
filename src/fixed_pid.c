
#include <stdint.h>

#include <ert/fixed_point.h>
#include <ert/fixed_pid.h>

/* 
	pid.Dt = Fixed32_FromFloat(0.1);
	pid.Max = Fixed32_FromFloat(100);
	pid.Min = Fixed32_FromFloat(-100);
	pid.Kp = Fixed32_FromFloat(0.1);
	pid.Kd = Fixed32_FromFloat(0.01);
	pid.Ki = Fixed32_FromFloat(0.5);
    */

void FixedPid_Init(FixedPid* self, Fixed32 dt, Fixed32 pidMin, Fixed32 pidMax, Fixed32 kp, Fixed32 kd, Fixed32 ki) {
    self->Dt = (Fixed32)((float)1.0);//Fixed32_FromFloat(dt);
    //self->Min = Fixed32_FromFloat(pidMin);
    //self->Max = Fixed32_FromFloat(pidMax);
    self->PrevError = 0;
    self->Integral = 0;
}

Fixed32 FixedPid_Calculate(FixedPid* self, Fixed32 setpoint, Fixed32 pv) {
    // Calculate error
    Fixed32 error = setpoint - pv; //setpoint - pv;

    // Proportional term
    Fixed32 Pout = Fixed32_Mul(self->Kp, error); // self.Kp * error;

    // Integral term
    self->Integral += Fixed32_Mul(error, self->Dt);  // self.Integral += error * self.Dt;
    Fixed32 Iout = Fixed32_Mul(self->Ki, self->Integral);

    // Derivative term
    Fixed32 derivative = Fixed32_Div(error - self->PrevError, self->Dt);
    Fixed32 Dout = Fixed32_Mul(self->Kd, derivative);

    // Calculate total output
    Fixed32 output = Pout + Iout + Dout;
	
    // Restrict to max/min
    if(output > self->Max) {
        output = self->Max;
	}
    else if(output < self->Min){
        output = self->Min;
	}

    // Save error to previous error
    self->PrevError = error;
    return output;
}
