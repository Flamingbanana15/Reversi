#include "MonteCarlo.h"

playerMove monteCarloMove(GameBoard* rootGame, int playerTurn, int depth) {
	MonteCarloNode *rootNode = (new MonteCarloNode(rootGame, playerTurn));
	if (rootNode->legalMoves.empty()) {
		return playerMove{ -1,-1,0 }; //No move
	}
	//Iterative Deepening
	for (int i = 0; i < depth; i++) {
		MonteCarloNode* tempNode = rootNode;
		while (tempNode->legalMoves.empty() && !tempNode->childNodes.empty())
		{
			tempNode = tempNode->findBestChildNode();
		}
		if (!tempNode->legalMoves.empty()) {
			if (tempNode->expandToNextChild()) {
				tempNode = tempNode->childNodes.back();
			}
		}
		int won = tempNode->simulateMoves();
		tempNode->backpropagate(won);
	}
	int max = 0;
	int index = 0;
	for (int i = 0; i < rootNode->childNodes.size(); i++) {
		int score = rootNode->childNodes[i]->nodeScore / rootNode->childNodes[i]->nodesViewed;
		if (score > max) {
			max = score;
			index = i;
		}
	}
	return rootNode->childNodes[index]->move;
}
