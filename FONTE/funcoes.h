float verificaCorrente (int p) {

  float Avalor = 0.00;
  Avalor = analogRead(p);

  int n = 1000;
  float ampere=0;
  float amp=0;
  for (int i=0;i<n;i++){
    ampere += map(Avalor, 509, 1023, 0, 3000)-5;
    // ampere += map(Avalor, 512, 0, 0, 3000);
  }
  ampere /= n;

  // ampere += (.048828 * (Avalor-511));;
  ampere = ampere*0.01;
  if (ampere < 0) ampere = 0.0;
  if (ampere > 100) ampere = 99.99;

  return (ampere); 
  n++;
}
float verificaTencao (int p) {

  float volt = 0.0;
  float R1 = 98000.0;
  float R2 = 10000.0;
  float vin = 0.00;
  float Vvalor = 0.00;
  Vvalor = analogRead(p);
  volt = (Vvalor * 5.0) / 1023.0;
  vin = volt / (R2/(R1+R2));
  if (vin > 100) vin = 99.99;

  return (vin);
}


int StrInt (String Str) {
  //  int b = Str.toInt();
  int tam = Str.length()+1;
  char variavel[tam];
  Str.toCharArray(variavel,tam);
  int ret = atoi(variavel);
  return (ret);
}
char StrChar (String Str) {
  int tam = Str.length()+1;
  char variavel[tam];
  Str.toCharArray(variavel,tam);
}

float imprimaTencao (int pin, int y, int x) {
  float v = verificaTencao(pin);
  corrente[pin]=v;
  if (v<10){
    Tela.print ("0",x,y);
    Tela.printNumF (v,2,x+24,y);
  } 
  else {
    Tela.printNumF (v,2,x,y);
  }
}
float imprimaCorrente (int pin, int y, int x) {
  float a = verificaCorrente(pin);  
  if (a<10){
    Tela.print ("0",x,y);
    Tela.printNumF (a,2,x+24,y);
  } 
  else {
    Tela.printNumF (a,2,x,y);
  }
}
float imprimaEntrada (float valor, int y, int x) {

  if (valor<10){
    Tela.print ("0",x,y);
    Tela.printNumF (valor,2,x+24,y);
  } 
  else {
    Tela.printNumF (valor,2,x,y);
  }
}

float seguranca (){

  tencaoMax = verificaTencao(pinTencaoTotal);

  int r=0;
  while (corrente[r]){
    corrente[r] = verificaCorrente(pinCorrente[r]);
    if ((corrente[r] >= correnteMax) || (curto[r] = true)) {
      curto[r] = true; 
      botaoLigado[r]=false;
      // corFundoAlerta[r]=VGA_RED;
      digitalWrite (portaRELE[r],0); 

    } 
    else {
      //curto[r] = false; 
      corFundoAlerta[r]=VGA_BLACK;
    }
    r++;
  }
}
int Ajustar(int id) {
  float saida;
  float entrada = manda[id];
  float atual = verificaTencao(id);
  //Serial.println(atual);
  if (entrada>atual){
    if (potencia[id] < 255){
      if (entrada-atual > 1){
        saida=25;
      } 
      else if (entrada-atual > 0.50){
        saida=10;
      } 
      else if (entrada-atual < 0.50) {
        saida=5;        
      } 
      else if (entrada-atual <= 0.10) {
        saida=1; 
      }
    }
  } 
  else if (entrada<atual){
    if (potencia[id] > -255){
      if (entrada-atual < -1) {
        saida=-25;
      } 
      else if (entrada-atual < -0.50){
        saida=-10;
      } 
      else if (entrada-atual > -0.50) {
        saida=-5;        
      } 
      else if (entrada-atual >= -0.10) {
        saida=-1; 
      } 
    }
  } else if (entrada==atual) {
    
    saida=0;
  }
    

  if (botaoLigado[id+2]==true) { 

    if (potencia[id]+(saida) < -255) {
      potencia[id]=(-255); 
    } else if (potencia[id]+(saida) > 255) {
      potencia[id]=255; 
    }else {
     potencia[id]+=(saida);  
    }
    analogWrite(portaPOT[id], potencia[id]);
    Serial.print(potencia[id]);
    Serial.print(" | ");
    Serial.println(saida);

  } 
  else {

  }
  return(saida);
}


