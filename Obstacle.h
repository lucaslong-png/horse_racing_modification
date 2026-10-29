#include <LiquidCrystal.h>

class Obstacle {
  private:
    static byte[][] obstacles[3][8];
    byte[] image;
    int xpos;
    int ypos;

  public:
    Obstacle(int oc, int ypos) {
      this.ypos = ypos
      image = obstacles[oc];
      xpos = 15;
      Display.loadSprite(15, ypos, image)
    }

    static Obstacle spawn(int type, int ypos) {
      obs = new Obstacle(type, ypos)
    }

    void moveLeft() {
      Display.clearCell(xpos, ypos);
      if (xpos > 0) {
        --xpos;
        Display.loadSprite(xpos, ypos);
      }
    }

    }
}
