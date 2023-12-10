// Prototipo porta autmatica ---- 29/11/2012

//#include <IRremote.h>

int PinAbre = 9;
int PinFecha = 10;
int PinSensrFech = 4;
int PinSensrAbre = 5;

int PinIR = 7;
int PinBtAbre = 8;
int PinSensOpt = 11;
//IRrecv irrecv(PinIR);
//decode_results resultadoIR;




int SensAbre;
int SensFech;
int btAbre;
int EstadoPorta = 0;
int SensorAbre = digitalRead(PinSensrAbre);
int SensorFecha = digitalRead(PinSensrFech);
int atividade = 0;   
int VelMax = 170;
int VelMin = 0;
int parado;
int testeAberto = 0;
int SensOptico;

void setup() {
  //  pinMode (PinAbre, OUTPUT);
  //  pinMode (PinFecha, OUTPUT);
  pinMode (PinSensrAbre, INPUT);
  pinMode (PinSensrFech, INPUT);
  pinMode (PinBtAbre, INPUT);

//  irrecv.enableIRIn();
  Serial.begin (9600);

  // analogWrite(PinAbre, 0);
  // analogWrite(PinFecha, 0);

  Serial.println("Iniciando o sistema porta 1.0");
  Serial.println("-----------------------------------");
  Serial.println();
}

void loop(){
//  ControleRemoto();  
  if (testeAberto == 0) {
    
    verificaSensor (0);
  } else if(testeAberto == 1) {
    verificaSensor (1);
  }
}
/*
 void ControleRemoto(){

  //39015  Abre
  //47175  fecha

  if (irrecv.decode(&resultadoIR)) {
    word valorIR = (resultadoIR.value);
    Serial.println("=======IR=======");
    Serial.print("Valor recebido: ");
    Serial.println(valorIR);  
    irrecv.resume();

    if (valorIR == 39015){
      Abre(); 
    }
    if (valorIR == 47175){
      Fecha(); 
    }
    if (valorIR==37230){
      Parar(); 
    }
    if (valorIR == 16830){
      if (VelMax < 255){
        VelMax+=10;
      }
    }
    if (valorIR == 4845){

     if (testeAberto == 0) {
       Serial.println();
       Serial.println("=============================");
       Serial.println("Iniciando Modo de TESTE");
       Serial.println();
       
      testeAberto = 1; 
     } else if (testeAberto == 1){
       Serial.println();
       Serial.println("Parando Modo de TESTE");
       testeAberto = 0;
       Parar();
       Serial.println("=============================");
     }

    }

    if (valorIR == 49470) {
      if (VelMax > 20){
        VelMax-=10;
      }
    }


  }
}
*/
void verificaSensor (int teste) {
  SensorAbre = digitalRead(PinSensrAbre);
  SensorFecha = digitalRead(PinSensrFech);
  SensOptico = analogRead(PinSensOpt);
  /*
   if (SensOptico < 100){
   Serial.print("Valor Sensor Optico: ");
   Serial.println(SensOptico);
   }
   */
  if (SensorAbre == 0 and SensorFecha == 0){
    EstadoPorta = 0; //porta entreaberta
    if (atividade == 0) {
      if (parado == 0) {
        Serial.println("Porta entreaberta sendo fechada!");

        Fecha();
      }
    } 
  }
  if (SensorAbre == 1){
    EstadoPorta = 1;
  }
  if (SensorFecha == 1){
    EstadoPorta = 2;
  }

  if (EstadoPorta == 0) {


  }
  if (EstadoPorta == 1) {

    analogWrite (PinFecha, 0);
   
  }
  if (EstadoPorta == 2) {

    analogWrite (PinAbre, 0);
    
  }
  if (atividade == 1 and parado == 1){
    parado=0;
    Serial.println ("Desligando estado parado");
  }
  
}

void Abre () {

  if (parado == 1 and SensorAbre == 0) {
    atividade = 1; 
    analogWrite (PinFecha, VelMax); 
    Serial.println("Abrir Porta parada!");

  } 
  else if (EstadoPorta == 2 and SensorAbre == 0) {
    atividade = 1; 
    analogWrite (PinFecha, VelMax); 
    Serial.println("Abrir Porta!");


  } 
  else {
    analogWrite (PinFecha, VelMin);

    atividade = 0; 
    Serial.println("Porta Aberta!");
  }

}
void Fecha () {

  if (parado == 1 and SensorFecha == 0) {
    atividade = 1; 
    analogWrite (PinAbre, VelMax);
    Serial.println("Fechando porta parada!");
  }
  else if (atividade == 0 and SensorAbre == 0 and SensorFecha == 0 and parado == 0) {
    atividade = 1; 
    analogWrite (PinAbre, VelMax);
    Serial.println("Autofechando!");
  } 
  else if (EstadoPorta == 1 and SensorFecha == 0) {
    atividade = 1; 
    analogWrite (PinAbre, VelMax);
    Serial.println("Fechar Porta!");

  } 
  else {
    analogWrite (PinAbre, VelMin);

    atividade = 0; 
    Serial.println("Porta Fechada!");
  }

}

void Parar() {
  analogWrite(PinAbre, VelMin);
  analogWrite (PinFecha, VelMin);
  atividade = 0; 
  parado = 1;
}

void testar (int qtd) {

  Serial.print("Iniciando Teste - tqd: ");
  Serial.println(qtd);
  
  SensorAbre = digitalRead(PinSensrAbre);
  SensorFecha = digitalRead(PinSensrFech);
  
  

/*
  if (atividade == 0){
    for (int i=0; i<qtd; i++){
      Serial.print("Q: ");
      Serial.println(i);
      if (atividade == 0) {
        if (testeAberto == 0) {
          Fecha(); 

        } 
        else  if (testeAberto == 1) {
          Abre(); 

        }
      } 
    }
  }
**/
}

