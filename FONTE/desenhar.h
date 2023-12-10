void desenharStatus () {
  
  if (StatusDesenhado == false){
    Tela.setBackColor(VGA_TRANSPARENT);
    Tela.setColor(80,80,80);
   
    Tela.setColor(50,50,50);
    Tela.fillRect(0,0,319,12);
    Tela.setColor(41,100,139);
    Tela.fillRect(0,12,319,13);
    Tela.setColor(180,180,180);
    Tela.setFont(SmallFont);
    Tela.print("CT:", 2,0);
       
    Tela.setColor(10,10,10);
    Tela.fillRect(0,182,319,239);
    Tela.setColor(50,50,50);
   
    
    Tela.setColor(80,80,80);
    Tela.drawRect(0,86,319,99);
    
    
    
    Tela.drawRect(0,134,319,147); 
    Tela.drawRect(0,182,319,195); 
    Tela.setColor(50,50,50);
    Tela.fillRect(1,87,318,98);
    Tela.fillRect(1,135,318,146);
    Tela.fillRect(1,183,319,194);
   
    Tela.drawRect(0,0,319,239); 
    Tela.drawLine(159,16,159,239);
    
    Tela.setColor(VGA_YELLOW);
    Tela.print("TENCAO 1", 35,87);
    Tela.print("TENCAO 2", 195,87);
    Tela.setColor(255,109,8);
    Tela.print("CORRENTE 1", 35,135);
    Tela.print("CORRENTE 2", 195,135);
    Tela.setColor(VGA_WHITE);
    Tela.print("SAIDA 1", 30,183);
    Tela.print("AUTO", 127,183);
    Tela.print("SAIDA 2", 190,183);
    Tela.print("AUTO", 287,183);
    StatusDesenhado = true;
  }
 
}


float geraMenu() {

  botaoLigaDesliga( 0, 2, 199, 130, 35, "LIGAR", "DESLIGAR", "azul", "vermelho");
  botaoLigaDesliga( 1, 162, 199, 130, 35, "LIGAR", "DESLIGAR", "azul", "vermelho");
  botaoLigaDesliga( 2, 134, 199, 22, 35, "A", "A", "verdeC", "marron");
  botaoLigaDesliga( 3, 294, 199, 22, 35, "A", "A", "verdeC", "marron");
  botaoSeta(0, 18, 15, "cima");
  botaoSeta(1, 18, 66, "baixo");
  botaoSeta(2, 91, 15, "cima");
  botaoSeta(3, 91, 66, "baixo");
 
  botaoSeta(4, 180, 15, "cima");
  botaoSeta(5, 180, 66, "baixo");
  botaoSeta(6, 251, 15, "cima");
  botaoSeta(7, 251, 66, "baixo");
  
 //  botaoLigaDesliga( 4,30, 30, 22, 35, "A", "A", "verdeC", "marron");
}


