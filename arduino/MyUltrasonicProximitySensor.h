//
// Created by ertemu on 6/7/17.
//

#ifndef PROJECTT_MYULTRASONICPROXIMITYSENSOR_H
#define PROJECTT_MYULTRASONICPROXIMITYSENSOR_H

 

#include "MyDevice.h"
#include "Log.h"
#include <Servo.h>

class MyUltrasonicProximitySensor:public MyDevice
{
public:
    MyUltrasonicProximitySensor(String name, int triggerPort, int echoPort, SoftwareSerial *raspiSerial);

    virtual bool handleSerialPortMessage(String message);
    virtual void postDeviceState();
    int updateDistanceMeasurement();

    int triggerPort = -1;
    int echoPort = -1;
    int lastMeasuredDistanceInCm = -1;

    SoftwareSerial *raspiSerial;
};
#endif //PROJECTT_MYULTRASONICPROXIMITYSENSOR_H
