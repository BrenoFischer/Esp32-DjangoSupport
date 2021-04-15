#include <ArduinoJson.h>

#define LED 2

String string_test;
DynamicJsonDocument json_receive(1024);
StaticJsonDocument<200> json_send;

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
      json_send["id"] = "2";
      json_send["type"] = 3;
      json_send["count"] = 2;
      json_send["lat"] = 53.2839936;
      json_send["lng"] = -9.302038;
      json_send["high"] = 10.2;
      serializeJson(json_send, Serial);
      Serial.print("\n");
    }
    else {
      digitalWrite(LED,HIGH);
      json_send["id"] = "2";
      json_send["type"] = 4;
      json_send["count"] = 2;
      json_send["lat"] = 53.2839936;
      json_send["lng"] = -9.302038;
      json_send["high"] = 10.2;
      serializeJson(json_send, Serial);
      Serial.print("\n");
    }
  }
}
