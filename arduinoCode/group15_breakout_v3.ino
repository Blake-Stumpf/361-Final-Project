#include "Adafruit_Arcada.h"
Adafruit_Arcada arcada;

uint32_t buttons, last_buttons;

uint8_t paddle_pos = 85;

uint8_t ballX = 25;
uint8_t ballY = 120; 

uint8_t ballRad = 5;

int direcx = 1;
int direcy = 1;

int user_score = 0;

bool start = false;

// preallocates vectors
bool block[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}; // weather the block is active
uint8_t block_y0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //top left corner y location
uint8_t block_x0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //top left corner x location
uint8_t block_ylen[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //length of y axis
uint8_t block_xlen[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //length of x axis
int pointVal[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //point values of the blocks
uint16_t colorVec[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // colors of the blocks

int maxScore = 0;
int gamespeed = 0;
#define grey 0x94B2

void setup()
{
  block[0] = true;
  block_y0[0] = 15;
  block_x0[0] = 10;
  block_ylen[0] = 10;
  block_xlen[0] = 35;
  pointVal[0] = 10;
  colorVec[0] = ARCADA_BLUE;

  block[1] = true;
  block_y0[1] = 15;
  block_x0[1] = 55;
  block_ylen[1] = 10;
  block_xlen[1] = 35;
  pointVal[1] = 10;
  colorVec[1] = ARCADA_BLUE;

  block[2] = true;
  block_y0[2] = 15;
  block_x0[2] = 100;
  block_ylen[2] = 10;
  block_xlen[2] = 35;
  pointVal[2] = 10;
  colorVec[2] = ARCADA_BLUE;

  block[3] = true;
  block_y0[3] = 15;
  block_x0[3] = 145;
  block_ylen[3] = 10;
  block_xlen[3] = 35;
  pointVal[3] = 10;
  colorVec[3] = ARCADA_BLUE;

  block[4] = true;
  block_y0[4] = 15;
  block_x0[4] = 190;
  block_ylen[4] = 10;
  block_xlen[4] = 35;
  pointVal[4] = 10;
  colorVec[4] = ARCADA_BLUE;

  block[5] = true;
  block_y0[5] = 35;
  block_x0[5] = 10;
  block_ylen[5] = 10;
  block_xlen[5] = 35;
  pointVal[5] = 5;
  colorVec[5] = ARCADA_ORANGE;

  block[6] = true;
  block_y0[6] = 35;
  block_x0[6] = 55;
  block_ylen[6] = 10;
  block_xlen[6] = 35;
  pointVal[6] = 5;
  colorVec[6] = ARCADA_ORANGE;

  block[7] = true;
  block_y0[7] = 35;
  block_x0[7] = 100;
  block_ylen[7] = 10;
  block_xlen[7] = 35;
  pointVal[7] = 5;
  colorVec[7] = ARCADA_ORANGE;

  block[8] = true;
  block_y0[8] = 35;
  block_x0[8] = 145;
  block_ylen[8] = 10;
  block_xlen[8] = 35;
  pointVal[8] = 5;
  colorVec[8] = ARCADA_ORANGE;

  block[9] = true;
  block_y0[9] = 35;
  block_x0[9] = 190;
  block_ylen[9] = 10;
  block_xlen[9] = 35;
  pointVal[9] = 5;
  colorVec[9] = ARCADA_ORANGE;

  block[10] = true;
  block_y0[10] = 55;
  block_x0[10] = 10;
  block_ylen[10] = 10;
  block_xlen[10] = 35;
  pointVal[10] = 3;
  colorVec[10] = ARCADA_YELLOW;

  block[11] = true;
  block_y0[11] = 55;
  block_x0[11] = 55;
  block_ylen[11] = 10;
  block_xlen[11] = 35;
  pointVal[11] = 3;
  colorVec[11] = ARCADA_YELLOW;

  block[12] = true;
  block_y0[12] = 55;
  block_x0[12] = 100;
  block_ylen[12] = 10;
  block_xlen[12] = 35;
  pointVal[12] = 3;
  colorVec[12] = ARCADA_YELLOW;

  block[13] = true;
  block_y0[13] = 55;
  block_x0[13] = 145;
  block_ylen[13] = 10;
  block_xlen[13] = 35;
  pointVal[13] = 3;
  colorVec[13] = ARCADA_YELLOW;

  block[14] = true;
  block_y0[14] = 55;
  block_x0[14] = 190;
  block_ylen[14] = 10;
  block_xlen[14] = 35;
  pointVal[14] = 3;
  colorVec[14] = ARCADA_YELLOW;

  block[15] = true;
  block_y0[15] = 75;
  block_x0[15] = 10;
  block_ylen[15] = 10;
  block_xlen[15] = 35;
  pointVal[15] = 1;
  colorVec[15] = ARCADA_GREEN;

  block[16] = true;
  block_y0[16] = 75;
  block_x0[16] = 55;
  block_ylen[16] = 10;
  block_xlen[16] = 35;
  pointVal[16] = 1;
  colorVec[16] = ARCADA_GREEN;

  block[17] = true;
  block_y0[17] = 75;
  block_x0[17] = 100;
  block_ylen[17] = 10;
  block_xlen[17] = 35;
  pointVal[17] = 1;
  colorVec[17] = ARCADA_GREEN;

  block[18] = true;
  block_y0[18] = 75;
  block_x0[18] = 145;
  block_ylen[18] = 10;
  block_xlen[18] = 35;
  pointVal[18] = 1;
  colorVec[18] = ARCADA_GREEN;

  block[19] = true;
  block_y0[19] = 75;
  block_x0[19] = 190;
  block_ylen[19] = 10;
  block_xlen[19] = 35;
  pointVal[19] = 1;
  colorVec[19] = ARCADA_GREEN;

  for (int i = 0; i<20; i++)
  {
    maxScore = maxScore + pointVal[i];
  }

  Serial.begin(115200);
  arcada.displayBegin();
  // Turn on backlight
  arcada.setBacklight(255);
  arcada.display->fillScreen(ARCADA_BLACK);
}

void loop() 
{
  while(start == false)
  {
    gamespeed = gameMenu1();
    uint8_t pressed_buttons = arcada.readButtons();
    if (pressed_buttons & ARCADA_BUTTONMASK_A) 
    {
      arcada.display->fillScreen(ARCADA_BLACK);
      blocks(); //calls the blocks function to generate the blocks
      user_score = 0;
      scoreBoard(0);
      paddle_pos = 85;
      ballX = 25;
      ballY = 120;
      direcx = 3;
      direcy = 4;
      start = true;
    }
    if (pressed_buttons & ARCADA_BUTTONMASK_B) 
    {
      arcada.display->fillScreen(ARCADA_BLACK);
      blocks(); //calls the blocks function to generate the blocks
      user_score = 0;
      scoreBoard(0);
      paddle_pos = 85;
      ballX = 25;
      ballY = 120; 
      direcx = 3;
      direcy = 4;
      start = true;
    }
  }

  uint8_t pressed_buttons = arcada.readButtons();

  if (pressed_buttons & ARCADA_BUTTONMASK_A) // moves paddle based on what button is pressed
  {
    paddle_pos = paddle(-5,paddle_pos); // moves back 5 spots
  }
  if (pressed_buttons & ARCADA_BUTTONMASK_B) 
  {
    paddle_pos = paddle(5,paddle_pos); // moves forward 5 spots
  }
  last_buttons = buttons;
  delay(gamespeed);

  ball();

  delay(gamespeed);

  if (user_score == maxScore)
  {
    start = false;
    victory();
  }

}

uint8_t paddle(int x, uint8_t posx)
{
  //pos 0 to 240 - width
  uint8_t width = 35;

  if(x != 0)
  {
    arcada.display->fillRect(posx, 225, width, 5, ARCADA_BLACK);
    posx = posx + x;
    if (posx < 0 || posx >= 240)
    {
      posx = 0; //ensures the paddle doesn't go off screen to the left
    }
    else if (posx > 240-width)
    {
      posx = 240-width; //240-width is the right boundry
    }
    arcada.display->fillRect(posx, 225, width, 5, ARCADA_WHITE);
    //Serial.println(posx);
  }
  return posx;
}

void ball()
{
  if(direcx!=0 || direcy!=0)
  {
    arcada.display->fillCircle(ballX, ballY, ballRad, ARCADA_BLACK);
    start = bounds();
    if (start == false)
    {
      return;
    }
    blocks();
    arcada.display->fillCircle(ballX, ballY, ballRad, ARCADA_MAGENTA);
    paddle(0, paddle_pos);
  }
}

bool bounds()
{
  uint8_t propBLX1 = 0; // proposed ball positions
  uint8_t propBLY1 = 0;
  uint8_t propBLX2 = 0;
  uint8_t propBLY2 = 0;

  propBLX1 = ballX+direcx+ballRad;
  propBLX2 = ballX+direcx-ballRad;
  propBLY1 = ballY+direcy+ballRad;
  propBLY2 = ballY+direcy-ballRad;

  if((propBLY1 >= 225 && propBLX1 >= paddle_pos && propBLX1 <= paddle_pos+35)||(propBLY2 >= 225 && propBLX2 >= paddle_pos && propBLX2 <= paddle_pos+35))
  {
    if (((propBLX1 >= paddle_pos && propBLX1 <= paddle_pos+7) || (propBLX1 >= paddle_pos+28 && propBLX1 <= paddle_pos+35))||((propBLX2 >= paddle_pos && propBLX2 <= paddle_pos+7) || (propBLX2 >= paddle_pos+28 && propBLX2 <= paddle_pos+35)))
    // if the ball hits the outsides of the paddle
    {
      if ((propBLX1 >= paddle_pos && propBLX1 <= paddle_pos+17)||(propBLX2 >= paddle_pos && propBLX2 <= paddle_pos+17)) 
      {
        direcx = -3;
      }
      else
      {
        direcx = 3;
      }

      if (direcy > 0)
      {
        direcy = 4;
      }
      else
      {
        direcy = -4;
      }

      direcy = direcy*-1;
    }
    else //if hits the inside of the paddle
    {
      if ((propBLX1 >= paddle_pos && propBLX1 <= paddle_pos+17)||(propBLX2 >= paddle_pos && propBLX2 <= paddle_pos+17))
      {
        direcx = -4;
      }
      else
      {
        direcx = 4;
      }

      if (direcy > 0)
      {
        direcy = 3;
      }
      else
      {
        direcy = -3;
      }
      direcy = direcy*-1;
    }
  }

  if((propBLY1 <= 10)||(propBLY2 <= 10)) // upper wall
  {
    direcy = direcy*-1;
  }

  if((propBLX1 <= 5 || propBLX1 >= 235)||(propBLX2 <= 5 || propBLX2 >= 235)) //side walls
  {
    direcx = direcx*-1;
  }

  ballX = ballX + direcx;
  ballY = ballY + direcy;

  if((propBLY1 > 240)||(propBLY2 > 240))
  {
    gameOver();
    return false;
  }
  else
  {
    return true;
  }
}

void gameOver()
{
  arcada.display->fillScreen(ARCADA_BLACK);
  arcada.display->setCursor(10, 80);
  arcada.display->setTextColor(ARCADA_GREEN);
  arcada.display->setTextSize(4);
  arcada.display->println("Game Over");

  arcada.display->setCursor(60, 130);
  arcada.display->setTextColor(ARCADA_YELLOW);
  arcada.display->setTextSize(2);
  arcada.display->print("Score: ");
  arcada.display->print(user_score);
  delay(2000);
}

void victory()
{
  arcada.display->fillScreen(ARCADA_BLACK);
  arcada.display->setCursor(0, 80);
  arcada.display->setTextColor(ARCADA_GREEN);
  arcada.display->setTextSize(4);
  arcada.display->println("Victory!!!");

  arcada.display->setCursor(60, 130);
  arcada.display->setTextColor(ARCADA_YELLOW);
  arcada.display->setTextSize(2);
  arcada.display->print("Score: ");
  arcada.display->print(user_score);
  delay(2000);
}


int scoreBoard(int scoreAdd)
{
  arcada.display->fillRect(0, 0, 100, 10, ARCADA_BLACK);
  arcada.display->setCursor(0, 0);
  arcada.display->setTextColor(ARCADA_YELLOW);
  arcada.display->setTextSize(1);
  arcada.display->print("Score: ");
  arcada.display->println(user_score+scoreAdd);
  return user_score+scoreAdd;
}

void blocks()
{
  uint8_t propBLX = 0; //proposed position of the ball
  uint8_t propBLY = 0;
  if (direcx > 0)
  {
    propBLX = ballX+direcx+ballRad;
  }
  else
  {
    propBLX = ballX+direcx-ballRad;
  }

  if (direcy > 0)
  {
    propBLY = ballY+direcy+ballRad;
  }
  else
  {
    propBLY = ballY+direcy-ballRad;
  }


  if(start == false) //generates blocks
  {

    for (int count = 0; count < 20; count++)
    {
    arcada.display->fillRect(block_x0[count], block_y0[count], block_xlen[count], block_ylen[count], colorVec[count]); 
    block[count] = true;
    }
  }

  for (int count = 0; count < 20; count++)
  {
    if(( propBLX <= block_x0[count]+block_xlen[count] && propBLX >=block_x0[count] && propBLY <= block_y0[count]+block_ylen[count] && block[count] == true)||( propBLX <= block_x0[count]+block_xlen[count] && propBLX >= block_x0[count] && propBLY <= block_y0[count]+block_ylen[count] && block[count] == true))
    {
      arcada.display->fillRect(block_x0[count], block_y0[count], block_xlen[count], block_ylen[count], ARCADA_BLACK);
      direcy = direcy*-1; //switches direction
      block[count] = false;
      tone(46,1000,30);
      user_score = scoreBoard(pointVal[count]);
    }
  }
}

int gameMenu1()
{
  bool continue1 = true;
  uint8_t pressed_buttons = arcada.readButtons();
  uint8_t menu1 = 0;
  arcada.display->fillScreen(ARCADA_BLACK);
  arcada.display->fillRoundRect(15, 80, 210, 70, 5, grey);
  while (continue1 == true)
  {
    pressed_buttons = arcada.readButtons();
    if (pressed_buttons & ARCADA_BUTTONMASK_A) //iterates through speed settings
    {
      tone(46,500,100); //plays noise
      menu1 = menu1+1;
      if(menu1 == 1)
      {
        arcada.display->fillRoundRect(20, 85, 200, 60, 5, ARCADA_BLACK);
        arcada.display->setCursor(70, 100);
        arcada.display->setTextColor(ARCADA_CYAN);
        arcada.display->setTextSize(4);
        arcada.display->println("Slow");

        delay(200);
      }
      else if(menu1 == 2)
      {
        arcada.display->fillRoundRect(20, 85, 200, 60, 5, ARCADA_BLACK);
        arcada.display->setCursor(50, 100);
        arcada.display->setTextColor(ARCADA_YELLOW);
        arcada.display->setTextSize(4);
        arcada.display->println("Medium");
        delay(200);
      }
      else if(menu1 == 3)
      {
        arcada.display->fillRoundRect(20, 85, 200, 60, 5, ARCADA_BLACK);
        arcada.display->setCursor(70, 100);
        arcada.display->setTextColor(ARCADA_RED);
        arcada.display->setTextSize(4);
        arcada.display->println("Fast");
        delay(200);
      }
      else if(menu1 == 4)
      {
        arcada.display->fillRoundRect(20, 85, 200, 60, 5, ARCADA_BLACK);
        arcada.display->setCursor(25, 105);
        arcada.display->setTextColor(0x07E0);
        arcada.display->setTextSize(3);
        arcada.display->println("Impossible!");
        delay(200);
      }

      else
      {
        menu1 = 0;
      }

    }
    if (pressed_buttons & ARCADA_BUTTONMASK_B) 
    {
      if(menu1 == 1)
      {
        arcada.display->fillScreen(ARCADA_BLACK);
        return 12;
      }
      else if(menu1 == 2)
      {
        arcada.display->fillScreen(ARCADA_BLACK);
        return 9;
      }
      else if(menu1 == 3)
      {
        arcada.display->fillScreen(ARCADA_BLACK);
        return 7;
      }
      else if(menu1 == 4)
      {
        arcada.display->fillScreen(ARCADA_BLACK);
        return 5;
      }
      else
      {
        return 0;
      }
    }


  }
  return 0;
}

