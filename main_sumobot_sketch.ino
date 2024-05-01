#include <Ultrasonic.h>

int motor2pin2 = 5;
int motor2pin1 = 4;
int motor1pin2 = 3;
int motor1pin1 = 2;

int triggerPin = 6;
int echoPin = 7;

int ENA = 9;
int ENB = 10;

int distance, frontSensVal, backSensVal;

Ultrasonic ultrasonic(triggerPin, echoPin);

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
}

//-------------------------LOOP----------------------------
void loop() {
  delay(1000);

  distance = ultrasonic.read();

  frontSensVal = analogRead(frontIR);
  backSensVal = analogRead(backIR);

  //For Sensing Outer White Ring
  
  if(frontSensVal <= 500) {
    reverse(255);
    delay(1000);

    turnLeft(255);
    delay(1370);
    
    forward(255);
    delay(1000);
    
    stop();
  }
  if(backSensVal <= 500) {
    forward(255);
    delay(1000);
    
    turnLeft(255);
    delay(2740);
    
    stop();
  }

  if(distance <= 35) {
    do {
      forward(255); 

      distance = ultrasonic.read();
      frontSensVal = analogRead(frontIR);
      backSensVal = analogRead(backIR);

      if (frontIR > 512 || backIR  > 512) { 
        break;
      }
      delay(10);
    }
    while(distance <= 40);
  }
  else {
    turnLeft(60);
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
