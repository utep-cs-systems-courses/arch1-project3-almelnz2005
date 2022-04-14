#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define REDLED BIT6  /* note that bit zero req'd for display */
#define GREENLED BIT0
#define LEDS (BIT0 | BIT6)

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

short redrawScreen = 1;
short buttonSample = 1;

static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void switch_init(){			/* setup switch */  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 5) {		/* 10/sec */
    secCount = 0;
    buttonSample = 1;
  }
}
  
void ledBinary();

void main()
{
  
  P1DIR |= LEDS;		/**< Green led on when CPU on */
  P1OUT |= LEDS;
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (buttonSample) {
      buttonSample = 0;
      ledBinary();
    }
    or_sr(0x10);	/**< CPU OFF */
  }
}
    
void ledBinary(){
  if (switches & SW4){
    P1OUT &= ~GREENLED;	/* led off */
    P1OUT &= ~REDLED;	/* led on */
    buzzer_set_period(6000);
  }
  
  if (switches & SW3){
    P1OUT |= GREENLED;	/* led off */
    P1OUT |= REDLED;	/* led on */
    buzzer_set_period(5000);
  }
  
  if (switches & SW2){
    P1OUT |= GREENLED;	/* led off */
    P1OUT &= ~REDLED;	/* led on */
    buzzer_set_period(4000);
  }
  
  if (switches & SW1){
    P1OUT &= ~GREENLED;	/* led off */
    P1OUT |= REDLED;	/* led on */
    buzzer_set_period(3000);
  }
}

/* Switch on S2 */
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
