//
// Created by ertemu on 6/7/17.
//

#include "MyServo.h"
 

#include <HardwareSerial.h>
#include "Utils.hpp"
#include "Arduino.h"

MyServo::MyServo(String name, int portNum, SoftwareSerial *raspiSerial)
{
    this->name = name;
    this->portNum = portNum;
    this->raspiSerial = raspiSerial;

    this->myServo.attach(portNum);
    this->setAngle(0);
}

void MyServo::setAngle(int angle)
{
    this->currentAngle = angle;
    this->myServo.write(angle);

    String logMessage = "Servo (" + String(this->name) + ") angle is set to " + String(this->currentAngle);
    Log::getInst()->log(logMessage);
}

// example: MyServo|Servo_1|127
void MyServo::postDeviceState()
{
    String updateCommand = "MyServo|" + String(this->name) + "|";
    updateCommand += String(this->currentAngle);

    if (this->raspiSerial->available())
    {
        this->raspiSerial->println( (updateCommand).c_str() );
    }
    else
    {
      Serial.println((updateCommand).c_str());
    }
}

// example MyServo|Servo 1|ANGLE|127
bool MyServo::handleSerialPortMessage(String message)
{
    char ** splitted = Utils::str_split(message.c_str(), '|');
    const int commandPieceCount = 4;

    if (*(splitted + (commandPieceCount-1)))
    {
      String deviceType = splitted[0];
      String deviceName = splitted[1];
      String operation  = splitted[2];
      String value      = splitted[3]; 
      
      for (int i = 0; *(splitted + i); i++) {   free(*(splitted + i)); }  free(splitted);
         
      if (deviceType == "MyServo" && deviceName == this->name)
      { 
          if (operation == "ANGLE")
          {  
              this->setAngle(value.toInt());
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

