#include "AIPlayer.h"
#include "MoveGenerator.h"
#include "MoveExecutor.h"
#include <iostream>
#include <optional>
#include <algorithm>
#include <bits/stdc++.h>

AIPlayer::AIPlayer(Color color) : color(color), opColor(color == Color::RED ? Color::BLACK : Color::RED), MAX_DEPTH(5), MAX_POINTS(100){}

void print_tree(const State& s, int indent) { //for debug purposes
    std::cout << std::string(indent, ' ') << s.AI_move << s.value << "(" << s.move.from.row << "," << s.move.from.col << ") -> (" << s.move.to.row << "," << s.move.to.col << ")\n";
    for (const State& c : s.children) print_tree(c, indent * 2);
}


/////get game tree functions
std::vector<State> AIPlayer::buildGameTree(Board board, bool isAIPlayerTurn, int depth, std::optional<Position> chainFromPos) {
    // Base case: if depth limit reached, return empty states
    if (depth >= MAX_DEPTH) return std::vector<State>();

    Color currentPlayerColor = isAIPlayerTurn ? color : opColor;
    std::vector<Move> legalMoves;

    //Get legal moves
    if (chainFromPos.has_value()) {
        legalMoves = moveGenerator->getLegalMovesForPos(board, chainFromPos.value(), true);
        legalMoves = moveGenerator->getChainJumps(board, legalMoves, currentPlayerColor);

        // If no more chain jumps from this position, it's the other player's turn
        if (legalMoves.empty()) {
            return buildGameTree(board, !isAIPlayerTurn, depth + 1);
        }
    } else {
        legalMoves = moveGenerator->getAllLegalMoves(board, currentPlayerColor);
        if (legalMoves.empty()) {
            return {State(isAIPlayerTurn ? -MAX_POINTS : MAX_POINTS)};
        }
    }

    //gat gameTree according to legal moves
    std::vector<State> states;
    for (Move m : legalMoves) {
        Board nextBoard = Board(board); // Create a copy of the board for this move
        bool isEat = moveGenerator->isEatMove(board, m, currentPlayerColor);
        moveExecutor->apply(nextBoard, m);

        // Check if the applied move was an eat move that might lead to further jumps
        if (isEat) {
            // Case 1: The current piece might have more jumps (chaining) - the AI player's turn continues.
            State jumpingBoardState = State(nextBoard, m, isAIPlayerTurn, buildGameTree(nextBoard, isAIPlayerTurn, depth + 1, m.to));
            states.push_back(jumpingBoardState);

            // Case 2: The current player chooses NOT to make further jumps, or no more jumps are available.
            State noJumpingBoardState = State(nextBoard, m, isAIPlayerTurn, buildGameTree(nextBoard, !isAIPlayerTurn, depth + 1));
            states.push_back(noJumpingBoardState);
        } else {
            // Normal move or no further jumps possible/required after a jump - the turn switches to the other player.
            State nextPlayerBoardState = State(nextBoard, m, isAIPlayerTurn, buildGameTree(nextBoard, !isAIPlayerTurn, depth + 1));
            states.push_back(nextPlayerBoardState);
        }
    }
    return states;
}

//////////minimax
void AIPlayer::minimax(State& state, int depth){
    if (depth >= MAX_DEPTH - 1 || state.children.empty()) {
        state.value = evaluate(state.board, state.AI_move);
        return;
    }

    int maxAI = - MAX_POINTS;
    int minP = MAX_POINTS;

    for(State& child: state.children){
        if(minP <= maxAI){ 
            //implemented pruning- if at any point minP <= maxAI you can stop computing for the cases that 
            if(state.AI_move && !child.AI_move) continue;
            if(!state.AI_move && child.AI_move) continue;
        }
        minimax(child, depth+1);
        
        if(child.AI_move) maxAI = std::max(child.value, maxAI);
        else minP = std::min(child.value, minP);
    }

    if(state.AI_move) state.value = std::max(maxAI, minP);
    else state.value = std::min(maxAI, minP);
}

int AIPlayer::evaluate(const Board& board, bool isAI)const
{
    if(!moveGenerator ->hasLegalMoves(board, color)) return -MAX_POINTS;
    if(!moveGenerator ->hasLegalMoves(board, opColor)) return MAX_POINTS;

    double king_weight = 2;
    int value = (king_weight * board.countPieceColor(color, PieceType::KING) + board.countPieceColor(color, PieceType::SOLDIER)) - 
        (king_weight * board.countPieceColor(opColor, PieceType::KING) + board.countPieceColor(opColor, PieceType::SOLDIER));
    return value;
}

/////ai player functions
std::vector<Move> AIPlayer::getJumpMoves(const State& s) {
    if (s.children.empty()) return {};

    State best = s.children[0];

    for (const State& child : s.children) {
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
    std::vector<State> all_moves = buildGameTree(board, true, 0);

    int best = 0;
    for (int i=0; i<all_moves.size(); i++) {
        minimax(all_moves[i], 0);
        if (all_moves[i].value > all_moves[best].value) best = i;
    }

    //update possible jumps
    jump_moves = getJumpMoves(all_moves[best]);

    return all_moves[best].move;
}

Move AIPlayer::getChainMove(Board &board, std::vector<Move> jumps) {
    if (jump_moves.size() == 0) return Move();
    return jump_moves.back();
}
