#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct Ball {
    CircleShape shape;
    float ballRadius = 10.f, ballSpeed = 8.f;

    Vector2f speed{-ballSpeed, -ballSpeed};
    static constexpr int windowWidth{800}, windowHeight{600};

    Ball(float mX, float mY) {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }


    void setSpeed(float speed) {
      ballSpeed = speed;
    }

    float getSpeed(){
      return ballSpeed;
    }

//is this a real life? no this is just an illusion of movement
    void update() {
        shape.move(speed);

//checking the position to prevent ball leave the screen
        if (left() < 0) {
          speed.x = ballSpeed;
        }

        else if (right() > windowWidth) {
          speed.x = -ballSpeed;
        }

        if (top() < 0) {
          speed.y = ballSpeed;
        }
        else if(bottom() > windowHeight) {
           speed.y = 0;
           speed.x = 0;
           ballSpeed = 0;
           //endgame
        }
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getRadius(); }
    float right() { return x() + shape.getRadius(); }
    float top() { return y() - shape.getRadius(); }
    float bottom() { return y() + shape.getRadius(); }
};
#endif
