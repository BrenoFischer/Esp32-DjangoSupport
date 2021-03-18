#define NUM_ARR 1
#include <ArduinoJson.h>

typedef struct {
  String id;
  int type;
  int count;
  double lat;
  double lng;
  float high;
} MyJson;

MyJson arr[NUM_ARR];
String  string_test;
int seq;
int teste;
DynamicJsonDocument json_receive(1024);
StaticJsonDocument<200> json_send;

void sendJson();
void readJson();


void setup() {
  seq = 0;
  teste = 0;
  arr[0].id = "1"; arr[0].type = 1; arr[0].lat = 53.2839936; arr[0].lng = -9.302038; arr[0].high = 10.2;
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
  json_send["id"] = arr[0].id;
  json_send["type"] = arr[0].type;
  json_send["count"] = seq++;
  json_send["lat"] = arr[0].lat;
  json_send["lng"] = arr[0].lng;
  json_send["high"] = arr[0].high;
  serializeJson(json_send, Serial);
  Serial.println();
}

void receiveJson() {
  while(Serial.available()){
    string_test = Serial.readString();
    deserializeJson(json_receive, string_test);
    String id = json_receive["id"];
    int type = json_receive["type"];
    int count = json_receive["count"];
    float lat = json_receive["lat"];
    float lng = json_receive["lng"];
    float high = json_receive["high"];

    Serial.print("{\"id\": \"" + id + "\", ");
    Serial.print("\"type\": ");
    Serial.print(type);
    Serial.print(", \"count\": ");
    Serial.print(count);
    Serial.print(", \"lat\": ");
    Serial.print(lat);
    Serial.print(", \"lng\": ");
    Serial.print(lng);
    Serial.print(", \"high\": ");
    Serial.print(high);
    Serial.println("}");
  }
}
