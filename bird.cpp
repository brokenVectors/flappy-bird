#include "SFML/Graphics.hpp"
#include "constants.h"
#include "bird.h"

float clip(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}
sf::Vector2f Bird::GetPosition() {
    return Position;
}
void Bird::SetPosition(sf::Vector2f position) {
    if(position.y < 0) {
        position.y = 0;
    }
    if(position.y > WINDOW_HEIGHT - Size.y) {
        position.y = WINDOW_HEIGHT - Size.y;
    }
    position.y = clip(position.y, 0, WINDOW_HEIGHT - Size.y);
    Position = position;
}
sf::Vector2f Bird::GetVelocity() {
    return Velocity;
}
void Bird::SetVelocity(sf::Vector2f velocity) {
    Velocity = velocity;
}
sf::Vector2f Bird::GetSize() {
    return Size;
}
void Bird::SetSize(sf::Vector2f size) {
    Size = size;
}
void Bird::Update(float dt) {
    birdShape.setPosition(Position);
    SetPosition(GetPosition() + Velocity*dt);
    Velocity.y += BIRD_GRAVITY*dt;
}
void Bird::Jump() {
    Velocity.y = BIRD_JUMP;
}
sf::RectangleShape Bird::GetSprite() {
    return birdShape;
}
Bird::Bird(sf::Texture& texture) {
    Size = sf::Vector2f(32.5f * 1.25f, 25.f * 1.25f);
    birdShape = sf::RectangleShape(sf::Vector2f(Size.x, Size.y));
    birdShape.setTexture(&texture);
    birdShape.setFillColor(sf::Color::White);
    SetPosition(sf::Vector2f(50.f, BIRD_INIT_HEIGHT));
    SetVelocity(sf::Vector2f(0.f, 0.f));
}