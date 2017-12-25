//
// Created by ertemu on 6/7/17.
//

#ifndef PROJECTT_MYSERVO_H
#define PROJECTT_MYSERVO_H

#include "MyDevice.h"
#include "Log.h"
#include <Servo.h>

class MyServo:public MyDevice
{
public:
    MyServo(String name, int portNum, SoftwareSerial *raspiSerial);

    virtual bool handleSerialPortMessage(String message);
    virtual void postDeviceState();

    void setAngle(int angle);


    int portNum = -1;
    int currentAngle = -1;

    Servo myServo;
    SoftwareSerial *raspiSerial;
};
#endif //PROJECTT_MYSERVO_H
