#define RED 0
#define GREEN 2
#define BLUE 5

float redDistance, greenDistance, blueDistance = 0;
float oRedDistance, oGreenDistance, oBlueDistance = 0;



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
  
  redDistance = float(0.1f * float(readValue(RED))) + float(0.9f * float(oRedDistance));
  greenDistance = float(0.1f * float(readValue(GREEN))) + float(0.9f * float(oGreenDistance));
  blueDistance = float(0.1f * float(readValue(BLUE))) + float(0.9f * float(oBlueDistance));
  
  setOutputRGB( redDistance, greenDistance, blueDistance );
              
  
  Serial.print(redDistance);
  Serial.print(" - ");
  Serial.print(greenDistance);
  Serial.print(" - ");
  Serial.println(blueDistance);
}



int readValue(int cVal)
{
  int temp = 0;
  
  if (cVal == RED){
    oRedDistance = redDistance;
    temp = map( analogRead(cVal) , 230 , 480 , 0 , 255);
  } else if (cVal == GREEN){
    oGreenDistance = greenDistance;
    temp = map( analogRead(cVal) , 220 , 520 , 0 , 255);
  } else if (cVal == BLUE){
    oBlueDistance = blueDistance;
    temp = map( analogRead(cVal) , 200 , 460 , 0 , 255);
  }
  
  (temp > 255) ? (temp = 255) : (temp = temp);
  (temp < 0) ? (temp = 0) : (temp = temp);
  
  return temp;
}

void setRedRGB(int r, int g, int b)
{
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
