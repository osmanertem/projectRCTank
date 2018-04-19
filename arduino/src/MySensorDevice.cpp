//
// Created by gokhansi on 619/4/18.
//

#include "MySensorDevice.h"

#include <HardwareSerial.h>
#include "Utils.hpp"
#include "Arduino.h"

MySensorDevice::MySensorDevice(String name, int readPin, SoftwareSerial *raspiSerial)
{
    this->name = name;
    this->readPin = readPin;
    this->raspiSerial = raspiSerial;

    pinMode(readPin, INPUT);
}

void
MySensorDevice::postDeviceState()
{
    this->updatePinStatus();

    String updateCommand = "MySensorDevice|" + String(this->name) + "|";
    updateCommand += String(this->pinState);

    if (this->raspiSerial->available())
    {
        this->raspiSerial->println( (updateCommand).c_str() );
    }
    else
    {
        Serial.println((updateCommand).c_str());
    }
}

void
MySensorDevice::updatePinStatus()
{
  this->pinState = digitalRead(this->readPin);
}

bool
MySensorDevice::handleSerialPortMessage(String message)
{
    // nothing to listen from raspberry side
    return false;
}

