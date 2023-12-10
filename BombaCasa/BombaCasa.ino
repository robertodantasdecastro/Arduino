// A simple web server that always just says "Hello World"

#include "etherShield.h"
#include "ETHER_28J60.h"
int ligado = 0;
int RELligaPin = 3;
int RELdesligaPin = 4;
int BTestadoPin = 7;
int LedEstadoChavePin = 5;

static uint8_t mac[6] = {
  0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
static uint8_t ip[4] = {
  192, 168,0, 16};                       
static uint16_t port = 80;
ETHER_28J60 e;

void setup()
{ 
  Serial.begin(9600);
  e.setup(mac, ip, port);
  pinMode(RELligaPin, OUTPUT);
  pinMode(RELdesligaPin, OUTPUT);
  pinMode(LedEstadoChavePin, OUTPUT);
  pinMode(BTestadoPin,INPUT);
  Serial.println("Iniciando Modulo");

}

void loop()
{  
  //  digitalWrite (LedEstadoChavePin, digitalRead(BTestadoPin));
  int estadoCH=digitalRead(BTestadoPin);
  //  verificaReleBomba();
  char* params;
  /*  int estadoBomba = digitalRead(BTestadoPin);
   int eled = digitalRead(LedEstadoChavePin);
   */

  
  if (params = e.serviceRequest())
  {


    if (strcmp(params, "?cmd=on") == 0)
    {
      liga ();
      e.print("<A HREF='?cmd=off'>Desligar</A>");
    }
    else if (strcmp(params, "?cmd=off") == 0) // Modified -- 2011 12 15 # Ben Schueler
    {
      desliga();
      e.print("<A HREF='?cmd=on'>Ligar</A>");
    }
    e.print("<H1>Ativador Remoto</H1>");
    e.print("<BR><BR>");


    e.print("Estado Atual da Chave: ");
    if (ligado==1){
      e.print("Ligada!");
    }
    if (ligado==0){
      e.print("Desligada!");
    }

    //   digitalWrite (LedEstadoChavePin, digitalRead(BTestadoPin));
    e.print("<BR>");
    e.print("Estado Atual da Bomba: ");

    if (estadoCH==1){
      e.print("Ligada!");
    }
    if (estadoCH==0){
      e.print("Desligada!");
    }
    e.print("<BR><BR>");
    e.print("<BR><BR>");


    e.respond();  
  }
  //verificaReleBomba();
}


void liga() {
  if (ligado==0){
    digitalWrite(RELdesligaPin, HIGH);
    delay(400);
    digitalWrite(RELligaPin, HIGH);
    delay (750);
    digitalWrite(RELligaPin, LOW);
    ligado = 1;
    //  delay(500);
  }
}
void desliga(){
  if (ligado == 1){
    digitalWrite(RELdesligaPin, LOW);
    digitalWrite(RELligaPin, LOW);
    ligado = 0;
    // delay(500); 
  }
}
void verificaReleBomba() {


  if(digitalRead(BTestadoPin) == LOW){
    if(digitalRead(LedEstadoChavePin) == HIGH){
 //     Serial.println("Desligado");
      digitalWrite (LedEstadoChavePin, digitalRead(BTestadoPin));
    }
  }
  if(digitalRead(BTestadoPin) == HIGH){
     if(digitalRead(LedEstadoChavePin) == LOW){
    digitalWrite (LedEstadoChavePin, digitalRead(BTestadoPin));
  }
  }

}







