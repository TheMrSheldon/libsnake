# First Steps
## Defining a snake
~~~~~~~~~~~~~{.cpp}
#include <libsnake/snake.h>

// Defining the snake's body as an std::vector<ls::Position>.
// The head's position is at index 0.
// E.g. this snake's is at coordinates (1|1) and the next segment is at (2|1).
std::vector<ls::Position> body = { {1, 1}, {2, 1} };

// The snakes health. Generally this should be between 0 and 100 (both inclusive).
// A snake with health ≤0 is dead.
int health = 100;

// Defining a squad. This snake is going to be part of its own team (only snake 0).
// If we wanted two snakes to be in the same team we can calculate the or of the squad.
// E.g. the squad containing snake 1 and 2 would be:
//    ls::SnakeFlags::ByIndex(1) | ls::SnakeFlags::ByIndex(2)
auto squad = ls::SnakeFlags::ByIndex(0);

ls::Snake snake(body, health, squad);
~~~~~~~~~~~~~

## Defining a gamestate
~~~~~~~~~~~~~{.cpp}
#include <libsnake/state.h>

// Declaring two (or more) snakes as previously discussed
ls::Snake snake0(/*...*/);
ls::Snake snake1(/*...*/);

// Declaring the width and height of the play-area
unsigned width = 10;
unsigned height = 20;

// A vector of positions of the food placed on the map
std::vector<ls::Position> food = {{2, 2}, {5, 8}};

// A vector of positions of the hazards placed on the map
std::vector<ls::Position> hazards = {{4, 4}};

ls::State state(width, height, {snake0, snake1}, std::move(food), std::move(hazards));
~~~~~~~~~~~~~

## Declaring the gamemode (and its settings)
~~~~~~~~~~~~~{.cpp}
const auto &gamemode = ls::gm::Standard;
~~~~~~~~~~~~~

## Simulating a step
~~~~~~~~~~~~~{.cpp}
#include <libsnake/gamemodes/standard.h>

// Choosing the gamemode
const auto &gamemode = ls::gm::Standard;

// Declaring the gamestate as previously discussed
const ls::State state(/*...*/)

// For each snake in the gamestate define an ls::Move.
// In this example we have 2 snakes:
const ls::Move& move0 = ls::Move::left; // Snake 0 moves left
const ls::Move& move1 = ls::Move::up;   // Snake 1 moves up

// Stepping the gamestate
const auto nextState = gamemode.stepState(state, {move0, move1});
~~~~~~~~~~~~~