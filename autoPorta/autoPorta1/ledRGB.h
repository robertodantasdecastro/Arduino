

void fade (String led, int esp) {


  int vel = esp;
  long tg = 0 ;

  int vMin = 10;
  int vMax = 235;
  int estado = 0;
  
  if ((led == "verm") or (led == "verd") or (led == "azul")) {
    int ledPin;
    if (led == "verm") {
      ledPin = PinLedVerm;
    }
    if (led == "verd") {
      ledPin = pinLedVerd;
    }
    if (led == "azul") {
      ledPin = pinLedAzul;
    }

    //Serial.println(cont);
    if (cheio == 0) {

      cont ++;
      if (cont < vMax) {
        cont=  cont+vel;
        analogWrite (ledPin, cont);
      } 
      else if (cont > vMax) {
        cheio = 1;
        //analogWrite (ledPin, cont);

      }
    } 
    else if (cheio == 1) {

      cont --;
      if (cont > vMin) {
        cont=  cont-vel;
        analogWrite (ledPin, cont);
      } 
      else if (cont < vMin) {
        cheio = 0; 
        //analogWrite (ledPin, cont);
      }
    }
  } else if ((led == "amar") or (led == "amba") or (led == "roza")){
    int ledPin1;
    int ledPin2;
    if (led == "amar") {
      ledPin1 = pinLedVerd;
      ledPin2 = PinLedVerm;
      
    }
    if (led == "amba") {
      ledPin1 = pinLedAzul;
      ledPin2 = pinLedVerd;
    }
    if (led == "roza") {
      ledPin1 = PinLedVerm;
      ledPin2 = pinLedAzul;
    }
    
    if (cheio == 0) {

      cont ++;
      if (cont < vMax) {
        cont=  cont+vel;
        analogWrite (ledPin1, cont);
        analogWrite (ledPin2, cont);
      } 
      else if (cont > vMax) {
        cheio = 1;
        //analogWrite (ledPin, cont);

      }
    } 
    else if (cheio == 1) {

      cont --;
      if (cont > vMin) {
        cont=  cont-vel;
        analogWrite (ledPin1, cont);
        analogWrite (ledPin2, cont);
      } 
      else if (cont < vMin) {
        cheio = 0; 
        //analogWrite (ledPin, cont);
      }
    }
  }
  /*
      if (cont > esp) {
   estado = 1;
   } 
   if ((cont > esp) and (cont < (esp*2))){
   estado = 0;
   } else if (cont > (esp*2)) {
   estado = 0;
   cont = 0;
   }
   
   */
}

void acende (int cor){ 
  analogWrite(cor, 255);
}
void apaga (int cor){ 
  analogWrite(cor, 0);
}
void apagarTudo(){
  analogWrite(pinLedVerd, 0);
  analogWrite(pinLedAzul, 0);
  analogWrite(PinLedVerm, 0);
}
void piscaLed (int cor, int cor2, int tr){ 
  //Serial.println("piscaled");
  int estado = 0;
  long t = 0;
  int espera = tr;

  // if (millis() - t > espera) {

  cont ++;
  if (cont < espera) {
    estado = 1;
  } 
  if ((cont > espera) and (cont < (espera*2))){
    estado = 0;
  } 
  else if (cont > (espera*2)) {
    estado = 0;
    cont = 0;
  }

  //   } 

  if (estado == 1) {
    acende(cor);
    apaga(cor2);
  } 
  else {
    apaga(cor);
    acende(cor2);
  } 
  

}










