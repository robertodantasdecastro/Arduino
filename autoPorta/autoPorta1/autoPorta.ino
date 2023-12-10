#include <IRremote.h>
#include <SoftwareSerial.h>
#include "chave.h";
#include "config.h";
#include "rfid.h";


void setup () {

  pinMode(PinSensrFech, INPUT);
  pinMode(PinSensrAbre, INPUT);


  irrecv.enableIRIn();

  Serial.begin(9600);
  rfid.begin(9600);
  Serial.println("Iniciando o sistema porta 1.0-B2");
  Serial.println("-----------------------------------");
  Serial.println();
}



#include "ledRGB.h"
#include "funcoes.h"
void loop() {
  ControleRemoto();


  byte i = 0;
  byte val = 0;
  byte checksum = 0;
  byte bytesLidos = 0;
  byte tempByte = 0;
  byte tagBytes[6];
  char tagValor[10];

  if (autoTeste == 0){
    verificaSensor();


    if((val = rfid.read()) == 2) { 
      
      bytesLidos = 0;
      while (bytesLidos < 12) { 
        val = rfid.read();
        piscaLed (pinLedVerd, PinLedVerm, 2);
        if (bytesLidos < 10)
        {
          tagValor[bytesLidos] = val;
        }

        if((val == 0x0D)||(val == 0x0A)||(val == 0x03)||(val == 0x02)) {
          break; 
        }

        if ((val >= '0') && (val <= '9')) {
          val = val - '0';
        }
        else if ((val >= 'A') && (val <= 'F')) {
          val = 10 + val - 'A';
        }

        if (bytesLidos & 1 == 1) {

          tagBytes[bytesLidos >> 1] = (val | (tempByte << 4));

          if (bytesLidos >> 1 != 5) { 
            checksum ^= tagBytes[bytesLidos >> 1]; 
          };
        } 
        else {
          tempByte = val; 
        };

        bytesLidos++;
      }


      if (bytesLidos == 12) { 
        tagValor[10] = '\0'; 

        Serial.print("Lendo TAG: ");
        for (i=0; i<5; i++) {

          if (tagBytes[i] < 16) {
            Serial.print("0");
          }
          Serial.print(tagBytes[i], HEX);
        }
        Serial.println();

        Serial.print("Checksum: ");
        Serial.print(tagBytes[5], HEX);
        Serial.println(tagBytes[5] == checksum ? " -- Passou." : " -- Erro.");

        int tagId = encontrarChave( tagValor );


        if( tagId > 0 )
        {
          Serial.print("Autorizando tag ID: ");
          Serial.println(tagId);
          Serial.print("Destravando para: ");
          Serial.println(ChavesNomes[tagId - 1]); 
        
          permitido == 1;
          ArbrirTempo (120);

        } 
        else {
          Serial.println("Tag Nao autorizado!");
          //apagarTudo();
        }
        apagarTudo();
        Serial.println();
      }

      bytesLidos = 0;
    }
    
    
    //Serial.println("-----");
    //piscaLed (pinLedVerd, PinLedVerm, 2);
    //fade ("roza", 5);
    
  } 
  else if (autoTeste == 1){
    AbrirFechar();
  }
}

void Abrir() {
  
  int EstAtual=retornarSensor();
  
  if (EstAtual!=1) {
    Atividade = 1;
    
    Serial.print("Abrindo a porta! v: ");
    Serial.println(VelAtual);
     
    analogWrite (PinFech, VelMin);
    analogWrite (PinAbre, VelAtual);
    inicio = 1;
  }
  
  
}

void Fechar (){
  
  int EstAtual=retornarSensor();
  
  
  if (EstAtual!=2) {
    Atividade = 2;
    Serial.print("--> Fechando a porta! vel: ");
    Serial.print(VelAtual);
    analogWrite (PinFech, VelAtual);
    analogWrite (PinAbre, VelMin);
    inicio = 1;

    //int ampere = map (analogRead(pinAnpereMotor), 0, 1024, 0, 255);
  }
}

void Parar () { 
  Atividade = 0;
  Serial.println("Parando a porta!");
  analogWrite (PinFech, VelMin);
  analogWrite (PinAbre, VelMin);
  autoTeste = 0;
  parado = 1;
  VelAtual = 0;
  p = 0;
}

void ControleRemoto(){

  //39015  Abre
  //47175  fecha

  if (irrecv.decode(&resultadoIR)) {
    word valorIR = (resultadoIR.value);
    if (valorIR != 65535){
      Serial.println("=======IR=======");
      Serial.print("Valor recebido: ");
      Serial.println(valorIR);  
    }
    irrecv.resume();

    if (valorIR == 39015){//39015
      Abrir(); 
    }
    if (valorIR == 47175){//47175
      Fechar(); 
    }
    if (valorIR==37230){//37230
      Parar(); 
      autoTeste = 0;
    }
    if (valorIR == 16830){//16830
      if (VelAtual < VelMax-10){
        Serial.print("Subir Velocidade: ");
        VelAtual+=10;
         Serial.println(VelAtual);
      }
    }
    if (valorIR == 49470) {//49470
      if (VelAtual > VelMin){
        Serial.print("Diminuir Velocidade: ");
        VelAtual-=10;
        Serial.println(VelAtual);
      }
    }

    if (valorIR == 2295){
      if (autoTeste == 0){
        Serial.println("Ligar modo teste");
        autoTeste = 1;
      } 
      else if (autoTeste == 1){
        Serial.println("Desligar modo teste");
        autoTeste = 0;
      }      
    }
  } 
}



