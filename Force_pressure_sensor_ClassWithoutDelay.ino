#include "Arduino.h"

class Pressure_btn{
  public:
    Pressure_btn(){}
    void setup(int inputPin){
      pinMode(inputPin, INPUT);
      _inputPin = inputPin;
    }
    Pressure_btn(int inputPin){
      pinMode(inputPin, INPUT);
      _inputPin = inputPin;
    }
    int getPressLevel(int fsrReading){
      if(fsrReading <= 10){
        return 0;
      }
      else if(fsrReading >=11 and fsrReading <=70){
        return 1;
      }
      else{
        return 2;
      }
    }
    int press(){
      int fsrReading = analogRead( _inputPin);
      int pressLevelState = getPressLevel(fsrReading);
      // If the switch changed, due to noise or pressing:
      if(pressLevelState != _lastPressState){
        _lastDebounceTime = millis();
      }
      //reading is been there for longer than the debounce delay
      //take it as the actual current state
      if((millis() - _lastDebounceTime) > _debounceDelay){
        //Serial.println("input steady!!!");
        //if the button state has changed:
        if(pressLevelState != _btnState){
          //Serial.print("btnState changed!! from ");
          //Serial.print(_btnState);
          //Serial.print(" to ");
          //Serial.println(pressLevelState);
          _btnState = pressLevelState;
          return pressLevelState;
        }
        //if the button state has no changed:
        else{
          //Serial.print("btnState no changed!! ");
          return 0;
        }
      }
      else{
        //Serial.println("input unsteady!!!");
      }
      // save the reading.  Next time through the loop,
      // it'll be the lastButtonState:
      _lastPressState = pressLevelState;
      return 0;
    }
  private:
    int _inputPin;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 50;
    int _btnState;
    int _lastPressState = 0;
};

Pressure_btn btnA0;

void setup(){
  btnA0.setup(A0);
}

void loop(){
  int pressLevelState = btnA0.press();
  //if(pressLevelState !=0){
  //  Serial.print("Final result : ");
  //  Serial.println(pressLevelState);
  //}
  
}
