#pragma once

typedef int Move;

constexpr Move MoveUp = 1;
constexpr Move MoveLeft = 2;
constexpr Move MoveRight = 4;
constexpr Move MoveDown = 8;

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