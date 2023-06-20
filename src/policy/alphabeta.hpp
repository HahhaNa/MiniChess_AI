#pragma once
#include "../state/state.hpp"



/**
 * @brief Policy class for alphabeta policy, 
 * your policy class should have get_move method
 */
class AlphaBeta{
public:
  static Move get_move(State *state, int depth, int root_player);
  int minmax(State* state, int depth, int alpha, int beta, int root_player);
};