#include <cstdlib>
#include <fstream>

#include "../state/state.hpp"
#include "./alphabeta.hpp"



Move AlphaBeta::get_move(State *state, int depth, int root_player){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  AlphaBeta alphabeta;
  int alphabeta_val = alphabeta.minmax(state, depth, -1e8, 1e8, root_player);
  return state->pmove;
}


/**
 * @brief AlphaBeta to get a legal action
 * 
 * @param state Now state
 * @param depth return evaluate score when depth == 1
 * @return Move 
 */
bool initialize = false;
int AlphaBeta::minmax(State* state, int depth, int alpha, int beta, int root_player) {
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth==0 || state->legal_actions.empty()) {
    return state->evaluate(root_player);
  }
  if(root_player == state->player) { // Maximize
    int maxEva = -1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      int Eva = minmax(next_state, depth-1, alpha, beta, root_player);
      maxEva = std::max(maxEva, Eva);
      alpha = std::max(alpha, maxEva);
      if(!initialize) {
        state->pmove = next_state->pmove;
        initialize = true;
      }
      if((Eva>maxEva|| maxEva>alpha) && depth==6) state->pmove = next_state->pmove;
      if(beta <= alpha) break;
    }
    return maxEva;
  } else { // Minimize
    int minEva = 1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      int Eva = minmax(next_state, depth-1, alpha, beta, root_player);
      minEva = std::min(minEva, Eva);
      beta = std::min(beta, minEva);
      if(!initialize) {
        state->pmove = next_state->pmove;
        initialize = true;
      }
      if((Eva<minEva || minEva<beta) && depth==6) 
        state->pmove = next_state->pmove;
      if(beta <= alpha) break;
    }
    return minEva;
  }
}