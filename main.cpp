#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include "constants.h"
#include "bird_pipe_logic.h"
#include "bird.h"
#include "pipe.h"

void handleInput(sf::RenderWindow& window, Bird& bird) {
    sf::Event event;
    while(window.pollEvent(event)) {
        // handle input here
        if(event.type == sf::Event::Closed) {
            window.close();
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            bird.Jump();
        }
    }
}
sf::Text CreateScoreText(sf::Font& font) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(50.f, 50.f));
    return text;
}
float getDeltaTime(sf::Clock& clock) {
    return clock.restart().asSeconds();
}
void setScoreText(sf::Text& scoreText, int score) {
    scoreText.setString(std::to_string(score));
}

int main() {
    
    std::srand(time(0));
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Flappy Bird");
   
    // Load files
    sf::Font font;
    sf::Texture birdTexture;
    if (!font.loadFromFile("font/Pixeled.ttf")) std::cerr << "Could not load font/Pixeled.ttf";
    if (!birdTexture.loadFromFile("sprites/bird.png")) std::cerr << "Could not load sprites/bird.png";
    
    // Initialize game
    int score {0};
    sf::Text scoreText {CreateScoreText(font)};
    Bird bird {Bird(birdTexture)};
    Pipe pipes[PIPE_COUNT];

    InitializePipes(pipes);
    while(window.isOpen()) {
        float dt = getDeltaTime(clock);
        handleInput(window, bird);
        setScoreText(scoreText, score);
        bool birdGotHit = DidBirdCollideWithPipes(bird, pipes) || IsBirdOnEdge(bird);
        if(birdGotHit) Reset(pipes, bird, score);
        window.clear(sf::Color::Cyan);
        bird.Update(dt);
        UpdatePipes(pipes, score, dt);
        drawEverything(window, pipes, bird, scoreText);
        window.display();
    }
    return 0;
}