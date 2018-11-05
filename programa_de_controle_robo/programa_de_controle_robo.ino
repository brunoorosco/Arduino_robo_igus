/*
 * Interrupção EXTERNA PINOS 2, 3, 21, 20, 19, 18
 * 
 * 
 // mover(1,0, 5000,100); // eixo 4 sobe ponta motor de acionamento, sentido de giro, e quantidade de passo
 // mover(1,1,10000,100); // eixo 4 desce ponta
 // mover(2,1, 5000,100); //eixo 3 desce  ---- motor de acionamento, sentido de giro, e quantidade de passo
 // mover(2,0, 5000,100); //eixo 3 sobe  ---- motor de acionamento, sentido de giro, e quantidade de passo
 // mover(3,0,5000,100); //eixo 2 desce
 // mover(3,1,9000,100); //eixo 2 sobe
 // mover(4,0,5000,100); //antihorario eixo base
 // mover(4,0,10000,100);
     
*/
//////definição geral
const int PUL[5] = {0,16,14,5,56};
const int STEP[5] = {0,17,15,4,55};
const int VELOCIDADE = 200;
const byte PinoInt2 = 1;

#define HORARIO       01
#define ANTIHORARIO   00
#define ENABLE        07
#define GND           06
#define HOME1         53
#define HOME2         51
#define HOME3         47
#define HOME4         49
#define BT_teste      45
#define VACUO         44
#define CLP_ARD       39
#define ARD_CLP       33
#define LED_PROG      35
#define LED_INT       37

#define BT1 57
#define BT2 58
#define BT3 59
#define BT4 60

////definição dos estados do switch case
#define posicao_inicial 0
#define aguarda_robo    1
#define posicao_1       2
#define posicao_2       3
#define posicao_3       4
#define posicao_4       5
#define posicao_5       6
#define posicao_6       7
#define posicao_7       8
#define posicao_8       9
#define posicao_final   10


int y;
int address[5] = {0,1,5,9,13};
int estado = posicao_inicial;
signed long posicao_setup[5]={0,-11900,10200,6700,0}; //{0,-17800,16000,-20000,0};
signed long posicaoTampa[5]={0,-4050,3300,5700,0}; //{0,-17800,16000,-20000,0};
//signed long posicaoTampa[5]={0, -4100, 2100, 4500,0};
int n_motor=0;
int giro=2;
long posicao_atual[5]={0,0,0,0,0};
long tempoAtual[5], tempoAnterior[5];
bool flagMove=0;
bool START=1;
/////DECLARAÇÃO DAS SUBROTINAS

#include "memoria.h"
#include "movimento.h"
#include "conf_inicial.h"

void pos_inicial(); //o robo posiciona todos os eixos para a posição home
void init_IO(); //inicialização das portas como saída e entrada
int mover(int motor, int sentido, int passo, int acelera);
void pos_1();
void pos_2();
void pos_3();
void pos_4();
void pos_5();
void pos_6();
void pos_7();
void pos_8();
void pos_f();
void pos_Tampa();
long EEPROMReadlong(long address);
void EEPROMWritelong(int address, long value);
///// FINAL DA DECLARAÇÃO DA SUBROTINA

///////////rotina de interrupção //////////////
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 60000;
 digitalWrite(LED_PROG, !digitalRead(LED_PROG));
 }


void INICIO(){
  
  START = 0;
}


void setup() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 60000;

  //OCR1A = 34280;
//  TCCR1B |= (1 << WGM12); // MODO CTC
  TCCR1B |= (1 << CS12); // PRESCALER 256
  TIMSK1 |= (1 << TOIE1);
  interrupts(); //habilita interrupções
  attachInterrupt(2, INICIO, FALLING);
   
  delay(1000);
  init_IO();
  Serial.begin(230400);
  
   for(int x=0; x<=4;x++)
   {
  //    posicao_atual[x] = EEPROMReadlong(address[x]);
      Serial.println(posicao_atual[x]);
        }
   delay(1000);
  
}



