#include <Servo.h>
//#include <NewPing.h>



const int trigPin1 = 10, echoPin1 = 11;
const int trigPin2 = 3, echoPin2 = 4;

const int laser_1 = 13;
const int laser_2 = 6;
int led_R = A0, led_G = A1, buzz = A2;

Servo servo1, servo2;

int angle1 = 0, angle2 = 0;
bool dir1 = true, dir2 = false;  // direction flags

unsigned long lastMoveTime = 0;
const unsigned long moveInterval = 30; // ms between movements

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(laser_1, OUTPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(laser_2, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(buzz, OUTPUT);

  servo1.attach(12);
  servo2.attach(5);
  Serial.begin(9600);
  digitalWrite(led_G, HIGH);

}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH,25000); // 20ms timeout

  int distance = duration * 0.034 / 2;
  return (duration == 0) ? -1 : distance;
}

void loop() {
  if (millis() - lastMoveTime >= moveInterval) {
    lastMoveTime = millis();

    // Servo 1 scanning
    servo1.write(angle1);
    int d1 = getDistance(trigPin1, echoPin1);
    Serial.print("S1: "); 
    Serial.print(angle1); 
    Serial.print(","); 
    Serial.print(d1);
    
    if (d1 > 0 && d1 <= 25) {
      servo2.write(angle1);
      delay(100);
      digitalWrite(laser_1, HIGH);
      digitalWrite(led_G, LOW);
      digitalWrite(led_R, HIGH);
      digitalWrite(buzz, HIGH);

    } 
    
    else {
      digitalWrite(led_G, HIGH);
      digitalWrite(laser_1, LOW);
      digitalWrite(led_R, LOW);
      digitalWrite(buzz, LOW);

    }
    

     /*  
    // Continuously follow object until it moves out of range
    while (d1 > 0 && d1 <= 10) {
      servo1.write(angle1);
      delay(1);
      digitalWrite(laser_1, HIGH);
      digitalWrite(led_R, HIGH);
      digitalWrite(buzz, HIGH);
      digitalWrite(led_G, LOW);

      d1 = getDistance(trigPin1, echoPin1);
      if (d1 > 10) {
        digitalWrite(laser_1, LOW);
        digitalWrite(led_R, LOW);
        digitalWrite(buzz, LOW);
        digitalWrite(led_G, HIGH);
        break;
      }
    }
    */

    // update angle1
    if (dir1) angle1++;
    else angle1--;
    if (angle1 >= 180 || angle1 <= 0) dir1 = !dir1;

    // Servo 2 scanning
    servo2.write(angle2);
    int d2 = getDistance(trigPin2, echoPin2);
    Serial.print("\t S2: "); 
    Serial.print(angle2); 
    Serial.print(","); 
    Serial.print(d2); 
    Serial.println(".");
    
    if (d2 > 0 && d2 <= 25) {
      servo2.write(angle2);
      delay(100);
      digitalWrite(laser_2, HIGH);
      digitalWrite(led_R, HIGH);
      digitalWrite(led_G, LOW);
      digitalWrite(buzz, HIGH);
    } 

    
    else {
      digitalWrite(led_G, HIGH);
      digitalWrite(laser_2, LOW);
      digitalWrite(led_R, LOW);
      digitalWrite(buzz, LOW);
    } 
    
    
    /*
     // Continuously follow object until it moves out of range
    while (d2 > 0 && d2 <= 10) {
      servo1.write(angle2);
      delay(10);
      digitalWrite(laser_2, HIGH);
      digitalWrite(led_R, HIGH);
      digitalWrite(buzz, HIGH);
      digitalWrite(led_G, LOW);

      d2 = getDistance(trigPin2, echoPin2);
      if (d2 > 10) {
        digitalWrite(laser_2, LOW);
        digitalWrite(led_R, LOW);
        digitalWrite(buzz, LOW);
        digitalWrite(led_G, HIGH);
        break;
      }
    }
    */
    
    // update angle2
    if (dir2) angle2--;
    else angle2++;
    if (angle2 >= 180 || angle2 <= 0) dir2 = !dir2;
  }
}
