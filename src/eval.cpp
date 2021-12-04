#include "eval.h"

#include <algorithm>
#include <deque>

Evaluator::Evaluator() noexcept : envbuffer(scan_radius) {}

Evaluation Evaluator::evaluate(const State& state) noexcept {
    Evaluation result;
    result.winner = state.getWinner();
    if (!state.isGameOver()) {
        result.snakes[0].health = state.getSnake(0).getHealth();
        result.snakes[1].health = state.getSnake(1).getHealth();
        scanProximity(state, result);
    }
    return result;
}

uint8_t& Evaluator::getEnvBuffEntry(const Position& pos) noexcept {
    return envbuffer[pos.x + scan_radius*pos.y];
}

__attribute__((optimize("unroll-loops")))
void Evaluator::scanProximity(const State& state, Evaluation& results) noexcept {
    struct PosStr {
        Position pos;
        unsigned dist_rem;
    };
    
    // Initialize env-buffer to contain only 0 and for fields occupied by snake 1
    // the LSB is set and for fields occupied by snake 2 the second bit is set.
    std::fill(envbuffer.begin(), envbuffer.end(), 0); //set all entries to false
    const auto& snake1Pos = state.getSnake(0).getHeadPos();
    const auto& snake2Pos = state.getSnake(1).getHeadPos();
    for (const auto& tail : state.getSnake(0).getBody())
        getEnvBuffEntry(tail - snake1Pos) &= 1;
    for (const auto& tail : state.getSnake(1).getBody())
        getEnvBuffEntry(tail - snake2Pos) &= 2;
    for (const auto&  food : state.getFood()) {
        getEnvBuffEntry(food - snake1Pos) &= 3;
        getEnvBuffEntry(food - snake2Pos) &= 4;
    }

    // Scan the environment
    for (uint snake = 0; snake < 2; ++snake) {
        const uint8_t bit = 1<<snake;
        const uint8_t foodbit = 4<<snake;
        std::deque<PosStr> frontier = {PosStr{{scan_radius,scan_radius}, scan_radius}};
        unsigned totalVisited = 0;
        unsigned foodReached = 0;
        while (!frontier.empty()) {
            auto cur = frontier.front();
            frontier.pop_front();
            if (cur.dist_rem > 0) {
                for (const auto dir : {Position(-1,0), Position(1,0), Position(0,-1), Position(0,1)}) {
                    const bool inbound = cur.pos.x > 0 && cur.pos.y && cur.pos.x < scan_radius-1 && cur.pos.y < scan_radius-1;
                    uint8_t& envbuff = getEnvBuffEntry(cur.pos + dir);
                    if (inbound && !(envbuff & bit)) {
                        envbuff &= bit;
                        frontier.push_back({cur.pos + dir, cur.dist_rem-1});
                    }
                    foodReached += (envbuff&foodbit) != 0;
                }
            }
            totalVisited++;
        }
        results.snakes[snake].mobility = totalVisited/(float)field_in_radius;
        results.snakes[snake].foodInReach = foodReached;
    }
}