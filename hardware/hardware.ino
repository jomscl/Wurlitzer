#include <Servo.h> 
#include <avr/pgmspace.h>

const byte PROGMEM charSet[]  = { 65, 32, 16, 10, 11};

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
  /////
  Serial.println(pgm_read_byte_near(charSet+2));
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
  int i=0;
  for (i=100;i<=180;i++){
    myservo.write(i);
    delay(20);
  }
  for (i=180;i<=100;i--){
    myservo.write(i);
    delay(20);
  }
}
