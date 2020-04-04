#define MOTOR1_ENABLE 2
#define MOTOR1_A 3
#define MOTOR1_B 4

#define MOTOR2_ENABLE 5
#define MOTOR2_A 6
#define MOTOR2_B 7

void setup() {
  pinMode(MOTOR1_ENABLE,OUTPUT);
  pinMode(MOTOR1_A,OUTPUT);
  pinMode(MOTOR1_B,OUTPUT);
  digitalWrite(MOTOR1_ENABLE,HIGH);

  pinMode(MOTOR2_ENABLE,OUTPUT);
  pinMode(MOTOR2_A,OUTPUT);
  pinMode(MOTOR2_B,OUTPUT);
  digitalWrite(MOTOR2_ENABLE,HIGH);
}

void loop() {
  // 5 sec forwards
  Forwards(5000);
  //360 degree turn
  Left(5000);
  // 5 sec backwards
  Backwards(5000);
  //180 degree turn
  Right(2500);

  delay(1000);
}

void Forwards(int duration)
{
  //Left Track
  digitalWrite(MOTOR1_A, HIGH); 
  digitalWrite(MOTOR1_B, LOW);
  //Right Track
  digitalWrite(MOTOR2_A, LOW);
  digitalWrite(MOTOR2_B, HIGH);
  delay(duration);
  Reset();
}

void Backwards(int duration)
{
  //Left Track
  digitalWrite(MOTOR1_A, LOW);
  digitalWrite(MOTOR1_B, HIGH);
  //Right Track
  digitalWrite(MOTOR2_A, HIGH); 
  digitalWrite(MOTOR2_B, LOW);
  delay(duration);
  Reset();
}

void Left(int duration)
{
  //Left Track
  digitalWrite(MOTOR1_A, HIGH); 
  digitalWrite(MOTOR1_B, LOW);
  //Right Track
  digitalWrite(MOTOR2_A, HIGH); 
  digitalWrite(MOTOR2_B, LOW);
  delay(duration);
  Reset();
}

void Right(int duration)
{
  //Left Track
  digitalWrite(MOTOR1_A, LOW);
  digitalWrite(MOTOR1_B, HIGH);
  //Right Track
  digitalWrite(MOTOR2_A, LOW);
  digitalWrite(MOTOR2_B, HIGH);
  delay(duration);
  Reset();
}

void Reset()
{
  //Left Track
  digitalWrite(MOTOR1_A, LOW);
  digitalWrite(MOTOR1_B, LOW);
  //Right Track
  digitalWrite(MOTOR2_A, LOW);
  digitalWrite(MOTOR2_B, LOW);
  delay(100);
}
