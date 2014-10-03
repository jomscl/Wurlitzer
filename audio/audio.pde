import ddf.minim.analysis.*;
import ddf.minim.*;

Minim minim;
AudioPlayer player;
FFT         fft;

File dir;
String[] children;
int childCount = 0;
boolean cambio = false;

void setup()
{
  size(512, 200, P3D);
  
  // we pass this to Minim so that it can load files from the data directory
  minim = new Minim(this);
  
  // listado de canciones
  dir = new File(dataPath("")); 

  children = dir.list();
 
   reproduceChange();
 
  fft = new FFT( player.bufferSize(), player.sampleRate() );  
}

void draw()
{
  background(0);
  stroke(255);
  int bandas=30;
  
  // calculo de furier
  fft.forward( player.mix );
  
  // dibujo de las bandas 
  for(int i = 0; i < fft.specSize(); i++)
  {
    // draw the line for frequency band i, scaling it up a bit so we can see it
    line( i, height, i, height - fft.getBand(i)*8 );
  }
  
  // calculo de la fuerza para los LEDs
  int suma=0;
  for (int p=0;p<bandas;p++){
    suma+=fft.getBand(p);
  }
  int fuerza=suma/bandas;
  
  
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
