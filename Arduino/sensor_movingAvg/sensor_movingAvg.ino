// download de library van https://github.com/AP-Elektronica-ICT/NewPing

#include <NewPing.h>

#define SONAR_NUM     4
#define MAX_DISTANCE 200
#define PING_INTERVAL 60
#define SAMPLE_LENGTH 10

uint8_t pingResults[SONAR_NUM];
uint8_t pingHistory[SONAR_NUM][SAMPLE_LENGTH];
uint8_t movingAvgResult[SONAR_NUM];

// pins volgens elek schema NewPing(trigger_pin, echo_pin, MAX_DISTANCE);
NewPing sonar[SONAR_NUM] = {
  NewPing(12, 11, MAX_DISTANCE),
  NewPing(10, 9, MAX_DISTANCE),
  NewPing(8, 7, MAX_DISTANCE),
  NewPing(6, 5, MAX_DISTANCE)
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (byte i = 0; i < SONAR_NUM; i++) {    
    pingResults[i] = sonar[i].ping_cm();
    pingHistory[i][0] = pingResults[i];

    movingAvgResult[i] = sonar[i].convert_movingAverage(pingHistory[i]);
    
    for (byte y = 10; y > 0; y--) {
      pingHistory[i][y] = pingHistory[i][y-1];
    }
    
    delay(PING_INTERVAL);
  }
  //SendData();
 

  // DEBUGGING, uncomment as needed 
  LogAvgInSerial();
  LogRawInSerial();
  //LogHistoryInSerial();
}

void SendData() {
  // Bekijk nieuwe versie, sensor_movingAvgI2C
}

void LogAvgInSerial() {
  for (byte i = 0; i < SONAR_NUM; i++) {
    Serial.print("Sensor " + String(i+1) + " AVG:"); 
    Serial.println(movingAvgResult[i]);
  }
  Serial.println("---------------------");
}

void LogRawInSerial() {
  for (byte i = 0; i < SONAR_NUM; i++) {
    Serial.print("Sensor " + String(i+1) + " RAW:"); 
    Serial.println(pingResults[i]);
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
