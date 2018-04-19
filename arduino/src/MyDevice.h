//
// Created by ertemu on 6/6/17.
//

#ifndef PROJECTTANK_DEVICE_H
#define PROJECTTANK_DEVICE_H

#include <SoftwareSerial.h>

class MyDevice
{
public:
    String name;
    virtual bool handleSerialPortMessage(String message) = 0;
    virtual void postDeviceState() = 0;
};

#endif //PROJECTTANK_DEVİCE_H
