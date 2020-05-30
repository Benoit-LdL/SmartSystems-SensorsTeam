#include <Wire.h>

typedef struct SensorData {
  uint8_t movingAverage[4];
} SensorData_t;

SensorData_t lastSensorData;

const uint8_t SENSOR_DATA_SIZE = sizeof(SensorData_t);
const uint8_t SENSOR_SLAVE_ADDRESS = 8;
byte buffer[SENSOR_DATA_SIZE];

void setup() {
  Wire.begin();
  Serial.begin(9600);
}
void loop() {
  Wire.requestFrom(SENSOR_SLAVE_ADDRESS, SENSOR_DATA_SIZE);

  while (Wire.available()) {
    for (size_t i = 0; i < SENSOR_DATA_SIZE; i++) {
      buffer[i] = Wire.read();
    }
    memcpy(&lastSensorData, &buffer, SENSOR_DATA_SIZE);
  }

  Serial.println("sensors :");
  Serial.println(lastSensorData.movingAverage[0]);
  Serial.println(lastSensorData.movingAverage[1]);
  Serial.println(lastSensorData.movingAverage[2]);
  Serial.println(lastSensorData.movingAverage[3]);
  Serial.println("*************************************************");

  delay(500);
}
