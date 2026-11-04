#pragma once
#include <LiquidCrystal.h>
#include "Display.h"

class Horse {
  private:
    int animationState; //0 = run1, 1 = run2, 2 = jump
    const int xpos = 1;
    int ypos;
    
  public:

    Horse() {
      setSprite(0);
      animationState = 0;
      ypos = 1;
    }

    void reset() {
      animationState = 0;
      ypos = 1;
    }

    void setSprite(int state) {
      animationState = state;
    }

    void display() {
      Display::loadSprite(xpos, ypos, animationState);
    }

    //ignores jumping animation state
    void run() {
      if (animationState == 0) {
        animationState = 1;
        setSprite(animationState);
        display();
      }
      else if (animationState == 1) {
        animationState = 0;
        setSprite(animationState);
        display();
      }
    }  

    //assumes ypos = 0
    long jump() {
      long starttime = millis();
      Display::clearCell(xpos, ypos);
      ypos = 0;
      animationState = 2;
      setSprite(animationState);
      display();
      return starttime;
    }

    void fall() {
      Display::clearCell(xpos, ypos);
      ypos = 1;
      animationState = 0;
      setSprite(animationState);
      display();
    }

    int getXpos() {
      return xpos;
    }

    int getYpos() {
      return ypos;
    }


};
