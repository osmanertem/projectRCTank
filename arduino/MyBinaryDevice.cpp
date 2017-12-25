//
// Created by ertemu on 6/6/17.
//

#include <HardwareSerial.h>
#include "MyBinaryDevice.h"
#include "Utils.hpp"
#include "Arduino.h"

MyBinaryDevice::MyBinaryDevice(String name, int portNum, SoftwareSerial *raspiSerial)
{
    this->name = name;
    this->portNum = portNum;
    this->raspiSerial = raspiSerial;

    pinMode(portNum, OUTPUT);
    this->setOff();
}

// example LED|LED_FRONT|ON
void MyBinaryDevice::postDeviceState()
{
    String updateCommand = "MyBinaryDevice|" + String(this->name) + "|";
    updateCommand += this->isOn() ? "ON" : "OFF";

    if (this->raspiSerial->available())
    {
        this->raspiSerial->println( (updateCommand).c_str() );
    }
    else
    {
      Serial.println((updateCommand).c_str());
    }
}
 

// example: MyBinaryDevice|Led 1|SET|ON
bool MyBinaryDevice::handleSerialPortMessage(String message)
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

      if (deviceType == "MyBinaryDevice" &&
          deviceName == this->name &&
          operation == "SET")
      {
          if (value == "ON")
          {
              this->setOn();
              return true;
          }
          else if (value == "OFF")
          {
              this->setOff();
              return true;
          }
          else
          {
            printf("UNKNOWN %s", value.c_str());
          }
          //this->postDeviceState();
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

void MyBinaryDevice::setOn()
{
    String message = "MyBinaryDevice(" + String(this->name) + ") is set to ON";
    Serial.println(message);

    digitalWrite(this->portNum, HIGH);
    this->ledIsOn = true;
}

void MyBinaryDevice::setOff()
{
    String message = "MyBinaryDevice(" + String(this->name) + ") is set to OFF";
    Serial.println(message);

    digitalWrite(this->portNum, LOW);
    this->ledIsOn = false;
}

bool MyBinaryDevice::isOn()
{
    return this->ledIsOn;
}
