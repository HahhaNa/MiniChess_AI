# NTHU Introduction to Programming 2 - MiniChess AI Project
## Introduction
- Design and implement an AI which can play MiniChess
- Read the current board and output the next move
- Determine the next move with a tree search algorithm

## What is MiniChess?
- Minichess is a board game is based on chess but has simplified rule.
- We have 2 players: white and black (white plays first)
- If a player makes any illegal move, they would lose.
- If 2 players have almost the same ability, the game will stop when the game costs over 50 step(25 turn). And count the piece value for deciding which player is winner. 

## Implementation
### 1. State Value Function
- This program should decide which move is better.
- A function to evaluate the score of the board, so we can pick the move which leads to the board with the highest board.
  - State: the board
  - Value: how "good" the board is
  - Function: given a board, output the value
### 2. Minimax Algorithm 
- Look forward to more steps and simulate how the opponent thinks to make the best choice with the least risk.
- I used the Minimax algorithm and based on the player-opponent interaction.
  - Player tries his best to win (pick the highest score)
  - Opponent tries its best to defeat the player( give the player the worst score) 
```pseudo
function minimax(node, depth, maximizingPlayer)
    if depth = 0 or node is a terminal node
        return the heuristic value of node
    if maximizingPlayer
        bestValue := -∞
        for each child of node
            val := minimax(child, depth - 1, FALSE))
            bestValue := max(bestValue, val);
        return bestValue
    else
        bestValue := +∞
        for each child of node
            val := minimax(child, depth - 1, TRUE))
            bestValue := min(bestValue, val);
        return bestValue
```
### 3. Alpha-Beta Pruning
- Since the size of search tree may drstically increase with the increase in search depth, I use Alphha-Beta Pruning to optimize and speedup the search process.
- The Alpha-Beta Pruning is the improved versioin of the Minimax method which eliminates some unnecessary branches.
  - Alpha: the maximum score that the player is assured of in the current search process
  - Beta: the minimum score that the opponent is assured of in the current search process
- Alpha-Beta Pruning detail:
  1. If alpha>=beta on a player node, we can stop to search on this branch.
  2. In this situation, the player will return a value >= beta on this branch.
  3. However, the opponent already has a better choice(beta). So the opponent will not pick this branch.
  4. Prune this branch since it will not affect the result
  5. Also stop to search if beta<=alpha on an opponent node.
  6.  psuedo code:
     ``` pseudo 
    function alphabeta(node, depth, α, β, maximizingPlayer) is
      if depth == 0 or node is terminal then
          return the heuristic value of node
      if maximizingPlayer then
          value := −∞
          for each child of node do
              value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
              α := max(α, value)
              if value ≥ β then
                  break (* β cutoff *)
          return value
      else
          value := +∞
          for each child of node do
              value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
              β := min(β, value)
              if value ≤ α then
                  break (* α cutoff *)
          return value
     ```

### 4. What I learned?
- Stepping into the field of AI-related projects for the first time was a journey filled with novelty and challenges for me. Throughout this process, I came to appreciate deeply the importance of algorithms required for developing board games. Through continuous research and learning, I gradually understood the workings of algorithms such as Minimax and Alpha-Beta Pruning. Through practical implementation experiences, I gained a profound understanding of the practical application and optimization methods of these techniques.
- My first encounter with the use of Git version control system left a profound impression on me. This tool not only allowed me to effectively manage project versions and history but, more importantly, it provided an efficient and unified platform for team collaboration. Through Git, I learned how to branch, merge, and resolve conflicts, skills that are crucial in team collaboration and further boosted my confidence to dive into project development.
- This implementation not only deepened my understanding of AI-related technologies but also nurtured my problem-solving abilities and teamwork skills. Such valuable experiences will lay a solid foundation for my future learning and professional career.
