int white = 5;
int red = 6;        
int green = 9; 
int blue = 10;

// tmie 
 
int time = 30;


void setup() {
   // declare pin mode 
 
  pinMode(white, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

}

void loop() {


  analogWrite( white, 255);
  delay(time);
  analogWrite(white, 0);
  delay(time);
  

}
