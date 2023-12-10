int retornarSensor (){
  //
  int SensorAbre = digitalRead(PinSensrAbre);
  int SensorFech = digitalRead(PinSensrFech);
  int EstadoPorta;

  if (SensorAbre == 1 and SensorFech == 0) {
  ///  Serial.println("Sensor Abre");
    if (inicio == 2 and Atividade == 1) {
      inicio = 3;
    }
    if (parado == 0) {
      EstadoPorta=1;
      
    } 
     
    else if (parado == 1) {
      // Serial.println("movimento fechando=1");
      EstadoPorta=1;

    }
  }
  else if (SensorAbre == 0 and SensorFech == 1) {
 ///   Serial.println("Sensor Fech");
    if (inicio == 2 and Atividade == 2) {
      inicio = 3;
    }
    if (parado == 0) {
      EstadoPorta=2;
         
    } 
    else if (parado == 1) {
      //  Serial.println("movimento Abrindo=2");
      EstadoPorta=2;

    }
  }
  else if (SensorAbre == 0 and SensorFech == 0) {
    
    //inicio = 0;
    EstadoPorta=3; 
   
  }
  else if (SensorAbre == 1 and SensorFech == 1) {
    inicio = 0;
    Parar();
    EstadoPorta=4; ///Estado de erro!
    Serial.println("ERRO! - os dois sensores estao ativos");

  }
  return(EstadoPorta);
}


void SubirDiminuir (){
  //  Serial.println(inicio);
  // Serial.println(VelAtual);
  if (inicio == 0) {

    analogWrite (PinFech, 0);
    analogWrite (PinAbre, 0); 
  }
  else
    if (inicio == 3){
      // Serial.println("ta no 3");
      if (VelAtual <= VelMenor){
        inicio = 4;
        Serial.println("Pulando p o 4");

      } 
      else 
        if (VelAtual >= VelMenor){
        //  int EstadoPorta = retornarSensor();
        VelAtual -= velFadePorta;
     //   Serial.print("V1: ");
      //  Serial.println(VelAtual);
        if (parado == 0){
          if (Atividade==1) {
    //        Serial.println("A1");
            analogWrite (PinFech, 0);
            analogWrite (PinAbre, VelAtual);
          } 
          else if (Atividade==2) {
     //       Serial.println("A");
            analogWrite (PinAbre, 0);
            analogWrite (PinFech, VelAtual);
          }
        }
      }

    } 
    else
      if (inicio == 1){
        if (VelAtual < VelMax){
          VelAtual += velFadePorta;
    //      Serial.print("V2: ");
    //      Serial.println(VelAtual);
          if (parado == 0){
            if (Atividade==1) {
    //          Serial.println("A2");
              analogWrite (PinFech, 0);
              analogWrite (PinAbre, VelAtual);
            } 
            else if (Atividade==2) {
    //          Serial.println("F2");
              analogWrite (PinAbre, 0);
              analogWrite (PinFech, VelAtual);
            }
          }

        }
        if (VelAtual >= VelMax){
          Serial.println("Mudou pra o 2");
          inicio = 2;

        }
      }
  delay (velDelay);
}

void verificaSensor (){
  //Serial.println(Atividade);
  int EstAtual=retornarSensor();

  if (Atividade > 0) {
    if (EstAtual == 1 and parado == 0 and Atividade == 1 and inicio == 4) {
      Serial.println("PRD!!");
      Serial.println("PARADO 1");
      Parar ();
    }
    else if (EstAtual == 2 and parado == 0 and Atividade == 2 and inicio == 4) {
      Serial.println("PARADO 2-");
      Parar (); 
    }
    else if (EstAtual == 4 and parado == 0) {
      Parar (); 
      Serial.println("PARADO 3");   
    }
    else if (EstAtual == 0 and parado == 1) {
      parado = 0;   
    }
  }

}

void AbrirFechar(){

  int EstAtual=retornarSensor();

  if (EstAtual==1) {
    Fechar ();
    //delay000);
  } 
  else if (EstAtual==2) {
    Abrir();
    //delay(2000);
  } 
  else if (EstAtual>2) {
    //  Fechar ();
  }  
}


void ArbrirTempo (int tempo) {
  int T = tempo * 1000;
  int T_atual = millis();
  int T_corrente;

  Serial.println("Abrir Fechar TEMPO!!!");

  int EstAtual=retornarSensor();

  Serial.print("Estado Atual: ");
  Serial.println(EstAtual);

  if (EstAtual==1 or (EstAtual==3 and parado == 1)) {
    Fechar ();
    Serial.println("Fechar!");
  } 
  else if (EstAtual==2) {
    Abrir();
    Serial.println("Abrir!");
    //delay(2000);
  }


  if (EstAtual==4){
    //  Fechar ();
    int Aut1; 

    if (millis() - tempo > 5000) {

      Aut1 = 0;
    } 
    else {
      Aut1 = 1;
    }
    if (inicio == 0 or Aut1 == 1) {

      Fechar ();
      Serial.println("0 - Fechar 0");
    }

  }

}


