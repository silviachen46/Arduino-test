#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.print("I2C scanner");
  

}

void loop() {
  byte error,address;
  int nDevices;
  Serial.print("Scanning...");
  nDevices=0;
  for(address=1;address<127;address++){
Wire.beginTransmission(address);
error=Wire.endTransmission();}


if(error==0){
Serial.print("I2Cdevice found at address 0x");
if(address<16)
Serial.print("0");
Serial.println(address,HEX);

nDevices++;
}

else if(error==4)
{
  Serial.print("unknown error at address 0x");
  if(address<16)
  Serial.print("0");
  Serial.println(address,HEX);}

  if(nDevices==0)
{Serial.println("No I2C devices found");}
else
{Serial.println("done");
delay(5000);}
}
