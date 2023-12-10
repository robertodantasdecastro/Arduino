void Iniciar_rfid(){
  int i;
  //byte i = 0;
 
  int val = 0;
  int checksum = 0;
  int bytesLidos = 0;
  int tempByte = 0;
  int tagBytes[6];
  char tagValor[10];

}


int encontrarChave( char tagValor[10] ) {
  for (int estaChave = 0; estaChave < NumeroDeChaves; estaChave++) {
    if(strcmp(tagValor, ChavesPermitidas[estaChave]) == 0)
    {
      return(estaChave + 1);
    }
  }
  return(0);
}

void verificaRFID () {
  
}
