// D2 pin naar 1,2EN van de SN754410, D3 pin naar 1A, D4 pin naar 2A
#define M1_EN 2
#define M1_A 3
#define M1_B 4

// D5 pin naar 3,4EN van de SN754410, D6 pin naar 3A, D7 pin naar 4A
#define M2_EN 5
#define M2_A 6
#define M2_B 7


void setup() {
  pinMode(M1_EN, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  
  pinMode(M2_EN, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M2_B, OUTPUT);
  
  digitalWrite(M1_EN, HIGH);
  digitalWrite(M2_EN, HIGH);
}

void loop() {
  // De waarden van deze parameters hebben een impact op hoe de tank rijd,
  // bv bij een oppervlak met meer weerstand moet er langer gedraaid worden
  
  // 5 sec voorwaarts
  Forwards(5000);
  // 360° draaien
  Left(5000);
  // 5 sec achterwaarts
  Backwards(5000);
  // 180° draaien
  Right(2500);

  delay(3000);
}

void Forwards(int duration)
{
  //Left Track
  digitalWrite(M1_A, HIGH); 
  digitalWrite(M1_B, LOW);
  //Right Track
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, HIGH);
  delay(duration);
  Reset();
}

void Backwards(int duration)
{
  // Left Track
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
  // Right Track
  digitalWrite(M2_A, HIGH); 
  digitalWrite(M2_B, LOW);
  delay(duration);
  Reset();
}

void Left(int duration)
{
  // Left Track
  digitalWrite(M1_A, HIGH); 
  digitalWrite(M1_B, LOW);
  // Right Track
  digitalWrite(M2_A, HIGH); 
  digitalWrite(M2_B, LOW);
  delay(duration);
  Reset();
}

void Right(int duration)
{
  // Left Track
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
  // Right Track
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, HIGH);
  delay(duration);
  Reset();
}

void Reset()
{
  // Left Track
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, LOW);
  // Right Track
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, LOW);
  delay(100);
}
