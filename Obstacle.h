#pragma once
#include <LiquidCrystal.h>
#include "Display.h"

class Obstacle {
  protected:
    //static int obstacleCount = 0;
    //static const byte sprites[3][8]; 
    //byte image[8];
    int spriteChoice;
    int xpos;
    int ypos;
    bool exists;

  public:
    Obstacle() {
      exists = false;
    }

    virtual void display() {
      Display::loadSprite(xpos, ypos, spriteChoice + 3);
    }

    void setSprite(int type) {
      spriteChoice = type;
    }

    //obstacles length will be 8
    static void spawn(Obstacle obstacles[], int type, int ypos) {
      for (int i = 0; i < 16; ++i) {
        if (!obstacles[i].exists) {
          obstacles[i].xpos = 15;
          obstacles[i].ypos = ypos;
          obstacles[i].setSprite(type);
          obstacles[i].exists = true;
          obstacles[i].display();
          break;
        }
      }
    }

    void moveLeft() {
      if (!exists) {
        return;
      }
      Display::clearCell(xpos, ypos);
      if (xpos > 0) {
        --xpos;
        display();
      }
      else {
        exists = false;
      }
    }

    void setExists(bool b) {
      exists = b;
    }
    

    
};
