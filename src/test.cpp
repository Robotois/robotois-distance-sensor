#include <cstdio>
#include <bcm2835.h>

#include "./Modules/Distance/DistanceSensor.h"
#include "./Libraries/Timer/AccurateTiming.h"

void i2c_init();
void i2c_end();

int main(int argc, char const *argv[]){
  i2c_init();
  DistanceSensor *usonic1 = new DistanceSensor(1);
  DistanceSensor *usonic2 = new DistanceSensor(2);
  DistanceSensor *usonic3 = new DistanceSensor(4);
  // float value1, value2, value3;
  int16_t value1, value2, value3;
  while(true){
    // value1 = usonic1->getValue();
    // value2 = usonic2->getValue();
    // value3 = usonic3->getValue();
    // printf("dist1: %0.2fcm, dist2: %0.2fcm, dist3: %0.2fcm\n",value1,value2,value3);
    value1 = usonic1->getBasicValue();
    value2 = usonic2->getBasicValue();
    value3 = usonic3->getBasicValue();
    printf("dist1: %dcm, dist2: %dcm, dist3: %dcm\n",value1,value2,value3);
    mDelay(250);
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
