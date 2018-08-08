int red = D5; //ok 
int green = D6; // ok 
int blue = D7; // ok 
int white = D8; // ok 


void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(white, OUTPUT);


}

void loop() {

  digitalWrite(white, HIGH);                                                    
  delay(1000);                     
  digitalWrite(white, LOW);  
  delay(2000); 
  
  digitalWrite(red, HIGH);                                                    
  delay(1000);                     
  digitalWrite(red, LOW);  
  delay(2000); 
  
  digitalWrite(green, HIGH);                                                    
  delay(1000);                     
  digitalWrite(green, LOW);  
  delay(2000);    

  digitalWrite(blue, HIGH);                                                    
  delay(1000);                     
  digitalWrite(blue, LOW);  
  delay(2000);  
  
  
}
