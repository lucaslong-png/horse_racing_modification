#pragma once

#include <LiquidCrystal.h>
#include <Constants.h>
#include <Display.h>

class horse {
  private:
    int ypos;
    int xpos = 1 //can change
    int animationState //0 = run1, 1 = run2, 2 = jump
    byte[] image;
    byte[][] horseImages = {}; //3x5
    
  public:
    void run() {

    }  

    void jump() {
      long starttime = millis()
      clear(1, 0);
      Display.loadSprite(1, 1, image);
      ypos = 1
      delay(1000 / tickrate);
    }


};
