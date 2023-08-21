#include <Arduino.h>

#define CUBE_SIZE 7

const int layerPins[CUBE_SIZE] = {2, 3, 4, 5, 6, 7, 8};

int cube[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE] = {0};

void setup() {
  for (int i = 0; i < CUBE_SIZE; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }

  Serial.begin(9600);
}

void loop() {

  for (int layer = 0; layer < CUBE_SIZE; layer++) {
    for (int row = 0; row < CUBE_SIZE; row++) {
      for (int col = 0; col < CUBE_SIZE; col++) {

        cube[layer][row][col] = HIGH;
        updateCube();
        delay(100);


        cube[layer][row][col] = LOW;
        updateCube();
        delay(100);
      }
    }
  }
}

void updateCube() {
  for (int layer = 0; layer < CUBE_SIZE; layer++) {
    digitalWrite(layerPins[layer], HIGH);

    for (int row = 0; row < CUBE_SIZE; row++) {
      for (int col = 0; col < CUBE_SIZE; col++) {
        digitalWrite(col + 9, cube[layer][row][col]);
      }
    }

    delay(1);
    digitalWrite(layerPins[layer], LOW);
  }
}
