
#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Geometry.h>

int toqueX, toqueY, btCima1, btBaixo1, btLiga, VQ, n;
float tempoDelay = 5, tempoToque;
long tempoAtual = 0;
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


extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t UbuntuBold[];

UTFT          Tela(ITDB24E_8,19,18,17,16);
UTouch        Toque(15,10,14,9,8);
UTFT_Geometry geo(&Tela);
#define beep_Pin A5

void setup() {
  analogReference(DEFAULT);
  Tela.InitLCD();
  Tela.clrScr();
  Tela.fillScr(corFundo);
  Toque.InitTouch();
  Toque.setPrecision(PREC_MEDIUM);
  
  // put your setup code here, to run once:

}

#include "botoes.h";
void loop() {
  Tela.setFont(SmallFont);
  Tela.print("OK!", 2,0);
  botaoLigaDesliga( 0, 2, 199, 130, 35, "LIGAR", "DESLIGAR", "azul", "vermelho");
  // put your main code here, to run repeatedly: 
  
}
