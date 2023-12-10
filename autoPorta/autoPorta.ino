
#include <SoftwareSerial.h>
#include "chave.h";
#include "config.h";
#include "rfid.h";


void setup () {

  //digitalRead (PinSensrFech);
  //digitalRead (PinSensrAbre);

  pinMode(PinSensrFech, INPUT);
  pinMode(PinSensrAbre, INPUT);
  pinMode(pinAmpereMotor, INPUT);
  pinMode(cargaRELE, OUTPUT);
  pinMode(voltPIN, INPUT);
  pinMode(progBTN, INPUT);

  pinMode(PinFech, OUTPUT);
  pinMode(PinAbre, OUTPUT);


 
  Serial.begin(9600);
  rfid.begin(9600);
  Serial.println("  Iniciando o sistema porta 1.0-B2");
  Serial.println("------------------------------------");
  Serial.println();
}

#include "voltimetro.h";
#include "ledRGB.h"
#include "funcoes.h"


void loop() {

  CarregaBateria();
  fade ("verm", 15);
  //fade ("azul", 15);
  //fade ("verd", 15);
  // Serial.println(verificaAmpere ());
  //delay(500);

  /*
    Serial.print ("Volt da bateria: ");
    Serial.println (Vvolt);
    /*
    Serial.println("==================");
    Serial.print("Ampere: ");
    float v = map (ampere, 515, 0, 0, 300);
    Serial.println(v/100);
  */
  if (autoTeste == 0) {
    verificaSensor();
    SubirDiminuir ();



    byte i = 0;
    byte val = 0;
    byte checksum = 0;
    byte bytesLidos = 0;
    byte tempByte = 0;
    byte tagBytes[6];
    char tagValor[10];

    if ((val = rfid.read()) == 2) {

      bytesLidos = 0;
      if (Atividade == 0 ) {
        while (bytesLidos < 12) {
          val = rfid.read();
          piscaLed (pinLedVerd, PinLedVerm, 2);
          if (bytesLidos < 10)
          {
            tagValor[bytesLidos] = val;
          }

          if ((val == 0x0D) || (val == 0x0A) || (val == 0x03) || (val == 0x02)) {
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
          for (i = 0; i < 5; i++) {

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


          if ( tagId > 0 )
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

    }
    //Serial.println("-----");
    //piscaLed (pinLedVerd, PinLedVerm, 2);
    //fade ("roza", 5);

  }
  else if (autoTeste == 1) {
    AbrirFechar();
  }
}

void Abrir() {

  int EstAtual = retornarSensor();
  Serial.print("Atividade: ");
  Serial.println(Atividade);

  if (EstAtual != 1) {
    if (Atividade != 1 and parado == 1) {
      parado = 0;
      Atividade = 1;

      Serial.print("Abrindo a porta! v: ");
      Serial.println(VelAtual);

      analogWrite (PinFech, 0);
      analogWrite (PinAbre, VelAtual);
      inicio = 1;
    }
  }

}

void Fechar () {

  int EstAtual = retornarSensor();
  Serial.print("Atividade: ");
  Serial.println(Atividade);
  if (EstAtual != 2) {
    if (Atividade != 2 and parado == 1) {
      // if (Atividade == 1 and parado == 1) {
      parado = 0;
      Atividade = 2;
      Serial.print("--> Fechando a porta! vel: ");
      Serial.println(VelAtual);

      analogWrite (PinFech, VelAtual);
      analogWrite (PinAbre, 0);
      inicio = 1;
    }
    //int ampere = map (analogRead(pinAnpereMotor), 0, 1024, 0, 255);
  }
}

void Parar () {

  if (inicio == 3) {

  }

  Atividade = 0;
  Serial.println("-->Parando a porta!");
  analogWrite (PinFech, 0);
  analogWrite (PinAbre, 0);
  autoTeste = 0;
  parado = 1;
  VelAtual = 0;
  p = 0;
  inicio = 0;
}





