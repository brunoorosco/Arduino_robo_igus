# Arduino_robo_igus
controle do motor de 4 eixos da igus.

Iniciamente desenvolvido no IDE Arduino.

- movimento inicial(HOME);
- movimento de retirada da tampa;
- movimento inicial;
- movimento fechamento da embalagem.

Programa principal //Program Main
   - programa_de_controle_robo.ino

Subprogramas //subprogram
   - conf_inicial.h //configuração inicial do uC
   - movimento.h    // trecho do programa que realiza os movimentos
   - memoria.h      // futuro programa de armazenamento das variaveis do encoder
