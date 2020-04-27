// download de library van https://github.com/AP-Elektronica-ICT/NewPing
// en verwijder andere NewPing libraries

#include <NewPing.h>
#define SONAR_NUM     4
#define MAX_DISTANCE 200
#define PING_INTERVAL 33

#define SAMPLE_LENGTH 10

byte pingResults[SONAR_NUM];
byte pingHistory[SONAR_NUM][SAMPLE_LENGTH];
byte movingAvgResult[SONAR_NUM];

NewPing sonar[SONAR_NUM] = {
  NewPing(12, 11, MAX_DISTANCE),
  NewPing(10, 9, MAX_DISTANCE),
  NewPing(8, 7, MAX_DISTANCE),
  NewPing(6, 5, MAX_DISTANCE)
};

void setup() {
  //pingHistory vullen om te testen
  for (int i = 0; i < SAMPLE_LENGTH; i++) {
    pingHistory[1][i] = 10;
  }
  
  // Setup I2C
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    // Dit is de code om een ping te doen
    pingResults[i] = sonar[i].ping_cm();

    // TODO: code ^^ in pingHistory[][] steken en telkens op te schuiven,
    // First in, first out. (Best met byte shifts gaan werken denk ik,
    // het is al een array van bytes)
    
    // Geef een array van de pingHistory en krijg de moving average er van terug
    movingAvgResult[1] = sonar[1].convert_movingAverage(pingHistory[1]);
    
    delay(PING_INTERVAL);
  }
  SendData();
}

void SendData() {
  // Stuur movingAvgResult[] met I2C
}
