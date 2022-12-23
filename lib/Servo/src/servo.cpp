#include "Servo.h"

Servo::Servo(float ma, float Ma, float pd, float mpw, float Mpw, float cpw, PinName p) : pin(p)
{
    minAngle = ma;
    maxAngle = Ma;
    period = pd;
    minPulseWidth = mpw;
    maxPulseWidth = Mpw;
    centerPulseWidth = cpw;

    pin.period(pd);
}   

float Servo::pulse_width(float angle)
{
    // limit angle range
    angle = angle > maxAngle ? maxAngle : angle;
    angle = angle < minAngle ? minAngle : angle;

    // compute pulse width
    float pulseWidth = centerPulseWidth;
    if (angle > 0) {
        pulseWidth += (angle / maxAngle) * (maxPulseWidth - centerPulseWidth);
    }
    else if (angle < 0) {
        pulseWidth += (angle / minAngle) * (minPulseWidth - centerPulseWidth);
    }

    // limit pulse width range
    pulseWidth = pulseWidth > maxPulseWidth ? maxPulseWidth : pulseWidth;
    pulseWidth = pulseWidth < minPulseWidth ? minPulseWidth : pulseWidth;
    
    printf("%.5f %.5f\n", angle, pulseWidth);

    return pulseWidth;
}

void Servo::move(float angle)
{
    pin.pulsewidth(this->pulse_width(angle));
}