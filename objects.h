#include <SFML/Graphics.hpp>
#include "constants.h"

#ifndef OBJECTS_H
#define OBJECTS_H
float clamp(float val, float min, float max);
class Object {
    private:
        sf::Vector2f Position {};
        sf::Vector2f Velocity {};
    public:
        void SetPosition(sf::Vector2f position);
        sf::Vector2f GetPosition();
        void SetVelocity(sf::Vector2f velocity);
       
        sf::Vector2f GetVelocity();
        Object(sf::Vector2f position);
};
class Ball : public Object {
    private:
        float Size {};
        float Speed {0.05f};
    public:
        Ball(sf::Vector2f position, float size=5.f);
        sf::CircleShape Draw();
        float GetSize();
        float GetSpeed();
        void SetSpeed(float speed);
        void Update();
        
};
class Paddle : public Object {
    private:
        sf::Vector2f Size {};
    public:
        Paddle(sf::Vector2f position);
        bool IsBallInside(Ball& ball);
        sf::RectangleShape Draw();
        sf::Vector2f GetSize();
        void Update();
        
};


#endif