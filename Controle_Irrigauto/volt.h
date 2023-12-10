
float R1 = 100000.0;
float R2 = 10000.0;

//int voltPIN = A1;

float verificaVoltagem (int voltPIN) { 
  
  float volt = 0.0;
  float Vvalor = 0;
  float vin = 0;
  Vvalor = analogRead(voltPIN);
  volt = (Vvalor * 5.0) / 1024.0;
  vin = volt / (R2/(R1+R2));
  return (vin);
}
