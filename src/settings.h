//positions in degrees from bottom limit
#define DOWN_POSITION 10
#define UP_POSITION 250
#define UPPER_LIMIT 260

//accel settings
#define MAXSPEED 4000
#define ACCEL 3000
#define HOMING_SPEED 2000

//Motor Pins
#define S_PIN1 3 //pulse pin for driver
#define S_PIN2 4 //direction pin for driver

//limit pins
#define UPPER_LIMIT_PIN 6
#define LOWER_LIMIT_PIN 7

//Drive mech settings
#define STEPS_PER_REV 6400 //see dip switches on driver


#define TopLimitInSteps (UPPER_LIMIT / 360) * STEPS_PER_REV
#define TopInSteps (UP_POSITION / 360) * STEPS_PER_REV
#define BottomInSteps (DOWN_POSITION / 360) * STEPS_PER_REV

enum positions {
    TopLimit = TopLimitInSteps,
    BottomLimit = 0,
    Top = TopInSteps,
    Bottom = BottomInSteps
};