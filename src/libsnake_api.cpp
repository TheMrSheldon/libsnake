#include "libsnake_api.h"

#include <iostream>

State* State_new(unsigned width, unsigned height, SnakeData snake1, SnakeData snake2, PosArray food) {
    return new State(width, height, snake1, snake2, food);
}
void State_free(State* state) { delete state; }
bool State_isGameOver(const State* state) { return state->isGameOver(); }
Move State_getPossibleActions(const State* state, unsigned snake) { return state->getPossibleActions(snake); }
State* State_afterAction(const State* state, Move snake1Action, Move snake2Action) { return state->afterAction(snake1Action, snake2Action); }
void State_print(const State* state) { state->print(std::cout); }

Evaluator* Evaluator_new() { return new Evaluator(); }
void Evaluator_free(Evaluator* eval) { delete eval; }
Evaluation Evaluator_evaluate(Evaluator* eval, State* state) { return eval->evaluate(*state); }