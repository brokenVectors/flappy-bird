#include "SFML/Graphics.hpp"
#include "pipe.h"
#include "bird.h"
#include "constants.h"

Pipe::Pipe(float startXPosition) {
    TopRect = sf::RectangleShape();
    BottomRect = sf::RectangleShape();

    sf::Color darkGreen = sf::Color(0,100,0);
    TopRect.setFillColor(darkGreen);
    BottomRect.setFillColor(darkGreen);
    SetStartXPosition(startXPosition);
}
void Pipe::SetStartXPosition(float startXPosition) {
    XPosition = startXPosition;
    StartXPosition = startXPosition;
}
void Pipe::SetTopHeight(float topHeight) {
    TopHeight = topHeight;
} 
sf::Vector2f Pipe::GetBottomRectPosition() {
    // Under the bottom of the top rectangle, with a gap between both rects
    return sf::Vector2f(XPosition, 0) + sf::Vector2f(0.f, TopHeight + PIPE_GAP);
}
sf::Vector2f Pipe::GetBottomRectSize() {
    // Between position and bottom of screen
    return sf::Vector2f(Width, WINDOW_HEIGHT-BottomRect.getPosition().y);
}

void Pipe::Update(int& score, float dt) {
    XPosition -= PIPE_SPEED*dt;
    TopRect.setPosition(sf::Vector2f(XPosition, 0));
    TopRect.setSize(sf::Vector2f(Width, TopHeight));
    BottomRect.setPosition(GetBottomRectPosition());
    BottomRect.setSize(GetBottomRectSize());

    if(XPosition < 0.f - Width) {
        XPosition = WINDOW_WIDTH+150;
        scoreAdded = false;
    }
    if(XPosition < 0.f && !scoreAdded) {
        scoreAdded = true;
        ++score;
    }
}
bool Pipe::DidBirdTopCollide(Bird& bird) {
    sf::Vector2f birdPos = bird.GetPosition()+sf::Vector2f(bird.GetSize().x,0);
    sf::Vector2f topRectTopCorner = sf::Vector2f(XPosition, 0);
    sf::Vector2f topRectBottomCorner = topRectTopCorner + sf::Vector2f(Width, TopHeight);
    sf::Vector2f bottomRectTopCorner = GetBottomRectPosition();
    sf::Vector2f bottomRectBottomCorner = GetBottomRectPosition() + GetBottomRectSize();
    bool isInTopRect = (birdPos.x > topRectTopCorner.x) && (birdPos.x < topRectBottomCorner.x) && (birdPos.y > topRectTopCorner.y) && (birdPos.y < topRectBottomCorner.y);
    bool isInBottomRect = (birdPos.x > bottomRectTopCorner.x) && (birdPos.x < bottomRectBottomCorner.x) && (birdPos.y > bottomRectTopCorner.y) && (birdPos.y < bottomRectBottomCorner.y);
    return isInTopRect || isInBottomRect;
}
bool Pipe::DidBirdBottomCollide(Bird& bird) {
    sf::Vector2f birdPos = bird.GetPosition()+sf::Vector2f(0, bird.GetSize().y);
    sf::Vector2f topRectTopCorner = sf::Vector2f(XPosition, 0);
    sf::Vector2f topRectBottomCorner = topRectTopCorner + sf::Vector2f(Width, TopHeight);
    sf::Vector2f bottomRectTopCorner = GetBottomRectPosition();
    sf::Vector2f bottomRectBottomCorner = GetBottomRectPosition() + GetBottomRectSize();
    bool isInTopRect = (birdPos.x > topRectTopCorner.x) && (birdPos.x < topRectBottomCorner.x) && (birdPos.y > topRectTopCorner.y) && (birdPos.y < topRectBottomCorner.y);
    bool isInBottomRect = (birdPos.x > bottomRectTopCorner.x) && (birdPos.x < bottomRectBottomCorner.x) && (birdPos.y > bottomRectTopCorner.y) && (birdPos.y < bottomRectBottomCorner.y);
    return isInTopRect || isInBottomRect;
}
bool Pipe::DidBirdCollide(Bird& bird) {
    return DidBirdTopCollide(bird) || DidBirdBottomCollide(bird);
}
PipeSprite Pipe::GetSprite() {
    return PipeSprite {TopRect, BottomRect};
}
void Pipe::RandomizeTopHeight() {
    SetTopHeight( (((float) std::rand() / RAND_MAX) + 1) * 150 );
}
void Pipe::Reset() {
    XPosition = StartXPosition;
    RandomizeTopHeight();
}