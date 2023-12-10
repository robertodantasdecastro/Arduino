#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include "DHT.h"

#include "EepromUtil.h";
#include "volt.h";
#include "icones.h";  


//Variaveis do LCD 16x2
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8); Pinagem padrao
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
//----------------------------------------



//Variaveis da Ethernet
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#endif
EthernetClient client;
//---------------------


//----DHT11-----

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//--------------
void receiveEvent(int howMany)
{
  while (1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}


void setup() {  
  Serial.begin(9600);
  
  eeprom_write_int(8, 123);
  
  dht.begin();
  lcd.begin(16,2); 
  Wire.begin(4);    // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  
  lcd.createChar(1,termometro);
  lcd.createChar(2,gota);
  lcd.createChar(3,setaDir);
  lcd.createChar(4,setaEsq);
  lcd.createChar(5,setaCim);
  lcd.createChar(6,setaBax);
  
  lcd.clear();
  lcd.setCursor(0,0);  
  
/*  //REDE
  lcd.print("Aguardando IP...");
  
  #if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
  if (Ethernet.begin() == 0) {
#else
  if (Ethernet.begin(mac) == 0) {
#endif  
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.autoscroll();
   lcd.print("A configuracao do via DHCP falhou!"); 
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  // print your local IP address:
  lcd.clear();
  lcd.setCursor(0,0);
   
  lcd.print("IP: ");
 // lcd.setCursor(0,1);
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    lcd.print(Ethernet.localIP()[thisByte], DEC);
    if (thisByte < 3){
      lcd.print(".");
    }
  }
  
  int *v;
  */
 // eeprom_read_int(8,v);
  
//  lcd.setCursor(0,0);
//  lcd.print("V eeprom:");

 // delay(3000);
   lcd.clear();
 
  
  
}

void loop() {
  
  
  
  lcd.setCursor(0,0); 
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  float sol = verificaVoltagem (A2);
  float bat = verificaVoltagem (A1);
  lcd.write(1);
  lcd.print(t);
  lcd.print((char)223); //degree sign
  lcd.print("C - ");
  
  lcd.write(2);
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("S:");
  lcd.print(sol);
  lcd.print("v  ");
  lcd.print("B:");
  lcd.print(bat);
  lcd.print("v");
  
  
  delay(500);
}

  
