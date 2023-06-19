#include <iostream>
#include <fstream>

#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/minimax.hpp"


State* root;

/**
 * @brief Read the board from the file
 * 
 * @param fin 
 */
void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        // std::cout << c << " ";
        board.board[pl][i][j] = c;
      }
      // std::cout << std::endl;
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}


/**
 * @brief randomly choose a move and then write it into output file
 * 
 * @param fout 
 */
void write_valid_spot(std::ofstream& fout) { 
  // Keep updating the output until getting killed.
  while(true) {
    // Choose a minimax spot.
    Minimax minimax;
    Movement movement;
    int depth = 0;
    while (true){
        movement = minimax.get_minimax(root, depth, true);
        fout << movement.move.first.first << " " << movement.move.first.second << " "\
          << movement.move.second.first << " " << movement.move.second.second << std::endl;
        depth += 1;
        if(depth>2) break;
    }
    
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
    break;
  }
}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
