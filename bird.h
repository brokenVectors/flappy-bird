#ifndef BIRD_H
#define BIRD_H
#include "SFML/Graphics.hpp"
#include "constants.h"
class Bird {
    private:
    sf::Vector2f Position;
    sf::Vector2f Size;
    sf::Vector2f Velocity;
    sf::RectangleShape birdShape;
    public:
    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetVelocity();
    void SetVelocity(sf::Vector2f velocity);
    sf::Vector2f GetSize();
    void SetSize(sf::Vector2f size);
    void Update(float dt);
    void Jump();
    Bird(sf::Texture& texture);
    sf::RectangleShape GetSprite();
};
#endif