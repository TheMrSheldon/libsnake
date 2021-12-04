#pragma once

#include "state.h"

#include <inttypes.h>
#include <vector>

struct SnakeEval {
    float mobility;
    unsigned health;
    unsigned foodInReach;
};

struct Evaluation {
    Winner winner;
    SnakeEval snakes[2];
};

class Evaluator final {
private:
    const uint scan_radius = 4;
    const uint field_in_radius = (scan_radius * (scan_radius+1) * 2);

    std::vector<uint8_t> envbuffer;

    void scanProximity(const State& state, Evaluation& results) noexcept;
    uint8_t& getEnvBuffEntry(const Position& pos) noexcept;

    Evaluator(const Evaluator& other) = delete;
    Evaluator& operator=(const Evaluator& other) = delete;
public:
    Evaluator() noexcept;

    Evaluation evaluate(const State& state) noexcept;
};