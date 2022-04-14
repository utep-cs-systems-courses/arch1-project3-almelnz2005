#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include <stdio.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW0 1
#define SW1 2
#define SW2 4
#define SW3 8
#define SWITCHES 15 		/* only 1 switch on this board */

int count = 0;
int countFactor = 1;
int noteToPlay = 0;

int a = 4545;
int f = 5714;
int cH = 3824;
int eH = 3034;
int fH = 2865;
int gS = 4819;
int noSound = 0;

int switches = 0;

void switch_init(){
    P2REN |= SWITCHES;		/* enables resistors for switches */
    P2IE |= SWITCHES;		/* enable interrupts from switches */
    P2OUT |= SWITCHES;		/* pull-ups for switches */
    P2DIR &= ~SWITCHES;		/* set switches' bits for input */
}

void leds_init(){
    P1DIR |= LEDS;
    P1OUT &= ~LEDS;		/* leds initially off */
}

static char switch_update_interrupt_sense(){
  char p2val = P2IN;		/* switch is in P1 */

  /* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void switching_tempo(){
  printf("DEBUG - The count before switching_tempo: %d\n", count);
  printf("DEBUG - Switches and SW0 is: %d.\n", switches & SW0);
  if(switches & SW0){
    //countFactor = 1;
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;


  }
  else if(switches & SW1){
    //countFactor = 2;
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;


  }
  else if(switches & SW2){
    //countFactor = 5;
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;

  }
  else if(switches & SW3){
    //countFactor = 10;
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED;
  }

  count  = count/10;
  count = count + countFactor;
}

int main() {
    configureClocks();
    enableWDTInterrupts();
    buzzer_init();
    switch_init();
    leds_init();

    //DEBUG - testing differt sounds. To set the frequecy with the period
    //divide the clock by the frequency you want this will give you the period you are
    //looking for
    //buzzer_set_period(8000);	/* start buzzing!!! 2MHz/1000 = 2kHz*/
    //buzzer_set_period(4000);
    
    or_sr(0x18);// CPU off, GIE on
}

void starWarsThemeSong(){
  switch(count){
  case 0:
    noteToPlay = 1;
    break;
  case 1500:
    noteToPlay = 2;
    break;
  case 1850:
    noteToPlay = 3;
    break;
  case 2000:
    noteToPlay = 1;
    break;
  case 2500:
    noteToPlay = 2;
    break;
  case 2850:
    noteToPlay = 3;
    break;
  case 3000:
    noteToPlay = 1;
    break;
  case 3650:
    noteToPlay = 0;
    break;
  case 4150:
    noteToPlay = 4;
    break;
  case 5650:
    noteToPlay = 5;
    break;
  case 6000:
    noteToPlay = 3;
    break;
  case 6150:
    noteToPlay = 6;
    break;
  case 6650:
    noteToPlay = 2;
    break;
  case 7000:
    noteToPlay = 0;
    count = 0;
    break;
  }

  switch(noteToPlay){
  case 0:
    buzzer_set_period(noSound);
    break;
  case 1:
    buzzer_set_period(a);
    break;
  case 2:
    buzzer_set_period(f);
    break;   
  case 3:
    buzzer_set_period(cH);
    break;
  case 4:
    buzzer_set_period(eH);
    break;
  case 5:
    buzzer_set_period(fH);
    break;
  case 6:
    buzzer_set_period(gS);
    break;
  default:
    break;
  }

  //switching_tempo();
  count = count + countFactor;
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}

void __interrupt_vec(WDT_VECTOR) WDT(){
  starWarsThemeSong();
  
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    //printf("DEBUG - Button pressed. In the PORT2_VECTOR.\n");
    switch_interrupt_handler();
  }
}
