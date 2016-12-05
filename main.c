#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"

#include "main_asm.h" /* interface to the assembly module */

const unsigned short HSYNC_PERIOD    = 763;
const unsigned short HSYNC_ACTIVE    = 153;
const unsigned short ROWS = 523;

word row = 0;
unsigned int lasth = 0;

  
void interrupt 8 unset_interrupt(){
  //PORTB |= row?0x03:0x02;
  PORTB  = 0x03;
  TC0 += HSYNC_PERIOD;
  TFLG1 = 0x01;       // bset clear the interrupt
}



void interrupt 9 hsync_interrupt(){
  //lasth = TCNT; 
  /*
  if(++row == ROWS){
    row = PORTB = 0x00;     // Bring hysnc and vsync low for new frame
               
  } else {
    PORTB = 0x01;    // Bring hsync low for new row
  }*/
  
  PORTB  = ++row == ROWS?row=0:0x01;

  PTP = 0;              // Bring the color bits low every new row


  TC1 += HSYNC_PERIOD;
  TFLG1 = 0x02;        // bset clear the interrupt
}




void sync_init(){
  TSCR2 = 0x00;     // Timer Prescaler
  TIOS = 0x03;      // Enable Input Compare on T 0,1
  TSCR1 = 0x80;     // Enable Timer TCNT
  TC0 = HSYNC_PERIOD - HSYNC_ACTIVE;  
  TC1 = HSYNC_PERIOD;
  TIE = 0x03;       // Enable TC0 TC1 interrupts
  asm{
    cli
  }
}

void main(void) {
  unsigned int i;
  int xpos;
  word col;
  word color = 1;
  //int ypos; count 
  unsigned long x1sq;
  unsigned long y1sq;
  unsigned long x2sq;
  unsigned long y2sq;
  
  PLL_init();        // set system clock frequency to 24 MHz 
  DDRB = 0x03;
  DDRP = 0x07;
  PORTB |= 0x03;
  sync_init();
  ad0_enable();
  
  
  for(;;){

     //PTP = (lasth -TCNT);
     
     //PTP = vram[TC1-TCNT%680];
    for(i = 0; i <0x3FFF; i++){
      xpos = (TC1-TCNT) ;
      if(xpos > x1sq && row > y1sq && xpos < x2sq  && row < y2sq){
        PTP = color;
      }else{
        PTP = color >> 3;
      }
    }
    PTP = color >> 3;
    
    //x1sq = 512;
    //y1sq = 512;
    color += PORTA?0:1;
    
    x1sq = ad0conv(7)-200;
    y1sq = ad0conv(6)-200;
    
   // x1sq = x1sq * HSYNC_PERIOD / 1023;
    x2sq = x1sq + 75;
    
    //y1sq = y1sq * 480 / 1023;
    //y1sq += 23;
    y2sq = y1sq + 75 ; 
    
     
     
  
    /*col = TC1 - TCNT;
    if( col> 300 && col < 350 && row > 250 && row <300){
      PTP = 1;
    } else {
      PTP = 3 ;
    }*/
  }
  for(;;);
}
