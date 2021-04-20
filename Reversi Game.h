#pragma once
#include <iostream>
#include <sstream>
#include <time.h>
#include <utility>
#include <vector>

struct playerMove
{
	int row;
	int col;
	int player;
};


class GameBoard {
public:
	int playerTurn;
	int board[8][8];
	const int compyAI[8][8] = { {20,  -5,  8,  8,  8,  8,  -5, 20},
								{-5, -10, -4, -4, -4, -4, -10, -5},
								{ 8,  -4,  2,  0,  0,  2,  -4,  8},
								{ 8,  -4,  0,  1,  1,  0,  -4,  8},
								{ 8,  -4,  0,  1,  1,  0,  -4,  8},
								{ 8,  -4,  2,  0,  0,  2,  -4,  8},
								{-5, -10, -4, -4, -4, -4, -10, -5},
								{20,  -5,  8,  8,  8,  8,  -5, 20} };

	GameBoard();
	GameBoard(const GameBoard*);
	void printBoard(std::ostream& out = std::cout);
	bool makeMove(int, int, int);
	bool checkPath(int, int, int, int, int, bool);
	bool validateMove(int, int, int);
	bool canMove(int);
	void showMoves(int);
	bool fullGame();
	void clearBoard();
	int scoreBoard(int);
	void copyBoard(const GameBoard*);
	int evaluateBoard(int);
	//int stableBoard(int);
	int stablePieces(int, int, int);
	bool makeMinimaxMove(GameBoard*, int);
	bool makeMonteCarloMove(GameBoard*, int);
	int countNeighbors(int, int);
	std::vector<playerMove> generateMoves();
};