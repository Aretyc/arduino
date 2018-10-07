#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

ESP8266WebServer server;


char* ssid = "tl-wr740n";
char* password = "madagaskar123";

IPAddress ip(192, 168, 0, 110); //static ip
IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(192, 168, 0, 1);  //DNS
String deviceName = "pokuj światło"; 

String power = "on";


// 

int switchIn = D8; 


void setup() {


// pin mode 
  
  pinMode(switchIn , OUTPUT);
  digitalWrite(switchIn, HIGH);

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
  dataOut();

}


void loop() {
server.handleClient();
}


void dataIn()
{
 

  server.sendHeader("Access-Control-Allow-Origin", "*");
  
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  String status = jObject["status"];
  
  server.send(204,"");

  Serial.print(status);

  power = status;  
 if(status=="off"){

    digitalWrite(switchIn,LOW);
  }
  else
  {
        digitalWrite(switchIn,HIGH);     
  }

}

void dataOut() 
{
 String temp;
 server.sendHeader("Access-Control-Allow-Origin", "*");
 temp="{\"status\":\""+power+"\"}";
 server.send(200,"aplication/json",temp);
 server.send(204,"");
}
