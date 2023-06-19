#include <cstdlib>
#include <fstream>
#include <iostream>

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


Board next_board(State* state, Move move){
  Board next = state->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[state->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-state->player][to.first][to.second]){
    next.board[1-state->player][to.first][to.second] = 0;
  }
  
  next.board[state->player][from.first][from.second] = 0;
  next.board[state->player][to.first][to.second] = moved; 
  
  return next;
}

int evaluate_board(int player, Board board) {
  static const int material_table[7] = {0, 2, 6, 7, 8, 20, 100};
  int score = 0;
  std::cout << "Player: " << player << std::endl;
  for(int i=0; i<BOARD_H; i++) {
    for(int j=0; j<BOARD_W; j++) {
      int t = board.board[player][i][j] ;
      // std::cout << "type: " << t << std::endl;
      score += material_table[t];
    }
  }
  std::cout << "Final Score: " << score << std::endl;
  return score;

}



/**
 * @brief Return max score move
 * 
 * @param state Now state
 * @param depth maybe 3-4?
 * @return Movement 
 */

Movement pre_movement;

Movement Minimax::get_minimax(State *state, int depth, bool isPlayer){
  static Movement movement;
  std::ofstream log("gamelog.txt");
  if(!state->legal_actions.size())
    state->get_legal_actions();

  if(state->legal_actions.empty() ) {
    return pre_movement;
  }
  if(!isPlayer) {
    static Movement min;
    min.score = 1e8;
    for(auto it: state->legal_actions) {
      std::cout << "from: " << it.first.first << " " << it.first.second << std::endl;
      std::cout << "to: " << it.second.first << " " << it.second.second << std::endl;
      Board board = next_board(state, it);
      int tmp_score = evaluate_board(state->player, board);
      Movement tmp(it, tmp_score);
      std::cout << "tmp score: " << tmp.score << std::endl; 
      pre_movement = tmp;
      State* next_state = new State(board, 1-state->player);
      if(depth==0) min = tmp.score < min.score? tmp:min;
      else Movement min = (get_minimax(next_state, depth-1, true).score < min.score? get_minimax(next_state, depth-1, true) :min);
      std::cout << "min score: " << min.score << std::endl; 
    }
    if(depth == 0) return min;
  }
  if(isPlayer) {
    static Movement max;
    max.score = -1e8;
    for(auto it: state->legal_actions) {
      std::cout << "from: " << it.first.first << " " << it.first.second << std::endl;
      std::cout << "to: " << it.second.first << " " << it.second.second << std::endl;
      Board board = next_board(state, it);
      int tmp_score = evaluate_board(state->player, board);
      Movement tmp(it, tmp_score);
      std::cout << "tmp score: " << tmp.score << std::endl; 
      pre_movement = tmp;
      State* next_state = new State(board, 1-state->player);
      if(depth==0) max = tmp.score < max.score? tmp:max;
      else Movement min = (get_minimax(next_state, depth-1, true).score < min.score? get_minimax(next_state, depth-1, true) :min);
      std::cout << "max score: " << max.score << std::endl; 
    }
    if(depth == 0) return max;
  } 
  log.close();
  return movement;
}