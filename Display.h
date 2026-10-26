#include <LiquidCrystal.h>
#index 0-2 = horse
#index 3-5 = obstacle
//index 6-7 = collectible
#define HORSE1 0
#define HORSE2 1
#define HORSE2 2
#define OBSTACLE1 3
#define OBSTACLE2 4
#define OBSTACLE3 5
#define COLLECTIBLE1 6
#define COLLECTIBLE2 7

class Display {
  private:
    int horsechoice;
    Static byte[][] graphics = {}; //2d array
    byte[0] = horsechoice.drawing;
  public:
    void setupLCD() {
      lcd.begin();
      for (int i = 0; i < 8; ++i) {
        lcd.createChar(i, graphics[i]);
      }
    }
    
    void loadSprite(int x, int y, byte[] image) {
      lcd.setCursor(x, y);
      lcd.write(image);
    }

    void clearCell(int x, int y) {
      lcd.setCursor(x, y);
      lcd.print(" ");
    }

    void setHorseChoice(int c) {
      horsechoice = c
    }
};
