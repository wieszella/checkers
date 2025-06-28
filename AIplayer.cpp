#include "AIPlayer.h"
#include "MoveComputer.h"
// #include <climits>
// #include <algorithm>

// int getPathValue(Board &board, Color player){
    
// }

// std::vector<Move> AIPlayer::miniMax(tree decisionTree, int depth, bool ourTurn, int alpha, int beta){
//     if(depth == 0)
//         return numberofcolor; //return the amount of 

//     if(ourTurn){
//         int maxVal = INT_MIN;
//         for(child:decisionTree){
//             int newVal = miniMax(child, depth-1, false, beta, alpha);
//             maxVal = std::max(maxVal, newVal);
//             alpha = std::max(alpha, newVal);
//             if(beta <= alpha)
//                 break;
//         }
//         return maxVal;
//     }
//     else{
//         int minVal = INT_MAX;
//         for(child:decisionTree){
//             int newVal = miniMax(child, depth-1, true, alpha, beta);
//             minVal = std::min(minVal, newVal);
//             beta = std::min(beta, newVal);
//             if(beta <= alpha)
//                 break;
//         }
//         return minVal;
//     }
// }


// std::vector<Move> minimaxStart(Board board, Color c, bool maximizing)
// {
//     int alpha = -1000, beta = 1000;
//     std::vector<std::vector<Move>> possible_moves;
//     board.genAllMoves(s, possible_moves);
//     std::vector<double> heuristics;
//     if (possible_moves.empty()) {
//         return {-1};
//     }
//     Board tempBoard;
//     int num_moves = possible_moves.size();
//     for (int i = 0; i < num_moves; i++) {
//         tempBoard = *board.clone();
//         Status status = tempBoard.makeMove(possible_moves[i], s);
//         // if (status != COMPLETED && status != GAME_OVER) {
//         //     continue;
//         // }
//         heuristics.push_back(minimax(tempBoard, switchSide(s), !maximizing, depth - 1, alpha, beta));
//     }
//     double max_heuristics = -1000;
//     int num_heuristics = heuristics.size();
//     for (int i = num_heuristics - 1; i >= 0; i--) {
//         if (heuristics[i] >= max_heuristics) {
//             max_heuristics = heuristics[i];
//         }
//     }
//     for (int i = 0; i < num_heuristics; i++) {
//         // cout << "number of heuristics: " << num_heuristics << endl;
//         // cout << "i: " << i << endl;
//         if (heuristics[i] < max_heuristics) {
//             heuristics.erase(heuristics.begin() + i);
//             possible_moves.erase(possible_moves.begin() + i);
//             i--;
//             num_heuristics--;
//         }
//     }
//     num_moves = possible_moves.size();
//     // cout << "Number of moves: " << num_moves << endl;
//     Move final_move = possible_moves[rand() % num_moves];
//     // cout << "FINAL MOVE: " << final_move.start.row << " " << final_move.start.col << " to " << final_move.end.row << " " << final_move.end.col << "\n";
//     return final_move;
// }

// double minimaxVal(Board board, Color c, bool maximizing, int depth, int alpha, int beta) {
//     if (depth == 0) {
//         return getHeuristic(board);
//     }
//     vector<Move> possible_moves;
//     board.genAllMoves(c, possible_moves);
//     int n = possible_moves.size();
//     int initial = 0;
//     Board tempBoard;
//     if (maximizing) {
//         for (int i = 0; i < n; i++) {
//             tempBoard = *board.clone();
//             Status status = tempBoard.makeMove(possible_moves[i], s);
//             if (status != COMPLETED && status != GAME_OVER) {
//                 continue;
//             }
//             int result = minimax(tempBoard, switchSide(c), !maximizing, depth - 1, alpha, beta);
//             initial = max(result, initial);
//             alpha = max(initial, alpha);
//             if (alpha >= beta) {
//                 break;
//             }
//         }
//     } else {
//         initial = 1000;
//         for (int i = 0; i < n; i++) {
//             tempBoard = *board.clone();
//             Status status = tempBoard.makeMove(possible_moves[i], s);
//             if (status != COMPLETED && status != GAME_OVER) {
//                 continue;
//             }
//             int result = minimax(tempBoard, switchSide(s), !maximizing, depth - 1, alpha, beta);
//             initial = std::min(result, initial);
//             beta = std::min(beta, initial);
//             if (alpha >= beta) {
//                 break;
//             }
//         }
//     }
//     return initial;
// }