void loop() {

switch (estado)
  {  
    //PISIÇÃO INICIAL = HOME EM TODOS OS EIXOS
    case posicao_inicial:
      pos_inicial();
      START = 1;
    break;
        
    case aguarda_robo:
      while(!START)
      {
       //START=0;
      // estado = posicao_1;
      //  if(!digitalRead(CLP_ARD))
      //    {
      //     digitalWrite(ARD_CLP, 0);
            estado = posicao_1;
            START = 1;
          
       }
    
    break;

    case posicao_1:
      pos_1();
      
    break;

    case posicao_2:
      pos_2();
       
    break;

    case posicao_3:
      pos_3();
    break;
    
    case posicao_4:
      pos_4();
    break;
    
    case posicao_5:
      pos_5();
    break;

    case posicao_6:
      pos_6();
    break;
    case posicao_7:
      pos_7();
    break;
    
    case posicao_8:
      pos_8();
    break;

     case posicao_final:
      pos_f();
     break;

    }
  }
//}
void pos_inicial()
{
 if(!digitalRead(HOME1))
  {
    char sentido_temp;
   // if(posicao_atual[1]<0)sentido_temp=HORARIO;  //SE MENOR QUE ZERO SENTIDO HORARIO
    //  else sentido_temp=ANTIHORARIO;      // SE MAIOR QUE ZERO SENTODO ANTIHORARIO
    sentido_temp = HORARIO;
    mover(1,sentido_temp,1,VELOCIDADE-25);
  }
 if(!digitalRead(HOME2))
  {
    char sentido_temp;
    //if(posicao_atual[2]<0)sentido_temp=HORARIO;
      //else sentido_temp=ANTIHORARIO;   
    sentido_temp = ANTIHORARIO;   
    mover(2,sentido_temp,1,VELOCIDADE+50); 
    
  }
 if(!digitalRead(HOME3))
  {
    char sentido_temp;
 //   if(posicao_atual[3]<0)sentido_temp=ANTIHORARIO;
  //    else sentido_temp=HORARIO;
       sentido_temp = ANTIHORARIO;   
    mover(3,sentido_temp,1,VELOCIDADE-50);
   }  
 if(digitalRead(HOME1) & digitalRead(HOME2) & digitalRead(HOME3) & digitalRead(HOME4))
  {   
    for(int i=0; i<=5;i++)
    { posicao_atual[i] =0;
      Serial.println(posicao_atual[i]);
    }
    estado = aguarda_robo;   
  }    
}


///retirar a peça ///////////////////////////////////////////////////////
void pos_1(){
 
  char sentido_temp;
        if(posicao_atual[1] != posicao_setup[1])
          {
            if(posicao_setup[1]<0)sentido_temp=ANTIHORARIO;
              else sentido_temp=HORARIO;
            mover(1,sentido_temp,1,50);       
          }
         else estado = posicao_2;
   }
/////////////////////////////////////////////////////////////////////////
void pos_2(){
   char sentido_temp;
    if(posicao_atual[2]!=posicao_setup[2])
      {
     
        if(posicao_setup[2]>=0)sentido_temp=HORARIO;
          else sentido_temp=ANTIHORARIO;
        
        mover(2,sentido_temp,1,100);    
          }
        else estado = posicao_3;      
}

///retirar a peça
void pos_3(){
  char sentido_temp;
       if(posicao_atual[3]!=posicao_setup[3])
          {
            if(posicao_setup[3]>=0) sentido_temp=HORARIO;               
             else sentido_temp=ANTIHORARIO;
            mover(3,sentido_temp,1,75);
          }
          else 
          {
            //while(1);
            estado = posicao_4;
            delay(1000);
            digitalWrite(VACUO, 1);
            delay(3000);
          }
}
///////////////////////////////////////////////////          
void pos_4(){
char sentido_temp;
if(!digitalRead(HOME3))
  {   
    if(posicao_atual[3]>0)sentido_temp=ANTIHORARIO;
      else sentido_temp=HORARIO;
    
    mover(3,sentido_temp,1,200);
    }
    else estado = posicao_5;
   if(!digitalRead(HOME1))
  {
   //   if(posicao_atual[1]<=0)sentido_temp=HORARIO;
   //   else sentido_temp=ANTIHORARIO;    
    mover(1,!sentido_temp,1,300);
  }
    }

