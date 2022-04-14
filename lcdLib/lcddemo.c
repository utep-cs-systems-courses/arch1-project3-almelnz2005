/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <math.h>

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  //int col = 30;
  //int row  = 50;
  int col = 0;
  int row = 0;
  int a;
  int length = 20;
  int fCol = 50;
  int fRow = 50;

  //for(int j = 0; j < 10; j++){
  //  drawPixel(col, row, COLOR_WHITE);
  //  col ++;
  //  row ++;
  //}

  //col = 60;
  //row = 50;
  //for(int j = 0; j < 10; j++){
  //  drawPixel(col, row, COLOR_WHITE);
  //  col ++;
  //  row ++;
  //}

  //row = 80;
  //col = 30;
  //for(int j = 0; j < 40; j++){
  //  drawPixel(col, row, COLOR_WHITE);
  //  col++;
  //}

  //for(int j = 0; j < 10; j++){
  //  drawPixel(fCol+col, fRow+row, COLOR_WHITE);
  //  drawPixel(fCol-col, fRow+row, COLOR_GRAY);
  //  col ++;
  //  row ++;   
  //}

  //for(int j = 0; j < 10; j++){
  //  drawPixel(fCol+col, fRow+row, COLOR_WHITE);
  //  drawPixel(fCol+10-col,fRow+row, COLOR_GRAY);
  //  col ++;
  //  row ++;
  //}

  //or to draw an x using the following

  //for(int j = 0; j <= 10; j++){
  //  drawPixel(fCol + j, fRow+j, COLOR_WHITE);
  //  drawPixel(fCol+j, fRow+10-j, COLOR_GRAY);
  //}

  //for(int j = 0; j <= 10; j++){
  //  drawPixel(fCol+j, fRow+j, COLOR_WHITE);
  //  drawPixel(fCol+j, fRow-j, COLOR_GRAY);
  //  drawPixel(fCol-j, fRow+j, COLOR_BLUE);
  //  drawPixel(fCol-j, fRow-j, COLOR_GREEN);
  //}

  for(a = 0; a < length; a++){
    drawPixel(fCol+a, fRow+a, COLOR_BLUE);
    drawPixel(fCol+a, fRow, COLOR_PURPLE);
    drawPixel(fCol+length, fRow+a, COLOR_GREEN);

    //draws on every other pixel, on all odds
    if(a%2 == 1){
      for(int v = 0; v < a; v++){
	drawPixel(fCol+v, fRow+a, COLOR_PINK);
      }
    }
    
  }

  int sCol = 50, sRow = 100;
  int s;
  for(s = 0; s < length; s++){
    drawPixel(sCol+s, sRow+s, COLOR_BLACK);
    drawPixel(sCol+(length/2), sRow+s, COLOR_BLACK);
    drawPixel(sCol+s, sRow+(length/2), COLOR_BLACK);
    drawPixel(sCol+length-s, sRow+s, COLOR_BLACK);
  }

  int b = 45;
  int x = 0;

  x = sin(b);
}
