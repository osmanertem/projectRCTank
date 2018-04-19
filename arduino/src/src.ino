/*Rather than using the CLion Serial Monitor plugin, I simply use a Terminal within CLion to upload and start the monitor as soon as possible:
        pio run -t upload; pio serialports monitor -b 115200
*/
//
// Created by ertemu on 6/6/17.
//

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "MyDevice.h"
#include "MyBinaryDevice.h"
#include "MySensorDevice.h"
#include "MyServo.h"
#include "MyDCMotor.h"
#include "MyUltrasonicProximitySensor.h"
#include "Log.h" 



MyDevice **deviceArr;
SoftwareSerial raspiSerial(11, 11); // RX, TX
 
void constructDeviceList();

void setup()
{
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    raspiSerial.begin(115200);
    Log::getInst()->log("================ STARTING ================");
    
    constructDeviceList();
}

#define DEVICE_COUNT 7
int counter=1;
void loop()
{ 
    delay(2 * 1000);
    Serial.println(counter);
    counter++;
    
    String newCommand;
    if(Serial.available())
    {  
        newCommand = Serial.readStringUntil('\n');   
        Log::getInst()->log(newCommand); 
        Serial.flush();
    }
    else
    { 
        Serial.flush();
    }
   Serial.println("------");

    if (newCommand.length() > 0)
    { 
        for (int i=0; i<DEVICE_COUNT; i++)
        { 
            String tempCommand(newCommand); 
            if (deviceArr[i]->handleSerialPortMessage(newCommand))
            {
                Log::getInst()->log("Command successfully handled : " + newCommand);
                break;
            } 
            else
            {
                Log::getInst()->log("Command not handled : " + newCommand);
            }
        }
    } 

    // force all devices to post their state to raspberry
    for (int i=0; i<DEVICE_COUNT; i++)
    { 
        deviceArr[i]->postDeviceState(); 
    }
}

  
// MyServo|YATAY|ANGLE|127
// MyServo|DUSEY|ANGLE|127
// MyBinaryDevice|LED|SET|ON
// MyBinaryDevice|LASER|SET|ON
void constructDeviceList()
{
    deviceArr = new MyDevice*[DEVICE_COUNT]; 
    
//MyDCMotor::MyDCMotor(char* name, int pwmPort, int directionPort_1, int directionPort_2, SoftwareSerial *Serial)
    deviceArr[0] = static_cast<MyDevice *>(new MyDCMotor(String("MotorLeft"), 3, 4, 5, &raspiSerial)); 
    deviceArr[1] = static_cast<MyDevice *>(new MyDCMotor(String("MotorRight"), 8, 7, 6, &raspiSerial));
     
    deviceArr[2] = static_cast<MyDevice *>(new MyServo(  String("YATAY"),    A1,       &raspiSerial)); 
    deviceArr[3] = static_cast<MyDevice *>(new MyServo(  String("DUSEY"),    A4,       &raspiSerial)); 
    
    deviceArr[4] = static_cast<MyDevice *>(new MyBinaryDevice(  String("LED"),   A2, &raspiSerial)); 
    deviceArr[5] = static_cast<MyDevice *>(new MyBinaryDevice(  String("LASER"), A3, &raspiSerial)); 

    deviceArr[6] = static_cast<MyDevice *>(new MyUltrasonicProximitySensor("MyUltrasonicProximitySensor", A6, A5, &raspiSerial)); 
}


