// double getHeuristic(Board board) {
//     double king_weight = 1.5;
//     if (getSide() == BLACK_SIDE) {
//         return (king_weight * board.getNumBlackKings() + board.getNumBlack()) - (king_weight * board.getNumWhiteKings() + board.getNumWhite());
//     }
//     return (king_weight * board.getNumWhiteKings() + board.getNumWhite()) - (king_weight * board.getNumBlackKings() + board.getNumBlack());
// }

AIPlayer::AIPlayer(Color color, Color opColor) : color(color), opColor(opColor), max_depth(20), max_points(10){}


std::vector<State> AIPlayer::getGameTreesFromMoves(Board board, std::vector<Move> moves, bool AI, bool jump) {
    std::vector<State> states;

    for (Move m : moves) {
        Board b = Board(board);
        b.movePiece(m.from, m.to); 

        if (MoveComputer::isEatMove(b, m, b.getPiece(m.from)->getColor())) {
            State jumping_board = State(b, m, AI, getGameTree(b, AI, true));
            State no_jumping_board = State({b, m, AI, getGameTree(b, ~AI, false)});
            states.push_back(jumping_board);
            states.push_back(no_jumping_board);
        } else {
            State next_player_board = State(b, m, AI, getGameTree(b, ~AI, false));
            states.push_back(next_player_board);
        }
    }

    return states;
}

std::vector<State> AIPlayer::getGameTree(Board board, bool AI, bool jump) {
    Color c = AI ? color : opColor;
    std::vector<Move> all_moves = MoveComputer::getAllLegalMoves(board, c);// all possible legal moves

    // if there are no available moves, but the player is currently jumping, switch to next player
    if (all_moves.empty() && jump) return getGameTree(board, ~AI, false);

    return getGameTreesFromMoves(board, all_moves, AI, jump);
}

void AIPlayer::minimax(State& state, int depth) {
    if (depth >= max_depth) {
        state.value = 0;
    }

    if (state.children.empty()) {
        state.value = (state.AI_move) ? -max_points : max_points;
        return;
    }

    int val_found;
    if (state.AI_move) {
        val_found = -max_points;
        for (State& child : state.children) {
            minimax(child, depth+1);
            int val = child.value;
            if (val > val_found) val_found = val;
        }
    } else {
        val_found = max_points;
        for (State& child : state.children) {
            minimax(child, depth+1);
            int val = child.value;
            if (val < val_found) val_found = val;
        }
    }

    state.value = val_found;
}

std::vector<Move> AIPlayer::getJumpMoves(State s) {
    if (s.children.empty()) return {};

    State best = s.children[0];

    for (State& child : s.children) {
        if (child.value > best.value || (child.value == best.value && child.AI_move)) {
            best = child;
        }
    }

    if (best.AI_move) {
        std::vector<Move> jumps = getJumpMoves(best);
        jumps.push_back(best.move);
        return jumps;
    } else return {};
}

Move AIPlayer::getMove(Board &board) {
    std::vector<State> all_moves = getGameTree(board, true, false);

    State best = all_moves[0];
    for (State& state : all_moves) {
        minimax(state, 0);
        if (state.value > best.value) best = state;
    }

    jump_moves = getJumpMoves(best);

    return best.move;
}

Move AIPlayer::getChainMove(Board &board, std::vector<Move> jumps) {
    Move jump = jump_moves.back();
    return jump;
}

