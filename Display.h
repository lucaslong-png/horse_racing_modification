#include <LiquidCrystal.h>
//index 0-2 = horse
//index 3-5 = obstacle
//index 6-7 = collectible
#define HORSERUN1 0
#define HORSERUN2 1
#define HORSEJUMP 2
#define OBSTACLE1 3
#define OBSTACLE2 4
#define OBSTACLE3 5
#define COLLECTIBLE1 6
#define COLLECTIBLE2 7

class Display {
  private:
    static LiquidCrystal lcd;
  public:
    static void setupLCD() {
      static byte graphics[8][8] = {}; //8x8 
      lcd.begin(16, 2);
      for (int i = 0; i < 8; ++i) {
        lcd.createChar(i, graphics[i]);
      }
    }
    
    static void loadSprite(int x, int y, int slot) {
      lcd.setCursor(x, y);
      lcd.write(byte(slot));
    }

    static void clearCell(int x, int y) {
      lcd.setCursor(x, y);
      lcd.print(" ");
    }

};
LiquidCrystal Display::lcd(12, 11, 6, 5, 4, 3);