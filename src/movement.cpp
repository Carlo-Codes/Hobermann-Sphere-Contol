#include "movement.h"
#include "AccelStepper.h"



Movement::Movement(){
    moveUpStatus = false;
    moveDownStatus = false;
    upperEndStop = false;
    lowerEndStop = false;
    homingRequired = true;
    
};

void Movement::setUpStepper(int pin1, int pin2, int speed, int accel){
    stepper = new AccelStepper(1, pin1, pin2);
    stepper->setAcceleration(accel);
    stepper->setMaxSpeed(speed);
}

void Movement::setUpButtons(uint8_t motUp, uint8_t motDown, uint8_t maintBtn){
    pinMode(motUp,INPUT);
    pinMode(motDown,INPUT);
    pinMode(maintBtn,INPUT);
}

void Movement::setUpObstructionLED(uint8_t pin){
    pinMode(pin, OUTPUT);
}

void Movement::setUpLimitSwitches(uint8_t upperLimit, uint8_t lowerLimit){
    pinMode(upperLimit,INPUT_PULLUP);
    pinMode(lowerLimit,INPUT_PULLUP);
}

void Movement::checkLimits(uint8_t upperLimit, uint8_t lowerLimit){
    int upper = digitalRead(upperLimit);
    int lower = digitalRead(lowerLimit);
    upperEndStop = upper;
    lowerEndStop = lower;
    if(upperEndStop){
        emergencyStop();
        stepper->setCurrentPosition(TopLimit);
       
    }
    if(lowerEndStop){
        emergencyStop();
        stepper->setCurrentPosition(Bottom);

        //RESET SETTINGS AFTER HOMING
        homingRequired = false;
        stepper->setMaxSpeed(MAXSPEED);
    }
}



void Movement::checkMoveToUpPosition(){
    if(moveUpStatus == true && stepper->currentPosition() != Top && stepper->targetPosition() != Top && homingRequired == false ){
        stepper->moveTo(Top);    
    }
}

void Movement::checkMoveToDownPosition(){
     if(moveDownStatus == true && stepper->currentPosition() != Bottom && stepper->targetPosition() != Bottom && homingRequired == false){
        stepper->moveTo(Bottom);
    }
}


void Movement::checkMoveToReady(){
     if(stepper->currentPosition() == BottomLimit && homingRequired == false){
        stepper->moveTo(Bottom);
    }
}

void Movement::checkTopLimitMoveToTop(){
    if(stepper->currentPosition() == TopLimit){
        stepper->moveTo(Top);
    }
}

void Movement::checkIfMovementFinished(){
    if(stepper->distanceToGo() == 0){
        moveUpStatus = false;
        moveDownStatus = false;
    }
}

void Movement::homeIfRequired(){
    if(homingRequired == true){
        stepper->setMaxSpeed(HOMING_SPEED);
        stepper->move(-Top);
    }
}

void Movement::step(){
    stepper->run();
}

void Movement::emergencyStop(){
    moveUpStatus = false;
    moveDownStatus = false;
    stepper->moveTo(stepper->currentPosition());
}

void Movement::debug(){
    Serial.println("///////////");
    Serial.print("Position = ");
    Serial.print(stepper->currentPosition());
    Serial.print("\n");

    Serial.print("moveUpStatus = ");
    Serial.print(moveUpStatus);
    Serial.print("\n");

    Serial.print("moveDownStatus = ");
    Serial.print(moveDownStatus);
    Serial.print("\n");
    
    Serial.print("homing required = ");
    Serial.print(homingRequired);
    Serial.print("\n");

    Serial.print("lowerEndStop = ");
    Serial.print(lowerEndStop);
    Serial.print("\n");

    Serial.print("upper Endstop = ");
    Serial.print(upperEndStop);
    Serial.print("\n");

    
    delay(3);
}

void Movement::stressTest(){
    if(stepper->currentPosition() >= Top){
        stepper->moveTo(Bottom);
    }if(stepper->currentPosition() == Bottom){
        stepper->moveTo(Top);
    }
}











