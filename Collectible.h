#include <LiquidCrystal.h>
//not done
class Collectible : public Obstacle {
    void display() override {
        Display.loadSprite(xpos, ypos, spriteChoice + 6);
    }
}