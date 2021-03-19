#include <ArduinoJson.h>

String  string_test;
int seq;
int teste;
DynamicJsonDocument json_receive(1024);
StaticJsonDocument<200> json_send;
StaticJsonDocument<200> json_echo_send;

void sendJson();
void readJson();


void setup() {
  seq = 0;
  teste = 0;

  Serial.begin(115200);
  while(!Serial) {}
}

void loop() {
  receiveJson();
  if(teste == 500000) {
    sendJson();
    teste = 0; 
  }
  teste++;
}

void sendJson() {
  json_send["id"] = "2";
  json_send["type"] = 1;
  json_send["count"] = seq++;
  json_send["lat"] = 53.2839936;
  json_send["lng"] = -9.302038;
  json_send["high"] = 10.2;
  serializeJson(json_send, Serial);
  Serial.print("\n");
}

void receiveJson() {
  while(Serial.available()){
    string_test = Serial.readString();
    deserializeJson(json_receive, string_test);
    json_echo_send["id"] = json_receive["id"];
    json_echo_send["type"] = 2;
    json_echo_send["count"] = json_receive["count"];
    json_echo_send["lat"] = json_receive["lat"];
    json_echo_send["lng"] = json_receive["lng"];
    json_echo_send["high"] = json_receive["high"];

    serializeJson(json_echo_send, Serial);
    Serial.print("\n");

    //Serial.print("{\"id\": \"" + id + "\", ");
    //Serial.print("\"type\": ");
    //Serial.print(type);
    //Serial.print(", \"count\": ");
    //Serial.print(count);
    //Serial.print(", \"lat\": ");
    //Serial.print(lat);
    //Serial.print(", \"lng\": ");
    //Serial.print(lng);
    //Serial.print(", \"high\": ");
    //Serial.print(high);
    //Serial.print("}\n");
  }
}
