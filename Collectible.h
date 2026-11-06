#include <LiquidCrystal.h>
//not done
class Collectible : public Obstacle {
    private:

    public:
        void display() override {
            Display::loadSprite(xpos, ypos, spriteChoice + 6);
        }

        static void spawn(Collectible collectibles[], int type, int ypos) {
            for (int i = 0; i < 16; ++i) {
                if (!collectibles[i].exists) {
                collectibles[i].xpos = 15;
                collectibles[i].ypos = ypos;
                collectibles[i].setSprite(type);
                collectibles[i].exists = true;
                collectibles[i].display();
                break;
                }
            }
        }
};