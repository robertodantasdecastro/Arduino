void enviaI2Cint(int valor){
  Wire.write(valor);
}
void enviaI2Cchar(char valor){
  Wire.write(int(valor));
}
String cmd;
int n=0;
boolean inicia = false;
boolean terminado = false; 
char recebe[]="";

void limpaChar(){
  int i=0;
  while (valor[i]!= '\0'){
    valor[i]='\0';
    i++;
  }
  memset(&valor[0],0,strlen(valor));
}
void envia() {
  //  Wire.write((uint8_t*)valor,6);
  int len = strlen(valor);
  //Serial.println(valor[index]);
  Wire.write(valor[index]);
  ++index;
  if (index >= len) {
    index = 0;
  }
}
void receba(int howMany){
  while (Wire.available()){    
    char c=char (Wire.read());  
    
    if (c==';'){
      inicia = false; 
      terminado = true;       
    }
    if (inicia) {
      recebe[n]=c;
      cmd = cmd+recebe[n];
      n++;
    }
    if (c=='@'){
      cmd = "";
      inicia = true;
    }
    else {
      n=0; 
    }
    if (terminado) {
      Serial.print(".... -");
      Serial.print(cmd);
      Serial.println("- ...."); 
      
      terminado = false; 
      cmd = "";
    }
  }
}
