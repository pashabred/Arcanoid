#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"

using namespace std;
using namespace sf;

constexpr int windowWidth{800}, windowHeight{600};


float blockWidth = 60.f, blockHeight = 20.f;
constexpr int countBlocksX{11}, countBlocksY{4};


//Making the collision
template <class T1, class T2>
bool isIntersecting(T1& mA, T2& mB) {
  return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

//collision between Paddle and the Ball
void tryCollisionPB(Paddle& mPaddle, Ball& mBall) {

  if (!isIntersecting(mPaddle,mBall)) {
    return;
  }
  mBall.speed.y = -mBall.getBallSpeed();

  if (mBall.x() < mPaddle.x()) {
    mBall.speed.x = -mBall.getBallSpeed();
  }
  else {
    mBall.speed.x = mBall.getBallSpeed();
  }
}
//collision between Ball and the Bricks
void tryCollisionBB(Brick& mBrick, Ball& mBall) {
  if (!isIntersecting(mBrick,mBall)) {
    return;
  }

  mBrick.isDestroyed = true;

  float overlapLeft = mBall.right() - mBrick.left();
  float overlapRight = mBrick.right() - mBall.left();
  float overlapTop = mBall.bottom() - mBrick.top();
  float overlapBottom =mBrick.bottom() - mBall.top();

  //check from which side did the ball come
  bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));

  bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

  float minOverlapX;
  if (ballFromLeft) {
    minOverlapX = overlapLeft;
  }
  else {
    minOverlapX = overlapRight;
  }

  float minOverlapY;
  if (ballFromTop) {
    minOverlapY = overlapTop;
  }
  else {
    minOverlapX = overlapBottom;
  }

  if(abs(minOverlapX) < abs(minOverlapY))
    if (ballFromLeft){
      mBall.speed.x = -mBall.getBallSpeed();
    }
    else {
        mBall.speed.x = mBall.getBallSpeed();
    }
    else
      if (ballFromTop) {
        mBall.speed.y = -mBall.getBallSpeed();
      }
      else {
        mBall.speed.y = mBall.getBallSpeed();
      }
}

int main() {

    Ball ball {windowWidth / 2, windowHeight - 70};
    Paddle paddle {windowWidth / 2, windowHeight - 50};
    Brick endGameBrick {windowWidth / 2, windowHeight / 2};
    vector<Brick> bricks;
    //creating the grid of blocks
    for (int iX=0;iX<countBlocksX;iX++) {
      for (int iY=0;iY<countBlocksY;iY++) {
        bricks.emplace_back( (iX+1) * (blockWidth + 3) + 22,(iY+2) * (blockHeight + 3));
      }
    }

    RenderWindow window {{windowWidth, windowHeight}, "Arcanoid"};
    window.setFramerateLimit(60);


    while(true) {
        window.clear(Color::Black);

        //start game with giving ball and paddle life
        if (Keyboard::isKeyPressed(Keyboard::Space)){
          ball.setBallSpeed(8.f);
          paddle.setPaddleSpeed(8.f);
        }
        //game over
        if (ball.getBallStatus()) {
          window.draw(endGameBrick.shape);
          //break;
        }
        //if esc is pressed break the loop
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
          break;
        }

        paddle.update();
        ball.update();

        tryCollisionPB(paddle,ball);

        for(auto& brick : bricks) tryCollisionBB(brick, ball);
        //remove bricks
        //it works, but i do not know how
        bricks.erase(remove_if(begin(bricks), end(bricks),
                    [](const Brick& mBrick) {
                             return mBrick.isDestroyed;
                         }),
            end(bricks));


        window.draw(paddle.shape);
        window.draw(ball.shape);
        for(auto& brick : bricks) window.draw(brick.shape);
        window.display();

    }

    return 0;
}
