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
static std::string x_axis = "ABCDEFGH";

State* head = NULL;
static Movement pre_move;
bool initialize = false;
int value;
Movement Minimax::get_minimax(State *state, int depth, bool isPlayer){
  std::ofstream log("gamelog.txt");

  if(!initialize) {
    auto actions = state->legal_actions;
    pre_move =  Movement(actions[0], 0);
  }

  if(!head) head = state;
  if(!state->legal_actions.size())
    state->get_legal_actions();
  Board board = state->board;
  state->get_legal_actions();

  log << "MiniDepth: " << depth << std::endl;
  log << "PreMove: " << x_axis[pre_move.move.first.first] << y_axis[pre_move.move.first.second] << " -> " 
                      << x_axis[pre_move.move.second.first] << y_axis[pre_move.move.second.second] << "\n";
  log << "Now valule: " << pre_move.score << std::endl;

  if(depth==0) {
    if(isPlayer) { //maximize
      value = -1e8;
      for(auto it: state->legal_actions) {
        if(!valid_move(it)) continue;
        log << "Player0 Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
                      << x_axis[it.second.first] << y_axis[it.second.second] << "\n";
        if(board.board[it.first.first][it.first.second] != 0) continue;
        if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
        State* next_state = state->next_state(it);
        if(next_state->evaluate() > value) {
          pre_move = Movement(it, next_state->evaluate());
          value = pre_move.score;
        }
      }
      return pre_move;
    } else { //minimize
      value = 1e8;
      for(auto it: state->legal_actions) {
        if(!valid_move(it)) continue;
        log << "Opponent0 Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
                      << x_axis[it.second.first] << y_axis[it.second.second] << "\n";
        if(board.board[it.first.first][it.first.second] != 0) continue;
        if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
        State* next_state = state->next_state(it);
        if(next_state->evaluate() < value) {
          pre_move = Movement(it, next_state->evaluate());
          value = pre_move.score;
        } 
      }
      return pre_move;
    }
    log.close();
  }
  if(!state->legal_actions.size() || state->game_state == WIN) {
    log << "Special ending\n";
    return pre_move;
  }
  if(isPlayer) { //maximize
    value = -1e8;

    for(auto it: state->legal_actions) {
      if(!valid_move(it)) continue;
      //log << "Player Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
      //                << x_axis[it.second.first] << y_axis[it.second.second] << "\n";
      if(board.board[it.first.first][it.first.second] != 0) continue;
      if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
      State* next_state = state->next_state(it);
      if(get_minimax(next_state, depth-1, false).score > value) {
        pre_move = get_minimax(next_state, depth-1, false);
      }
    }
    return pre_move;
  } else { //minimize
    value = 1e8;
    for(auto it: state->legal_actions) {
      if(!valid_move(it)) continue;
      //log << "Opponent Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
      //                << x_axis[it.second.first] << y_axis[it.second.second] << "\n";
      if(board.board[it.first.first][it.first.second] != 0) continue;
      if(it.first.first==it.second.first && it.first.second==it.second.second) continue;
      State* next_state = state->next_state(it);
      if(get_minimax(next_state, depth-1, false).score < value) {
        pre_move = get_minimax(next_state, depth-1, true);
      }
    }
    return pre_move;
  }
  
  return pre_move;
}