#pragma once
#include "Player.h"

struct State {
    Board board;
    Move move;
    bool AI_move;
    std::vector<State> children;

    int value;

    State(Board board, Move move, bool AI_move, std::vector<State> children) : board(board), move(move), AI_move(AI_move), children(children), value(0){}

    State(const State& other) : board(other.board), move(other.move), AI_move(other.AI_move), children(other.children), value(other.value) {}

    State(int value) : value(value) {}
};

class AIPlayer : public Player {
    Color color;
    Color opColor; // TODO - change
    std::vector<Move> jump_moves;
    int max_points;
    int max_depth;
public:
    AIPlayer(Color color, Color opColor);
    std::vector<State> getGameTreesFromMoves(Board board, std::vector<Move> moves, bool AI, int depth);
    std::vector<State> getGameTree(Board board, bool AI, int depth);
    std::vector<State> getGameTreeJump(Board board, bool AI, Position pos, int depth);
    void minimax(State& state, int depth);
    std::vector<Move> getJumpMoves(const State& s);
    Move getMove(Board &board)override;
    Move getChainMove(Board &board, std::vector<Move> jumps)override;
};
