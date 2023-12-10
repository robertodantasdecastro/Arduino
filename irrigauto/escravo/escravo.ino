#include <SPI.h>
#include <Wire.h>
#include "config.h"
#include "funcoes.h"

boolean config = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("Aguardando");  
  Wire.begin(id_ci);
  Wire.onReceive(receba);
  delay(10);  
  Wire.onRequest(envia);
//  delay(10);
//  Wire.onRequest(envia2);
  
 
}

void loop(){
  delay(100);
}


