#pragma once
#include "Player.h"

struct State {
    Board board;
    Move move;
    bool AI_move;
    std::vector<State> children;

    int value;

    State(Board board, Move move, bool AI_move, std::vector<State> children) : board(board), move(move), AI_move(AI_move), children(children), value(0){}
};

class AIPlayer : public Player {
    Color color;
    Color opColor; // TODO - change
    std::vector<Move> jump_moves;
    int max_points;
    int max_depth;
public:
    AIPlayer(Color color, Color opColor);
    std::vector<State> getGameTreesFromMoves(Board board, std::vector<Move> moves, bool AI, bool jump, int depth);
    std::vector<State> getGameTree(Board board, bool AI, bool jump, int depth);
    void minimax(State& state, int depth);
    std::vector<Move> getJumpMoves(State s);
    Move getMove(Board &board)override;
    Move getChainMove(Board &board, std::vector<Move> jumps)override;
};