#pragma once
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
      static byte graphics[8][8] = {
        {
          B00000,
          B00000,
          B00010,
          B00011,
          B00010,
          B01110,
          B01010,
          B01010,
        },
        
        {
          B00000,
          B00000,
          B00010,
          B00011,
          B00010,
          B01110,
          B01001,
          B10010,
        },

        {
          B00000,
          B00000,
          B00010,
          B00011,
          B00010,
          B01110,
          B01001,
          B10001,
        },

        {
          B01110,
          B11111,
          B11111,
          B01110,
          B00100,
          B00100,
          B00100,
          B00100,
        },

        {
          B00000,
          B00000,
          B00000,
          B00000,
          B00011,
          B00111,
          B00111,
          B00011,
        },

        {
          B00000,
          B00000,
          B00000,
          B00000,
          B11000,
          B11100,
          B11100,
          B11000,
        },
        {
          B00000,
          B00000,
          B00000,
          B00000,
          B00011,
          B00111,
          B00111,
          B00011,
        },

        {
          B00000,
          B00000,
          B00000,
          B00000,
          B11000,
          B11100,
          B11100,
          B11000,
        }
        //placeholders
        }; //8x8 
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

    static void clear() {
      lcd.clear();
    }

};
LiquidCrystal Display::lcd(12, 11, 6, 5, 4, 3);
