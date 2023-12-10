
#include <SPI.h>
//#include <SoftwareSerial.h>
#include <Wire.h>
#include "config.h"
#include "funcoes.h"
boolean config=false;
boolean inicia=false;
boolean recebeLinha=false;

//SoftwareSerial comIn(RX_TX[0],RX_TX[1]);

void setup () {

  Serial.begin(9600);
 // comIn.begin(57600);
  Serial.println("Iniciando");
  Wire.begin();


  int l=0; //variavel de controle de linhas
  int n=0; 
  int b=0; //variavel de controle de bombas

  int numeroBomba=0;

  String Valor="";
  String Valvula[45];
//  comIn.println("@INICIAR");
 // Serial.println("REINICIANDO!");
  while (!config) {    
//    testa_i2c();
    delay(50);
    
    
    
    if (!recebeLinha){

      if (comIn.available()>0) {
        char recebe[]="";
        char var = comIn.read();
        //  Serial.print("ST: ");
        //  Serial.println(var);
        if (var=='@'){
          inicia=true; 
        }
        if (var==';'){
          recebeLinha=true;
          Serial.println("Saindo.");   
        }
        if (inicia){        
          recebe[n]=var;
          Valor=Valor+recebe[n];
          n++;  

        } 
        else {
          n=0; 
        }

      } 
      else {   
        if (l==0){
          comIn.println("@CONFIG;"); 
          Serial.println("Enviando Congig");        
          delay(2000);
        }
      }
    } 
    else {

      // Serial.print(l);
      // Serial.print("  - Recebendo: ");
      Valvula[l]=Valor;
     // Serial.println(l);

      if (Valor.substring(0,1) == "@"){

        if (Valor.substring(1,2) == "V"){

          /// PROCESSAR LINHA DA VALVULA
          l++;
          b++;
          
          Serial.print("Processar Linha ");
          Serial.print(l);
          Serial.print(": ");
          Serial.println(Valor);

          //  @V:B04,XXX(A08,A09,A10,A11);           
          boolean configEscravo = configuraEscravos(Valor);       
  
  
          if (configEscravo) {
            comIn.println("@OKVAL;");
            Serial.println(validaTotal);
          } else {
            comIn.println("@ERVAL;");
          }
          
        }
        if (Valor.substring(1,2) == "F"){
          
          int vTotal=StringParaInt(Valor.substring(2,5));
          Serial.print("Resp v toal:");
          Serial.println(vTotal);
          if (validaTotal == vTotal){
            config=true;            
            Serial.println("FIM.");
            validaTotal=0;
            comIn.println("@OKCFG;");
          } else {
            comIn.println("@ERR;");
            validaTotal=0;
          }
          
           
        }

      }
      Valor="";
      recebeLinha=false;
      //  comIn.println(Valor);
    }
    
  }
  Serial.println("SAINDO P LOOP!");
}

void loop (){  
  // Serial.println("LOOP!");
  //comIn.println("@LOOP;");
  //  testa_i2c();

  delay(200);
}

