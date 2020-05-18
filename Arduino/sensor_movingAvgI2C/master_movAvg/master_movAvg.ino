//master
#include <Wire.h>
#define I2C_SDA 33
#define I2C_SCL 32
typedef struct SensorData {
  long movingAverage;
  long rawData1[4];
} SensorData_t;

SensorData_t lastSensorData;

//stored size of sensor data and slave address in constant for maintability and readability
const uint8_t SENSOR_DATA_SZ = sizeof(SensorData_t);
const uint8_t SENSOR_SLAVE_ADDRESS = 8;

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(9600);
}
void loop() {

  Wire.requestFrom(SENSOR_SLAVE_ADDRESS, SENSOR_DATA_SZ);
  while (Wire.available() < SENSOR_DATA_SZ);
  //read and store the expected bytes in a byte array
  byte buffer[SENSOR_DATA_SZ];
  for (size_t i = 0; i < SENSOR_DATA_SZ; i++)
  {
    buffer[i] = Wire.read();

  }

  //copy the byte array to struct bytes
  //more info about memcpy: https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
  memcpy(&lastSensorData, &buffer, SENSOR_DATA_SZ);

  //print received data for debugging purposes
  Serial.println("sensors :");
  Serial.println(lastSensorData.movingAverage);
  Serial.println(lastSensorData.rawData1[0]);
  Serial.println(lastSensorData.rawData1[1]);
  Serial.println(lastSensorData.rawData1[2]);
  Serial.println("*************************************************");


  delay(500);
}