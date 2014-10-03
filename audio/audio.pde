import ddf.minim.analysis.*;
import ddf.minim.*;
import processing.serial.*;

Minim minim;
AudioPlayer player;
FFT         fft;

File dir;
String[] children;
int childCount = 0;
boolean cambio = false;

Serial myPort; 
int inByte = -1;    // Incoming serial data

void setup()
{
  size(512, 200, P3D);
  
  // we pass this to Minim so that it can load files from the data directory
  minim = new Minim(this);
  
  // listado de canciones
  dir = new File(dataPath("")); 
  children = dir.list();

  // puerto serial
  println(Serial.list());
  String portName = Serial.list()[3];
  myPort = new Serial(this, portName, 9600); 
  
  reproduceChange();
   fft = new FFT( player.bufferSize(), player.sampleRate() );
}

void draw()
{
  
  int bandas=30;
  
  // calculo de furier
  fft.forward( player.mix );
  
   // calculo de la fuerza para los LEDs
  int suma=0;
  for (int p=0;p<bandas;p++){
    suma+=fft.getBand(p);
  }
  int fuerza=suma/bandas*10;
  
  // borrado de la pantalla
  background(fuerza*2,fuerza*4,fuerza*3);
  stroke(255);
  
  // dibujo de las bandas 
  for(int i = 0; i < fft.specSize(); i++)
  {
    // draw the line for frequency band i, scaling it up a bit so we can see it
    line( i, height, i, height - fft.getBand(i)*8 );
  }
  
   // transmision de la fuerza
    myPort.write(fuerza);
  
  // revision de puerto serial
  if (inByte=='m' && !cambio){
    reproduceChange();
    println("Moneda");  
  }
  // continuar con la siguiente canción.
  if (!player.isPlaying())
  {
    if (!cambio){
      reproduceChange();
    }else{
      reproduceAzar();
    }
  }

}

void reproduceChange(){
  cambio=true;
  try{
    if (player.isPlaying()){
      player.close();
      minim.stop();
      myPort.clear();
      inByte='a';
    }
  }
  catch (Exception e) {
    println("No hay nada sonando");
  }

  myPort.write(255);
  player = minim.loadFile("change.wav", 1024);
  player.play(); 
}

void reproduceAzar(){
  cambio=false;
  String archivo="";
  while (archivo.equals("")){
    int i=int(random(children.length));
    archivo=children[i];
    println(archivo);
    if (archivo.equals("change.wav")){archivo="";}
  }
  player = minim.loadFile(archivo, 1024);
  player.play();
 
}

void serialEvent(Serial myPort) {
  inByte = myPort.read();
}
