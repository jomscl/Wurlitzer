#include <Servo.h> 

#define pinServo A0
#define led13 13
#define moneda 3

Servo myservo;

bool estadoMoneda=false;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(pinServo);
  pinMode(led13,OUTPUT);
  pinMode(moneda,INPUT_PULLUP);
  analogWrite(led13,30);
  Serial.begin(9600);
}

void loop() {
  // Revisar puerto Serial
  if (Serial.available()){
      unsigned int msg=Serial.read();
      //Serial.println(msg);
      if (msg==255){cambiaDisco();}
    if (msg>13){  
    if (msg>100){digitalWrite(led13,HIGH);}else{digitalWrite(led13,LOW);}
    }
  }
  
  // revisar moneda
  if (!digitalRead(moneda)){
    if (!estadoMoneda){
      Serial.write('m');
      delay(40);
      estadoMoneda=true;
    }
  }
  else{
    estadoMoneda=false;
  }
}

void cambiaDisco(){
  myservo.write(100);
  delay(300);
  myservo.write(101);
  delay(300);
}
