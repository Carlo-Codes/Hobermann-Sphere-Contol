#include <Arduino.h>
#include "movement.h"


Movement sphere;


void setup() {
  sphere.setUpStepper(S_PIN1, S_PIN2, MAXSPEED, ACCEL);
  sphere.setUpLimitSwitches(UPPER_LIMIT_PIN, LOWER_LIMIT_PIN);
  
}

void loop() {

  //debugging//
  //sphere.debug();
  //sphere.printAmage();

  //check for inputs and porblems
  sphere.checkLimits(UPPER_LIMIT_PIN,LOWER_LIMIT_PIN);



  //outputs
  sphere.homeIfRequired();
  sphere.checkMoveToReady();
  sphere.checkMoveToUpPosition();
  sphere.checkMoveToDownPosition();
  sphere.checkTopLimitMoveToTop();
 

  //status update
  sphere.checkIfMovementFinished();


  //sphere.stressTest();

  sphere.step();

}





