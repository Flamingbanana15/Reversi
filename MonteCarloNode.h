#pragma once

#include "Reversi Game.h"
#include <utility>
#include <vector>

struct playerMove
{
	int row;
	int col;
	int player;
};

class MonteCarloNode {
private:

	int maximizingPlayer;
	
	MonteCarloNode* parentNode;
	std::vector<MonteCarloNode*> childNodes;
	int nodeScore;
	int nodesViewed;
	
	double findAverage();

public:
	playerMove move;
	GameBoard* currentBoard;
	std::vector<playerMove> legalMoves;

	MonteCarloNode(GameBoard*, int, MonteCarloNode* = NULL, playerMove = playerMove{ -1,-1,0 });
	MonteCarloNode* getMonteCarloNodeChild(MonteCarloNode* parent, playerMove);
	bool expandToNextChild();
	MonteCarloNode* getLastChildNode();
	bool getGameState();
	void stepBack(int);
	MonteCarloNode* findBestChildNode();
};