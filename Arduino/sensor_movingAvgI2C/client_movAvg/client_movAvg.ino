// download de library van https://github.com/AP-Elektronica-ICT/NewPing
// en verwijder andere NewPing libraries

#include <Wire.h>
#include <NewPing.h>

#define SONAR_NUM      4
#define MAX_DISTANCE 200
#define PING_INTERVAL 20
#define SAMPLE_LENGTH 5

typedef struct SensorData {
  uint8_t movingAverage[4];
} SensorData_t;

SensorData_t latestSensorData;
const uint8_t SENSOR_DATA_SIZE = sizeof(SensorData_t);
const uint8_t SENSOR_SLAVE_ADDRESS = 8;
byte buffer[SENSOR_DATA_SIZE];

uint8_t pingResults[SONAR_NUM];
uint8_t pingTotal=0;
uint8_t averageResult[SONAR_NUM];

/* //code movingAverage
//uint8_t pingHistory[SONAR_NUM][SAMPLE_LENGTH];
//uint8_t movingAvgResult[SONAR_NUM];
*/

// pins volgens elek schema NewPing(trigger_pin, echo_pin, MAX_DISTANCE);
NewPing sonar[SONAR_NUM] = {
  NewPing(5, 6, MAX_DISTANCE),
  NewPing(7, 8, MAX_DISTANCE),
  NewPing(9, 10, MAX_DISTANCE),
  NewPing(11, 12, MAX_DISTANCE),
};

void requestEvent() {
  Wire.write(buffer, SENSOR_DATA_SIZE);
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
    /* //code movingAverage
    pingResults[i] = sonar[i].ping_cm();
    pingHistory[i][0] = pingResults[i];
  
    movingAvgResult[i] = sonar[i].convert_movingAverage(pingHistory[i]);

    for (byte y = 10; y > 0; y--) {
      pingHistory[i][y] = pingHistory[i][y-1];
    }
    */
    
    for (byte j = 0; j < SAMPLE_LENGTH; j++)
    {
      pingTotal += sonar[i].ping_cm();
      delay(PING_INTERVAL);
    }
    averageResult[i] = pingTotal / SAMPLE_LENGTH;
    pingTotal = 0; //reset
  }
  SendData();
  /* DEBUGGING, uncomment as needed
  //LogRawInSerial();
  //LogAvgInSerial();
  //LogHistoryInSerial();
  */
}

void SendData() {
  //latestSensorData = {movingAvgResult[0],movingAvgResult[1],movingAvgResult[2],movingAvgResult[3]};
  latestSensorData = {averageResult[0],averageResult[1],averageResult[2],averageResult[3]};
  LogAvrg(); //print data in cli
  memcpy(&buffer, &latestSensorData, SENSOR_DATA_SIZE);
}

void LogAvrg()
{
  Serial.println("-----------------------");
  Serial.print("Sensor"); Serial.print(": ");
  for (int i = 0;i<SONAR_NUM;i++)
  {
     Serial.print(averageResult[i]); Serial.print(" - ");
  }
  Serial.println();
}

/* //Logging
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
*/
