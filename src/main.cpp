#include <mbed.h>

#define PWM_PERIOD 0.02
#define PULSE_WIDTH_MAX 0.0021
#define PULSE_WIDTH_MIN 0.0009

float map_adc_pulse_width(float adc_value) {
  float pulse_width = PULSE_WIDTH_MIN + (PULSE_WIDTH_MAX - PULSE_WIDTH_MIN) * adc_value;
  pulse_width = pulse_width > PULSE_WIDTH_MAX ? PULSE_WIDTH_MAX : pulse_width;
  pulse_width = pulse_width < PULSE_WIDTH_MIN ? PULSE_WIDTH_MIN : pulse_width;
  return pulse_width;
}

int main() {

  // Potentiometer inputs
  AnalogIn   ain0(A0);
  AnalogIn   ain1(A1);
  AnalogIn   ain2(A2);
  AnalogIn   ain3(A3);
  AnalogIn   ain4(A4);
  AnalogIn   ain5(A5);

  // Servo motors outputs
  PwmOut pwm0(D0);
  PwmOut pwm1(D1);
  PwmOut pwm2(D2);
  PwmOut pwm3(D3);
  PwmOut pwm4(D4);
  PwmOut pwm5(D5);

  // Set pwm period to 20 ms
  pwm0.period(PWM_PERIOD);
  pwm1.period(PWM_PERIOD);
  pwm2.period(PWM_PERIOD);
  pwm3.period(PWM_PERIOD);
  pwm4.period(PWM_PERIOD);
  pwm5.period(PWM_PERIOD);

  while(1) {
    // Read ADC and adjust PWM pulse width
    pwm0.pulsewidth(map_adc_pulse_width(ain0.read()));
    pwm1.pulsewidth(map_adc_pulse_width(ain1.read()));
    pwm2.pulsewidth(map_adc_pulse_width(ain2.read()));
    pwm3.pulsewidth(map_adc_pulse_width(ain3.read()));
    pwm4.pulsewidth(map_adc_pulse_width(ain4.read()));
    pwm5.pulsewidth(map_adc_pulse_width(ain5.read()));
  }
}