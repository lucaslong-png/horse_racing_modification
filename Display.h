#include <LiquidCrystal.h>
//index 0-2 = horse
//index 3-5 = obstacle
//index 6-7 = collectible
#define HORSE1 0
#define HORSE2 1
#define HORSE3 2
#define OBSTACLE1 3
#define OBSTACLE2 4
#define OBSTACLE3 5
#define COLLECTIBLE1 6
#define COLLECTIBLE2 7

class Display {
  private:
    int horsechoice;
    byte[0] = horsechoice.drawing;
    LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
  public:
    void setupLCD() {
      static byte graphics[][] = {}; //2d array
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
