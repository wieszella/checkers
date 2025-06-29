#include "AIPlayer.h"
#include "MoveComputer.h"
#include <iostream>

AIPlayer::AIPlayer(Color color, Color opColor) : color(color), opColor(opColor), max_depth(5), max_points(10){}

void print_tree(const State& s, int indent) {
    std::cout << std::string(indent, ' ') << s.AI_move << s.value << "(" << s.move.from.row << "," << s.move.from.col << ") -> (" << s.move.to.row << "," << s.move.to.col << ")\n";
    for (const State& c : s.children) print_tree(c, indent+1);
}

void eat(Board& board, const Move &move){
    // Determine the step direction for x and y
    int stepX = ((move.from.row - move.to.row) > 0) ? -1 : 1;
    int stepY = ((move.from.col - move.to.col) > 0) ? -1 : 1;

    Position currentPoint = move.from;

    for (int i = 0; i < std::abs(move.from.row - move.to.row) - 1; i++) {
        currentPoint.row += stepX;
        currentPoint.col += stepY;
        board.removePiece(currentPoint);
    }
}

std::vector<State> AIPlayer::getGameTreesFromMoves(Board board, std::vector<Move> moves, bool AI, int depth) {
    if (depth >= max_depth) return std::vector<State>();

    std::vector<State> states;

    for (Move m : moves) {
        Board b = Board(board);
        b.movePiece(m.from, m.to); 

        if (MoveComputer::isEatMove(b, m, AI ? color : opColor)) {
            eat(b, m);
            State jumping_board = State(b, m, AI, getGameTreeJump(b, AI, m.to, depth+1));
            State no_jumping_board = State(b, m, AI, getGameTree(b, !AI, depth+1));
            states.push_back(jumping_board);
            states.push_back(no_jumping_board);
        } else {
            State next_player_board = State(b, m, AI, getGameTree(b, !AI, depth+1));
            states.push_back(next_player_board);
        }
    }

    return states;
}

std::vector<State> AIPlayer::getGameTreeJump(Board board, bool AI, Position pos, int depth) {
    if (depth >= max_depth) return std::vector<State>();

    Color c = AI ? color : opColor;
    std::vector<Move> all_moves = MoveComputer::getLegalMovesForPos(board, pos);// all possible legal moves
    all_moves = MoveComputer::getChainJumps(board, all_moves, c);

    if (all_moves.empty()) return getGameTree(board, !AI, depth+1);

    return getGameTreesFromMoves(board, all_moves, AI, depth);
}

std::vector<State> AIPlayer::getGameTree(Board board, bool AI, int depth) {
    if (depth >= max_depth) return std::vector<State>();

    Color c = AI ? color : opColor;
    std::vector<Move> all_moves = MoveComputer::getAllLegalMoves(board, c);// all possible legal moves

    if (all_moves.empty()) return {State(AI ? -max_points : max_points)};

    return getGameTreesFromMoves(board, all_moves, AI, depth);
}

void AIPlayer::minimax(State& state, int depth) {
    if (depth >= max_depth - 1) {
        state.value = 0;
        return;
    }

    if (state.value != 0) {
        //state.board.print();
        //std::cout << depth << " " << ((state.AI_move) ? "AI lose" : "Human lose") << std::endl;
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
    std::vector<State> all_moves = getGameTree(board, true, 0);
    //for (const State& s : all_moves) print_tree(s, 0);

    State best = all_moves[0];
    for (State& state : all_moves) {
        minimax(state, 0);
        if (state.value > best.value) best = state;
    }

    jump_moves = getJumpMoves(best);

    //print_tree(best, 0);

    std::cout << best.value << std::endl;

    return best.move;
}

Move AIPlayer::getChainMove(Board &board, std::vector<Move> jumps) {
    if (jumps.size() == 0) return Move();
    Move jump = jump_moves.back();
    return jump;
}

