#include <cstdlib>
#include <iostream>
#include <fstream>

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

bool valid_move(Move move) {
  if(move.first.first>4) return false;
  if(move.second.first>4) return false;
  if(move.first.second>5) return false;
  if(move.first.second>5) return false;
  return true;
}

static std::string y_axis = "654321000";
static std::string x_axis = "ABCDEFFF";


bool initialize = false;
int bestvalue = -1e8;
int Minimax::get_minimax(State *state, int depth, bool isPlayer){
  std::ofstream log("gamelog.txt");
  int value;
  state->get_legal_actions();

  if(depth == 0) {
    bestvalue  = value = -1e8;
    for(auto it: state->legal_actions) {
      log << "Legal0 action : " << x_axis[it.first.first] << y_axis[it.first.second] << "->" 
                                << x_axis[it.second.first] << y_axis[it.second.second] << "\n";
      State* next_state = state->next_state(it);
      value = next_state->evaluate();
      if(value > bestvalue) 
        next_state->prev_move = state->prev_move;
      bestvalue = std::max(bestvalue, value);
    }
    return bestvalue;
  }

  if(isPlayer) { // max
    bestvalue  = value = -1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      log << "Legal action : " << x_axis[it.first.first] << y_axis[it.first.second] << "->" 
                                << x_axis[it.second.first] << y_axis[it.second.second] << "\n";
      value = get_minimax(next_state, depth-1, false);
      if(value > bestvalue && depth==4) state->prev_move = next_state->prev_move; 
      bestvalue = std::max(bestvalue, value);
    }
    return bestvalue;
  } else { // min
    bestvalue  = value = 1e8;
    for(auto it: state->legal_actions) {
      State* next_state = state->next_state(it);
      value = get_minimax(next_state, depth-1, true);
      if(value < bestvalue && depth==4) next_state->prev_move = state->prev_move;
      bestvalue = std::max(bestvalue, value);
    }
    return bestvalue;
  }
  
  log.close();
  return bestvalue;
  
}