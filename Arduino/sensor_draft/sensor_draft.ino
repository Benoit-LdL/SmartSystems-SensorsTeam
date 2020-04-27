#include <NewPing.h>
#define SONAR_NUM     4
#define MAX_DISTANCE 200
#define PING_INTERVAL 33

byte pingTime[SONAR_NUM];

NewPing sonar[SONAR_NUM] = {
  NewPing(12, 11, MAX_DISTANCE),
  NewPing(10, 9, MAX_DISTANCE),
  NewPing(8, 7, MAX_DISTANCE),
  NewPing(6, 5, MAX_DISTANCE)
};

void setup() {
  // Setup I2C
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    pingTime[i] = sonar[i].ping_cm();
    delay(PING_INTERVAL);
  }
  MovingConvert();
  SendData();
}

void MovingConvert(){
  // pingTime[] door moving average filter, dan MovingPingTime[]
}

void SendData() {
  // Stuur MovingPingTime[] met I2C
}
