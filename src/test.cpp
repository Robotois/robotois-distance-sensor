#include <cstdio>
#include <bcm2835.h>
#include <thread>
#include <chrono>

#include "./DistanceSensor.h"

void i2c_init();
void i2c_end();

int main(int argc, char const *argv[]){
  i2c_init();
  DistanceSensor *usonic1 = new DistanceSensor(5);
  while(true){
    printf("dist1: %d cm\n",usonic1->getBasicValue());
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }

  i2c_end();
}

void i2c_init(){
  uint16_t clockDiv = BCM2835_I2C_CLOCK_DIVIDER_626;

  if(!bcm2835_init()){
    printf("BCM2835 Error!!\n");
  }

  bcm2835_i2c_begin();
  bcm2835_i2c_setClockDivider(clockDiv);
}

void i2c_end(){
  bcm2835_i2c_end();
  bcm2835_close();
}
