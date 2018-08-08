int red = D5; //ok 
int green = D6; // ok 
int blue = D7; // ok 
int white = D8; // ok 

// tmie 
int delayTime = 10;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(white, OUTPUT);
}

void loop() {

// slow change color (britness)

 for(int i = 0 ; i<=255; i++ )
 {
   analogWrite( blue, 255-i);
   analogWrite(red, i);
   delay(delayTime);
 }

  for(int i = 0 ; i<=255; i++ )
 {
   analogWrite( red, 255-i);
   analogWrite(green, i);
   delay(delayTime);
 }
 
 

  for(int i = 0 ; i<=255; i++ )
 {
   analogWrite( green, 255-i);
   analogWrite(blue, i);
   delay(delayTime);
 }
  
 
  
}
