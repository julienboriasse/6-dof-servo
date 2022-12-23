#include <mbed.h>

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
  PwmOut pwm0(D5);
  PwmOut pwm1(D9);
  PwmOut pwm2(D10);
  PwmOut pwm3(D11);
  //PwmOut pwm4(D4);
  //PwmOut pwm5(D5);

  // Set pwm period to 20 ms
  printf("Configure motors PWM periods\r\n");
  pwm0.period(PWM_PERIOD);
  pwm1.period(PWM_PERIOD);
  pwm2.period(PWM_PERIOD);
  pwm3.period(PWM_PERIOD);
  //pwm4.period(PWM_PERIOD);
  //pwm5.period(PWM_PERIOD);

  while (1)
  {
    
    // Read ADC and adjust PWM pulse width
    pwm0.pulsewidth(map_adc_pulse_width(ain0.read()));
    printf("ADC: %.8f\tPWM: %.8f\n", ain0.read(), map_adc_pulse_width(ain0.read()));
    ThisThread::sleep_for(5ms);
    pwm1.pulsewidth(map_adc_pulse_width(ain1.read()));
    ThisThread::sleep_for(5ms);
    pwm2.pulsewidth(map_adc_pulse_width(ain2.read()));
    ThisThread::sleep_for(5ms);
    pwm3.pulsewidth(map_adc_pulse_width(ain3.read()));
    ThisThread::sleep_for(5ms);
    //pwm4.pulsewidth(map_adc_pulse_width(ain4.read()));
    //pwm5.pulsewidth(map_adc_pulse_width(ain5.read()));
  }
}