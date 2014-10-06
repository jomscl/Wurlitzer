
void cambiaDisco(){
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
