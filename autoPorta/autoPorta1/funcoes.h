int retornarSensor (){

  int SensorAbre = digitalRead(PinSensrAbre);
  int SensorFech = digitalRead(PinSensrFech);
  int EstadoPorta;

  if (SensorAbre == 1 and SensorFech == 0) {
    
   
     EstadoPorta=1;
  }
  else if (SensorAbre == 0 and SensorFech == 1) {
  
    EstadoPorta=2;
  }
  else if (SensorAbre == 0 and SensorFech == 0) {
    fade ("roza", 10);
    

    EstadoPorta=0; //porta encontra-se etreaberta;
    
    
    // Serial.println("Porta Entreaberta");
  }
  else if (SensorAbre == 1 and SensorFech == 1) {
    EstadoPorta=3; ///Estado de erro!
    //Serial.println("ERRO!");
    
  }
  return(EstadoPorta);
}
void subir (){
  if (p==0){
   if (VelAtual < VelMax){
      VelAtual += 10;
      Serial.println(VelAtual);
   }
   if (VelAtual >= VelMax){
     p=1;
     
   }
 }
}
void diminuir () {
   if (p==1) {
        if (VelAtual > VelMin+20){
        VelAtual -= 20;
        Serial.println(VelAtual);
        }
          
          if (VelAtual <= VelMin){
           p=2; 
        }
        
      }
}
void verificaSensor (){

  int EstAtual=retornarSensor();

  if (Atividade > 0) {
    
    if (Atividade == 2 or Atividade == 1) {
       
     subir();
     
    // p = 1;
      
    }
    
    
    if (EstAtual == 1 and parado == 0 and Atividade == 1) {
     
      diminuir ();
      
      if (p==2){
        Parar ();
      }
      Serial.println(VelAtual);
      diminuir (); 
      Serial.println("PARADO 1"); 

    }
    else if (EstAtual == 2 and parado == 0 and Atividade == 2) {

      
      diminuir ();
      
      if (p==2){
        Parar ();
      }  
       Serial.println(VelAtual); 
        diminuir ();
      Serial.println("PARADO 2"); 


    }
    else if (EstAtual == 3 and parado == 0) {

      
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
  else if (EstAtual==0) {
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
  
  if (EstAtual==1) {
    Fechar ();
    Serial.println("Fechar!");
  } 
  else if (EstAtual==2) {
    Abrir();
    Serial.println("Abrir!");
    //delay(2000);
  }
  
  
  if (EstAtual==0){
    Fechar ();
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


