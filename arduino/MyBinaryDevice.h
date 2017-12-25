//
// Created by ertemu on 6/6/17.
//

#ifndef PROJECTTANK_MYLED_H
#define PROJECTTANK_MYLED_H

#include "MyDevice.h"
#include "Log.h"


class MyBinaryDevice:public MyDevice
{
public:
    MyBinaryDevice(String name, int portNum, SoftwareSerial *raspiSerial);

    virtual bool handleSerialPortMessage(String message);
    virtual void postDeviceState();

    void setOn();
    void setOff();
    bool isOn();

    int portNum = -1;
    bool ledIsOn = false;
    SoftwareSerial *raspiSerial;
};

#endif //PROJECTTANK_MYLED_H
