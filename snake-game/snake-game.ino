#include "button.h"
#include "snake.h"
#include "fruit.h"
#include "renderer.h"

CREATE_INTERRUPT_BUTTON(buttonUp, D5);
CREATE_INTERRUPT_BUTTON(buttonDown, D6);
CREATE_INTERRUPT_BUTTON(buttonLeft, D0);
CREATE_INTERRUPT_BUTTON(buttonRight, D7);

Snake snake;
Fruit fruit(&snake);

void setup() {
  Serial.begin(115200);
  Renderer::initialize();
  }

void loop() {
  if (buttonUp.isPressed()) snake.turn(UP);
  if (buttonDown.isPressed()) snake.turn(DOWN);
  if (buttonLeft.isPressed()) snake.turn(LEFT);
  if (buttonRight.isPressed()) snake.turn(RIGHT);


  bool resetFruit = false;
  if(snake.nextHeadPosition() == fruit.getPosition()) {
    snake.grow();
    resetFruit = true;
  }

  snake.advance();
  if(resetFruit) fruit.randomize(&snake);
  
  Renderer::startFrame();
  Renderer::renderBorder();
  Renderer::renderSnake(&snake);
  Renderer::renderFruit(&fruit);
  if(!snake.isAlive()) Renderer::renderGameOver(&snake);
  Renderer::endFrame();
  
  delay(150);
}
