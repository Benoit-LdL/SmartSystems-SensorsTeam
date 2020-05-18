// download de library van https://github.com/AP-Elektronica-ICT/NewPing
// en verwijder andere NewPing libraries

#include <Wire.h>
#include <NewPing.h>

#define SONAR_NUM     4
#define MAX_DISTANCE 200
#define PING_INTERVAL 60
#define SAMPLE_LENGTH 10

typedef struct SensorData {
  long movingAverage;
  long rawData1[4];
} SensorData_t;

SensorData_t latestSensorData;
const uint8_t SENSOR_DATA_SIZE = sizeof(SensorData_t);
const uint8_t SENSOR_SLAVE_ADDRESS = 8;
byte buffer[SENSOR_DATA_SIZE];

uint8_t pingResults[SONAR_NUM];
uint8_t pingHistory[SONAR_NUM][SAMPLE_LENGTH];
uint8_t movingAvgResult[SONAR_NUM];
bool handled;

// pins volgens elek schema NewPing(trigger_pin, echo_pin, MAX_DISTANCE);
NewPing sonar[SONAR_NUM] = {
  NewPing(12, 11, MAX_DISTANCE),
  NewPing(10, 9, MAX_DISTANCE),
  NewPing(8, 7, MAX_DISTANCE),
  NewPing(6, 5, MAX_DISTANCE)
};

void requestEvent() {
  if (handled) {
    Wire.write(buffer, SENSOR_DATA_SIZE);
    handled = false;
  }
}

void setup() {
  Serial.begin(9600);
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
  Wire.begin(SENSOR_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
}

void loop() {
  for (byte i = 0; i < SONAR_NUM; i++) {
    pingResults[i] = sonar[i].ping_cm();
    pingHistory[i][0] = pingResults[i];
  
    movingAvgResult[0] = sonar[0].convert_movingAverage(pingHistory[0]);
    movingAvgResult[1] = sonar[1].convert_movingAverage(pingHistory[1]);
    movingAvgResult[2] = sonar[2].convert_movingAverage(pingHistory[2]);
    movingAvgResult[3] = sonar[3].convert_movingAverage(pingHistory[3]);

    for (byte y = 10; y > 0; y--) {
      pingHistory[i][y] = pingHistory[i][y-1];
    }
    delay(PING_INTERVAL);
  }
  SendData();

  // DEBUGGING, uncomment as needed
  //LogRawInSerial();
  //LogAvgInSerial();
  //LogHistoryInSerial();
}

void SendData() {
  latestSensorData = {movingAvgResult[0],movingAvgResult[1],movingAvgResult[2],movingAvgResult[3]};
  memcpy(&buffer, &latestSensorData, SENSOR_DATA_SIZE);
  if (!handled) {
   Serial.println("Requested");
    handled = true;
  }
}

void LogRawInSerial() {
  for (byte i = 0; i < SONAR_NUM; i++) {
    Serial.print("Sensor " + String(i+1) + " RAW:"); 
    Serial.println(pingResults[i]);
  }
  Serial.println("---------------------");
}

void LogAvgInSerial() {
  for (byte i = 0; i < SONAR_NUM; i++) {
    Serial.print("Sensor " + String(i+1) + " AVG:"); 
    Serial.println(movingAvgResult[i]);
  }
  Serial.println("---------------------");
}

void LogHistoryInSerial() {
  Serial.print("Sensor 1 RAW:"); 
  Serial.println(pingResults[0]);
  for (byte i = 0; i < SAMPLE_LENGTH; i++) {
    Serial.print(pingHistory[0][i]); 
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("---------------------");
}