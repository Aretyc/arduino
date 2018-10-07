#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

ESP8266WebServer server;

// Wi-Fi sittings declaration 
char* ssid = "tl-wr740n";
char* password = "madagaskar123";

IPAddress ip(192, 168, 0, 110); //static ip
IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(192, 168, 0, 1);  //DNS
String deviceName = "arduinoLed"; 


int ledRed = D6; //ok 
int ledGreen = D5; // ok 
int ledBlue = D7; // ok 
int ledWhite = D8; // ok 

String status = "off";

int animation = 0;
int animTime = 0;



void setup()
{
  // pin mode 
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledWhite, OUTPUT);



  WiFi.hostname(deviceName);
  WiFi.config(ip, dns, gateway, subnet); 
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

 // server.on("/",htmlContent);
  
  
  server.on("/dataIn", HTTP_POST, dataIn);
  server.on("/dataOut",HTTP_POST, dataOut);
  server.begin();
 
}


int loopIndex = 0;

void loop()
{
 server.handleClient();
  if(animation==1)
   {
    //rainbow();
    if(loopIndex>=3){loopIndex=0;}
    if(loopIndex==0){rainbow(ledBlue,ledRed,animTime);}
    if(loopIndex==1){rainbow(ledRed,ledGreen,animTime);}
    if(loopIndex==2){rainbow(ledGreen,ledBlue,animTime);}

    loopIndex++;
   }
 
 if(animation==2) 
 {
     analogWrite( ledRed, 200);
     delay(100);
     analogWrite( ledRed, 0);
     delay(100);
 }
  if(animation==3)
  {

   if(loopIndex>=3){loopIndex=0;}
    if(loopIndex==0){blikRgb(ledBlue,animTime);}
    if(loopIndex==1){blikRgb(ledRed,animTime);}
    if(loopIndex==2){blikRgb(ledGreen,animTime);}
    loopIndex++;  
  }
 
 
}

void dataIn()
{
 

  server.sendHeader("Access-Control-Allow-Origin", "*");
  
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  
  String red = jObject["r"];
  String green = jObject["g"];
  String blue = jObject["b"];
  String white = jObject["w"];
  String animTemp = jObject["animation"];
  String animTimeTemp = jObject["animTime"];
  server.send(204,"");

  animation = animTemp.toInt();
  animTime = animTimeTemp.toInt();
  //if(animTime>0){status="off";}
  Serial.print("animation: ");
  Serial.println(animation);
  
  Serial.print("animation tmie: ");
  Serial.println(animTime);

  
  
  
  color(red.toInt(),green.toInt(),blue.toInt(),white.toInt());
 
   
}
void dataOut() 
{
 String temp;
 server.sendHeader("Access-Control-Allow-Origin", "*");
 temp="{\"status\":\""+status+"\"}";
 server.send(200,"aplication/json",temp);
 server.send(204,"");
  
}

void color(int r,int g,int b,int w)
{
  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
  Serial.println(w);
  Serial.println(status);

  if(r==0&g==0&b==0&w==0&animTime<1)
  {
    status="off";
  }
  else
  {
    status="on";
  }
  
  analogWrite( ledRed, r);
  analogWrite( ledGreen, g);
  analogWrite( ledBlue, b);
  analogWrite( ledWhite, w);
  
  if(r>250){digitalWrite(ledRed, HIGH);}
  if(g>250){digitalWrite(ledGreen, HIGH);}
  if(b>250){digitalWrite(ledBlue, HIGH);}
  if(w>250){digitalWrite(ledWhite, HIGH);}
 
}

void rainbow(int led1,int led2,int time)
{

  for(int i = 0 ; i<=255; i+=5 )
 {
  
   analogWrite(led1, 255-i);
   analogWrite(led2, i);
   delay(time);
 }
}
void blikRgb(int led,int time)
{
  
  digitalWrite(led, HIGH);                                                    
  delay(time);                     
  digitalWrite(led, LOW);  
  delay(time); 
}




