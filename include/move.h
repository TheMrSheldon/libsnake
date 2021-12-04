#pragma once

typedef int Move;

constexpr Move MoveUp = 1;
constexpr Move MoveLeft = 2;
constexpr Move MoveDown = 4;
constexpr Move MoveRight = 8;
constexpr Move MoveMask = 0b1111;

constexpr bool isUp(const Move& move) {
    return move & MoveUp;
}
constexpr bool isLeft(const Move& move) {
    return move & MoveLeft;
}
constexpr bool isRight(const Move& move) {
    return move & MoveRight;
}
constexpr bool isDown(const Move& move) {
    return move & MoveDown;
}

constexpr Move opposite(const Move& move) {
    // Rotate input-bits right by 2
    return ((move >> 2) | (move << 2)) & MoveMask;
}