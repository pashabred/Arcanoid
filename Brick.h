#ifndef BRICK_H
#define BRICK_H
#include "Rectangle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

struct Brick : public Rectangle {

  bool isDestroyed{false};

  float blockWidth = 60.f, blockHeight = 20.f;

  float getBlockWidth(){
    return blockWidth;
  }
  float getBlockHeight(){
    return blockHeight;
  }

  Brick(float mX, float mY) {
    shape.setPosition(mX,mY);
    shape.setSize({blockWidth,blockHeight});
    shape.setFillColor(Color::Yellow);
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
  }
};
#endif
