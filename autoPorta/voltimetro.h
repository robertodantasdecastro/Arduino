int prev = 0;
int refresh = 1000;
float volt = 0.0;
float R1 = 100000.0;
float R2 = 10000.0;
float Vvalor = 0;
float vin = 0;
float voltMax = 12.1;
float voltMin = 11.0;

float verificaAmpere () {
 
  Avalor = analogRead(pinAmpereMotor);
  float ampere = map(Avalor, 0, 512, 0, 10);
 // ampere = ampere * 10;
  return (ampere); 
  
}

float verificaVoltagem () {

  Vvalor = analogRead(voltPIN);
  volt = (Vvalor * 5.0) / 1024.0;
  vin = volt / (R2/(R1+R2));
  return (vin);
}

void CarregaBateria () {

  if (millis() - TT > (TempVerBat * 1000)){

    //float ampere = analogRead (pinAnpereMotor);
    TT = millis();

    if (EstadoCarga == 0) {
      Vvolt = verificaVoltagem (); 


    }
    if (EstadoCarga == 1) {

      digitalWrite (cargaRELE, 0);
      delay(500);
      Vvolt = verificaVoltagem ();
      delay(100); 
      digitalWrite (cargaRELE, 1);


    }
    Serial.print("Volt. Bateria: ");
    Serial.println(Vvolt);

    if (Vvolt < VoltMin and EstadoCarga == 0) {
      EstadoCarga = 1;
      digitalWrite (cargaRELE, 1); 
      Serial.println("Ligando Carregador da bateria!");
    }
    if (Vvolt >= VoltMax and  EstadoCarga == 1) {
      EstadoCarga = 0;
      digitalWrite (cargaRELE, 0); 
      Serial.println("Carregador da bateria DESLIGADO!");
    }
  }

}



