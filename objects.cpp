#include "objects.h"

float clamp(float val, float min, float max) {
    if( (val > min) && (val < max)) {
        return val;
    }
    else if(val <= min) return min;
    else if(val >= max) return max;
}

void Object::SetPosition(sf::Vector2f position) {
    Position = position;
}
sf::Vector2f Object::GetPosition() {
    return Position;
}
void Object::SetVelocity(sf::Vector2f velocity) {
    Velocity = velocity;
}

sf::Vector2f Object::GetVelocity() {
    return Velocity;
}
Object::Object(sf::Vector2f position) {
    Position = position;
}

Ball::Ball(sf::Vector2f position, float size) : Object(position) {
    Size = size;
}
sf::CircleShape Ball::Draw() {
    sf::CircleShape circle(Size);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition( GetPosition() );
    return circle;
}
void Ball::Update() {
    sf::Vector2f pos = GetPosition();
    sf::Vector2f vel = GetVelocity();
    SetPosition(sf::Vector2f(clamp(pos.x + vel.x*6 * Speed, 0, WINDOW_WIDTH-Size*2), clamp(pos.y + (vel.y/1) * Speed, 0, WINDOW_HEIGHT-Size*2)));
}

float Ball::GetSize() {
    return Size;
}
float Ball::GetSpeed() {
    return Speed;
}
void Ball::SetSpeed(float speed) {
    Speed = speed;
}
Paddle::Paddle(sf::Vector2f position) : Object(position) {
    Size = sf::Vector2f(25.f, 100.f);
}
bool Paddle::IsBallInside(Ball& ball) {
    sf::Vector2f ballPosition = ball.GetPosition();
    sf::Vector2f paddlePosition = GetPosition();
    bool isXInside =  (ballPosition.x > paddlePosition.x) && (ballPosition.x < paddlePosition.x + Size.x);
    bool isYInside = (ballPosition.y > paddlePosition.y-20) && (ballPosition.y < paddlePosition.y + Size.y);
    return isYInside && isXInside;
}
sf::Vector2f Paddle::GetSize() {
    return Size;
}
sf::RectangleShape Paddle::Draw() {
    sf::RectangleShape rectangle(Size);
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(GetPosition());
    return rectangle;
}
void Paddle::Update() {
    sf::Vector2f pos = GetPosition();
    sf::Vector2f vel = GetVelocity();
    SetPosition(sf::Vector2f(clamp(pos.x + vel.x, 0, WINDOW_WIDTH-Size.x), clamp(pos.y + vel.y, 0, WINDOW_HEIGHT-Size.y)));
}