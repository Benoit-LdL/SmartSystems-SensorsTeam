// download de library van https://github.com/AP-Elektronica-ICT/NewPing
// en verwijder andere NewPing libraries

#include <NewPing.h>

#define SONAR_NUM     4
#define MAX_DISTANCE 200
#define PING_INTERVAL 60

#define SAMPLE_LENGTH 10

uint8_t pingResults[SONAR_NUM];
uint8_t pingHistory[SONAR_NUM][SAMPLE_LENGTH];

NewPing sonar[SONAR_NUM] = {
  NewPing(12, 11, MAX_DISTANCE), // sensor 1
  NewPing(10, 9, MAX_DISTANCE), // sensor 2
  NewPing(8, 7, MAX_DISTANCE), // sensor 3
  NewPing(6, 5, MAX_DISTANCE) // sensor 4
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (byte i = 0; i < SONAR_NUM; i++) {
    pingResults[i] = sonar[i].ping_cm();
    pingHistory[i][0] = pingResults[i];
    
    for (byte y = 9; y > 0; y--) {
      pingHistory[i][y] = pingHistory[i][y-1];
    }
    delay(PING_INTERVAL);
  }

  LogRawInSerial();
  LogHistoryInSerial(3);
}

void LogRawInSerial() {
  for (byte i = 0; i < SONAR_NUM; i++) {
    Serial.print("Sensor " + String(i+1) + " RAW:"); 
    Serial.println(pingResults[i]);
  }
  Serial.println("---------------------");
}

void LogHistoryInSerial(byte sensorNr) {
  Serial.print("Sensor 1 RAW:"); 
  Serial.println(pingResults[sensorNr]);
  for (byte i = 0; i < SAMPLE_LENGTH; i++) {
    Serial.print(pingHistory[sensorNr][i]); 
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("---------------------");
}
