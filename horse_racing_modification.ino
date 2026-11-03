#include "Constants.h"
#include <LiquidCrystal.h>
#include "Display.h"
#include "Horse.h"
//#include <Constants.h>
#include "Obstacle.h"
//#include <Collectible.h>

int tickrate = 5;
int currentTick = 0;
volatile bool buttonPushed = false;

//horse
Horse horse;
int jumpTick = -10; 
bool needsToFall = false;
const int threshold = 4;
bool collision = false;

//obstacle
Obstacle obs[16];
bool hasObstacle[16][2];
int row = random(2);

//collectibles
//Collectible col[8];


void buttonPush() {
  buttonPushed = true;
}

void moveHorse() {
  if (hasObstacle[horse.getXpos()][horse.getYpos()]) {
    collision = true;
    return;
  }
  if (buttonPushed and horse.getYpos() == 1) {
    horse.jump();
    jumpTick = currentTick;
  }
  buttonPushed = false;
  if (currentTick - jumpTick >= threshold) {
    jumpTick = -10;
    needsToFall = true;
  }
  if (needsToFall) {
    if (!(hasObstacle[horse.getXpos()][1])) {
      horse.fall();
      needsToFall = false;
    }
  }
  
  horse.run();
}

void generateObstacles() {
  int space = 0;
  double prob = 0;
  for (int i = 14; i >= 0; --i) {
    if (!hasObstacle[i][row]) {
      ++space;
    } 
    else {
      break;
    }
  }
  if (space == 0) {
    prob = 0.75;
  }
  else if (space < 4) {
    prob = 0;
  }
  else {
    row = random(2);
    prob = 1.0 * space / (space + 4);
  }
  if (random(100) / 100.0 < prob) {
    Obstacle::spawn(obs, random(0, 3), row);
    hasObstacle[15][row] = true;
  }
}

void moveObstacles() {
  for (int i = 0; i < 16; ++i) {
    obs[i].moveLeft();
  }
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 15; ++j) {
      hasObstacle[j][i] = hasObstacle[j + 1][i];
    }
    hasObstacle[15][i] = false;
  }
  //need to update hasobstacle
}


void tick() {
  moveHorse();
  generateObstacles();
  moveObstacles();
}

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUTTON, HIGH);
  pinMode(PIN_AUTOPLAY, OUTPUT);
  digitalWrite(PIN_AUTOPLAY, HIGH);

  // Digital pin 2 maps to interrupt 0
  attachInterrupt(0/*PIN_BUTTON*/, buttonPush, FALLING);

  Display::setupLCD();
  
}

void loop() {
  static bool playing = false;
  static unsigned int distance = 0;

  if (!playing) {
    collision = false;
    if (buttonPushed) {
      //initializeGraphics();
      playing = true;
      buttonPushed = false;
      distance = 0;
    }
    return;
  }


  tick();
  ++currentTick;
  if (collision) {
    playing = false;
    //will change
  }
  delay(1000 / tickrate);
}
