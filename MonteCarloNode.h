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

	int player;
	GameBoard* currentBoard;
	MonteCarloNode* parentNode;
	std::vector<MonteCarloNode*> childNodes;
	int nodeScore;
	std::vector<playerMove> legalMoves;
	int nodesViewed;
	
	double findAverage();

public:
	playerMove move;

	MonteCarloNode(GameBoard*, int, MonteCarloNode*, playerMove);
	MonteCarloNode* getMonteCarloNodeChild(MonteCarloNode* parent, playerMove, int);
	bool expandToNextChild();
	MonteCarloNode* getLastChildNode();
	bool getGameState();
	void stepBack(int);
	MonteCarloNode* findBestChildNode();
};