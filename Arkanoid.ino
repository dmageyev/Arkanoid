#include <GameBoy.h>
#include "Blocks.h"
GameBoy gb;

byte paddle[3] = { 1, 1, 1 };

byte Block_level_1[4][8] = {
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 }
};


byte Block_level_2[4][8] = {
  { 1, 0, 1, 0, 1, 0, 1, 0 },
  { 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 0, 1, 0 }
};

int paddleX = 3;
int paddleY = 14;

int ballX = 4;
int ballY = 13;
int directionX = 1;
int directionY = -1;

bool stateLevel = true;
int numLevel = 1;



void setup() {
  gb.begin(0);
  createLevel();
  Serial.begin(9600);
}

void loop() {


  ball();
  makePaddle();
  drawPaddle(paddle, paddleX, paddleY);
  delay(500);
  gb.drawDisplay();
}


void drawPaddle(byte arr[3], int x, int y) {
  for (int i = 0; i < 3; i++) {
    if (arr[i] == 1) {
      gb.drawPoint(x + i, y);
    }
  }
}

void makePaddle() {
  if (gb.getKey() == 4 && paddleX > 0) {
    paddleX--;
  }
  if (gb.getKey() == 5 && paddleX < 5) {
    paddleX++;
  }
}

void ball() {
  ballX += directionX;
  ballY += directionY;
  checkCollision();
  gb.drawPoint(ballX, ballY);
}


void checkCollision() {
  if (ballX <= 0 || ballX >= 7) directionX = -directionX;
  if (ballY <= 0 || ballY >= 15) directionY = -directionY;

  if (ballY == paddleY - 1 && ballX >= paddleX && ballX <= paddleX + 3 ) {
    directionY = -1;
  }

  if (gb.checkCollision(ballX, ballY)) {
    gb.wipePoint(ballX, ballY);
    directionY = 1;
    gb.sound(SCORE);

  }
}


void drawBricks(byte arr[4][8]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      if (arr[i][j] == 1) {
        gb.memDisplay(j, i);

      }
    }
  }
}


void createLevel() {
  memClear();
  if (numLevel == 1 && stateLevel) {
    gb.clearDisplay();
    drawBricks(Block_level_1);
    stateLevel = false;
  }
  else if (numLevel == 2 && stateLevel) {
    gb.clearDisplay();
    drawBricks(Block_level_2);
    stateLevel = false;
  }
}

void memClear() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      gb.display[j][i] = 0;
    }
  }
}



