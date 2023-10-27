#ifndef Movement_h
#define Movement_h
#include "Arduino.h" 
#include "AccelStepper.h"
#include "settings.h"

class Movement {

    private:
    //BUTTON STATUS'(could also be considered as moving status)
    bool moveUpStatus;
    bool moveDownStatus;

    //SAFTEY STATUS
    bool upperEndStop;
    bool lowerEndStop;
    bool homingRequired;





    //Motor
    protected:
    AccelStepper *stepper;

    //////////////Fuctions///////////////////////
    //setupFunctions
    public:
    Movement();
    void setUpStepper(int pin1, int pin2, int speed, int accel);
    void setUpButtons(uint8_t motUp, uint8_t motDown, uint8_t maintain);
    void setUpLimitSwitches(uint8_t upperLimit, uint8_t lowerLimit);
    void setUpFlapSwitch(uint8_t upperLimit);
    void setUpAmeter(uint8_t pin);
    void setUpObstructionLED(uint8_t pin);

    

    //outputs
    void homeIfRequired();
    void checkMoveToReady();

    void checkMoveToUpPosition();
    void checkMoveToDownPosition();
    void checkTopLimitMoveToTop();

    void checkIfMovementFinished();

    void displayObstructionStatus(uint8_t pin);

    void step();

    //saftey
    void emergencyStop();
    void checkLimits(uint8_t upperLimit, uint8_t lowerLimit);


    //debug
    void debug();
    void printAmage();

    //TESTING
    void stressTest();
};


#endif