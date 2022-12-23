#include <mbed.h>

#include "servo.h"

#define PWM_PERIOD 0.02
#define PULSE_WIDTH_MAX 0.0028
#define PULSE_WIDTH_MIN 0.0003

// Specify different pins to test printing on UART other than the console UART.
#define TARGET_TX_PIN USBTX
#define TARGET_RX_PIN USBRX

// Create a BufferedSerial object to be used by the system I/O retarget code.
static BufferedSerial serial_port(TARGET_TX_PIN, TARGET_RX_PIN, 115200);

FileHandle *mbed::mbed_override_console(int fd)
{
  return &serial_port;
}

float map_adc_pulse_width(float adc_value)
{
  float pulse_width = PULSE_WIDTH_MIN + (PULSE_WIDTH_MAX - PULSE_WIDTH_MIN) * adc_value;
  pulse_width = pulse_width > PULSE_WIDTH_MAX ? PULSE_WIDTH_MAX : pulse_width;
  pulse_width = pulse_width < PULSE_WIDTH_MIN ? PULSE_WIDTH_MIN : pulse_width;
  return pulse_width;
}

int main()
{
  printf(
      "Mbed OS version %d.%d.%d\n",
      MBED_MAJOR_VERSION,
      MBED_MINOR_VERSION,
      MBED_PATCH_VERSION);

  printf("Program start\r\n");

  // Potentiometer inputs
  printf("Configure ADC input pins\r\n");
  AnalogIn ain0(A0);
  AnalogIn ain1(A1);
  AnalogIn ain2(A2);
  AnalogIn ain3(A3);
  AnalogIn ain4(A4);
  AnalogIn ain5(A5);

  // Servo motors outputs
  printf("Configure motors output pins\r\n");

  Servo servo0(-90, -90, PWM_PERIOD, 0.0006, 0.0022, 0.0015, D11);
  Servo servo1(-90, -90, PWM_PERIOD, 0.0003, 0.0028, 0.0015, D10);
  Servo servo2(-90, -90, PWM_PERIOD, 0.0003, 0.0028, 0.0015, D9);
  Servo servo3(-90, -90, PWM_PERIOD, 0.0003, 0.0028, 0.0015, D5);

  while (1)
  {
    
    // Read ADC and adjust PWM pulse width
    servo0.move(0);
    servo1.move(0);
    servo2.move(0);
    servo3.move(0);

    /*
    pwm0.pulsewidth(map_adc_pulse_width(ain0.read()));
    printf("ADC: %.8f\tPWM: %.8f\n", ain0.read(), map_adc_pulse_width(ain0.read()));
    ThisThread::sleep_for(5ms);
    pwm1.pulsewidth(map_adc_pulse_width(ain1.read()));
    ThisThread::sleep_for(5ms);
    pwm2.pulsewidth(map_adc_pulse_width(ain2.read()));
    ThisThread::sleep_for(5ms);
    pwm3.pulsewidth(map_adc_pulse_width(ain3.read()));
    ThisThread::sleep_for(5ms);
    */
  }
}