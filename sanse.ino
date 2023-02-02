int a=0;
int b=9;
int i=0;
void setup() {
 Serial.begin(9600);
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);
}

void loop() {
 //float t=pulseIn(2,LOW);
 //Serial.println(t);
while(b<12){
if(digitalRead(2)==1&&digitalRead(3)==1){
  delay(50);
  
  if((digitalRead(2)==0||digitalRead(3)==0)||(digitalRead(2)==0&&digitalRead(3)==0))
  { 
    //if(t>3000000){
      //t=3000000;
      //}
    //float pwm=t/3000000*255;
    a=!a;
    //if(a>0){
     //a=pwm;
      //}
    analogWrite(b,a);
    i++;
    if(i%2==0){
      b++;
      }
    }
  }
  else if(digitalRead(2)==1&&digitalRead(3)==0){
    delay(10);
    if((digitalRead(2)==0&&digitalRead(3)==0)||(digitalRead(2)==0&&digitalRead(3)==1)){
       a=!a;
    digitalWrite(b,a);
    i++;
    if(i%2==0){
      b++;
      }
      }
    } 

    else if(digitalRead(2)==0&&digitalRead(3)==1){
    delay(10);
    if((digitalRead(2)==0&&digitalRead(3)==0)||(digitalRead(2)==1&&digitalRead(3)==0)){
       a=!a;
    digitalWrite(b,a);
    i++;
    if(i%2==0){
      b++;
      }
      }
    } 
}
b=9;
}
