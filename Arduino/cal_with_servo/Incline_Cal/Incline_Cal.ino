const int inclineup=11;
const int inclinedown=10;
const int inclinesense=9;
int inclUP=0;
int inclDOWN=0;




void setup(){
  pinMode(inclineup,INPUT);
  pinMode(inclinedown,INPUT);
  pinMode(inclinesense,OUTPUT);
  
}

void loop(){
  inclUP=digitalRead(inclineup);
  inclDOWN=digitalRead(inclinedown);
  

  if (inclUP==HIGH){
    digitalWrite(inclinesense,HIGH);//this is 10 up pulses and pause
    delay(250);
    digitalWrite(inclinesense,LOW);
    delay(50);
    digitalWrite(inclinesense,HIGH);
    delay(50);
    digitalWrite(inclinesense,LOW);
    delay(50);
    digitalWrite(inclinesense,HIGH);
    delay(50);
    digitalWrite(inclinesense,LOW);
    delay(50);
    digitalWrite(inclinesense,HIGH);
    delay(50);
    digitalWrite(inclinesense,LOW);
    delay(50);
    digitalWrite(inclinesense,HIGH);
    delay(50);
    digitalWrite(inclinesense,LOW);
    delay(3000);}
  else if(inclDOWN==HIGH){
    
  }
}
