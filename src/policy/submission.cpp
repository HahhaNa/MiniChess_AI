#include <cstdlib>
#include <fstream>

#include "../state/state.hpp"
#include "./submission.hpp"

Move Submission::get_move(State *state, int depth, int root_player){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  Submission minimax;
  int minimax_val = minimax.minmax(state, depth, root_player);
  return state->pmove;
  // return state->nmove;
}



int Submission::minmax(State* state, int depth, int root_player) {
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth==0 || state->legal_actions.empty()) {
    return state->evaluate(root_player);
  }
  if(root_player == state->player) {
    int rtn = -1e8;
    for(Move it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      int tmp = minmax(next_state, depth-1, root_player);
      if(tmp>rtn && depth==4) state->pmove = next_state->pmove;
      rtn = (tmp>rtn)? tmp:rtn;
    }
    return rtn;
  } else {
    int rtn = 1e8;
    for(Move it: state->legal_actions) {
      State* next_state = state->next_state(it);
      next_state->pmove = it;
      int tmp = minmax(next_state, depth-1, root_player);
      if(tmp<rtn && depth==4) state->pmove = next_state->pmove;
      rtn = (tmp<rtn)? tmp:rtn;
    }
    return rtn;
  }
}