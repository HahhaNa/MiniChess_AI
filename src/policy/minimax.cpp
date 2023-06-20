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

State* head = NULL;
static Movement pre_move;
bool initialize = false;
int value;
Movement Minimax::get_minimax(State *state, int depth, bool isPlayer){
  std::ofstream log("gamelog.txt");
  auto actions = state->legal_actions;
  if(!initialize) {
    pre_move =  Movement(actions[0], -100);
  }

  if(!head) head = state;
  if(!state->legal_initialize){
    state->get_legal_actions();
    state->legal_initialize = true;
  }

  Board board = state->board;

  log << "MiniDepth: " << depth << std::endl;
  log << "PreMove: " << x_axis[pre_move.move.first.first] << y_axis[pre_move.move.first.second] << " -> " 
                      << x_axis[pre_move.move.second.first] << y_axis[pre_move.move.second.second] << "\n";

  if(depth==0) {
    if(isPlayer) { //maximize
      value = -1e8;
      for(auto it: state->legal_actions) {
        if((int)(board.board[state->player][it.first.first][it.first.second]) == 0) continue;
        if((int)(board.board[state->player][it.second.first][it.second.second]) != 0) continue;
        if(it.first.first==it.second.first && it.first.second==it.second.second) continue;

        log << "Player0 Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
                      << x_axis[it.second.first] << y_axis[it.second.second] << "\n";


        State* next_state = state->next_state(it);
        if(next_state->evaluate() > value) {
          pre_move = Movement(it, next_state->evaluate());
          value = pre_move.score;
        }
      }
    }

    log << "Rtn Premove(" << depth << "): " << x_axis[pre_move.move.first.first] << y_axis[pre_move.move.first.second] << " -> " 
                        << x_axis[pre_move.move.second.first] << y_axis[pre_move.move.second.second] << "\n";
   
    return pre_move;  
  } 

  else {
    if(isPlayer) { //maximize
      value = -1e8;
      actions = state->legal_actions;
      for(auto i=actions.begin(); i!=actions.end(); i++) {
        Move it = *i;

        log << "Player Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
                        << x_axis[it.second.first] << y_axis[it.second.second] << "\n";

        if((int)(board.board[state->player][it.first.first][it.first.second]) == 0) continue;
        if((int)(board.board[state->player][it.second.first][it.second.second]) != 0) continue;
        if(it.first.first==it.second.first && it.first.second==it.second.second) continue;

        State* next_state = state->next_state(it);
        Movement tmp =  get_minimax(next_state, depth-1, false);
        if(tmp.score > value) {
          pre_move = tmp;
          log << "Pre Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
                        << x_axis[it.second.first] << y_axis[it.second.second] << "\n";
        }
      }
    } else { //minimize
      value = 1e8;
      actions = state->legal_actions;
      for(auto it: state->legal_actions) {
        if(!valid_move(it)) continue;

        log << "Opponent Move: " << x_axis[it.first.first] << y_axis[it.first.second] << " -> " 
                        << x_axis[it.second.first] << y_axis[it.second.second] << "\n";

        if((int)(board.board[state->player][it.first.first][it.first.second]) == 0) continue;
        if((int)(board.board[state->player][it.second.first][it.second.second]) != 0) continue;
        if(it.first.first==it.second.first && it.first.second==it.second.second) continue;

        State* next_state = state->next_state(it);
        Movement tmp =  get_minimax(next_state, depth-1, true);
        if(tmp.score < value) {
          pre_move = tmp;
        }
      }
    }

    log << "Rtn Premove(" << depth << "): " << x_axis[pre_move.move.first.first] << y_axis[pre_move.move.first.second] << " -> " 
                        << x_axis[pre_move.move.second.first] << y_axis[pre_move.move.second.second] << "\n";
    log.close();
    return pre_move;
  } 
}