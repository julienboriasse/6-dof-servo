#include <mbed.h>

#include "servo.h"

#define PWM_PERIOD 0.02
#define PULSE_WIDTH_MAX 0.0028
#define PULSE_WIDTH_MIN 0.0003
#define ANGLE_MIN -120
#define ANGLE_MAX 90


int target_positions[5][4] = {
  {0, 45, 0, 20},
  {10, 0, 15, 30},
  {20, 45, 45, -10},
  {2, 15, 45, -10},
  {2, 25, 15, 0},
};


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

float map_adc_angle(float adc_value)
{
  float angle =  ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * adc_value;
  angle = angle > ANGLE_MAX ? ANGLE_MAX : angle;
  angle = angle < ANGLE_MIN ? ANGLE_MIN : angle;
  //printf("%.5f %.5f\n", adc_value, angle);
  return angle;
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
  Servo servo0(-120, 90, PWM_PERIOD, 0.0003, 0.0028, 0.00148, D11);
  Servo servo1(-120, 90, PWM_PERIOD, 0.0003, 0.0028, 0.00161, D10);
  Servo servo2(-120, 90, PWM_PERIOD, 0.0003, 0.0028, 0.00172, D9);
  Servo servo3(-120, 90, PWM_PERIOD, 0.0003, 0.0028, 0.00168, D5);

  while (1)
  {
    for (int i = 0; i < 5; i++)
    {
      servo0.move(target_positions[i][0]);
      servo1.move(target_positions[i][1]);
      servo2.move(target_positions[i][2]);
      servo3.move(target_positions[i][3]);
      ThisThread::sleep_for(2s);
    }
    
    /*
    // Read ADC and adjust PWM pulse width
    servo0.move(map_adc_angle(ain0.read()));
    servo1.move(map_adc_angle(ain1.read()));
    servo2.move(map_adc_angle(ain2.read()));
    servo3.move(map_adc_angle(ain3.read()));
    */
    //printf("\n\n\n");

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