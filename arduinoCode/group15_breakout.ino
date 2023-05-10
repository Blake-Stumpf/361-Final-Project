#include "Adafruit_Arcada.h"
Adafruit_Arcada arcada;

uint32_t buttons, last_buttons;

uint8_t paddle_pos = 85;

uint8_t ballX = 5;
uint8_t ballY = 120; 

int direcx = 1;
int direcy = 1;

int user_score = 0;

bool start = false;

bool block_1 = true;
const uint8_t block_1_y0 = 15;
const uint8_t block_1_x0 = 10;
const uint8_t block_1_ylen = 10;
const uint8_t block_1_xlen = 35;

bool block_2 = true;
const uint8_t block_2_y0 = 15;
const uint8_t block_2_x0 = 55;
const uint8_t block_2_ylen = 10;
const uint8_t block_2_xlen = 35;

bool block_3 = true;
const uint8_t block_3_y0 = 15;
const uint8_t block_3_x0 = 100;
const uint8_t block_3_ylen = 10;
const uint8_t block_3_xlen = 35;

bool block_4 = true;
const uint8_t block_4_y0 = 15;
const uint8_t block_4_x0 = 145;
const uint8_t block_4_ylen = 10;
const uint8_t block_4_xlen = 35;

bool block_5 = true;
const uint8_t block_5_y0 = 15;
const uint8_t block_5_x0 = 190;
const uint8_t block_5_ylen = 10;
const uint8_t block_5_xlen = 35;

bool block_6 = true;
const uint8_t block_6_y0 = 35;
const uint8_t block_6_x0 = 10;
const uint8_t block_6_ylen = 10;
const uint8_t block_6_xlen = 35;

bool block_7 = true;
const uint8_t block_7_y0 = 35;
const uint8_t block_7_x0 = 55;
const uint8_t block_7_ylen = 10;
const uint8_t block_7_xlen = 35;

bool block_8 = true;
const uint8_t block_8_y0 = 35;
const uint8_t block_8_x0 = 100;
const uint8_t block_8_ylen = 10;
const uint8_t block_8_xlen = 35;

bool block_9 = true;
const uint8_t block_9_y0 = 35;
const uint8_t block_9_x0 = 145;
const uint8_t block_9_ylen = 10;
const uint8_t block_9_xlen = 35;

bool block_10 = true;
const uint8_t block_10_y0 = 35;
const uint8_t block_10_x0 = 190;
const uint8_t block_10_ylen = 10;
const uint8_t block_10_xlen = 35;

void setup()
{
  Serial.begin(115200);
  arcada.displayBegin();
  // Turn on backlight
  arcada.setBacklight(255);
  arcada.display->fillScreen(ARCADA_BLACK);
  arcada.display->fillCircle(ballX, ballY, 5, ARCADA_MAGENTA);
  arcada.display->fillRect(paddle_pos, 225, 35, 5, ARCADA_WHITE);
  scoreBoard(0);
  blocks(0, 0);
}

