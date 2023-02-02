#include "DHT11.h"
DHT11 dht; 

void setup() {
Serial.begin(9600);
pinMode(4,OUTPUT);
}

void loop() {
  int i=dht.read(4);
  int temp=dht.temperature;
  int humi=dht.humidity;
  Serial.println(humi);
  Serial.println(temp);
  delay(1000);
}
