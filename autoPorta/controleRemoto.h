void ControleRemoto(){

  //39015  Abre
  //47175  fecha

  if (irrecv.decode(&resultadoIR)) {
    word valorIR = (resultadoIR.value);
    if (valorIR != 65535){
      Serial.println("======= IR =======");
      Serial.print("Valor recebido: ");
      Serial.println(valorIR);  
    }
    irrecv.resume();

    if (valorIR == 18615){
      Abrir(); 
    }
    if (valorIR == 16575){
      Fechar(); 
    }
    if (valorIR==2295){
      Parar(); 
      autoTeste = 0;
    }
    if (valorIR == 41055){
      if (VelAtual < VelMax-10){
        Serial.println("Subir Velocidade");
        VelAtual+=10;
      }
    }
    if (valorIR == 57375) {
      if (VelAtual > VelMin){
        Serial.println("Diminuir Velocidade");
        VelAtual-=10;
      }
    }

    if (valorIR == 45135){
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


