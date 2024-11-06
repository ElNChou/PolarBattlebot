//traducción de pines
//const int D0=16,D1=5,D2=4,D3=0,D4=2,D5=14,D6=12,D7=13,D8=15,RX=3,TX=1,SD3=10,SD2=9;
using namespace std;
//***********************************************
#include <ESP8266WiFi.h>
#include "puenteH.h"
const char* ssid = "PolarTesting";
const char* password = "elguantedeboxeo";

WiFiServer server(80);

bool encendido=false;

//Inicializamos los 3 motores creando la una clase de "puenteH" para cada uno
//D5,D6,D8
puenteH Right(14,12,15);
//D2,D1,D7
puenteH Left(4,5,13);
//D0,TX,D4
puenteH Tail(16,1,2);


//También declaramos el pin donde está el arma, D3
const int arma=0;

//Y por último las variables donde guardaremos el input de la app
int joystick[2];


//https://www.servomagazine.com/magazine/article/get-rolling-with-omni-directional-wheels

void setup() {
  Serial.begin(115200);
  // Inicialización de WiFi
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Espera una nueva conexión
  if (!client) {
    return;
  }

  Serial.println("Cliente conectado");
  while(!client.available()){delay(1);}
  
  //Lectura del comando, pero solo la parte que importa
  String command = client.readStringUntil('/');
  command=client.readStringUntil('/');
  client.flush();
  Serial.print("Comando recibido: ");
  Serial.println(command);

  

  //Chequeemos si estamos encendidos primero
  //Si no estamos encendidos...
  if(!encendido){
    //Si recibimos un E, encender el programa
    encendido=(command[0]=='E');
  }else{

    //Si estamos encendidos, empezar la acción!!!
    //Leer el comando recibido
    switch (command[0]) {
     //Input de movimiento!!
     case 'M':
        //Leemos el componente x e y por separado
        command=client.readStringUntil('/');
        joystick[0]=command.toInt();
        command=client.readStringUntil('/');
        joystick[1]=command.toInt();
        break;
      
      //Input de rotación!!
      case 'R':
        command=client.readStringUntil('/');
        for(int i=0;i<4;i++)direccion[i] = (command[i]=='1');
        puente1.cambiar(direccion);
        break;

      //INPUT DE ATAQUE!!!
      case 'A':
        analogWrite(arma,150);
        break;

      //input de detener ataque...
      case 'S':
        digitalWrite(arma,0);
        break;

      case 'X':  // Apagar
        digitalWrite(arma,0);
        Right.mover(0);
        Left.mover(0);
        Tail.mover(0);
        encendido=false;
        break;
    }
  }
  //Apagamos el cliente para eliminar los datos basura restantes
  client.stop();
  Serial.println("Cliente desconectado");
}
