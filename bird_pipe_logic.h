#ifndef BIRD_PIPE_LOGIC_H
#define BIRD_PIPE_LOGIC_H
#include "SFML/Graphics.hpp"
#include "constants.h"
#include "bird.h"
#include "pipe.h"

void DrawPipes(Pipe* pipes, sf::RenderWindow& window); // Draws the given pipes to the given window.
void Reset(Pipe* pipes, Bird& bird, int& score); // Resets the game state: repositions bird, calls SetPipeTopHeights and sets score to 0.
void SetPipeTopHeights(Pipe* pipes); // Randomizes the size of the top rectangle of each pipe.
bool DidBirdCollideWithPipes(Bird& bird, Pipe* pipes); // Checks if the bird is in contact with any of the pipes.
void UpdatePipes(Pipe* pipes, int& score, float dt); // Calls the Update method of each pipe in the given array, which shifts them to the left by a given amount.
bool IsBirdOnEdge(Bird& bird); // Checks if the bird is on the top or bottom edge of the screen.
void InitializePipes(Pipe* pipes); // Set position of an array of pipes.
void drawEverything(sf::RenderWindow& window, Pipe* pipes, Bird& bird, sf::Text& scoreText);
#endif