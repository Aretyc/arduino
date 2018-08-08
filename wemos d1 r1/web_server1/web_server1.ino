#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>

ESP8266WebServer server;


char* ssid = "tl-wr740n";
char* password = "madagaskar123";

int ledRed = D5; //ok 
int ledGreen = D6; // ok 
int ledBlue = D7; // ok 
int ledWhite = D8; // ok 

String status = "off";





void setup()
{
  // pin mode 
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledWhite, OUTPUT);


  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",htmlContent);

  server.on("/displaydata", HTTP_OPTIONS, displayDataOptions);
  server.on("/displaydata", HTTP_POST, displayData);

  server.begin();
 
}

void htmlContent()
{
 String temp;
// temp ="<div>";
 temp+=status;
// temp+="</div>";
// server.client(temp);

 server.send(200,"text/plain",temp);
 
}


void loop()
{
 server.handleClient();
}

void toggleLED()
{
 // digitalWrite(pin_led,!digitalRead(pin_led));
 // server.send(204,"");
}

void displayDataOptions()
{
  server.sendHeader("Access-Control-Allow-Origin","*");
  //server.send(204,"");
  server.send(200,"");
}

void displayData()
{
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);

  String red = jObject["r"];
  String green = jObject["g"];
  String blue = jObject["b"];
  String white = jObject["w"];
  
  

  
  color(red.toInt(),green.toInt(),blue.toInt(),white.toInt());
  //server.send(204,"");
}

void color(int r,int g,int b,int w)
{
  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
  Serial.println(w);
  
  analogWrite( ledRed, r);
  analogWrite( ledGreen, g);
  analogWrite( ledBlue, b);
  analogWrite( ledWhite, w);
  
  if(r>250){digitalWrite(ledRed, HIGH);}
  if(g>250){digitalWrite(ledGreen, HIGH);}
  if(b>250){digitalWrite(ledBlue, HIGH);}
  if(w>250){digitalWrite(ledWhite, HIGH);}
  
}




