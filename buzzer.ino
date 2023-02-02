
int buzzer=5;
void setup() {
  pinMode(buzzer,OUTPUT);
}

long play(long i){
tone(buzzer,i);
delay(250);
noTone(buzzer);
delay(30);
}

long plays(long n){
tone(buzzer,n);
delay(150);
noTone(buzzer);
delay(5);
}


void loop() {
  long a=261;//do
  long b=294;//re
  long c=330;//mi
  long d=349;//fa
  long e=494;//B
  long f=554;//C#
  long g=622;//D#
  long a1=660;//E
  long b1=740;//F#
  long c1=831;//G#
  long d1=630;//fa
  long e1=988;//B
  long C1=1109;

 play(f);

 play(C1);

 play(c1);

 play(a1);
 
 play(c1);

 play(g);

  play(b1);

   play(a1);

    play(f);

     play(C1);

 play(c1);

 play(a1);

  play(g);

  plays(a1);

  plays(g);

      plays(f);
 
 
      delay(400);
}
