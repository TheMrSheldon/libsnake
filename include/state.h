#pragma once

#include "move.h"
#include "snake.h"
#include "definitions.h"

#include <array>
#include <vector>
#include <memory>

/**
 * @brief The winner enum class works as a flag. If the game is not over, no bit is set (Winner::None).
 * If the game was won by Player1, the first bit is set (Winner::Player1), if the game was won by Player2,
 * the second bit is set (Winner::Player2). If both players one, both these bits are set (Winner::Tie).
 */
enum class Winner : unsigned char {
    None = 0,
    Player1 = 1,
    Player2 = 2,
    Tie = static_cast<unsigned char>(Player1) | static_cast<unsigned char>(Player1)
};

class State final {
private:
    const unsigned width;
    const unsigned height;
    const std::array<const Snake, 2> snakes;
    const std::shared_ptr<const std::vector<Position>> foodPositions;
    
    /**
     * @brief Construct a new State object by "stepping" the provided state using the given information.
     * The created state will have the two snakes moved using the provided action. If either snake has
     * eaten (eaten1 or eaten2 respectively are set) the respective snake gets elongated. If either snake
     * was killed (kill1 or kill2 respectively) the according snake is set to 0 health.
     * 
     * @param other The previous state from which data is copied.
     * @param move1 The direction in which the first snake is moved for the new (this) state.
     * @param move2 The direction in which the second snake is moved for the new (this) state.
     * @param eaten1 True if the first snake has eaten after enacting move1 in transition to this state.
     * @param eaten2 True if the second snake has eaten after enacting move2 in transition to this state.
     * @param kill1 True if the first snake has died after enacting move1 in transition to this state.
     * @param kill2 True if the second snake has died after enacting move2 in transition to this state.
     * @see Snake::after_move()
     */
    State(const State& other, Move move1, Move move2, bool eaten1, bool eaten2, bool kill1, bool kill2) noexcept;
public:
    DLLEXPORT State(unsigned width, unsigned height, SnakeData snake1, SnakeData snake2, PosArray food) noexcept;
    DLLEXPORT bool isGameOver() const noexcept;
    DLLEXPORT Winner getWinner() const noexcept;

    DLLEXPORT Move getPossibleActions(unsigned snake) const noexcept;
    DLLEXPORT State* afterAction(Move snake1Action, Move snake2Action) const noexcept;

    const Snake& getSnake(std::size_t index) const noexcept { return snakes[index]; }
    const std::vector<Position>& getFood() const noexcept { return *foodPositions; }
    unsigned getWidth() const noexcept { return width; }
    unsigned getHeight() const noexcept { return height; }

    DLLEXPORT bool isFoodAt(const Position& pos) const noexcept;
};