#include <LiquidCrystal.h>
#include "Constants.h"
#include "Display.h"
#include "Horse.h"
#include "Obstacle.h"
//#include <Collectible.h>

//game
int tickrate = 5;
int currentTick = 0;
volatile bool buttonPushed = false;
bool playing = false;
unsigned int distance = 0;

//horse
Horse horse;
int jumpTick = -10; 
bool needsToFall = false;
const int threshold = 4;
bool collision = false;

//obstacle
Obstacle obs[16];
bool hasObstacle[16][2];
int row;

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
}


void tick() {
  moveHorse();
  generateObstacles();
  moveObstacles();
  distance += 50;
  if (distance > 500) { //100 is placeholder
    digitalWrite(LED_PIN, HIGH);
  } 
}

void gameSetup() {
  //game
  Display::clear();
  currentTick = 0;
  distance = 0;
  digitalWrite(LED_PIN, LOW);

  //horse
  jumpTick = -10;
  needsToFall = false;
  collision = false;
  horse.reset();
  
  //obstacle
  row = random(2);
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 2; ++j) {
      hasObstacle[i][j] = false;
    }
    obs[i].setExists(false);
  }
}

void setup() {
  randomSeed(analogRead(A1));
  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUTTON, HIGH);
  pinMode(PIN_AUTOPLAY, OUTPUT);
  digitalWrite(PIN_AUTOPLAY, HIGH);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(TICKRATE_PIN, INPUT);

  // Digital pin 2 maps to interrupt 0
  attachInterrupt(0, buttonPush, FALLING);

  Display::setupLCD(); 
}

void loop() {
  //setup
  if (!playing) {
    distance = 0;
    collision = false;
    digitalWrite(LED_PIN, LOW);
    if (buttonPushed) {
      playing = true;
      buttonPushed = false;
      gameSetup();
    }
    return;
  }

  tickrate = map(analogRead(TICKRATE_PIN), 0, 1023, 5, 40);
  tick();
  ++currentTick;
  if (collision) {
    tone(SOUND_PIN, 262, 200);
    playing = false;
  }
  buttonPushed = false;
  delay(1000 / tickrate);
}
