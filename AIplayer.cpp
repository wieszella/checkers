#include "AIPlayer.h"
#include "MoveComputer.h"

AIPlayer::AIPlayer(Color color, Color opColor) : color(color), opColor(opColor), max_depth(7), max_points(10){}


std::vector<State> AIPlayer::getGameTreesFromMoves(Board board, std::vector<Move> moves, bool AI, bool jump, int depth) {
    if(depth >= max_depth)
    return {};
    std::vector<State> states;

    for (Move m : moves) {
        Board b = Board(board);
        b.movePiece(m.from, m.to); 

        if (MoveComputer::isEatMove(b, m, AI ? color : opColor)) {
            State jumping_board = State(b, m, AI, getGameTree(b, AI, true, depth + 1));
            State no_jumping_board = State({b, m, AI, getGameTree(b, ~AI, false, depth + 1)});
            states.push_back(jumping_board);
            states.push_back(no_jumping_board);
        } else {
            State next_player_board = State(b, m, AI, getGameTree(b, ~AI, false, depth + 1));
            states.push_back(next_player_board);
        }
    }

    return states;
}

std::vector<State> AIPlayer::getGameTree(Board board, bool AI, bool jump, int depth) {
    if(max_depth <= depth)
    return {};
    Color c = AI ? color : opColor;
    std::vector<Move> all_moves = MoveComputer::getAllLegalMoves(board, c);// all possible legal moves

    // if there are no available moves, but the player is currently jumping, switch to next player
    if (all_moves.empty() && jump) return getGameTree(board, ~AI, false, depth + 1);

    return getGameTreesFromMoves(board, all_moves, AI, jump, depth + 1);
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
    std::vector<State> all_moves = getGameTree(board, true, false, 0);

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