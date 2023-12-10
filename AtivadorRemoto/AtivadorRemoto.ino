
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
//#include "IRremote.h"

//int outputPin = 6;


int estadoBTN = HIGH;
boolean periodoBTN;
int perAntBTN = LOW;
long tempo = 0;
long espera = 1500;
int l=0;


int BtLigaDeslPin = A4;
//int SDpin = 4;
int RELligaPin = 2;
int RELdesligaPin = 3;
int BTestadoPin = A3;
int intIR=7;
int LedEstadoChavePin = A2;
boolean ligado = digitalRead(RELdesligaPin);

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,2,16);

EthernetServer server(80);

void setup() {


  pinMode(RELligaPin, OUTPUT);
  // pinMode(RELdesligaPin, OUTPUT);
  pinMode(LedEstadoChavePin, OUTPUT);
  pinMode(BTestadoPin,INPUT);
  pinMode(BtLigaDeslPin,INPUT);
  pinMode(intIR, INPUT);

  //  digitalWrite (LedEstadoChavePin, 0);
  Serial.begin(9600);
  Serial.println("iniciando aplicacao!");
  Serial.println("========================");
  Serial.println("");

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Iniciando o servico");
  Serial.println(Ethernet.localIP());
}


void loop() {

  verificaReleBomba(1);
  LigaDesliga();

  EthernetClient cliente = server.available();

  if (cliente) {
    String LerString = "";
    boolean clienteLinhaAtualLimpa = true;
    while (cliente.connected()) {
      if (cliente.available()) {

        char c = cliente.read();

        if (LerString.length() < 15) {
          LerString += c; 
          //Serial.print(c);
        }
        // Serial.write(c);
        //


        if (c == '\n' && clienteLinhaAtualLimpa) {

          Serial.println(LerString);
          if (LerString.indexOf("lig") > 0) {
            Serial.println("LIGAR");
            liga();
          } 
          if (LerString.indexOf("des") > 0)  {
            Serial.println("DESLIGAR");
            desliga();
          }
          delay (100);


          cliente.println("<!--HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println("Connnection: close--!>");
          cliente.println();
          cliente.println("<!DOCTYPE HTML>");
          cliente.println("<html>");
          cliente.println("<meta http-equiv=\"refresh\" content=\"10\">");
          cliente.print("<title>Ativador Remoto</title>");
          cliente.print("<style type=\"text/css\">");
          cliente.print("a { font-family: Verdana; }");
          cliente.print("</style>");
          cliente.println("<body bgcolor=\"#cad7ea\" leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">");
          cliente.println("<div align=\"center\" class=\"Titulo\"><b>Ativador Remoto</b></div>")>
            cliente.println("<br><div align=\"center\">");
          cliente.print("<table height=\"0\" width=\"10\" border=\"0\" cellspacing=\"1\" bgcolor=");
          //if (ligado == 0){ 
          if (digitalRead(BTestadoPin) == 1) {
            cliente.print("\"#0a51b0\""); 
          } 
          else  { //if (ligado == 1){ 
            cliente.print("\"#FF3333\""); 
          }
          cliente.println ("cellpadding=\"0\">");
          cliente.println("<tr><td>");
          if (ligado == 0){ 

            cliente.println("<a href=\"?lig\">"); 
          }
          else { 
            cliente.println("<a href=\"?des\">"); 
          }
          cliente.print("<button class=\"botaoLigar\" style=\"border:1px; border-left:1px; border-bottom:1px; border-right:1px; border-top:1px; border-color:#060;\" type='button' >");
          if (ligado == 0){ 
            cliente.print("LIGAR"); 
          }
          else { 
            cliente.print("DESLIGAR"); 
          }
          cliente.println("</button>");
          cliente.println("</a>");
          cliente.println("</td></tr></table>");
          cliente.println("</div>");



          break;
        }

        if (c == '\n') {
          // you're starting a new line
          clienteLinhaAtualLimpa = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          clienteLinhaAtualLimpa = false;
        }

      }
    }
    // give the web browser time to receive the data

    // close the connection:
    cliente.stop();
    cliente.stop();
    delay(100);
    Serial.println("clientee descnectado!");
  }
}


void liga() {


  if (ligado==0){
    digitalWrite(RELdesligaPin, HIGH);

    for(int i = 0; i<130; i++){
      //Serial.println(i);
      delay(5);
      if (i==60){

        Serial.println("Start");
        digitalWrite(RELligaPin, HIGH);      
      }
      if (i==120){
        Serial.println("up");
        digitalWrite(RELligaPin, LOW);  

      }
    }

    // l=l+1;
    ligado = 1;
  }

}
void desliga(){
  if (ligado == 1){
    digitalWrite(RELdesligaPin, LOW);
    digitalWrite(RELligaPin, LOW);
    ligado = 0;
    // if (l == 5){
    //  void (* softReset)(void)=0; 
    //softReset();
    //   }
    delay(200);
    verificaReleBomba(1);
  }
}

void LigaDesliga(){

  periodoBTN = digitalRead(BtLigaDeslPin);
  // Serial.println(periodoBTN);
  if (periodoBTN == HIGH && perAntBTN == LOW and millis() - tempo > espera) {

    if (estadoBTN == HIGH)
      estadoBTN = LOW;
    else
      estadoBTN = HIGH;

    tempo = millis();  

    if (ligado == 0 && estadoBTN == LOW){
      liga(); 
    }
    if (ligado == 1 && estadoBTN == HIGH) {
      desliga(); 
    }

  }
  // perAntBTN = estadoBTN;
  perAntBTN = periodoBTN;

}


void verificaReleBomba(int ops) {
  int i = digitalRead(BTestadoPin);
  int v = LOW;
  if (i==LOW){
    v = HIGH;
  } 
  else {
    v = LOW;
  }
  if (ops == 1){
    digitalWrite (LedEstadoChavePin, v);
  } 
  else if (ops == 2){
    //return(v); 
  }

}








