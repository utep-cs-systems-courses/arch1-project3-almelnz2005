#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "music.h"

int a = 4545;
int f = 5714;
int cH = 3824;
int eH = 3034;
int fH = 2865;
int gS = 4819;
int noSound = 0;

void starWarsThemeSong(int count){
  static int noteToPlay = 0;
  
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
}
