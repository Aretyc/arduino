
// pin declaration

int white = 5;
int red = 6;        
int green = 9; 
int blue = 10;

// tmie 
 
int time = 10;


void setup() {
  
 // declare pin mode 
 
  pinMode(white, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {

// slow change color (britness)

  
 for(int i = 0 ; i<=255; i++ )
 {
   analogWrite( blue, 255-i);
   analogWrite(red, i);
   delay(time);
 }

  for(int i = 0 ; i<=255; i++ )
 {
   analogWrite( red, 255-i);
   analogWrite(green, i);
   delay(time);
 }
 
 

  for(int i = 0 ; i<=255; i++ )
 {
   analogWrite( green, 255-i);
   analogWrite(blue, i);
   delay(time);
 }
 
}
