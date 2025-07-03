
#pragma once
#include "IPlayer.h"
#include "MoveExecutor.h"
#include "MoveGenerator.h"
#include <optional>

struct State {
    Board board;
    Move move;
    bool AI_move;
    std::vector<State> children;

    int value; //the value is given during the minMax

    State(Board board, Move move, bool AI_move, std::vector<State> children) : board(board), move(move), AI_move(AI_move), children(children), value(0){}
    State(const State& other) : board(other.board), move(other.move), AI_move(other.AI_move), children(other.children), value(other.value) {} //copy constructor
    State(int value) : value(value) {} //constructor for leaf
};

class AIPlayer : public Player {
    Color color;
    Color opColor; 
    std::vector<Move> jump_moves;
    const int MAX_POINTS;
    const int MAX_DEPTH;

    std::unique_ptr<MoveGenerator> moveGenerator;
    std::unique_ptr<MoveExecutor> moveExecutor;

    int evaluate(const Board& board, bool isAI)const;
    int getMax(std::vector<State> children)const;
    int getMin(std::vector<State> children)const;
    std::vector<State> buildGameTree(Board board, bool isAIPlayerTurn, int depth, std::optional<Position> forceJumpPos = std::nullopt);
    void minimax(State& state, int depth);

public:
    AIPlayer(Color color);

    std::vector<State> getGameTreesFromMoves(Board board, std::vector<Move> moves, bool AI, int depth);
    std::vector<State> getGameTreeJump(Board board, bool AI, Position pos, int depth);
    std::vector<State> getGameTree(Board board, bool AI, int depth);
    
    std::vector<Move> getJumpMoves(const State& s);
    Move getMove(Board &board)override;
    Move getChainMove(Board &board, std::vector<Move> jumps)override;
};
