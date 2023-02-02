float dt=0.01;
int esum=0;
float error1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12,OUTPUT);//led
  pinMode(7,OUTPUT);//stby
  pinMode(8,OUTPUT);//neg
  pinMode(9,OUTPUT);//posi
  pinMode(10,OUTPUT);//pwm
}

float pid(float error){
    float kp=300;
    float ki=100;
    float kd=40;
    float ediff=(error1-error)/dt;
    float output=kp*error+esum*ki+ediff*kd;
    return output;
    }
    
void loop() {
  digitalWrite(7,HIGH);
 float eaim=analogRead(A1);
  float enow=analogRead(A0);  
  eaim=eaim/1024*5;
  enow=enow/1024*5;
  Serial.print("ENOW");
  Serial.println(enow);
//  delay(300);
  Serial.print("eaim");
  Serial.println(eaim);

  float error=eaim-enow;
  Serial.print("error");
  Serial.println(error);
 
  if(error>0){
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
     Serial.print("right");
    }
  else if(error<0){
     digitalWrite(9,LOW);
     digitalWrite(8,HIGH);
      Serial.print("left");
      } 
  esum+=error*dt;
  float value=pid(error);
  Serial.print("value");
  Serial.println(value);
  if(value>255){
    value=255;
    }
  float error1=error;
  value=abs(value);
  analogWrite(10,value);
  delay(10);
 }
