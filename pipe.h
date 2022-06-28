#include "SFML/Graphics.hpp"
#include "constants.h"
#include "bird.h"

#ifndef PIPE_H
#define PIPE_H
struct PipeSprite {
    sf::RectangleShape topRect;
    sf::RectangleShape bottomRect;
};

class Pipe {
    private:
    sf::RectangleShape TopRect;
    sf::RectangleShape BottomRect;
    PipeSprite sprite;
    float Width { 50.f };
    float TopHeight;
    float XPosition {};
    float StartXPosition {};
    bool scoreAdded {false};
    public:
    Pipe(float startXPosition=WINDOW_HEIGHT);
    void SetTopHeight(float topHeight);
    sf::Vector2f GetBottomRectPosition();
    sf::Vector2f GetBottomRectSize();

    void Update(int& score, float dt);
    bool DidBirdTopCollide(Bird& bird);
    bool DidBirdBottomCollide(Bird& bird);
    bool DidBirdCollide(Bird& bird);
    void SetStartXPosition(float startXPosition);
    PipeSprite GetSprite();
    void RandomizeTopHeight();
    void Reset();
};
#endif