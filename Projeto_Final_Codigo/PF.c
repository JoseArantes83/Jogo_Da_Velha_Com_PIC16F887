#include <PF.h>

#INT_TIMER0
void  TIMER0_isr(void) 
{

}

void main()
{
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT);      //1,0 ms overflow

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);

   while(TRUE)
   {

   }
}

