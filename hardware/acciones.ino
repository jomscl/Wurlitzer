
void cambiaDisco1(){
  boolean seguir=true;
  int pos=posCambiaDisco;
  byte dato;
  byte comando;
  byte valor;
  
  while (seguir){
    // leer dato
    dato=pgm_read_byte_near(datos+pos);
    
    // decodificar dato
    comando=(dato & B11100000);
    valor=dato & B00011111;
    
    switch (comando){
      case 0: // comandos al servo1
        sDisco.write(valor*8); break;
      case 32: // comandos al servo2
        sAguja.write(valor*8); break;
      case 64: // Sleep o delay
        delay(10*valor); break;
      case 96: // fin de rutina
        seguir=false; break;
      case 128: // volver a empezar
        pos=posCambiaDisco; break;
      case 160: // Modo RGB1
        break;
      case 192: // Modo RGB2
        break;
      case 224: // Modo blanco
        break;  
    }
    // ejecutar
    
    pos++;  
  }
}

void cambiaDisco(){
  int i;
  //aguja home
  for (i=finAguja;i<=homeAguja;i++){
    sAguja.write(i);
    delay(15);  
  }
  delay(1000);
  // Disco fin
  for (i=homeDisco;i<=finDisco;i++){
    sDisco.write(i);
    delay(15);  
  }
  //pausa
  delay (3000);
  
  // disco abajo
  for (i=finDisco;i>=homeDisco;i--){
    sDisco.write(i);
    delay(15);  
  }
  delay(1200);
  // aguja fin
  for (i=homeAguja;i>finAguja;i--){
    sAguja.write(i);
    delay(15);  
  }
}

void mueveRgb(){
  byte delta=1;
  if (sonando){delta=30;}
  if (secuenciaRgb0==0){// rojo++
    va0r+=delta;
    if (va0r>=255){
      va0r=255;
      secuenciaRgb0=nuevaSecuenciaRgb(secuenciaRgb0);
    }else{
      analogWrite(a0r,va0r);
    }  
  }
  
    if (secuenciaRgb0==1){// rojo--
    va0r-=delta;
    if (va0r<=0){
      va0r=0;
      secuenciaRgb0=nuevaSecuenciaRgb(secuenciaRgb0);
    }else{
      analogWrite(a0r,va0r);
    } 
  }
  
  if (secuenciaRgb0==2){// green++
      va0g+=delta;
    if (va0g>=255){
      va0g=255;
      secuenciaRgb0=nuevaSecuenciaRgb(secuenciaRgb0);
    }else{
      analogWrite(a0g,va0g);
    } 
  }
  
  if (secuenciaRgb0==3){// green--
      va0g-=delta;
    if (va0g<=0){
      va0g=0;
      secuenciaRgb0=nuevaSecuenciaRgb(secuenciaRgb0);
    }else{
      analogWrite(a0g,va0g);
    } 
  }
  
  if (secuenciaRgb0==4){// blue++
      va0b+=delta;
    if (va0b>=255){
      va0b=255;
      secuenciaRgb0=nuevaSecuenciaRgb(secuenciaRgb0);
    }else{
      analogWrite(a0b,va0b);
    } 
  }
  
  if (secuenciaRgb0==5){// blue--
      va0b-=delta;
    if (va0b<=0){
      va0b=0;
      secuenciaRgb0=nuevaSecuenciaRgb(secuenciaRgb0);
    }else{
      analogWrite(a0b,va0b);
    } 
  }
  
  Serial.println(secuenciaRgb0);
}

int nuevaSecuenciaRgb(int anterior){
  int salida=anterior;
  while (anterior==salida){
      salida=random(6); 
  }


 return salida; 
}
