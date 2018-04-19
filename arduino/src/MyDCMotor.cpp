//
// Created by ertemu on 6/7/17.
//

#include "MyDCMotor.h"

#include <HardwareSerial.h> 
#include "Utils.hpp"
#include "Arduino.h"

MyDCMotor::MyDCMotor(String name, int pwmPort, int directionPort_1, int directionPort_2, SoftwareSerial *raspiSerial)
{
    this->name = name;
    this->portNum = pwmPort;
    this->directionPort_1 = directionPort_1;
    this->directionPort_2 = directionPort_2;
    this->raspiSerial = raspiSerial;

    pinMode(pwmPort, OUTPUT);
    pinMode(directionPort_1, OUTPUT);
    pinMode(directionPort_2, OUTPUT);
    this->setDirection("STOPPED");
    this->setPWM(0);
}

// new pwm is between 0-255
void MyDCMotor::setPWM(int newPwmValue)
{
    String message = "MyDCMotor(" + this->name + ") PWM is set to :" + String(newPwmValue);
    Log::getInst()->log(message);

    analogWrite(this->portNum, newPwmValue);
    this->currentPWM = newPwmValue;
}

/*
    ENA	IN1	IN2	Description
    0	N/A	N/A	Motor A is off
    1	0	0	Motor A is stopped (brakes)
    1	0	1	Motor A is on and turning backwards
    1	1	0	Motor A is on and turning forwards
    1	1	1	Motor A is stopped (brakes)
 */
// direction = FORWARDS, BACKWARDS, STOPPED
void
MyDCMotor::setDirection(char* direction)
{
    String logMessage = "DCMotor " + String(this->name) + " direction is set to ";

    if (strcmp(direction, "FORWARDS") == 0)
    {
        digitalWrite(this->directionPort_1, HIGH);
        digitalWrite(this->directionPort_2, LOW);
        this->direction = "FORWARDS";

        logMessage += "FORWARDS";
    }
    else if (strcmp(direction, "BACKWARDS") == 0)
    {
        digitalWrite(this->directionPort_1, LOW);
        digitalWrite(this->directionPort_2, HIGH);
        this->direction = "BACKWARDS";

        logMessage += "BACKWARDS";
    }
    else if (strcmp(direction, "STOPPED") == 0)
    {
        digitalWrite(this->directionPort_1, LOW);
        digitalWrite(this->directionPort_2, LOW);
        this->direction = "STOPPED";

        logMessage += "STOPPED";
    }

    Log::getInst()->log(logMessage);
}

// example: MyDCMotor|MotorLeft|ENABLED|FORWARDS|127
void MyDCMotor::postDeviceState()
{ 
    String updateCommand = "MyDCMotor|" + this->name + "|"; 
    updateCommand += this->direction + "|"; 
    updateCommand += String(this->currentPWM); 

    if (this->raspiSerial->available())
    {

        this->raspiSerial->println( (updateCommand).c_str() );
    }
    else
    {
        Log::getInst()->log(updateCommand);
    }
}

// example MyDCMotor|MotorLeft|PWM|200
// example MyDCMotor|MotorLeft|DIRECTION|FORWARDS
// example MyDCMotor|MotorLeft|DIRECTION|BACKWARDS
// example MyDCMotor|MotorLeft|DIRECTION|STOPPED

// example MyDCMotor|MotorRight|PWM|200
// example MyDCMotor|MotorRight|DIRECTION|FORWARDS
// example MyDCMotor|MotorRight|DIRECTION|BACKWARDS
// example MyDCMotor|MotorRight|DIRECTION|STOPPED
bool MyDCMotor::handleSerialPortMessage(String message)
{ 
    char ** splitted = Utils::str_split(message.c_str(), '|');
    const int commandPieceCount = 4;

    if (*(splitted + (commandPieceCount-1)))
    {
      String deviceType = splitted[0];
      String deviceName = splitted[1];
      String operation = splitted[2];
      String value = splitted[3]; 
      
      for (int i = 0; *(splitted + i); i++) {   free(*(splitted + i)); }  free(splitted);

      if (deviceType == "MyDCMotor" &&
          deviceName == this->name)
      { 
          if (operation == "PWM")
          {  
              this->setPWM(value.toInt());
              return true;
          }
          else if (operation == "DIRECTION")
          {
              this->setDirection(value.c_str());
              return true;
          } 
          this->postDeviceState();
      }
      else
      {
          return false;
      }
    }
    else
    {
        for (int i = 0; *(splitted + i); i++) {   free(*(splitted + i)); }  free(splitted);
        Serial.println("Command does not have 4 pieces");
    }

    return false;  
}

