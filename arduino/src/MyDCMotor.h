//
// Created by ertemu on 6/7/17.
//

#ifndef PROJECTT_MYDCMOTOR_H
#define PROJECTT_MYDCMOTOR_H

#include "MyDevice.h"
#include "Log.h"

class MyDCMotor:public MyDevice
{
public:
    MyDCMotor(String name, int pwmPort, int directionPort_1, int directionPort_2, SoftwareSerial *raspiSerial);

    virtual bool handleSerialPortMessage(String message);
    virtual void postDeviceState();

    void setPWM(int newPwmValue);
    void setDirection(char* direction);

    bool enabled = false;
    String direction;
 
    int portNum = -1;
    int currentPWM = false;
    int directionPort_1;
    int directionPort_2;
    SoftwareSerial *raspiSerial;
};
#endif //PROJECTT_MYDCMOTOR_H
