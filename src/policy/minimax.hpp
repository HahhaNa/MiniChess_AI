#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for minimax policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  Movement get_minimax(State *state, int depth);
};