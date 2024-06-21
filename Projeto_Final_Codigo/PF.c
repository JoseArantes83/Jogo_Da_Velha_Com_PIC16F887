#include <PF.h>

int8 i = 0, j = 0;
int8 pontuacaoJ1 = 0, pontuacaoJ2 = 0, ganhador = 0;
int8 tabuleiro[3][3];

#INT_TIMER0
void  TIMER0_isr(VOID) {

   

}

void reinicia_tabuleiro(){

   for(i = 0; i < 3; i++){
   
      for(j = 0; j < 3; j++){
      
         tabuleiro[i][j] = -1;
      
      }
   
   }

}

int8 verifica_ganhador(int8 matriz[3][3]){
    
    int i = 0, j = 0;
    
    for(i = 0; i < 3; i++){
        
        if(matriz[i][0] != -1 && matriz[i][0] == matriz[i][1] && matriz[i][0] == matriz[i][2])
            return matriz[i][0];
        if(matriz[0][i] != -1 && matriz[0][i] == matriz[1][i] && matriz[0][i] == matriz[2][i])
            return matriz[0][i];
        
    }
    
    if(matriz[0][0] != -1 && matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2])
        return matriz[0][0];
        
    else if(matriz[0][2] != -1 && matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0])
        return matriz[0][2];
    
    else
        return 0;
    
}

void main(){
   setup_timer_0 (RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT); //1, 0 ms overflow
   enable_interrupts (INT_TIMER0) ;
   enable_interrupts (GLOBAL) ;
   
   reinicia_tabuleiro();

   WHILE(TRUE){
   
      
   
   }
}

