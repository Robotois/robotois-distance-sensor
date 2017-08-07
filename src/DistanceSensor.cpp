/*
 * File:   DistanceSensor.cpp
 * Author: yova
 *
 * Created on 16 de abril de 2016, 06:17 PM
 *
 * This Class is intendend to handle the Ultrasonic sensor HC-SR04, therefore it
 * is needed two digital IO of the RPI. For this reason we connect the sensor to one
 * of the Digital Headers and the order of the pins is:
 * Header->io_pin1 => Trigger
 * Header->io_pin2 => Echo
 *
 */

#include "DistanceSensor.h"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdint.h>
#include <thread>
#include <chrono>
#include <cmath>

DistanceSensor::DistanceSensor() {}

DistanceSensor::DistanceSensor(uint8_t header) {
    initialize(header);

    if(!connectionTest()){
        printf("Error reading echo from the Ultrasonic Sensor...\n");
        return;
    }
}

DistanceSensor::DistanceSensor(const DistanceSensor& orig) {
}

DistanceSensor::~DistanceSensor() {
    delete IOHeader;
}

/**
 * Initializes the IO pins of the given header to match the default Trigger and
 * Echo pins.
 * @param header
 */
void DistanceSensor::initialize(uint8_t header){
    // The first IO pin must be stablished as Output since it its the Trigger Pin.
    // The second IO pin of the header is the Echo pin of the sensor, so it is an input.
    // Trigger is on the io_pin1, echo in on the io_pin2
    IOHeader = new DigitalHeader(header, AS_INPUT, AS_OUTPUT);
}

float DistanceSensor::getValue(){
    return measure(2);
}

uint16_t DistanceSensor::getBasicValue(){
    return (uint16_t)(std::round(measure(2)));
}

float DistanceSensor::measure(uint8_t samples){
    unsigned int echoSum = 0; // Echo length sum [us]
    float average = 0.0f;
    unsigned int millis;
    unsigned int maxWaitTime = 60; // 30ms => half the mearuse cycle

    for(uint8_t i = 0; i < samples; i++){
        auto startTime = std::chrono::high_resolution_clock::now();
        echoSum += readSensor();

        auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        millis = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count();
        while(millis < maxWaitTime){
            elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
            millis = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count();
        }
    }
    // Se retorna el promedio del tiempo en [ns]
    average = (( (float) echoSum / samples ))/58.0f; // La regla es T[us]/58 = dist[cm]
//    return (float) echoSum/58.0f;
    return average;
}

unsigned int DistanceSensor::readSensor(){
    unsigned int echoTime = 0;

    // High enable, cuando se detecta un alto se dispara un evento EDS (Event Detect Status)
    // - Enviar el trigger
    IOHeader->io2_write(HIGH);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    IOHeader->io2_write(LOW);

    echoTime = readEcho();
    return echoTime;
}

unsigned int DistanceSensor::readEcho(){
    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    unsigned int maxWaitTime = 30000; // 30ms => half the mearuse cycle
    unsigned int microseconds, maxLength = 17400;
//    unsigned int echolength = 0;

    while(true){
      // Echo Signal has arrived
      if(IOHeader->io1_read() == 1){
        // -- Start measuring the Echo time length
        startTime = std::chrono::high_resolution_clock::now();
        while(true){
            elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
            microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();

            // -- Echo has reached the end
            if(IOHeader->io1_read() == 0){
                return microseconds;
            }
            // -- It is taking too long for the end to arrive
            if(microseconds > maxWaitTime){
                return maxLength;
            }
        }
      }

      // - Si nunca llega el echo, se manda una distancia de 300[cm]
      elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
      microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();

      if(microseconds > maxWaitTime){
        return maxLength;
      }
    }
    return 0;
}

bool DistanceSensor::connectionTest(){
    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    unsigned int maxWaitTime = 30000; // 30ms => half the mearuse cycle
    unsigned int microseconds;


    // - Send the trigger
    IOHeader->io2_write(HIGH);
//    uDelay(10); // 10us de trigger
    std::this_thread::sleep_for(std::chrono::microseconds(10));    
    IOHeader->io2_write(LOW);

    // - Rise Event Enable
    IOHeader->io1_riseEnable();

    while(true){
        // Echo Signal has arrived
        if(IOHeader->io1_riseDetected()){
//            mDelay(60);
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
            return true;
        }

      // - Si nunca llega el echo, se manda una distancia de 200[cm]
        elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();

        // - Echo never received
        if(microseconds > maxWaitTime){
            return false;
        }
    }
    return false;
}

void DistanceSensor::release(){
    IOHeader->release();
    delete IOHeader;
    printf("[DistanceSensor] => Released\n");
}
