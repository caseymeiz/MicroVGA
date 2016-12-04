#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"

#include "main_asm.h" /* interface to the assembly module */

const int HSYNC_PERIOD = 763;
const int HSYNC_ACTIVE = 50;
const word ROWS         = 523;

word row = 0;

  
  
void interrupt 8 unset_interrupt(){
  PORTB |= row?0x03:0x02;
  TFLG1 |= 0x01;
}



void interrupt 9 hsync_interrupt(){
  TC1 += HSYNC_PERIOD;
  TC0 = TC1 - HSYNC_ACTIVE; 
  
  //PORTB = (++row ^ ROWS)?(PORTB & ~0x02):(row =0x00);   //maybe faster
  
  PORTB &= (++row == ROWS)?~0x03:~0x02;
  row = row^ROWS?row:0;

  PTP = 0;

  TFLG1 |= 0x02;        // bset clear the interrupt
}




void sync_init(){
  TSCR2 = 0x00;     // Timer Prescaler
  TIOS = 0x03;      // Enable Input Compare on T 0,1
  TSCR1 = 0x80;     // Enable Timer TCNT
  TC1 = HSYNC_PERIOD;
  TC0 = TC1 - HSYNC_ACTIVE;  
  TIE = 0x03;       // Enable TC0 TC1 interrupts
  asm{
    cli
  }
}

void main(void) {
  PLL_init();        // set system clock frequency to 24 MHz  
  DDRB = 0x03;
  DDRP = 0xFF;
  PORTB |= 0x03;
  sync_init();
  for(;;){

    PTP = (TC1-TCNT)>>6;
  }
  for(;;);
}
