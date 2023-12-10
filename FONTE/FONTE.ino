
#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Geometry.h>
//#include "regrasFuzzy.h";


float correnteMax = 9.00;
float tencaoMax = 0.00;


boolean descanso=false, desenhado=false;
float tempoDelay = 5, tempoToque;
long tempoAtual = 0;
int toqueX, toqueY, btCima1, btBaixo1, btLiga, VQ, n; 
long TempoBeep = 0;
boolean botaoLigado[]={
  false,false,true,true,false};
boolean botaoDesenho[]={
  false,false,false,false,false};
boolean botaoPress[]={
  false,false,false,false,false,false,false,false};
boolean telaTQ=false;

boolean StatusDesenhado=false;
boolean StatusDesenhoCurto[] = {
  false,false};
word corFundo = VGA_BLACK;
word corFundoAlerta[] = {
  VGA_BLACK, VGA_BLACK};



float manda[]={
  5.00,12.00};

boolean curto[]={
  false,false,false,false,false};
float corrente[]={
  0.00,0.00};
int potencia[]={
  0,0};
int pinCorrente[]={
  A1,A2};
int pinTencao[]={
  A3,A4};
int portaRELE[]={
  14,15};
int portaPOT[]={
  8,9};

#define beep_Pin A5
#define pinTencaoTotal A0


extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t UbuntuBold[];
//UTFT          Tela(ITDB24E_8,19,18,17,16);
//UTFT          Tela(ITDB24E_8,19,18,17,16);
//UTouch        Toque(15,10,14,9,8);

UTFT   Tela(ITDB32S, 38,39,40,41);
UTouch Toque(6,5,4,3,2);
UTFT_Geometry geo(&Tela);

void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);
  Tela.InitLCD();
  Tela.clrScr();
  Tela.fillScr(corFundo);
  Toque.InitTouch();
  Toque.setPrecision(PREC_MEDIUM);
  int r=0;
  while (portaRELE[r]){
    pinMode(portaRELE[r], OUTPUT);
    pinMode(portaPOT[r], OUTPUT);
    r++;
  }
  r=0;
  while (pinTencao[r]){
    pinMode(pinTencao[r], INPUT);
    r++;                                 
  }
  r=0;
  while (pinCorrente[r]){
    pinMode(pinCorrente[r], INPUT);
    r++;
  }

  r=0;
  /*
  while (portaPOT[r]){
   pinMode(portaPOT[r],OUTPUT);
   }
   */
  analogWrite(portaPOT[0], 125);
  analogWrite(portaPOT[1], 255);
  pinMode(pinTencaoTotal, INPUT);

}

#include "funcoes.h";
#include "botoes.h";
#include "desenhar.h";



void loop() {

  seguranca ();
  TocarTela();
  desenharStatus();
  analiza(false);
  geraMenu();
  Ajustar(0);

  //delay(1);
}
float analiza(boolean agora){

  if (!agora){
    if (tempoAtual >= tempoDelay) {

      tempoAtual = 0;
      Tela.setFont(SmallFont);
      Tela.setBackColor(50,50,50);
      Tela.setColor(180,180,180);
      imprimaTencao (pinTencaoTotal, 0,28);

      Tela.setFont (UbuntuBold);
      Tela.setBackColor(corFundo);

      Tela.setColor (VGA_WHITE);
      imprimaEntrada (manda[0],34,20);
      imprimaEntrada (manda[1],34,180);
      Tela.setColor (VGA_YELLOW);
      if (!curto[0]) imprimaTencao (pinTencao[0],102,20);
      if (!curto[1]) imprimaTencao (pinTencao[1],102,180); 
      Tela.setColor (255,109,8);
      if (!curto[0]) imprimaCorrente (pinCorrente[0],150,20);
      if (!curto[1]) imprimaCorrente (pinCorrente[1],150,180);
      int s=0;

      while (curto[s]){
        if (curto[s]){
          if (s==0){
            if (!StatusDesenhoCurto[s]){
              Tela.setColor(VGA_RED);
              Tela.drawRoundRect( 4, 92, 155, 190 );
              Tela.drawRoundRect( 5, 93, 154, 189 );
              Tela.drawRoundRect( 6, 94, 153, 188 );
              Tela.setColor(VGA_MAROON);
              Tela.fillRoundRect( 6, 95, 152, 187 );
              Tela.setBackColor(VGA_MAROON);
              Tela.setColor(VGA_WHITE);
              Tela.print("CURTO!", 9, 105);
              StatusDesenhoCurto[n]=true;

            }
            botaoLigaDesliga(4, 13, 140, 130, 35, "RELIGAR", "OK", "azul", "marron");
          }

        } 
        else {

        }
        s++;
      }

    }
  } else {

    Tela.setFont(SmallFont);
    Tela.setBackColor(50,50,50);
    Tela.setColor(180,180,180);

    imprimaTencao (pinTencaoTotal, 0,28);

    Tela.setFont (UbuntuBold);
    Tela.setBackColor(corFundo);
    //Tela.setColor (VGA_LIME);
    Tela.setColor (VGA_WHITE);
    imprimaEntrada (manda[0],34,20);
    imprimaEntrada (manda[1],34,180);
    Tela.setColor (VGA_YELLOW);
    if (!curto[0]) imprimaTencao (pinTencao[0],102,20);
    if (!curto[1]) imprimaTencao (pinTencao[1],102,180);
    Tela.setColor (255,109,8);
    if (!curto[0]) imprimaCorrente (pinCorrente[0],150,20);
    if (!curto[1]) imprimaCorrente (pinCorrente[1],150,180);

  }
  tempoAtual++;  
}


