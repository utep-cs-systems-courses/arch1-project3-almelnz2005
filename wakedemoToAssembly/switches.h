#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

extern char switch_update_interrupt_sense();
extern void switch_interrupt_handler();
extern int switches;
