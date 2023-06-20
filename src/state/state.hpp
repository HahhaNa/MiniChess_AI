#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <cstdlib>
#include <vector>
#include <set>
#include <utility>

#include "../config.hpp"


typedef std::pair<size_t, size_t> Point;
typedef std::pair<Point, Point> Move;
typedef struct Movement {
  Move move;
  int score = 0;
  Movement() :score(0) {};
  Movement(Move move, int score): move(move), score(score){};
} Movement;
class Board{
  public:
    char board[2][BOARD_H][BOARD_W] = {{
      //white
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},
    }, {
      //black
      {6, 5, 4, 3, 2},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }};
};

enum GameState {
  UNKNOWN = 0,
  WIN,
  DRAW,
  NONE
};


class State{
  public:
    //You may want to add more property for a state
    GameState game_state = UNKNOWN;
    Board board;
    int player = 0;
    std::vector<Move> legal_actions;

    /*// 將avl_actions 由score從小排到大
    struct cmp {
        bool operator ()(const Movement &a, const Movement &b) const{
            return  (a.score < b.score);
        }
    };
    std::set<Movement, cmp> avl_actions;*/
    Move pmove, nmove;
    bool legal_initialize = false;
      
    State(){};
    State(int player): player(player){};
    State(Board board): board(board){};
    State(Board board, int player): board(board), player(player){};
    
    int evaluate(int root_player);
    State* next_state(Move move);
    void get_legal_actions();
    std::string encode_output();
    std::string encode_state();
};

#endif