#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

//not needed
//#define LED BIT6

void move_square_shape(){
  static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static char blue = 31, green = 0, red = 31;
  static unsigned char step = 0;

  //fillRectangle(row, col, 1, 1, colors);
}

void update_triangle_shape(int drawState){
  static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static char blue = 31, green = 0, red = 31;
  static unsigned char step = 0;
  if(drawState == 4){
    return;
  }
  if(step <= 60){
    int startCol = col - step;
    int endCol = col + step;
    int width = 1 + endCol - startCol;
    //a color in this BGN encoding is BBBB BGGG GGGR RRRR
    unsigned int color = (blue << 11) | (green << 5) | red;
    fillRectangle(startCol, row + step, width, 1, color);
    fillRectangle(startCol, row - step, width, 1, color);
    switch(drawState){
    case 1:
      red = (red - 3) % 32;
      break;
    case 2:
      blue = (blue + 2) % 32;
      break;
    case 3:
      green = (green + 1) % 64;   
      break;
    default:
      break;
    }
    step ++;
  }
  else{
    clearScreen(COLOR_BLUE);
    step = 0;
  }
}
