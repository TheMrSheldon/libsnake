#pragma once

#include "state.h"
#include "definitions.h"
#include "winner.h"

#include <inttypes.h>
#include <vector>

struct SnakeEval {
    unsigned mobility;
    float mobility_per_area;
    unsigned health;
    unsigned foodInReach;
};

struct Evaluation {
    ls::Winner winner;
    SnakeEval snakes[2];
};

class Evaluator final {
private:
    const uint32_t scan_radius = 4;
    const uint32_t scan_area_width = 2*scan_radius+1;
    const uint32_t field_in_radius = (scan_radius * (scan_radius+1) * 2);

    std::vector<uint8_t> envbuffer;

    inline void scanProximity(const State& state, Evaluation& results) noexcept;
    inline bool isInEnvBuff(const Position& pos) const noexcept;
    inline uint8_t& getEnvBuffEntry(const Position& pos) noexcept;

    Evaluator(const Evaluator& other) = delete;
    Evaluator& operator=(const Evaluator& other) = delete;
public:
    DLLEXPORT Evaluator() noexcept;

    DLLEXPORT Evaluation evaluate(const State& state) noexcept;
};