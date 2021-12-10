#pragma once
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
