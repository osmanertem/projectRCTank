//
// Created by ertemu on 6/7/17.
//

#include "MyUltrasonicProximitySensor.h"

#include <HardwareSerial.h>
#include "Utils.hpp"
#include "Arduino.h"

MyUltrasonicProximitySensor::MyUltrasonicProximitySensor(String name, int triggerPort, int echoPort, SoftwareSerial *raspiSerial)
{
    this->name = name;
    this->triggerPort = triggerPort;
    this->echoPort = echoPort;
    this->raspiSerial = raspiSerial;

    pinMode(triggerPort, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPort, INPUT); // Sets the echoPin as an Input
}

// example: MyUltrasonicProximitySensor|US_SENSOR|127 cm
void
MyUltrasonicProximitySensor::postDeviceState()
{
    this->updateDistanceMeasurement();

    String updateCommand = "MyUltrasonicProximitySensor|" + String(this->name) + "|";
    updateCommand += String(this->lastMeasuredDistanceInCm);

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
MyUltrasonicProximitySensor::updateDistanceMeasurement()
{
    // Clears the trigPin
    digitalWrite(this->triggerPort, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(this->triggerPort, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->triggerPort, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    double duration = pulseIn(this->echoPort, HIGH);
    // Calculating the distance
 
    this->lastMeasuredDistanceInCm = static_cast<int>(duration*0.034/2);
}

bool
MyUltrasonicProximitySensor::handleSerialPortMessage(String message)
{
    // nothing to listen from raspberry side
    return false;
}

