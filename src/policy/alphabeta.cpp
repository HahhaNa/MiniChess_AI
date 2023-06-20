#include <cstdlib>
#include <fstream>

#include "../state/state.hpp"
#include "./alphabeta.hpp"
#include "./minimax.hpp"



Move AlphaBeta::get_move(State *state, int depth, int root_player){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  AlphaBeta alphabeta;
  int alphabeta_val = alphabeta.minmax(state, depth, -1e8, 1e8, root_player);
  return state->pmove;
  // return state->nmove;
}


/**
 * @brief AlphaBeta to get a legal action
 * 
 * @param state Now state
 * @param depth return evaluate score when depth == 1
 * @return Move 
 */
int AlphaBeta::minmax(State* state, int depth, int alpha, int beta, int root_player) {
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth==0 || state->legal_actions.empty()) {
    return state->evaluate(root_player);
  }
  if(root_player == state->player) {
    int maxEva = -1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      Minimax minimax;
      int Eva = minimax.minmax(next_state, depth-1, root_player);
      maxEva = std::max(maxEva, Eva);
      alpha = std::max(alpha, maxEva);
      if(beta <= alpha) break;
    }
    return maxEva;
  } else {
    int minEva = 1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      Minimax minimax;
      int Eva = minimax.minmax(next_state, depth-1, root_player);
      minEva = std::max(minEva, Eva);
      beta = std::max(beta, minEva);
      if(beta <= alpha) break;
    }
    return minEva;
  }
  
}