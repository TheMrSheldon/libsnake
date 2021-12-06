#pragma once

#include "position.h"
#include "move.h"

#include <vector>

struct PosArray {
    Position* data;
    std::size_t length;

    PosArray(Position* data, std::size_t length) : data(data), length(length) {}
    PosArray(std::vector<Position>& vector) : PosArray(vector.data(), vector.size()) {}
};
struct SnakeData {
    struct PosArray body;
    Move direction;
    unsigned health;

    SnakeData(PosArray body, Move direction, unsigned health) : body(body), direction(direction), health(health) {}
};

class Snake final {
private:
    const std::vector<Position> body;
    const Move direction;
    const int health;

    Snake(std::vector<Position>&& body, Move direction, int health) noexcept : body(std::move(body)), direction(direction), health(health) {}
public:
    Snake(SnakeData data) noexcept : body(data.body.data, data.body.data+data.body.length), direction(data.direction), health(data.health) {}

    inline const Position& getHeadPos() const noexcept { return body[0];}
    inline const std::size_t length() const noexcept { return body.size(); }

    inline const Move& getDirection() const noexcept { return direction; }
    inline const int& getHealth() const noexcept { return health; }

    inline const std::vector<Position>& getBody() const noexcept { return body; }

    inline Snake afterMove(const Move& move, bool hasEaten, bool dead) const noexcept {
        if (dead)
            return Snake(std::vector<Position>(), move, 0);
        const std::size_t newLength = body.size() + hasEaten;
        std::vector<Position> newbody;
        newbody.reserve(newLength);
        newbody.emplace_back(getHeadPos().after_move(move));
        for (std::size_t i = 0; i < body.size()-!hasEaten; ++i)
            newbody.emplace_back(body[i]);
        return Snake(std::move(newbody), move, hasEaten? 100 : health-1);
    }
};