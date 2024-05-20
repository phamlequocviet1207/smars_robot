#include <AFMotor.h>
#include <Servo.h> 

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int TRIG_PIN = A0;
int ECHO_PIN = A1;
int MAX_SPEED = 100;

Servo myservo;

double distance = 100;

double distanceR, distanceL;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(10);
  myservo.write(75);
  motorStop();
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  // distanceR = lookRight();
  // Serial.println(distanceR);
  // delay(1000);
  // distanceL = lookLeft();
  // Serial.println(distanceL);
  // delay(1000);
  if(distance<=20){
    motorStop();
    delay(100);
    runBackward();
    delay(300);
    motorStop();
    delay(200);
    distanceR = lookRight();
    Serial.println(distanceR);
    delay(200);
    distanceL = lookLeft();
    Serial.println(distanceL);
    delay(200);

    if(distanceR>=distanceL){
      turnRight();
      motorStop();
    }
    else{
      turnLeft();
      motorStop();
    }
  }
  else{
    runForward2();
  }

  distance = measure();
  Serial.println(distance);
//  delay(1000);
}
void motorStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void runForward(){
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);  
  for (int speedSet = 0; speedSet < MAX_SPEED; speedSet +=1){
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void runForward2(){
  int speedSet = 100;
  motor1.setSpeed(speedSet);
  motor2.setSpeed(speedSet);
  motor3.setSpeed(speedSet);
  motor4.setSpeed(speedSet);

  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);  
  
}

void runBackward(){
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);  
  for (int speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnLeft(){
  motor1.setSpeed(60);
  motor2.setSpeed(60);
  motor3.setSpeed(60);
  motor4.setSpeed(60);
  motor1.run(FORWARD);
  motor4.run(FORWARD);
  motor3.run(BACKWARD);
  motor2.run(BACKWARD);     
  delay(750);
  // motor1.run(FORWARD);      
  // motor4.run(FORWARD);
  // motor3.run(FORWARD);
  // motor2.run(FORWARD);
}

void turnRight(){
  motor1.setSpeed(60);
  motor2.setSpeed(60);
  motor3.setSpeed(60);
  motor4.setSpeed(60);
  motor1.run(BACKWARD);     
  motor4.run(BACKWARD);  
  motor3.run(FORWARD);
  motor2.run(FORWARD);   
  delay(750);
  // motor1.run(FORWARD);     
  // motor4.run(FORWARD);
  // motor3.run(FORWARD);
  // motor2.run(FORWARD);
}

int lookRight()
{
    myservo.write(0); 
    delay(500);
    int distance = measure();
    delay(100);
    myservo.write(75); 
    return distance;
}
int lookLeft()
{
    myservo.write(160); 
    delay(500);
    int distance = measure();
    delay(100);
    myservo.write(75); 
    return distance;
    delay(100);
}

double measure(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  double duration = pulseIn(ECHO_PIN, HIGH);
  double distance = 0.017 * duration;
  // Serial.println(distance);
  return distance;

}

