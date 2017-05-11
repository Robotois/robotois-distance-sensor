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
#include <chrono>
#include <cmath>
#include "../../Libraries/Timer/AccurateTiming.h"

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
    IOHeader = new DigitalHeader(header,AS_OUTPUT,AS_INPUT);
    // We save the io adresses just to simplify their usage.
    triggerPin = IOHeader->io_pin1;
    echoPin = IOHeader->io_pin2;
}

float DistanceSensor::getValue(){
    return measure(1);
}

uint8_t DistanceSensor::getBasicValue(){
    return (uint8_t)(std::round(measure(1)));
}

float DistanceSensor::measure(uint8_t samples){
    unsigned int echoSum = 0; // Echo length sum [us]
    // float average = 0.0f;
    // unsigned int microseconds;
    // unsigned int maxWaitTime = 60000; // 30ms => half the mearuse cycle

    // for(uint8_t i = 0; i < samples; i++){
    //     auto startTime = std::chrono::high_resolution_clock::now();
        echoSum += readSensor();

    //     auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    //     microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
    //     while(microseconds < maxWaitTime){
    //         auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    //         microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
    //     }
    // }
    // Se retorna el promedio del tiempo en [ns]
    // average = (( (float)echoSum/samples ))/58.0f; // La regla es T[us]/58 = dist[cm]
    return (float) echoSum/58.0f;
}

unsigned int DistanceSensor::readSensor(){
    unsigned int echoTime = 0;

    // High enable, cuando se detecta un alto se dispara un evento EDS (Event Detect Status)
    // - Enviar el trigger
    IOHeader->io1_write(HIGH);
    uDelay(10); // 10us de trigger
    IOHeader->io1_write(LOW);

    // - Rise Event Enable
    IOHeader->io2_riseEnable();

    echoTime = readEcho();
    return echoTime;
}

unsigned int DistanceSensor::readEcho(){
    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    unsigned int maxWaitTime = 30000; // 30ms => half the mearuse cycle
    unsigned int microseconds;
    unsigned int echolength = 0;

    while(true){
      // Echo Signal has arrived
      if(IOHeader->io2_riseDetected()){
        // -- Start measuring the Echo time length
        startTime = std::chrono::high_resolution_clock::now();
        // -- Enble fall edge event on the echo pin
        IOHeader->io2_fallEnable();

        while(true){
            // -- Echo has reached the end
            if(IOHeader->io2_fallDetected()){
                elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
                microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
                break;
            }
        }

        echolength = microseconds;
        if(echolength > 17400){
            echolength = 17400;
        }
        break;
      }

      // - Si nunca llega el echo, se manda una distancia de 200[cm]
      elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
      microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();

      if(microseconds > maxWaitTime){
        echolength = 17400;
        break;
      }
    }
    return echolength;
}

bool DistanceSensor::connectionTest(){
    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    unsigned int maxWaitTime = 30000; // 30ms => half the mearuse cycle
    unsigned int microseconds;


    // - Send the trigger
    IOHeader->io1_write(HIGH);
    uDelay(10); // 10us de trigger
    IOHeader->io1_write(LOW);

    // - Rise Event Enable
    IOHeader->io2_riseEnable();

    while(true){
        // Echo Signal has arrived
        if(IOHeader->io2_riseDetected()){
            mDelay(60);
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
