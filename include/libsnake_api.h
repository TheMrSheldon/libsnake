#pragma once

#include "state.h"
#include "move.h"
#include "position.h"
#include "eval.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C" {
    DLLEXPORT State* State_new(unsigned width, unsigned height, SnakeData snake1, SnakeData snake2, PosArray food);
    DLLEXPORT void State_free(State* state);
    DLLEXPORT bool State_isGameOver(const State* state);
    DLLEXPORT Move State_getPossibleActions(const State* state, unsigned snake);
    DLLEXPORT State* State_afterAction(const State* state, Move snake1Action, Move snake2Action);

    DLLEXPORT Evaluator* Evaluator_new();
    DLLEXPORT void Evaluator_free(Evaluator* eval);
    DLLEXPORT Evaluation Evaluator_evaluate(Evaluator* eval, State* state);
}