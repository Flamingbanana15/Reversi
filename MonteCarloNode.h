#pragma once

#include "Reversi Game.h"
#include <utility>
#include <vector>

class MonteCarloNode {
public:

	int maximizingPlayer;
	
	MonteCarloNode* parentNode;
	std::vector<MonteCarloNode*> childNodes;
	int nodeScore;
	int nodesViewed;
	playerMove move;
	GameBoard* currentBoard;
	std::vector<playerMove> legalMoves;	

public :
	MonteCarloNode(GameBoard*, int);
	MonteCarloNode(MonteCarloNode*, playerMove);
	~MonteCarloNode();

	bool expandToNextChild();
	void backpropagate(int);
	MonteCarloNode* findBestChildNode();
	bool isLeafNode();
	int simulateMoves();
};