void loop() 
{
  while(start == false)
  {
    uint8_t pressed_buttons = arcada.readButtons();
    if (pressed_buttons & ARCADA_BUTTONMASK_A) 
    {
      arcada.display->fillScreen(ARCADA_BLACK);
      blocks(ballX, ballY);
      user_score = 0;
      scoreBoard(0);
      paddle_pos = 85;
      ballX = 5;
      ballY = 120; 
      direcx = 3;
      direcy = 4;
      start = true;
    }
    if (pressed_buttons & ARCADA_BUTTONMASK_B) 
    {
      arcada.display->fillScreen(ARCADA_BLACK);
      blocks(ballX, ballY);
      user_score = 0;
      scoreBoard(0);
      paddle_pos = 85;
      ballX = 5;
      ballY = 120; 
      direcx = 3;
      direcy = 4;
      start = true;
    }
  }

  uint8_t pressed_buttons = arcada.readButtons();

  if (pressed_buttons & ARCADA_BUTTONMASK_A) 
  {
    paddle_pos = paddle(-5,paddle_pos);
  }
  if (pressed_buttons & ARCADA_BUTTONMASK_B) 
  {
    paddle_pos = paddle(5,paddle_pos);
  }
  last_buttons = buttons;
  delay(9);

  ball(direcx, direcy);

  delay(9);

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
      posx = 0;
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

void ball(int x, int y)
{
  if(x!=0 || y!=0)
  {
    arcada.display->fillCircle(ballX, ballY, 5, ARCADA_BLACK);
    ballX = ballX+x;
    ballY = ballY+y;
    start = bounds(x, y);
    blocks(ballX, ballY);
    arcada.display->fillCircle(ballX, ballY, 5, ARCADA_MAGENTA);
    paddle(0, paddle_pos);
  }
}

bool bounds(int x, int y)
{
  if(ballY >= 225 && ballX >= paddle_pos && ballX <= paddle_pos+35)
  {
    ballX = ballX-x;
    ballY = ballY-y;

    direcy = direcy*-1;

    ballX = ballX+x;
    ballY = ballY+y;
  }

  if(ballY <= 10)
  {
    ballX = ballX-x;
    ballY = ballY-y;

    direcy = direcy*-1;

    ballX = ballX+x;
    ballY = ballY+y;
  }

  if(ballX <= 5 || ballX >= 235)
  {
    ballX = ballX-x;
    ballY = ballY-y;

    direcx = direcx*-1;

    ballX = ballX+x;
    ballY = ballY+y;
  }

  if(ballY > 240)
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
  //arcada.display->setTextSize(1);
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

void blocks(int x, int y)
{
  if(start == false) //generates blocks
  {
    arcada.display->fillRect(block_1_x0, block_1_y0, block_1_xlen, block_1_ylen, ARCADA_BLUE); 
    block_1 = true;

    arcada.display->fillRect(block_2_x0, block_2_y0, block_2_xlen, block_2_ylen, ARCADA_BLUE); 
    block_2 = true;

    arcada.display->fillRect(block_3_x0, block_3_y0, block_3_xlen, block_3_ylen, ARCADA_BLUE); 
    block_3 = true;

    arcada.display->fillRect(block_4_x0, block_4_y0, block_4_xlen, block_4_ylen, ARCADA_BLUE); 
    block_4 = true;

    arcada.display->fillRect(block_5_x0, block_5_y0, block_5_xlen, block_5_ylen, ARCADA_BLUE); 
    block_5 = true;

    arcada.display->fillRect(block_6_x0, block_6_y0, block_6_xlen, block_6_ylen, ARCADA_ORANGE); 
    block_6 = true;

    arcada.display->fillRect(block_7_x0, block_7_y0, block_7_xlen, block_7_ylen, ARCADA_ORANGE); 
    block_7 = true;

    arcada.display->fillRect(block_8_x0, block_8_y0, block_8_xlen, block_8_ylen, ARCADA_ORANGE); 
    block_8 = true;

    arcada.display->fillRect(block_9_x0, block_9_y0, block_9_xlen, block_9_ylen, ARCADA_ORANGE); 
    block_9 = true;

    arcada.display->fillRect(block_10_x0, block_10_y0, block_10_xlen, block_10_ylen, ARCADA_ORANGE); 
    block_10 = true;
  }

  if((x <= block_1_x0+block_1_xlen && x >=block_1_x0 && y <= block_1_y0+block_1_ylen && block_1 == true)||(x <= block_1_x0+block_1_xlen && x >=block_1_x0 && y <= block_1_y0+block_1_ylen && block_1 == true))
  {
    arcada.display->fillRect(block_1_x0, block_1_y0, block_1_xlen, block_1_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_1 = false;
    user_score = scoreBoard(10);
  }


  else if((x <= block_2_x0+block_2_xlen && x >=block_2_x0 && y <= block_2_y0+block_2_ylen && block_2 == true)||(x <= block_2_x0+block_2_xlen && x >=block_2_x0 && y <= block_2_y0+block_2_ylen && block_2 == true))
  {
    arcada.display->fillRect(block_2_x0, block_2_y0, block_2_xlen, block_2_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_2 = false;
    user_score = scoreBoard(10);
  }

  else if((x <= block_3_x0+block_3_xlen && x >=block_3_x0 && y <= block_3_y0+block_3_ylen && block_3 == true)||(x <= block_3_x0+block_3_xlen && x >=block_3_x0 && y <= block_3_y0+block_3_ylen && block_3 == true))
  {
    arcada.display->fillRect(block_3_x0, block_3_y0, block_3_xlen, block_3_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_3 = false;
    user_score = scoreBoard(10);
  }

  else if((x <= block_4_x0+block_4_xlen && x >=block_4_x0 && y <= block_4_y0+block_4_ylen && block_4 == true)||(x <= block_4_x0+block_4_xlen && x >=block_4_x0 && y <= block_4_y0+block_4_ylen && block_4 == true))
  {
    arcada.display->fillRect(block_4_x0, block_4_y0, block_4_xlen, block_4_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_4 = false;
    user_score = scoreBoard(10);
  }

  else if((x <= block_5_x0+block_5_xlen && x >=block_5_x0 && y <= block_5_y0+block_5_ylen && block_5 == true)||(x <= block_5_x0+block_5_xlen && x >=block_5_x0 && y <= block_5_y0+block_5_ylen && block_5 == true))
  {
    arcada.display->fillRect(block_5_x0, block_5_y0, block_5_xlen, block_5_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_5 = false;
    user_score = scoreBoard(10);
  }


  else if((x <= block_6_x0+block_6_xlen && x >=block_6_x0 && y <= block_6_y0+block_6_ylen && block_6 == true)||(x <= block_6_x0+block_6_xlen && x >=block_6_x0 && y <= block_6_y0+block_6_ylen && block_6 == true))
  {
    arcada.display->fillRect(block_6_x0, block_6_y0, block_6_xlen, block_6_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_6 = false;
    user_score = scoreBoard(5);
  }


  else if((x <= block_7_x0+block_7_xlen && x >=block_7_x0 && y <= block_7_y0+block_7_ylen && block_7 == true)||(x <= block_7_x0+block_7_xlen && x >=block_7_x0 && y <= block_7_y0+block_7_ylen && block_7 == true))
  {
    arcada.display->fillRect(block_7_x0, block_7_y0, block_7_xlen, block_7_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_7 = false;
    user_score = scoreBoard(5);
  }

  else if((x <= block_8_x0+block_8_xlen && x >=block_8_x0 && y <= block_8_y0+block_8_ylen && block_8 == true)||(x <= block_8_x0+block_8_xlen && x >=block_8_x0 && y <= block_8_y0+block_8_ylen && block_8 == true))
  {
    arcada.display->fillRect(block_8_x0, block_8_y0, block_8_xlen, block_8_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_8 = false;
    user_score = scoreBoard(5);
  }

  else if((x <= block_9_x0+block_9_xlen && x >=block_9_x0 && y <= block_9_y0+block_9_ylen && block_9 == true)||(x <= block_9_x0+block_9_xlen && x >=block_9_x0 && y <= block_9_y0+block_9_ylen && block_9 == true))
  {
    arcada.display->fillRect(block_9_x0, block_9_y0, block_9_xlen, block_9_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_9 = false;
    user_score = scoreBoard(5);
  }

  else if((x <= block_10_x0+block_10_xlen && x >=block_10_x0 && y <= block_10_y0+block_10_ylen && block_10 == true)||(x <= block_10_x0+block_10_xlen && x >=block_10_x0 && y <= block_10_y0+block_10_ylen && block_10 == true))
  {
    arcada.display->fillRect(block_10_x0, block_10_y0, block_10_xlen, block_10_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_10 = false;
    user_score = scoreBoard(5);
  }



}
