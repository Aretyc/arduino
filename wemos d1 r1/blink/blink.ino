
int ledPin = D5;

void setup() {
  pinMode(ledPin, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}
 
void loop() {
  digitalWrite(ledPin, LOW);                                                          
  delay(1000);                     
  digitalWrite(ledPin, HIGH);  
  delay(2000);                    
}
