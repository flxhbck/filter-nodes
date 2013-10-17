boolean foldOne, foldTwo = false;

void setup(){
 Serial.begin(9600);
 
 pinMode(7, INPUT);
 pinMode(6, INPUT);
}

void loop(){
  foldOne = digitalRead(7);
  foldTwo = digitalRead(6);
  
  Serial.print(foldOne);
  Serial.print( " - ");
  Serial.print(foldTwo);
  Serial.println( " - ");
}
