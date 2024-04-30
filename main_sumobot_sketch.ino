int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;

int triggerPin = 6;
int echoPin = 7;

int ENA = 9;
int ENB = 10;

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
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  //Right Motor 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Enable PWM
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sensors
  pinMode(frontIR, INPUT);
  pinMode(backIR, INPUT);
}

//-------------------------LOOP----------------------------
void loop() {
  delay(5000);
  int frontSensVal = analogRead(frontIR);
  int backSensVal = analogRead(backIR);

  int distance = readTime(triggerPin, echoPin) * 0.01715;

  while(distance <= 20) {
    forward(255);

    if (frontSensVal <= 500 || backSensVal <= 500) {
        break;
    }
  }

  // For Sensing Outer White Ring
  if(backSensVal <= 500) {
    stop();
    delay(50);
    forward(255);
    delay(750);
  }
  if(frontSensVal <= 500) {
    stop();
    delay(50);
    reverse(255);
    delay(1000);
    turnLeft(255);
    delay(50);
    forward(255);
  }
}

//-------------------------FUNCTIONS-----------------------
void forward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reverse(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  
}

void turnRight(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
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