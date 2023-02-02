float dt=0.01;
int esum=0;
float error1;
void setup() {
  Serial.begin(9600);
  pinMode(12,OUTPUT);//led
  pinMode(7,OUTPUT);//stby
  pinMode(8,OUTPUT);//neg
  pinMode(9,OUTPUT);//posi
  pinMode(10,OUTPUT);//pwm
  }  
float pid1(float error){
    float kp=50;
    float ki=25;
    float kd=10;
    float ediff=(error1-error)/dt;
    float output=kp*error+esum*ki+ediff*kd;
    return output;
    }
    
float pid2(float error){
    float kp=30;
    float ki=15;
    float kd=8;
    float ediff=(error1-error)/dt;
    float output=kp*error+esum*ki+ediff*kd;
    return output;
    }

 
void loop(){
  digitalWrite(7,HIGH);
    label1:
 float eaim=analogRead(A0);
  eaim=eaim/1024*5;
  delay(500);
  float eaim1=analogRead(A0);
  eaim1=eaim1/1024*5;
  float edif=(eaim1-eaim)/eaim1;
  edif=abs(edif);
   Serial.print("edif");
   Serial.println(edif);
  if(edif>0.005){
    goto label1;
  }

eaim=analogRead(A0);//step 3
eaim=eaim/1024*5; 
Serial.print("eaim");
Serial.println(eaim);

float enow=analogRead(A1); 
float enow1=(enow/1024)*5;  
float error=eaim-enow1;
Serial.print("error");
Serial.println(error);
if(error>0){
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    }
  else if(error<0){
     digitalWrite(9,LOW);
     digitalWrite(8,HIGH);
      } 
      error=abs(error);
if(error>0.05){
  label2:
  if(error>1.0){
while(1){
float enow=analogRead(A1); 
float enow1=enow/1024*5;  
float error=eaim-enow1;
error=abs(error);
Serial.print("error");
Serial.println(error);
  esum+=error*dt;
  float value=pid1(error);
  value=abs(value);
   Serial.print("PID1 value");
   Serial.println(value);
   float error1=error;
  if(value>250){
    value=250;
    }
  analogWrite(10,value);
  delay(10);
  if(error<0.02){
    goto label1;
    }
  else{
    goto label2;
    }
  }}
else{
while(1){
float enow=analogRead(A1); 
float enow1=enow/1024*5;  
float error=eaim-enow1;
Serial.print("error");
Serial.println(error);
  esum+=error*dt;
  float value=pid2(error);
   value=abs(value);
   Serial.print("PID2 value");
  Serial.println(value);
  float error1=error;
  if(value>250){
    value=250;
    }
    
  analogWrite(10,value);
  delay(10);
  if(error<0.02){
    goto label1;
    }
  else{
    goto label2;
    }
  }
}}
 else{
    goto label1;
    }
 }
 
