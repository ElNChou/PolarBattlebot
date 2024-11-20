//traducción de pines
//const int D0=16,D1=5,D2=4,D3=0,D4=2,D5=14,D6=12,D7=13,D8=15,RX=3,TX=1,SD3=10,SD2=9;
using namespace std;
//*******IMPORTANTE*********
//Cambia esta flag a "true" si estás usando un servo en vez de un motor DC.
//Esto lo implementamos porque nuestro motor estaba malo :( xd
bool usarServo=false;

#include <ESP8266WiFi.h>
#include <Servo.h>
#include "puenteH.h"
const char* ssid = "PolarTesting";
const char* password = "elguantedeboxeo";

WiFiServer server(80);
//Esto es para detener el robot cuando no lo estemos usando
bool encendido=false;

//Inicializamos los 3 motores creando la una clase de "puenteH" para cada uno
//D5,D6,D8
puenteH Right(12,14,15);
//D2,D1,D7
puenteH Left(4,5,13);
//D0,SD2,D4
puenteH Tail(16,9,2);


//También declaramos el pin donde está el arma, SD2
const int PinArma=9;
Servo arma;

//Y por último las variables donde guardaremos el input de la app
//Esto guardará la intensidad que deben tener los 3 motores en un momento dado
int joystick[3];


//https://www.servomagazine.com/magazine/article/get-rolling-with-omni-directional-wheels

void setup() {
  //Marcamos el arma como OUTPUT, los puenteH ya lo hacen por sí solos
  if(usarServo)arma.attach(PinArma);
  else pinMode(PinArma,OUTPUT);
  // Inicialización de WiFi
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Espera a recibir un comando
  if (!client) {
    return;
  }

  while(!client.available()){delay(1);}
  
  //Lectura del comando, pero solo la parte que importa hasta el '/'
  String command = client.readStringUntil('/');
  command=client.readStringUntil('/');
  client.flush();

  //Chequeemos si estamos encendidos primero
  //Si NO estamos encendidos, nos encederemos en caso de recibir un 'E'
  if(!encendido){
    encendido=(command[0]=='E');
  
  //Si ya estamos encendidos, empezar la acción!!!
  }else{
    //Interpretaremos el comando guardado en 'command'
    switch (command[0]) {
     //M = Input de movimiento!!
     case 'M':
        //Leemos las nuevas intensidades para los motores que precalculó la aplicación muy amablemente
        for(int i=0;i<3;i++){
          command=client.readStringUntil('/');
          joystick[i]=command.toInt();
        }
        
        //Y actualizamos los motores
        //Se reciben en el orden: Right,Left,Tail
        Right.move(joystick[0]);
        Left.move(joystick[1]);
        Tail.move(joystick[2]);
        break;

      //A = INPUT DE ATAQUE!!!
      case 'A':
        if(usarServo)arma.write(0);
        else digitalWrite(PinArma,1);
        break;

      //S = input de detener ataque...
      case 'S':
        if(usarServo)arma.write(180);
        else digitalWrite(PinArma,0);
        break;

      //test servo
      case 'T':
        command=client.readStringUntil('/');
        arma.write(command.toInt());
        break;

      //X = volver a apagar (estado inicial)
      case 'X':  // Apagar
        if(usarServo)arma.write(0);
        else digitalWrite(PinArma,0);
        Right.move(0);
        Left.move(0);
        Tail.move(0);
        encendido=false;
        break;
    }
  }
  //Apagamos el cliente para eliminar los datos basura restantes
  client.stop();
}
