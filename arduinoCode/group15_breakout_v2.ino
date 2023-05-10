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

int gamespeed = 0;
#define grey 0x94B2

void setup()
{
  Serial.begin(115200);
  arcada.displayBegin();
  // Turn on backlight
  arcada.setBacklight(255);
  arcada.display->fillScreen(ARCADA_BLACK);
  //arcada.display->fillCircle(ballX, ballY, ballRad, ARCADA_MAGENTA);
  //arcada.display->fillRect(paddle_pos, 225, 35, 5, ARCADA_WHITE);
  //scoreBoard(0);
  //blocks();
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
      blocks();
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
      blocks();
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

  if (pressed_buttons & ARCADA_BUTTONMASK_A) 
  {
    paddle_pos = paddle(-5,paddle_pos);
  }
  if (pressed_buttons & ARCADA_BUTTONMASK_B) 
  {
    paddle_pos = paddle(5,paddle_pos);
  }
  last_buttons = buttons;
  delay(gamespeed);

  ball();

  delay(gamespeed);

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
  uint8_t propBLX1 = 0;
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
      Serial.println("3,4");
    }
    else
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
      Serial.println("4,3");
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

void blocks() // position of ball
{
  uint8_t propBLX = 0;
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

  if(( propBLX <= block_1_x0+block_1_xlen && propBLX >=block_1_x0 && propBLY <= block_1_y0+block_1_ylen && block_1 == true)||( propBLX <= block_1_x0+block_1_xlen && propBLX >= block_1_x0 && propBLY <= block_1_y0+block_1_ylen && block_1 == true))
  {
    arcada.display->fillRect(block_1_x0, block_1_y0, block_1_xlen, block_1_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_1 = false;
    user_score = scoreBoard(10);
  }


  else if((propBLX <= block_2_x0+block_2_xlen && propBLX >= block_2_x0 && propBLY <= block_2_y0+block_2_ylen && block_2 == true)||( propBLX <= block_2_x0+block_2_xlen && propBLX>= block_2_x0 && propBLY <= block_2_y0+block_2_ylen && block_2 == true))
  {
    arcada.display->fillRect(block_2_x0, block_2_y0, block_2_xlen, block_2_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_2 = false;
    user_score = scoreBoard(10);
  }

  else if(( propBLX <= block_3_x0+block_3_xlen && propBLX >=block_3_x0 && propBLY <= block_3_y0+block_3_ylen && block_3 == true)||( propBLX <= block_3_x0+block_3_xlen && propBLX >=block_3_x0 && propBLY <= block_3_y0+block_3_ylen && block_3 == true))
  {
    arcada.display->fillRect(block_3_x0, block_3_y0, block_3_xlen, block_3_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_3 = false;
    user_score = scoreBoard(10);
  }

  else if(( propBLX <= block_4_x0+block_4_xlen && propBLX >= block_4_x0 && propBLY <= block_4_y0+block_4_ylen && block_4 == true)||( propBLX <= block_4_x0+block_4_xlen && propBLX >=block_4_x0 && propBLY <= block_4_y0+block_4_ylen && block_4 == true))
  {
    arcada.display->fillRect(block_4_x0, block_4_y0, block_4_xlen, block_4_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_4 = false;
    user_score = scoreBoard(10);
  }

  else if(( propBLX <= block_5_x0+block_5_xlen && propBLX >= block_5_x0 && propBLY <= block_5_y0+block_5_ylen && block_5 == true)||( propBLX <= block_5_x0+block_5_xlen &&propBLX>=block_5_x0 && propBLY <= block_5_y0+block_5_ylen && block_5 == true))
  {
    arcada.display->fillRect(block_5_x0, block_5_y0, block_5_xlen, block_5_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_5 = false;
    user_score = scoreBoard(10);
  }


  else if(( propBLX <= block_6_x0+block_6_xlen && propBLX >= block_6_x0 && propBLY <= block_6_y0+block_6_ylen && block_6 == true)||(propBLX <= block_6_x0+block_6_xlen && propBLX >=block_6_x0 && propBLY <= block_6_y0+block_6_ylen && block_6 == true))
  {
    arcada.display->fillRect(block_6_x0, block_6_y0, block_6_xlen, block_6_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_6 = false;
    user_score = scoreBoard(5);
  }


  else if(( propBLX <= block_7_x0+block_7_xlen && propBLX >=block_7_x0 && propBLY <= block_7_y0+block_7_ylen && block_7 == true)||( propBLX <= block_7_x0+block_7_xlen && propBLX >=block_7_x0 && propBLY <= block_7_y0+block_7_ylen && block_7 == true))
  {
    arcada.display->fillRect(block_7_x0, block_7_y0, block_7_xlen, block_7_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_7 = false;
    user_score = scoreBoard(5);
  }

  else if(( propBLX <= block_8_x0+block_8_xlen && propBLX >=block_8_x0 && propBLY <= block_8_y0+block_8_ylen && block_8 == true)||( propBLX <= block_8_x0+block_8_xlen && propBLX >=block_8_x0 && propBLY <= block_8_y0+block_8_ylen && block_8 == true))
  {
    arcada.display->fillRect(block_8_x0, block_8_y0, block_8_xlen, block_8_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_8 = false;
    user_score = scoreBoard(5);
  }

  else if(( propBLX <= block_9_x0+block_9_xlen && propBLX >=block_9_x0 && propBLY <= block_9_y0+block_9_ylen && block_9 == true)||( propBLX <= block_9_x0+block_9_xlen && propBLX >=block_9_x0 && propBLY <= block_9_y0+block_9_ylen && block_9 == true))
  {
    arcada.display->fillRect(block_9_x0, block_9_y0, block_9_xlen, block_9_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_9 = false;
    user_score = scoreBoard(5);
  }

  else if(( propBLX <= block_10_x0+block_10_xlen && propBLX >=block_10_x0 && propBLY <= block_10_y0+block_10_ylen && block_10 == true)||( propBLX <= block_10_x0+block_10_xlen &&propBLX>=block_10_x0 && propBLY <= block_10_y0+block_10_ylen && block_10 == true))
  {
    arcada.display->fillRect(block_10_x0, block_10_y0, block_10_xlen, block_10_ylen, ARCADA_BLACK);
    direcy = direcy*-1; //switches direction
    block_10 = false;
    user_score = scoreBoard(5);
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
    if (pressed_buttons & ARCADA_BUTTONMASK_A) 
    {
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
