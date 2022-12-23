#include "mbed.h"

#ifndef SERVO_H_
#define SERVO_H_

/*
Library based on https://os.mbed.com/users/luverolla/code/servo-driver/
*/

class Servo
{
private:

    /**
     * smallest angle [deg]
     */
    float minAngle;

    /**
     * greatest angle [deg]
     */
    float maxAngle;

    /**
     * PWM period [s]
     */
    float period;

    /**
     * smallest pulse width [s]
     */
    float minPulseWidth;

    /**
     * greatest pulse width [s]
     */
    float maxPulseWidth;

    /**
     * center pulse width [s]
     */
    float centerPulseWidth;

    /**
     * pin name, must be enabled for PWM output.
     * check your board's datasheet
     */
    PwmOut pin;

    /**
     * converts angle to pulse width
     * @param angle desidered angle [deg]
     *
     * @returns pulse width [s]
     */
    float pulse_width(float angle);

public:
    // START SPECIFIC SERVO:
    // here can be added static methods to specific servo models.

    /**
     * Creates Servo object to control a S06NF servo
     *
     * @returns S06NF servo object
     */
    static Servo S06NF(PinName p);

    /**
     * Creates Servo object to control a S05NF servo
     *
     * @returns S05NF servo object
     */
    static Servo S05NF(PinName p);

    // END SPECIFIC SERVO

    /**
     * Sets up new Servo object with specified properties
     * @param ma smallest angle [deg]
     * @param Ma greatest angle [deg]
     * @param pd period [s]
     * @param mpw smallest pulse width [s]
     * @param Mpw greatest pulse width [s]
     * @param cpw center pulse width [s]
     * @param p  pin name (must be enabled for PWM output)
     */
    Servo(float ma, float Ma, float pd, float mpw, float Mpw, float cpw, PinName p);

    /**
     * moves servo to certain angle
     * @param angle desidered angle [deg]
     */
    void move(float angle);
};

#endif
