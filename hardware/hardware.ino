#include <Servo.h> 
#include <avr/pgmspace.h>

const byte PROGMEM datos[]  = { 65, 32, 16, 10, 11};
#define posCambiaDisco 0;

#define pinServo0 A0
#define pinServo1 A1
#define moneda A2
#define a0r 6
#define a0g 7
#define a0b 8
#define a1r 9
#define a1g 10
#define a1b 11
#define bl0 2
#define bl1 3
#define bl2 4
#define bl3 5

Servo sDisco;
Servo sAguja;

#define homeAguja 160
#define finAguja 100
#define homeDisco 5
#define finDisco 130

bool estadoMoneda=false;
byte secuenciaBl=0;
byte vbl0=0;
byte vbl1=0;
byte vbl2=0;
byte vbl3=0;

byte secuenciaRgb0=0;
byte va0r=0;
byte va0g=0;
byte va0b=0;

byte secuenciaRgb1=0;
byte va1r=0;
byte va1g=0;
byte va1b=0;

boolean sonando=false;

void setup() {
  sDisco.attach(pinServo0,660,2000); // de 0 a 130
  sAguja.attach(pinServo1,660,2000); // 100 a 160 home
  
  // posicion inicial servos
  sAguja.write(homeAguja);
  delay(500);
  sDisco.write(homeDisco);
  
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
  
   randomSeed(analogRead(4));
  //cambiaDisco();
  /////
  //Serial.println(pgm_read_byte_near(charSet+2));
}

void loop() {
  // Revisar puerto Serial
  if (Serial.available()){
      unsigned int msg=Serial.read();
      
      if (msg==255){cambiaDisco();}
      
      if (secuenciaBl<25){
         vbl0=msg;
         if (msg>50){
           digitalWrite(bl3,HIGH);sonando=true;}
         else{digitalWrite(bl3,LOW);sonando=false;}
         //Serial.print("10 ");Serial.println(vbl0);
      }else{
         vbl1=msg;
         if (msg>50){
           digitalWrite(bl2,HIGH);sonando=true;}
         else{digitalWrite(bl2,LOW);sonando=false;}
         //Serial.print("11 ");Serial.println(vbl1);
      }
      secuenciaBl++;
      Serial.println(secuenciaBl);
      if ((secuenciaBl)>=50){secuenciaBl=0;}
 
  }
  
  delay(10);
  if(vbl0<=0){vbl0=0;}else{vbl0-=1;}
  if(vbl1<=0){vbl1=0;}else{vbl1-=1;}
  analogWrite(bl0,vbl0);
  analogWrite(bl1,vbl1);
  
  // revisar moneda
  int valor=analogRead(moneda);
  //Serial.println(analogRead(moneda));
  if (valor<=1000){
    if (!estadoMoneda){
      Serial.write('m');
      delay(40);
      estadoMoneda=true;
    }
  }
  else{
    estadoMoneda=false;
  }
  
  mueveRgb();
}

