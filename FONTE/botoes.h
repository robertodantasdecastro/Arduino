void beep(unsigned int tmpBeep, int vol){

  TempoBeep = millis() + tmpBeep;
  analogWrite(beep_Pin, vol);
  // delay(tmpBeep);
  analogWrite(beep_Pin, 0); 
}

void execuataLigaDesliga (int id){http://www.diariodosertao.com.br/

  if (!Toque.dataAvailable()) {
    if (id==0){
      if (curto[id]==false && botaoLigado[id]==true){
        digitalWrite (portaRELE[id],1); 
      } 
      else {
        digitalWrite (portaRELE[id],0);  
      }
    } 
    else if (id==1){
      if (curto[id]==false && botaoLigado[id]==true){
        digitalWrite (portaRELE[id],1);
      } 
      else {
        digitalWrite (portaRELE[id],0);  
      }
    } 
    else if (id==2){



    } else if (id==4){

      curto[0] = false;
StatusDesenhoCurto[id]=false;
botaoDesenho[id]=false;
botaoLigado[id]=false;
StatusDesenhado = false;
    }
  }
  if (curto[id]==true){
    digitalWrite (portaRELE[id],0);  
  }
}
void TocarTela(){
  if (Toque.dataAvailable()){
    Toque.read();
    toqueX = Toque.getX();
    toqueY = Toque.getY();
    tempoToque = 0;
  }
}

void LigaDesliga(int id, int x1, int y1, int x2, int y2) {
  //Tela.setColor(255, 255, 255);
  Tela.setColor(150,150,150);
  Tela.drawRoundRect (x1, y1, x2, y2);

  TocarTela();

  if (Toque.dataAvailable() && (((toqueX>=x1)&&(toqueX<=x2))&&((toqueY>=y1)&&(toqueY<=y2)))) {
    //  analiza();
    if ((curto[id]==false) && botaoLigado[id]==false){
      botaoLigado[id]=true;
      Tela.setColor(VGA_MAROON);
    }
    else{
      botaoLigado[id]=false;

      Tela.setColor(VGA_BLUE);
    }
    Tela.drawRoundRect (x1, y1, x2, y2);
    botaoDesenho[id] = false;
    delay(500);
  }
}



void botaoLigaDesliga(int id, int x1, int y1, int t_x, int t_y, String t1, String t2, String cor1, String cor2){
  /*
  //tamanho do botao
   int f_x=146;
   int f_y=35;
   //---------------
   **/
  int f_x=t_x;
  int f_y=t_y;

  int x2 = x1+f_x;
  int y2 = y1+f_y;

  int v1 = t1.length();
  int p1;
  if (v1>1){
    p1 = (((v1*10)+(v1*6) - f_x)/2)*(-1);
  } 
  else {
    p1 = 3; 
  }
  int v2 = t2.length();
  int p2;
  if (v2>1){
    p2 = (((v2*10)+(v2*6) - f_x)/2)*(-1);
  } 
  else {
    p2 = 3; 
  }

  LigaDesliga(id, x1,y1,x2,y2);

  if (!Toque.dataAvailable() && (botaoDesenho[id] == false)){
    int sombra=1;
    Tela.setColor(41,58,69);
    Tela.fillRoundRect(x1+sombra,y1+sombra,x2+sombra,y2+sombra);
    String cor;
    if (botaoLigado[id]==false){
      cor = cor1;
    }
    else{
      cor = cor2;
    }
    if (cor == "verde"){
      Tela.setColor(50,90,50);
    }
    else if (cor == "vermelho"){
      Tela.setColor(VGA_RED);
    }
    else if (cor == "azul"){
      Tela.setColor(41,100,139);
    }
    else if (cor == "verdeC"){
      Tela.setColor(VGA_OLIVE);
    }
    else if (cor == "rosa"){
      Tela.setColor(180,100,139);
    }
    else if (cor == "laranja"){
      Tela.setColor(255,109,8);
    }
    else if (cor == "marron"){
      Tela.setColor(VGA_MAROON);
    }
    else if (cor == "limao"){
      Tela.setColor(VGA_LIME);
    }
    if (botaoLigado[id]==false){

      Tela.fillRoundRect(x1,y1,x2,y2);
      Tela.setColor(VGA_WHITE);
      Tela.setBackColor(VGA_TRANSPARENT);
      Tela.setFont(BigFont);
      Tela.print(t1, x1+p1,y1+9);

    }
    else{

      Tela.fillRoundRect(x1,y1,x2,y2);
      Tela.setColor(VGA_WHITE);
      Tela.setBackColor(VGA_TRANSPARENT);
      Tela.setFont(BigFont);
      Tela.print(t2, x1+p2,y1+9);

    }

    botaoDesenho[id]=true;
    execuataLigaDesliga (id);
  }
}

