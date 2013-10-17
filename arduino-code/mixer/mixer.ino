int redDistance = 0;
int greenDistance = 0;
int blueDistance = 0;


void setup(){
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
    
    initializeRGBs();
    
    setRedRGB(100, 0, 0);
    setGreenRGB(0, 100, 0);
    setBlueRGB(0, 0, 100);
    
    setOutputRGB(255,255,255);

}

void loop(){
  
  redDistance = analogRead(0);
  greenDistance = analogRead(2);
  blueDistance = analogRead(5);
  
  setOutputRGB( map(redDistance, 0, 600, 0, 255),
                map(greenDistance, 0, 600, 0, 255),
                map(blueDistance, 0, 600, 0, 255)
              );
              
  
  Serial.print(redDistance);
  Serial.print(" - ");
  Serial.print(greenDistance);
  Serial.print(" - ");
  Serial.print(blueDistance);
  Serial.println(" - ");
  
  //setBlueRGB(0,0,map(greenDistance, 0, 600, 0, 255));
}

void setRedRGB(int r, int g, int b){
  //led is rgb but only red is hooked up to pwm.
  analogWrite(3, r);
  
  if (g > 0) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  
  if (b > 0) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
  
}

void setGreenRGB(int r, int g, int b){
  //led is rgb but only green is hooked up to pwm.
  if (r > 0) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  
  analogWrite(11, g);
  
  if (b > 0) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }
}

void setBlueRGB(int r, int g, int b){
  //led is rgb but only blue is hooked up to pwm.
  
  if (r > 0) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  
  if (g > 0) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
  
  analogWrite(10, b);

}


void setOutputRGB(int r, int g, int b){
  //5,6,9
  analogWrite(5, r);
  analogWrite(6, g);
  analogWrite(9, b);
  
}


void initializeRGBs(){
  for(int i = 2; i <= 13; i++){
    pinMode(i, OUTPUT);
  }
}  
