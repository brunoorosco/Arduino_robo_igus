
//********* subrotina de movimento do motor **************// 
int mover(int motor, int sentido, int passo, int acelera){
  

   digitalWrite(STEP[motor], sentido);
   tempoAtual[motor] = micros();
   if (tempoAtual[motor] - tempoAnterior[motor] >= acelera)
   {   
  
  /*  
    Serial.print(tempoAtual[motor]);
    Serial.print("-");
    Serial.println(tempoAnterior[motor]);
    Serial.println(tempoAtual[motor] - tempoAnterior[motor]);
    if( y++ == 5)while(1);*/
       digitalWrite(PUL[motor],!digitalRead(PUL[motor]));
       tempoAnterior[motor] = micros();
       flagMove=1;
       digitalWrite(STEP[motor], sentido);

         if(y++ ==2)
         {
      /*
      Serial.print("posicao 1 - ");
      Serial.println(posicao_atual[1]);
      Serial.print("posicao 2 - ");
      Serial.println(posicao_atual[2]);
      Serial.print("posicao 3 - ");
      Serial.println(posicao_atual[3])*/  
          y=0;
         if(sentido)posicao_atual[motor]++;
         else posicao_atual[motor]--;
         }
    
   }
}
