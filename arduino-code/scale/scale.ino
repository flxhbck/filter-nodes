#include <Servo.h>

#define ACCEL_PIN A1
#define SERVO_PIN 10

Servo wServo;  // create servo object to control a servo  

int accelValue = 0;
int servoPos = 90;

void setup() 
{ 
  Serial.begin(9600);
  
  pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);
  
  wServo.attach(SERVO_PIN, 500, 2400); 
  wServo.write(90);
  
  accelValue = analogRead(ACCEL_PIN);
  
} 
 
 
void loop() 
{ 
  
  accelValue = (accelValue*0.97) + (analogRead(ACCEL_PIN)*0.03);
  
  Serial.println(accelValue);
  
  servoPos = map(accelValue, 449, 557, 140, 30);
  
  wServo.write(servoPos);
  
  //Serial.println(servoPos);
  
  /*
  wServo.write(0);
  
  delay(10000);
  
  wServo.write(150);
  
  delay(10000);
  */
  
  // determine whether or not scale is being moved actively
  // IDEA: speed of the movement.
  
  // if moving, follow accelValue

}
