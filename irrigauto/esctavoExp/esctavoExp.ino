#include <Wire.h>


void setup() {
 Serial.begin(9600);
 
 Wire.begin (5);
 Wire.onReceive(receba);
 delay(10);
 Wire.onRequest(envia);

}
int x=0;
void loop() {
  delay(100);
}

void receba(int howMany){
  while (1<Wire.available()){
     char c = Wire.read();
     Serial.print("C: ");
     Serial.println(c); 
  }
  x = Wire.read();
  Serial.print("I: ");
  Serial.println(x);
  
  
}

void envia () {
  
  Wire.write(x);
  
}
