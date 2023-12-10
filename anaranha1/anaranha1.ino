#include <Servo.h> 
#include <PS2X_lib.h> 
 


// Variaveis dos pinos das artivulaces
int pinFD1=2;
int pinFD2=3;
int pinFE1=4;
int pinFE2=5;
int pinTD1=6;
int pinTD2=7;
int pinTE1=8;
int pinTE2=9;


// Variaveis dos passos
int inicio = 0;
int passos = 0;
int pos;
int posInicial1 = 15;
int posInicial2 = 55;
int posTrans1 = 35;
int posFinal1 = 10;
int posFinal2 = 130;
      
 /// Variaveis do joistick:
PS2X ps2x;
int error = 0; 
byte type = 0;
byte vibrate = 0;
int vLY;
int vLX;
int vRY;
int vRX;


int retornaInverso(int val){
  return (map (val, 0, 180, 180, 0));
}



Servo ArtPernaFD1;
Servo ArtPernaFD2;
Servo ArtPernaFE1;
Servo ArtPernaFE2;
Servo ArtPernaTD1;
Servo ArtPernaTD2;
Servo ArtPernaTE1;
Servo ArtPernaTE2;

void moverGeral (int par, int impar) {
  
  int invPar = retornaInverso(par);
  int invInpar = retornaInverso(impar);
  
  ArtPernaFD1.write(par);
  ArtPernaFD2.write(impar);
  ArtPernaFE1.write(invPar);
  ArtPernaFE2.write(invInpar);
  ArtPernaTD1.write(invPar);
  ArtPernaTD2.write(invInpar);
  ArtPernaTE1.write(par);
  ArtPernaTE2.write(impar);

}

void dePe (){
  moverGeral (10,120);
}
void Deitar (){
  moverGeral (105,120);
}
void mergulhar (){
  moverGeral (105,170);
}
void Paralelo (){
  moverGeral (105,70);
}

void setup() 
{ 
  Serial.begin(9600);
  
  error = ps2x.config_gamepad(13,12,11,10,true,true);
  Serial.print("Estado do Joistick: ");
  if (error == 0) {
    Serial.println("Presente e operacional!");
  } 
  else if (error == 1) {
    Serial.println("Joistick nao encontrado!");
  } 
  else if (error == 2) {
    Serial.println("Joistick existe, mais nao aceita os comandos!");
  } 
  else if (error == 3) {
    Serial.println("Joistick nao compativel");
  } 
  type = ps2x.readType(); 
  Serial.print("Tipo de Joistick: ");
  switch(type) {
  case 0:
    Serial.println("Nao identificado");
    break;
  case 1:
    Serial.println("DualShock Controller encontrado!");
    break;
  case 2:
    Serial.println("GuitarHero Controller encontrado!");
    break;
  }
  
  ArtPernaFD1.attach(pinFD1);
  ArtPernaFD2.attach(pinFD2);
  ArtPernaFE1.attach(pinFE1);
  ArtPernaFE2.attach(pinFE2);
  ArtPernaTD1.attach(pinTD1);
  ArtPernaTD2.attach(pinTD2);
  ArtPernaTE1.attach(pinTE1);
  ArtPernaTE2.attach(pinTE2);

  //Deitar();
  dePe();
  

 
 /*ArtPernaFD1.write(10);
 ArtPernaFD2.write(60);
*/


} 


 
void andar (String direcao, int velocidade) {
  
  
  
  if (passos < 3){
    
    
    if (inicio == 0){
      Serial.println("Posicao Inicial Andar Frente");
      ArtPernaFD1.write(posInicial1);
      ArtPernaFD2.write(posInicial2);
      ArtPernaFE1.write(retornaInverso(posFinal1));
      ArtPernaFE2.write(retornaInverso(posFinal2));
      
      ArtPernaTE1.write(posInicial1);
      ArtPernaTE2.write(posInicial2);
      
      ArtPernaTD1.write(retornaInverso(posInicial1));
      ArtPernaTD2.write(posInicial2);
      
      inicio = 1;
      } else if (inicio == 1){
        Serial.print("andando a velocidade: ");
        Serial.println(velocidade);
        
        
         for(pos = posInicial2; pos < posFinal2; pos += 1) {                                  
            ArtPernaFD2.write(pos);   
            ArtPernaFE2.write(pos-30); 
            ArtPernaTD2.write(retornaInverso(pos));
            ArtPernaTE2.write(retornaInverso(pos));
            ArtPernaFD1.write(posTrans1); 
            ArtPernaTE1.write(posTrans1);
            ArtPernaTD1.write(retornaInverso(posInicial1)); 
            ArtPernaFE1.write(retornaInverso(posInicial1));      
            delay(velocidade);                       
         } 
         for(pos = posFinal2; pos>=posInicial2; pos-=1) {                                
            ArtPernaFD2.write(pos); 
            ArtPernaFE2.write(pos-30);
            ArtPernaTD2.write(retornaInverso(pos));
            ArtPernaTE2.write(retornaInverso(pos));
            ArtPernaTE1.write(posInicial1);
            ArtPernaFD1.write(posInicial1);
            ArtPernaTD1.write(retornaInverso(posTrans1));  
            ArtPernaFE1.write(retornaInverso(posTrans1));
            delay(velocidade);                        
          } 
          
       }
    
    
  }
  
}
 
void joistik () {
 if(error == 1) 
  return; 
  
  if(type == 2){
    Serial.println("GuitarHero Controller nao controla essse dispositivo!");
  } else {
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

    if(ps2x.Button(PSB_START)){               //will be TRUE as long as button is pressed
      Serial.println("Botao Start Precionado");
    }
    
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");


    if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   


    vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
    //how hard you press the blue (X) button    

    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {



      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_GREEN)){
        Serial.println("Triangle pressed");
        dePe();
      }
    }   


    if(ps2x.ButtonPressed(PSB_RED))  {           //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
  mergulhar ();  
  }
    if(ps2x.ButtonReleased(PSB_PINK))  {           //will be TRUE if button was JUST released
      Serial.println("Square just released");     
  Paralelo ();  
  }
    if(ps2x.NewButtonState(PSB_BLUE)) {           //will be TRUE if button was JUST pressed OR released
      Deitar();
      Serial.println("X just changed");    
    }

    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
      
      vLY = ps2x.Analog(PSS_LY);
      if (vLY < 128) {
        int valVel = map(vLY, 128, 0, 20, 0);
        andar ("fernte", valVel);
      }else if (vLY>128) {
        int valVel = map(vLY, 128, 255, 20, 0);
        andar ("tras", valVel);
      }
      
      vLX = ps2x.Analog(PSS_LX);
   
      
      vRY = ps2x.Analog(PSS_RY); 
      
      
     
      
      vRX = ps2x.Analog(PSS_RX); 
      
      
      
      vRX = map(vRX, 0, 1024, 0, 1024);
      
     
      
      
      Serial.print("Valores do Stick:");
      
      Serial.print(vLY); 
      Serial.print(",");
      Serial.print(vLX); 
      Serial.print(",");
      Serial.print(vRY); 
      Serial.print(",");  
      Serial.println(vRX);
     
    } 


  } 
}
 
void loop() 
{ 
  
  
 // andar ("frente", 10);  
  joistik ();
  
  
  
  
  
  
  
  
  
} 
