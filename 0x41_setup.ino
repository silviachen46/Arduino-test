#include <Wire.h>


void requestEvent(){
  Wire.write("hello");
  }
  
void setup() {
  Wire.begin(0x41);
  Wire.onRequest(requestEvent);
  

}

void loop() {
  delay(100);
}