void ApertaEM(int id, int x1, int y1, int x2, int y2) {

   
    Tela.setColor(40,40,40);
    Tela.drawRect (x1, y1, x2, y2);

    TocarTela();

    //delay(30);
    if (Toque.dataAvailable() && ((toqueX>=x1)&&(toqueX<=x2))&&((toqueY>=y1)&&(toqueY<=y2))) {


      // int n=1;
      if ((id >= 0) && (id <= 3)) {
        n=0;
      } 
      else if ((id >= 4) || (id <= 7)) {
        n=1;
      }
      Tela.setColor(VGA_YELLOW);
      if (((manda[n]+1) < tencaoMax) && ((id == 0) || (id==4))){
        manda[n]+=1.00;
      } 
      else if (((manda[n]-1) > 0.05) && ((id == 1) || (id==5))){ 
        manda[n]-=1.00;
      } 
      else if (((manda[n]+0.05) < tencaoMax) && ((id == 2) || (id==6))){ 
        manda[n]+=0.05;
      }
      else if (((manda[n]-0.05) > 0.00) && ((id == 3) || (id==7))){ 
        manda[n]-=0.05;
      } 
      else {
        Tela.setColor(VGA_RED);
      }

      Tela.drawRect (x1, y1, x2, y2);
      botaoPress[id] = false;
      delay(10);
      analiza(true);
    }
    
}

void botaoSeta(int id, int x1, int y1, String dir){
  int tamX = 50;
  int tamY = 18;
  int x2 = x1+tamX;
  int y2 = y1+tamY;

  ApertaEM(id, x1,y1,x2,y2);

  if (!Toque.dataAvailable() && botaoPress[id] == false){


    int sombra=0;
    if (sombra>0){
      Tela.setColor(41,58,69);
      // Tela.setColor(cor);
      Tela.fillRect(x1+sombra,y1+sombra,x2+sombra,y2+sombra);

    }


    Tela.setColor(41,100,139); 
    Tela.fillRect(x1,y1,x2,y2);

    Tela.setColor(40,40,40);
    Tela.drawRect(x1,y1,x2,y2);

    Tela.setColor(100,100,240);
    Tela.drawLine(x1+1,y1+1,x1+tamX-1,y1+1);
    Tela.drawLine(x1+1,y1+1,x1+1,y1+tamY-1);
    Tela.drawLine(x1+2,y1+2,x1+tamX-1,y1+2);
    Tela.drawLine(x1+2,y1+2,x1+2,y1+tamY-1);

    Tela.setColor(0,0,45);
    Tela.drawLine(x1+1,y1+tamY-1,x1+tamX-1,y1+tamY-1);
    Tela.drawLine(x1+2,y1+tamY-2,x1+tamX-2,y1+tamY-2);
    Tela.drawLine(x1+tamX-1,y1+1,x1+tamX-1,y1+tamY-1);
    Tela.drawLine(x1+tamX-2,y1+2,x1+tamX-2,y1+tamY-2);

    int tamMeio = tamX / 2;

    int Tri_x1,Tri_y1,Tri_x2,Tri_y2,Tri_x3,Tri_y3;
    if (dir == "cima"){
      Tri_x2 = x1+tamMeio;
      Tri_y2 = y1+5;

      Tri_x1 = x1+(tamMeio/2)+5;
      Tri_y1 = y1+tamY-5;

      Tri_x3 = x1+(tamMeio/2)+tamMeio-5;
      Tri_y3 = y1+tamY-5;

    }
    else if(dir == "baixo"){
      Tri_x2 = x1+tamMeio;
      Tri_y2 = y1+tamY-5;

      Tri_x1 = x1+(tamMeio/2)+5;
      Tri_y1 = y1+5;

      Tri_x3 = x1+(tamMeio/2)+tamMeio-5;
      Tri_y3 = y1+5;
    }


    Tela.setColor(VGA_WHITE);
    geo.fillTriangle(Tri_x1,Tri_y1,Tri_x2,Tri_y2,Tri_x3,Tri_y3);
    botaoPress[id]=true;
    //rial.println("Desenhar");


  }
}





