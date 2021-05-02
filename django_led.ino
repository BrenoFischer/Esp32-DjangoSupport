#include <ArduinoJson.h>

#define LED 2

String string_test;
int seq;
int teste;
DynamicJsonDocument json_receive(1024);
StaticJsonDocument<256> json_send;

void sendJson();


void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  //digitalWrite(LED,HIGH);
  while(!Serial) {}
}


void loop() {
  while(Serial.available())  
  {
    string_test = Serial.readString( );
    deserializeJson(json_receive, string_test);
    if (json_receive["type"] == 1){
      digitalWrite(LED,LOW);
    }
    else {
      digitalWrite(LED,HIGH);
    }
  }
  if(teste == 500000) {
    JsonObject root = json_send.to<JsonObject>(); 
        
    root["id"] = "1";
    root["type"] = 1;
    root["seq"] = seq++;
    JsonObject payload = root.createNestedObject("payload");
    payload["lat"] = 56.75608;
    payload["lng"] = -9.302038;
    payload["high"] = 10;
    
    serializeJson(root, Serial);
    Serial.print("\n");
    /*sendJson();*/
    teste = 0; 
  }
  teste++;
}


void sendJson() {
  json_send["serial"] = "connected";
  
  JsonObject payload = json_send.createNestedObject("payload");
  payload["id"] = "1";
  payload["type"] = 1;
  payload["count"] = 50000;
  payload["lat"] = 56.75608;
  payload["lng"] = -9.302038;
  payload["high"] = 10;
  
  serializeJson(json_send, Serial);
  Serial.print("\n");
}
