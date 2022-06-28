#include "SFML/Graphics.hpp"
#include "constants.h"
#include "bird_pipe_logic.h"
#include "pipe.h"
#include "bird.h"

void DrawPipes(Pipe* pipes, sf::RenderWindow& window) {
    for(int i{0}; i < PIPE_COUNT; i++) {
        PipeSprite pipeSprite = pipes[i].GetSprite();
        window.draw(pipeSprite.topRect);
        window.draw(pipeSprite.bottomRect);
    }
}
void Reset(Pipe* pipes, Bird& bird, int& score) {
    for(int i{0}; i < PIPE_COUNT; ++i) {
        pipes[i].Reset();
    }
    bird.SetVelocity(sf::Vector2f(0.f,0.f));
    bird.SetPosition(sf::Vector2f(50.f, BIRD_INIT_HEIGHT));
    score = 0;
    // for debug purposes
}
void SetPipeTopHeights(Pipe* pipes) {
    for(int i{0}; i < PIPE_COUNT; ++i) {
        pipes[i].RandomizeTopHeight();
    }
}
bool DidBirdCollideWithPipes(Bird& bird, Pipe* pipes) {
    // TODO: Get std::size working and replace 5 with it
    bool collided {false};
    for(int i{0}; i < PIPE_COUNT; ++i) {
        if(pipes[i].DidBirdCollide(bird)) {
            collided = true;
        }
    }
    return collided;
}
void UpdatePipes(Pipe* pipes, int& score, float dt) {
    for(int i{0}; i < PIPE_COUNT; ++i) {
        pipes[i].Update(score, dt);
    }
}
bool IsBirdOnEdge(Bird& bird) {
    return bird.GetPosition().y == 0 || bird.GetPosition().y == WINDOW_HEIGHT-bird.GetSize().y;
}
void InitializePipes(Pipe* pipes) {
    for(int i{0}; i < PIPE_COUNT; ++i) {
        //pipes[i] = Pipe(WINDOW_WIDTH/2 + i*200);
        pipes[i].SetStartXPosition(WINDOW_WIDTH/2 + i*200);
    }
    SetPipeTopHeights(pipes);
}
void drawEverything(sf::RenderWindow& window, Pipe* pipes, Bird& bird, sf::Text& scoreText) {
    window.draw(bird.GetSprite());
    DrawPipes(pipes, window);
    window.draw(scoreText);
}