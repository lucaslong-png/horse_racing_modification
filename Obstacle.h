#include <LiquidCrystal.h>
#include <Display.h>

class Obstacle {
  private:
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

    void display() {
      Display.loadSprite(xpos, ypos, spriteChoice + 3);
    }

    void setSprite(int type) {
      spriteChoice = type;
    }

    //obstacles length will be 8
    static void spawn(Obstacle obstacles[], int type, int ypos) {
      for (int i = 0; i < 8; ++i) {
        if (obstacles[i].exists == false) {
          obstacles[i].xpos = 15;
          obstacles[i].ypos = ypos;
          obstacles[i].setSprite(type);
          obstacles[i].exists = true;
          obstacles[i].display();
          break;
        }
      }
    }

    static void deleteObstacle(Obstacle& o) {
      Display.clearCell(o.xpos, o.ypos);
      o.exists = false;
    }

    void moveLeft() {
      Display.clearCell(xpos, ypos);
      if (xpos > 0) {
        --xpos;
        display();
      }
      else {
        exists = false;
      }
    }
    

    
};
