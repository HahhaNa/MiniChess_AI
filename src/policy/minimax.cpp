#include <cstdlib>
#include <fstream>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Minimax to get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth, int root_player){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  Minimax minimax;
  int minimax_val = minimax.minmax(state, depth, root_player);
  // the proper move for minimax_val
  return state->pmove;
}

int Minimax::minmax(State* state, int depth, int root_player) {
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth==0 || state->legal_actions.empty()) {
    return state->evaluate(root_player);
  }
  if(root_player == state->player) { //maximize
    int rtn = -1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      int tmp = minmax(next_state, depth-1, root_player);
      if(tmp>rtn && depth==4) state->pmove = it;
      rtn = (tmp>rtn)? tmp:rtn;
    }
    return rtn;
  } else { // minimize
    int rtn = 1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      int tmp = minmax(next_state, depth-1, root_player);
      if(tmp<rtn && depth==4) state->pmove = it;
      rtn = (tmp<rtn)? tmp:rtn;
    }
    return rtn;
  }
}