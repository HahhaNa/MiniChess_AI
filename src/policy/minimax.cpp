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


/**
 * @brief Return max score move
 * 
 * @param state Now state
 * @param depth ?
 * @return Move 
 */
State* root = NULL;
int self = -1;
Move Minimax::get_minimax_move(State *state, int depth){
  static Move move;
  
  if(!root) {
    root = state;
    self = state->player;
  }
  if(depth==0 || state->avl_actions.empty()) {
    return move;
  }
  if(!(state->player == self)) {
    static int value = 1e8;
    Movement tmp = *(state->avl_actions.begin());
    move = tmp.score < value? tmp.move : move;
    return move;
  } else if(state->player == self) {
    static int value = -1e8;
    Movement tmp = *(state->avl_actions.end());
    move = tmp.score > value? tmp.move : move;
    return move;
  } 
}