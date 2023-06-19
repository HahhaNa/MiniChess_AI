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

static std::string y_axis = "654321";
static std::string x_axis = "ABCDE";

State* head = NULL;
static Movement pre_move;
int value;
Movement Minimax::get_minimax(State *state, int depth, bool isPlayer){
  std::ofstream log("gamelog.txt");
  if(!head) head = state;
  Board board = state->board;
  state->get_legal_actions();
  log << "MiniDepth: " << depth << std::endl;
  log << "PreMove: " << x_axis[pre_move.move.first.first] << " " << y_axis[pre_move.move.first.second] << " -> " 
                      << x_axis[pre_move.move.second.first] << " " << y_axis[pre_move.move.second.second] << "\n";

  if(depth==0) {
    if(isPlayer) { //maximize
      value = -1e8;
      for(auto it: state->legal_actions) {
        log << "Player0 Move: " << x_axis[it.first.first] << " " << y_axis[it.first.second] << " -> " 
                      << x_axis[it.second.first] << " " << y_axis[it.second.second] << "\n";
        if(board.board[it.first.first][it.first.second] != 0) continue;
        if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
        State* next_state = state->next_state(it);
        if(next_state->evaluate() > value) {
          pre_move = Movement(it, next_state->evaluate());
          value = pre_move.score;
        }
      }
    } else { //minimize
      value = 1e8;
      for(auto it: state->legal_actions) {
        log << "Opponent0 Move: " << x_axis[it.first.first] << " " << y_axis[it.first.second] << " -> " 
                      << x_axis[it.second.first] << " " << y_axis[it.second.second] << "\n";
        if(board.board[it.first.first][it.first.second] != 0) continue;
        if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
        State* next_state = state->next_state(it);
        if(next_state->evaluate() < value) {
          pre_move = Movement(it, next_state->evaluate());
          value = pre_move.score;
        } 
      }
    }
    log.close();
    return pre_move;
  }
  if(!state->legal_actions.size() || state->game_state == WIN) {
    return pre_move;
  }
  if(isPlayer) { //maximize
    value = -1e8;

    for(auto it: state->legal_actions) {
      log << "Player Move: " << x_axis[it.first.first] << " " << y_axis[it.first.second] << " -> " 
                      << x_axis[it.second.first] << " " << y_axis[it.second.second] << "\n";
      if(board.board[it.first.first][it.first.second] != 0) continue;
      if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
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
      log << "Opponent Move: " << x_axis[it.first.first] << " " << y_axis[it.first.second] << " -> " 
                      << x_axis[it.second.first] << " " << y_axis[it.second.second] << "\n";
      if(board.board[it.first.first][it.first.second] != 0) continue;
      if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
      State* next_state = state->next_state(it);
      if(get_minimax(next_state, depth-1, false).score < value) {
        pre_move = get_minimax(next_state, depth-1, true);
        value = pre_move.score;
      } 
    }
    return pre_move;
  }
  
  // default
  auto actions = state->legal_actions;
  return Movement(actions[0], 0);
}