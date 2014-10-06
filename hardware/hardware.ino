#include <Servo.h> 
#include <avr/pgmspace.h>

const byte PROGMEM datos[]  = { 65, 32, 16, 10, 11};
#define posCambiaDisco 0;

#define pinServo0 A0
#define pinServo1 A1
#define moneda A2
#define a0r 2
#define a0g 3
#define a0b 4
#define a1r 5
#define a1g 6
#define a1b 7
#define bl0 8
#define bl1 9
#define bl2 10
#define bl3 11

Servo sDisco;
Servo sAguja;

bool estadoMoneda=false;

void setup() {
  sDisco.attach(pinServo0,660,2000); // de 0 a 130
  sAguja.attach(pinServo1,660,2000); // 100 a 160 home
  
  // posicion inicial servos
  sDisco.write(0);
  sAguja.write(0);
  
  // Leds
  pinMode(a0r,OUTPUT);
  pinMode(a0g,OUTPUT);
  pinMode(a0b,OUTPUT);
  pinMode(a1r,OUTPUT);
  pinMode(a1g,OUTPUT);
  pinMode(a1b,OUTPUT);
  pinMode(bl0,OUTPUT);
  pinMode(bl1,OUTPUT);
  pinMode(bl2,OUTPUT);
  pinMode(bl3,OUTPUT);
    
  // fotocelda
  pinMode(moneda,INPUT_PULLUP);
  Serial.begin(9600);
  /////
  //Serial.println(pgm_read_byte_near(charSet+2));
}

void loop() {
  // Revisar puerto Serial
  if (Serial.available()){
      unsigned int msg=Serial.read();
      //Serial.println(msg);
      if (msg==255){cambiaDisco();}
    if (msg>13){  
    //if (msg>100){digitalWrite(led13,HIGH);}else{digitalWrite(led13,LOW);}
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

