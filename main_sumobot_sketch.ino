#include <stdlib.h> // Include the library for random number generation

int motor2pin2 = 5;
int motor2pin1 = 4;
int motor1pin2 = 3;
int motor1pin1 = 2;

int triggerPin = 6;
int echoPin = 7;

int ENA = 9;
int ENB = 10;

int distance, frontSensVal, backSensVal;

#define frontIR A3
#define backIR A2

//Function Call
float readTime(int triggerPin, int echoPin);
void forward(int speed);
void reverse(int speed);
void turnLeft(int speed);
void turnRight(int speed);
void stop();

//--------------------------SETUP---------------------------
void setup() {
  Serial.begin(9600);
  delay(5000);

  //Left Motor
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);

  //Right Motor 
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1pin1, OUTPUT);

  //Enable PWM
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sensors
  pinMode(frontIR, INPUT);
  pinMode(backIR, INPUT);

  // Seed the random number generator
  randomSeed(analogRead(0));
}

//-------------------------LOOP----------------------------
void loop() {
  frontSensVal = analogRead(frontIR);
  backSensVal = analogRead(backIR);
  distance = readTime(triggerPin, echoPin) * 0.034 / 2;

  if (frontSensVal <= 500) {
    stop();
    delay(50);
    reverse(255); // Reverse at full speed
    delay(500);
  } 
  else if (backSensVal <= 500) { // Check if the back IR sensor detects white ring
    stop();
    delay(50);
    reverse(255); // Reverse at full speed
    delay(500);
  } 
  else if (distance <= 30) { // If an object is detected within 30cm by ultrasonic sensor
    forward(255); // Move forward at full speed
    delay(1500); // Move forward for 1.5 seconds
  } 
  else { // If no object detected within 30cm
    // Generate a random number between 0 and 3
    int randomMovement = random(4);
    
    // Perform random movements
    switch (randomMovement) {
      case 0:
        forward(50); // Move forward at slower speed
        break;
      case 1:
        reverse(50); // Reverse at slower speed
        break;
      case 2:
        turnLeft(50); // Turn left at slower speed
        break;
      case 3:
        turnRight(50); // Turn right at slower speed
        break;
    }
    delay(1500);
    stop(); // Stop after random movement
  }
}

//-------------------------FUNCTIONS-----------------------
void forward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void reverse(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void turnLeft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void turnRight(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void stop() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

float readTime(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);

  return pulseIn(echoPin, HIGH);
}
