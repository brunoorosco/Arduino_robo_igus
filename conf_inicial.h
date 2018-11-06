//inicialização dos pinos
void init_IO()
{
//////COLOCANDO PINOS COMO SAÍDA
  pinMode(STEP[1],1);
  pinMode(STEP[2],1);
  pinMode(STEP[3],1);
  pinMode(STEP[4],1);
  pinMode(PUL[1],1);
  pinMode(PUL[2],1);
  pinMode(PUL[3],1);
  pinMode(PUL[4],1);
  pinMode(ENABLE,1);
  pinMode(GND,1);
  pinMode(VACUO,1);
  pinMode(ARD_CLP,1);
  pinMode(LED_PROG,1);
  pinMode(LED_INT,1);
  
 ////CONFIGURAÇÃO COMO ENTRADA 
  pinMode(HOME1,0);
  pinMode(HOME2,0);
  pinMode(HOME3,0);
  pinMode(HOME4,0);
  pinMode(BT1,0);
  pinMode(BT2,0);
  pinMode(CLP_ARD,INPUT_PULLUP);
  digitalWrite(CLP_ARD,1);
  pinMode(PinoInt2, INPUT_PULLUP);

//VALOR INICIAL DAS PORTAS DIGITAIS
  digitalWrite(STEP[1],0);
  digitalWrite(STEP[2],0);
  digitalWrite(STEP[3],0);
  digitalWrite(STEP[4],0);
  digitalWrite(PUL[1],0);
  digitalWrite(PUL[2],0);
  digitalWrite(PUL[3],0);
  digitalWrite(PUL[4],0);
  digitalWrite(GND,0);
  digitalWrite(ENABLE,1);
  digitalWrite(VACUO,0);
  digitalWrite(38,0);
  digitalWrite(GND,0);
  //////////////////////////////////////
  
  //COLOCANDO PINOS COMO ENTRADA
}
