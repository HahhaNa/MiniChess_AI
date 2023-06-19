#include <cstdlib>
#include <fstream>
#include "../state/state.hpp"
#include "./minimax.hpp"

/* 
// Returns the optimal value a maximizer can obtain.
// depth is current depth in game tree.
// nodeIndex is index of current node in scores[].
// isPlayer is true if current move is
// of maximizer, else false
// scores[] stores leaves of Game tree.
// h is maximum height of Game tree
*/


/**
 * @brief Return max score move
 * 
 * @param state Now state
 * @param depth ?
 * @return Move 
 */
Move minimax(int depth, int nodeIndex, bool isPlayer,
            std::vector<Move> legal_actions, int h)
{
    // Terminating condition. i.e
    // leaf node is reached
    if (depth == h)
        return legal_actions.at(nodeIndex);
 
    //  If current move is maximizer,
    // find the maximum attainable
    // value
    if (isPlayer)
       return max(minimax(depth+1, nodeIndex*2, false, legal_actions, h),
            minimax(depth+1, nodeIndex*2 + 1, false, legal_actions, h));
 
    // Else (If current move is Minimizer), find the minimum
    // attainable value
    else
        return min(minimax(depth+1, nodeIndex*2, true, legal_actions, h),
            minimax(depth+1, nodeIndex*2 + 1, true, legal_actions, h));
}