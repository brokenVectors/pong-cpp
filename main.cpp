#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "objects.h"
#include <string>

void draw(sf::RenderWindow& window, Paddle& left, Paddle& right, Ball& ball) {
    window.draw(left.Draw());
    window.draw(right.Draw());
    window.draw(ball.Draw());
}
sf::RenderWindow createWindow() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    return sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Pong");
    
}
void ResetBall(Ball& ball) {
    ball.SetPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    ball.SetVelocity(sf::Vector2f(-2.f, 0.f));
    ball.SetSpeed(0.05f);
}
void handleInput(sf::RenderWindow& window, sf::Event& event, Paddle& leftPaddle, Ball& ball) {
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
        bool isUpPressed {sf::Keyboard::isKeyPressed(sf::Keyboard::Up)};
        bool isDownPressed {sf::Keyboard::isKeyPressed(sf::Keyboard::Down)};
        if (isUpPressed) {
            leftPaddle.SetVelocity(sf::Vector2f(0,-0.1f));
        }
        if (isDownPressed) {
            leftPaddle.SetVelocity(sf::Vector2f(0,0.1f));
        }
        if(!isUpPressed && !isDownPressed) {
            leftPaddle.SetVelocity(sf::Vector2f(0,0.f));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            ResetBall(ball);
        }
    }
}
inline float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
    return lv.x * rv.x + lv.y * rv.y;
}
inline sf::Vector2f normalise(sf::Vector2f source)
{
    float length = std::sqrt(dot(source, source));
    if (length != 0) source /= length;
    return source;
}

void checkPaddleBounce(Paddle& paddle, Ball& ball, float xVelocity) {
    if(paddle.IsBallInside(ball)) {
        sf::Vector2f ballPosition = ball.GetPosition();
        sf::Vector2f paddlePosition = paddle.GetPosition();
        ball.SetSpeed(ball.GetSpeed() + 0.01f);
        if(ballPosition.y < paddlePosition.y + paddle.GetSize().y/2) {
            ball.SetVelocity(sf::Vector2f(xVelocity, -1.f));
        }
        else {
            ball.SetVelocity(sf::Vector2f(xVelocity, 1.f));
        }
    }
}
void checkEdgeBounce(Ball& ball) {
    sf::Vector2f ballPosition = ball.GetPosition();
    sf::Vector2f ballVelocity = ball.GetVelocity();
    float ballSize = ball.GetSize();
    if( (ballPosition.y == WINDOW_HEIGHT-ballSize*2) || (ballPosition.y == 0) ) {
        ball.SetVelocity(sf::Vector2f(ballVelocity.x, -ballVelocity.y));
    }
}
void checkBallInGoal(Ball& ball, int& leftPoints, int& rightPoints) {
    float x = ball.GetPosition().x;
    if(x < LEFT_GOAL-20) {
        ++rightPoints;
        std::cout << "Right wins!" << std::endl;
        ResetBall(ball);
    }
    if(x > RIGHT_GOAL+20) {
        ++leftPoints;
        std::cout << "Left wins!" << std::endl;
        ResetBall(ball);
    }
    //std::cout << getScoreString(leftPoints, rightPoints) << std::endl;
}
std::string getScoreString(int leftPoints, int rightPoints) {
    return std::to_string(leftPoints) + " - " + std::to_string(rightPoints);
}
int main()
{
    int leftPoints {0};
    int rightPoints {0};
    sf::RenderWindow window {createWindow()};
    Paddle leftPaddle = Paddle(sf::Vector2f(LEFT_GOAL, WINDOW_HEIGHT / 2));
    Paddle rightPaddle = Paddle(sf::Vector2f(RIGHT_GOAL, WINDOW_HEIGHT / 2));
    Ball ball = Ball( sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2) );

    ResetBall(ball);
    while(window.isOpen()) {
        sf::Event event;
        handleInput(window, event, leftPaddle, ball);
        
        checkPaddleBounce(leftPaddle, ball, 0.1f);
        checkPaddleBounce(rightPaddle, ball, -0.1f);
        checkEdgeBounce(ball);
        checkBallInGoal(ball, leftPoints, rightPoints);
        // Don't need to update because right paddle has no velocity, constantly follows the ball
        rightPaddle.SetPosition(sf::Vector2f(rightPaddle.GetPosition().x, ball.GetPosition().y));
        leftPaddle.Update();
        ball.Update();
        window.clear(sf::Color::White);
        draw(window, leftPaddle, rightPaddle, ball);
        window.display();
    }
    return 0;
}