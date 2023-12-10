byte x = 0; 
void testa_i2c(){

  Wire.beginTransmission(5); 
  Wire.write("ci 1: ");        
  Wire.write(x);                
  Wire.endTransmission();    
/*
  Wire.beginTransmission(5); 
  Wire.write("ci 2: ");    
  Wire.write(x);              
  Wire.endTransmission(); 
  
  Wire.beginTransmission(3); 
  Wire.write("ci 2: ");    
  Wire.write(x);              
  Wire.endTransmission(); 
  */
  x++;
}
int verificaCi(String ci){
  int ci_real=0;
  if (ci=="A"){
    ci_real=1;
  } 
  if (ci=="B"){
    ci_real=2;   
  }
  if (ci=="C"){
    ci_real=3;
  } 
  if (ci=="D"){
    ci_real=4;   
  }
  return ci_real;
}
int StringParaInt (String s){
  int tamString = s.length(); 
  char c[tamString+1];
  s.toCharArray(c,tamString+1);
  int i = atoi(c);
  return i;
}

void configPortaCi(int ci, int porta, boolean estado) { //estado -> 0=OUTPUT 1=INPUT 
  Serial.print("T: ");
  Serial.print(ci);
  Serial.print(" - ");
  Serial.println(porta);
  Wire.beginTransmission(ci);
  
  
  
  char* saida="@P";
  saida+=char(porta);
 // saida+=',';
  //saida+=estado;
  Serial.print("V: ");
  Serial.println(saida);
//  Wire.write(saida);
  
  
//  char* p = "2,3,4,5";
//  Wire.write(0);
  //Wire.write(estado);
  Wire.endTransmission();
  delay(200);
  
}

void escrevePortaCi(int ci, int porta, int estado){
  
  Wire.beginTransmission(ci);
  Wire.write("@P");
  Wire.write(porta);
  Wire.write(estado);
  Wire.endTransmission();

}
boolean estadoPortaCi(int ci, int porta){

  Wire.beginTransmission(ci);
  Wire.write("#P");
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(ci, 1);
  while(Wire.available()){
    boolean rec=Wire.read(); 
    return rec;
  }

}
int validaTotal = 0;
boolean configuraEscravos (String Valor){ 
  //  @V:B04,XXX(A08,A09,A10,A11);  
  int valida = 0;
  

  boolean inicia=false;
  boolean lerValida=false;
  char recebe[]="";
  String valString="";
  String vValida="";
  boolean recebeLinha=false;

  char* Vvalor[]={
  };
  int ll =0;

  for (int i=0; i<Valor.length()-1; i++){
    if (!recebeLinha){
      if (inicia){
        if (Valor[i] == ',' or Valor[i] == ')') {
          if (valString.length()>0){
            int tc = valString.length();           
            char c[tc+2];
            valString.toCharArray(c,tc+1);
            Vvalor[ll]=c;
        /*  Serial.print(ll);
            Serial.print(" - Valor da porta: ");          
            Serial.println(Vvalor[ll]);  */
            String t = Vvalor[ll];
            int idVal = verificaCi(t.substring(0,1));
            int portaVal = StringParaInt(t.substring(1,3)); 
            configPortaCi(idVal, portaVal, 0);
            valida += portaVal;     
            ll++;
            valString="";
          }
        } 
        else {
          valString=valString+Valor[i];
        }
      }
      if (lerValida){
        vValida=vValida+Valor[i];
      }
      if (Valor[i]=='('){
        inicia=true; 
      }
      if (Valor[i]==')'){
        //recebeLinha=true;
        lerValida=true;
        inicia=false;
      } 
      if (Valor[i]==';'){
        lerValida=false;
        recebeLinha=true; 
        //inicia=false;       
      } 
    }
  }
  
  int id_ciBomba = verificaCi(Valor.substring(3,4));        //id do ci da bomba
  int porta_ciBomba = StringParaInt (Valor.substring(4,6)); //porta da bomba
  valida += porta_ciBomba;
  int id_VciBomba = false;  //verificador de atividade da chave magnetica
  int porta_VciBomba = false;  
  
  if (Valor.substring(7,8) != "X"){
    id_VciBomba = verificaCi(Valor.substring(7,8));  //verificador de atividade da chave magnetica
    porta_VciBomba = StringParaInt(Valor.substring(8,10));
    valida += porta_VciBomba;
  } 
  
  int vf = StringParaInt(vValida.substring(0,3));
  Serial.print(ll); 
  Serial.print(" Valida: ");
  Serial.print(vf);
  Serial.print(" - ");
  Serial.println(valida);
  validaTotal+=valida;
  /*
  for (int r=0; r<ll; r++){
    Serial.println(r);
 //   String ST = Vvalor[r];
  // Serial.println(ST);
 
 }*/

  
  
  if (Valor.substring(7,8) != "X"){ 
    //   configPortaCi(id_VciBomba, porta_VciBomba, 1); 
  }
  // configPortaCi(id_ciBomba, porta_ciBomba, 0);  //configurar porta da bomba
    
  if (vf==valida){
    return true;
  } else {
    return false;
  } 
}







