/*
 * File:   DistanceSensor.h
 * Author: yova
 *
 * Created on 16 de abril de 2016, 06:17 PM
 */

#ifndef DISTANCESENSOR_H
#define	DISTANCESENSOR_H

#include <bcm2835.h>
#include "./libraries/robotois-digital-header/DigitalHeader.h"

class DistanceSensor {
public:
    DistanceSensor();
    DistanceSensor(uint8_t header);
    DistanceSensor(const DistanceSensor& orig);
    virtual ~DistanceSensor();

    float getValue();
    uint16_t getBasicValue();

    void initialize(uint8_t header);

    bool connectionTest();

    void release();
private:
    DigitalHeader *IOHeader;
    uint8_t triggerPin, echoPin;

    float measure(uint8_t samples);
    unsigned int readSensor();
    void sendTrigger();
    unsigned int readEcho();
};

#endif	/* ULTRASONICSENSOR_H */
