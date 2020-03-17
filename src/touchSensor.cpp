#include "touchSensor.h"

void TouchSensor::checkSensor() {
  _tRead = touchRead(_tNum);
}

bool TouchSensor::isTouched() {
  if(_tRead > 0 /*for prevent vibrate*/ && _tRead < _readRange) {
    //prevent multiple input
    unsigned long currentTime = millis();
    if(currentTime - previousTime <= 600) {
      return false;
    } else {
      previousTime = currentTime; 
      return true; 
    }
  }
  return false;
}
