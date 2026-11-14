#include <LiquidCrystal.h>
#include "Display.h"
#include "Horse.h"
#include "Obstacle.h"
#include "Collectible.h"

//pins
#define PIN_BUTTON 2
#define TICKRATE_PIN A1
#define SOUND_PIN 9

//game
int tickrate = 5;
int currentTick = 0;
volatile bool buttonPushed = false;
bool playing = false;
int score = 0;

//horse
Horse horse;
int jumpTick = 0; 
bool needsToFall = false;
const int threshold = 4;
bool collision = false;

//obstacle
Obstacle obs[16];
bool hasObstacle[16][2];
int row;
int currentobs;

//collectibles
Collectible col[16];
bool hasCollectible[16][2];
int gap = 0;

void buttonPush() {
  buttonPushed = true;
}

void moveHorse() {
  if (hasObstacle[horse.getXpos()][horse.getYpos()]) {
    collision = true;
    return;
  }
  if (hasCollectible[horse.getXpos()][horse.getYpos()]) {
    score += 200;
    tone(SOUND_PIN, 800, 200);
    for (int i = 0; i < 16; ++i) {
      if (col[i].getExists() and col[i].getXpos() == horse.getXpos() and col[i].getYpos() == horse.getYpos()) {
        col[i].setExists(false);
        Display::clearCell(horse.getXpos(), horse.getYpos());
        horse.display();
        break;
      }
    }
  }
  if (buttonPushed and horse.getYpos() == 1) {
    horse.jump();
    jumpTick = currentTick;
  }
  if (jumpTick >= 0 and currentTick - jumpTick >= threshold) {
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
    prob = 0.66;
  }
  else if (space < 4) {
    prob = 0;
  }
  else {
    row = random(2);
    currentobs = random(3);
    prob = 1.0 * space / (space + 4);
  }
  if (random(100) / 100.0 < prob) {
    Obstacle::spawn(obs, currentobs, row);
    hasObstacle[15][row] = true;
  }

}

void generateCollectibles() {
  double prob = 1.0 * gap / (gap + 100);
  int colRow;
  if (random(100) / 100.0 < prob) {
    colRow = random(2);
    if (!hasObstacle[15][colRow]) {
      Collectible::spawn(col, random(2), colRow);
      hasCollectible[15][colRow] = true;
      gap = 0;
    }
  }
}

void moveObjects() {
  for (int i = 0; i < 16; ++i) {
    obs[i].moveLeft();
    col[i].moveLeft();
  }

  ++gap;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 15; ++j) {
      hasObstacle[j][i] = hasObstacle[j + 1][i];
      hasCollectible[j][i] = hasCollectible[j + 1][i];
    }
    hasObstacle[15][i] = false;
    hasCollectible[15][i] = false;
  }
}




void tick() {
  generateObstacles();
  generateCollectibles();
  moveObjects();
  moveHorse();
  Display::displayScore(score);
  score += 50;

}

void gameSetup() {
  //game
  Display::clear();
  currentTick = 0;
  score = 0;
  //horse
  jumpTick = -10;
  needsToFall = false;
  collision = false;
  horse.reset();
  horse.display();
  
  //obstacle
  row = random(2);
  currentobs = random(3);
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 2; ++j) {
      hasObstacle[i][j] = false;
    }
    obs[i].setExists(false);
  }

  //collectible
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 2; ++j) {
      hasCollectible[i][j] = false;
    }
    col[i].setExists(false);
  }
  gap = 0;
}

void setup() {
  randomSeed(analogRead(A0));
  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUTTON, HIGH);
  pinMode(TICKRATE_PIN, INPUT);
  pinMode(SOUND_PIN, OUTPUT);
  tone(SOUND_PIN, 255, 200);

  // Digital pin 2 maps to interrupt 0
  attachInterrupt(0, buttonPush, FALLING);
  Display::setupLCD(); 
  buttonPushed = false;
  Display::startScreen();
  while (!buttonPushed) {}
}

void loop() {
  //setup
  if (!playing) {
    if (buttonPushed) {
      playing = true;
      buttonPushed = false;
      gameSetup();
    }
    return;
  }

  tickrate = map(analogRead(TICKRATE_PIN), 0, 1023, 2, 25);
  tick();
  ++currentTick;
  if (collision) {
    tone(SOUND_PIN, 262, 200);
    playing = false;
  }
  buttonPushed = false;
  delay(1000 / tickrate);
}
