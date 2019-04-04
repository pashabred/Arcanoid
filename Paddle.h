#ifndef PADDLE_H
#define PADDLE_H
#include "Rectangle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


struct Paddle : public Rectangle {
  Vector2f speed;

  float paddleWidth = 60.f, paddleHeight = 20.f, paddleSpeed = 0;
      static constexpr int windowWidth{800}, windowHeight{600};

  Paddle(float mX, float mY) {
    shape.setPosition(mX,mY);
    shape.setSize({paddleWidth,paddleHeight});
    shape.setFillColor(Color::Green);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
  }

  void setPaddleSpeed(float speed) {
    paddleSpeed = speed;
  }
  //paddle left/right gameplay and check if the paddle inside the window
  void update() {
    shape.move(speed);

    if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) {
      speed.x = -paddleSpeed;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth) {
      speed.x = paddleSpeed;
    }
    else {
      speed.x = 0;
    }
  }
};
#endif
