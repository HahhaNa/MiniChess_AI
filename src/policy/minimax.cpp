#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/* From ppt: 
function  minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value
*/
State* head = NULL;
Movement pre_move;
int value;
Movement Minimax::get_minimax(State *state, int depth, bool isPlayer){
  if(!head) head = state;
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth==0 || !state->legal_actions.size() || state->game_state == WIN) {
    return pre_move;
  }
  if(isPlayer) { //maximize
    value = -1e8;

    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      if(get_minimax(next_state, depth-1, false).score > value) {
        pre_move = get_minimax(next_state, depth-1, false);
        value = pre_move.score;
      } 
    }
    return pre_move;
  } else { //minimize
    value = 1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      if(get_minimax(next_state, depth-1, false).score < value) {
        pre_move = get_minimax(next_state, depth-1, true);
        value = pre_move.score;
      } 
    }
    return pre_move;
  }
  
  auto actions = state->legal_actions;
  return Movement(actions[0], 0);
}