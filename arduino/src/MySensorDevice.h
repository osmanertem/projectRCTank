//
// Created by ertemu on 6/7/17.
//

#ifndef PROJECTT_MYSENSORDEVICE_H
#define PROJECTT_MYSENSORDEVICE_H

#include "MyDevice.h"
#include "Log.h"
#include <Servo.h>

class MySensorDevice:public MyDevice
{
public:
    MySensorDevice(String name, int readPin, SoftwareSerial *raspiSerial);

    virtual bool handleSerialPortMessage(String message);
    virtual void postDeviceState();
    void updatePinStatus();

	int readPin = 7;  // This is our input pin
	int pinState = -1;  // HIGH MEANS NO OBSTACLE

    SoftwareSerial *raspiSerial;
};
#endif //PROJECTT_MYSENSORDEVICE_H