void pos_5(){
char sentido_temp;
    if(!digitalRead(HOME1) & digitalRead(HOME2) )
  {
   
   // if(posicao_atual[1]<0)
   sentido_temp=HORARIO;
   //   else sentido_temp=ANTIHORARIO;    
    mover(1,sentido_temp,1,VELOCIDADE);
  }
//    if(digitalRead(HOME1)) {
 //     mover(1,sentido_temp,1,VELOCIDADE);
  //    delay(100);
 //  }
    
   if(!digitalRead(HOME2))
  {
  
    if(posicao_atual[2]>0)sentido_temp=ANTIHORARIO;
      else sentido_temp=HORARIO;
     mover(2,sentido_temp,1,VELOCIDADE);
  }
  if(digitalRead(HOME2) & digitalRead(HOME1)){
      estado = posicao_6;
      
     
      }
  }

void pos_6(){

  char sentido_temp;   

  if(posicaoTampa[1] != posicao_atual[1]){
    if(posicaoTampa[1]>posicao_atual[1])sentido_temp=HORARIO;
      else sentido_temp=ANTIHORARIO;
    mover(1,sentido_temp,1,VELOCIDADE-50);
  }
  else  estado = posicao_7;
}
 void pos_7(){

  char sentido_temp;   
    if(posicaoTampa[2] != posicao_atual[2]){
    if(posicaoTampa[2]>posicao_atual[2])sentido_temp=HORARIO;
      else sentido_temp=ANTIHORARIO;
    mover(2,sentido_temp,1,VELOCIDADE);
  }
   else  estado =  posicao_8;
 }
 void pos_8(){
  long posicaoAnterior;
  char sentido_temp;  
   if(posicaoTampa[3] != posicao_atual[3]){
    if(posicaoTampa[3]>posicao_atual[3])sentido_temp=HORARIO;
      else sentido_temp=ANTIHORARIO;
    mover(3,sentido_temp,1,300);
  }
       
    
    if(posicaoTampa[1] == posicao_atual[1] && posicaoTampa[2]== posicao_atual[2] && posicaoTampa[3]== posicao_atual[3])
     {
    
      for(int x=0; x<=4;x++){
      EEPROMWritelong(address[x], posicao_atual[x]);
      }
      delay(1000);
      long x = posicao_atual[3];
      while( posicao_atual[3] - x < 600){
                mover(3,HORARIO,1,50);    
              //  Serial.println(posicao_atual[3]); 
               // Serial.println(posicao_atual[3] - x); 
      }
      
      digitalWrite(VACUO, 0);
      estado = posicao_final;
    }
    
  //  if(posicao_atual[2]<=0)sentido_temp=ANTIHORARIO;
  //    else sentido_temp=HORARIO;
    
  //  mover(2,sentido_temp,1,VELOCIDADE);
   
}
void pos_f()
{
  if(!digitalRead(HOME1))
  {
    char sentido_temp;
   // if(posicao_atual[1]<0)sentido_temp=HORARIO;  //SE MENOR QUE ZERO SENTIDO HORARIO
    //  else sentido_temp=ANTIHORARIO;      // SE MAIOR QUE ZERO SENTODO ANTIHORARIO
    sentido_temp = HORARIO;
    mover(1,sentido_temp,1,150);
  }
 if(!digitalRead(HOME2))
  {
    char sentido_temp;
    //if(posicao_atual[2]<0)sentido_temp=HORARIO;
      //else sentido_temp=ANTIHORARIO;   
    sentido_temp = ANTIHORARIO;   
    mover(2,sentido_temp,1,150); 
    
  }
 if(!digitalRead(HOME3))
  {
    char sentido_temp;
 //   if(posicao_atual[3]<0)sentido_temp=ANTIHORARIO;
  //    else sentido_temp=HORARIO;
       sentido_temp = ANTIHORARIO;   
    mover(3,sentido_temp,1,150);
   }  
 if(digitalRead(HOME1) & digitalRead(HOME2) & digitalRead(HOME3) & digitalRead(HOME4))
  {   
    for(int i=0; i<=5;i++)
    { posicao_atual[i] =0;
      Serial.println(posicao_atual[i]);
    }
    //digitalWrite(ARD_CLP, 1);
    
    digitalWrite(ARD_CLP, 1);
    digitalWrite(ARD_CLP, 1);
      while(!digitalRead(CLP_ARD));
    delay(1000);
     digitalWrite(ARD_CLP, 0);
    estado = posicao_inicial;
    }    
}
