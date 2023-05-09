# -*- coding: utf-8 -*-
"""
Created on Mon May 16 22:55:34 2022

@author: kaitl
"""
import pygame as pg
import numpy as np
pg.init()  #Initialize pygame

#Set up the screen
screenwidth = 800
screenheight = 800
reso = (screenwidth,screenheight)
scr = pg.display.set_mode(reso)
rgbcolor = (21,41,88)


#set up initial conditions and colors
paddle_pos = np.array([400,780])
ball_pos = np.array([430,400])
ball_spd = np.array([600,600])
nrows = 8
ncolumns = 20
brick_color = (255,0,0)
ball_color = (255,255,255)  #Ball color is black
paddle_color = (0,255,0)  #paddle color is green
gain = 5
timestep = 5
r_ball = 4
paddlewidth = 60
paddleheight = 6
brickwidth = 40
brickheight = 15

#making the grid
# grid = np.ones(nrows, ncolumns)
grid = []
for i in range(0, nrows):
    row= []
    for j in range(0, ncolumns):
        row.append(1)
    grid.append(row)
brickx = np.arange(0, ncolumns+1)*brickwidth
bricky = np.arange(0,nrows+1)*brickheight + 100


def collision(positionx, positiony, width, height):
    """
    determines if the ball collides with something
    inputs: item postion, width, and height
    returns: True or False collision
    """
    colli = False
    # print(positionx, ball_pos[0], positionx + width)
    if positionx <= ball_pos[0] <= positionx+ width:
        dist_top = abs(positiony - ball_pos[1])
        dist_bot = abs((positiony + height) - ball_pos[1]) #Check if plus or nah
        if dist_top <= r_ball:# or dist_bot <= r_ball:
            ball_spd[1] = ball_spd[1] * (-1)
            colli = True
        if dist_bot <= r_ball:
            ball_spd[1] = ball_spd[1] * (-1)
            colli = True
    if positiony <= ball_pos[1] and ball_pos[1] <= positiony + height:
        dist_left = abs(positionx - ball_pos[0])
        dist_right = abs((positionx + width) - ball_pos[0]) 
        if dist_left <= r_ball:
            ball_spd[0] = ball_spd[0] * (-1)
            colli = True
        if dist_right <= r_ball:
            ball_spd[0] = ball_spd[0] * (-1)
            colli = True
    return colli
    
    # dist_top = abs(position[1] - ball_pos[1])
    # dist_bot = abs((position[1] + height) - ball_pos[1]) #Check if plus or nah
    # dist_left = abs(position[0] - ball_pos[0])
    # dist_right = abs((position[0] + width) - ball_pos[0]) 
    # minimum = min(dist_top, dist_bot, dist_left, dist_right)
    
    # if (position[0] <= ball_pos[0] <= position[0]+ width) and (position[1] <= ball_pos[1] and ball_pos[1] <= position[1] + height):
        
    #     if( minimum == dist_left or minimum == dist_right ) and (minimum == dist_top or minimum == dist_bot):
    #         return colli
        
    #     elif minimum == dist_left:# or dist_bot <= r_ball:
    #         ball_spd[0] = ball_spd[0] * (-1)
    #         colli = True
    #         ball_pos[0] = position[0] - r_ball
            
    #     elif minimum == dist_right:
    #         ball_spd[0] = ball_spd[0] * (-1)
    #         colli = True
    #         ball_pos[0] = position[0] + width + r_ball
        
    #     elif minimum == dist_top:# or dist_bot <= r_ball:
    #         ball_spd[1] = ball_spd[1] * (-1)
    #         colli = True
    #         ball_pos[1] = position[1] - r_ball
            
    #     elif minimum == dist_bot:
    #         ball_spd[1] = ball_spd[1] * (-1)
    #         colli = True
    #         ball_pos[1] = position[1] + height + r_ball
        
            
    # return colli

         
escape = False
while not escape:
   # Check for ESC key or quit event:
   scr.fill(rgbcolor)
   keys=pg.key.get_pressed()
   escape=keys[pg.K_ESCAPE]
   paddle = pg.Rect(paddle_pos[0], paddle_pos[1], paddlewidth, paddleheight)
   pg.draw.rect(scr,paddle_color, paddle)
   pg.draw.circle(scr,ball_color,ball_pos,r_ball)
   
   pg.display.update()
   if keys[pg.K_LEFT]:
       paddle_pos[0] = paddle_pos[0] - gain  #move paddle to the left by the gain
       if paddle_pos[0] <= 0:
           paddle_pos[0] = 0
           paddle = pg.Rect(paddle_pos[0], paddle_pos[1], paddlewidth, paddleheight)
       else:
           paddle_pos[0] = paddle_pos[0]
           paddle = pg.Rect(paddle_pos[0], paddle_pos[1], paddlewidth, paddleheight)
           
   if keys[pg.K_RIGHT]:
       paddle_pos[0] = paddle_pos[0] + gain  #move paddle to the right by the gain
       if paddle_pos[0] >= 740:
           paddle_pos[0] = 740
           paddle = pg.Rect(paddle_pos[0], paddle_pos[1], paddlewidth, paddleheight)
       else:
        paddle_pos[0] = paddle_pos[0]
        paddle = pg.Rect(paddle_pos[0], paddle_pos[1], paddlewidth, paddleheight)
   
   #Ball movement
   ball_pos[0] = ball_pos[0] + ball_spd[0] * timestep/1000
   ball_pos[1] = ball_pos[1] + ball_spd[1] * timestep/1000
   #Wall bounces
   if ball_pos[0] <= r_ball or ball_pos[0] >= screenwidth-r_ball:
       ball_spd[0] = -1 * ball_spd[0] #if the ball hits a wall
   if ball_pos[1] <= r_ball or ball_pos[1] >= screenheight + r_ball:
         ball_spd[1] = -1 * ball_spd[1]
   
  #Paddle collision
   colli = collision(paddle_pos[0], paddle_pos[1], paddlewidth, paddleheight)
   # print(colli)
   
   #collision with the grid
   i = 0
   for row in grid:
       j = 0
       for brick in row:
           
           if brick == 1: #The drawn bricks
               collibrick = collision(brickx[j], bricky[i], brickwidth, brickheight)
               if collibrick == False:
                   brickrect = pg.Rect(brickx[j], bricky[i], brickwidth, brickheight)
                   pg.draw.rect(scr,brick_color, brickrect)
                   pg.draw.rect(scr,(255,255,255), brickrect, width = 1)
               # print(brickx[j], bricky[i])
               else:
                   grid[i][j] = 0
           j += 1
               
       i += 1
               
       # print(row)
   # collibrick = collision(brickx, bricky, brickwidth, brickheight)
   # print(collibrick)
                  
   pg.time.wait(timestep)
   pg.display.flip()
   pg.display.update()
   # And check if the window close button is clicked
   pg.event.pump()
   for event in pg.event.get():
      if event.type==pg.QUIT:
          escape=True
pg.quit()