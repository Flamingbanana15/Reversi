#include "MonteCarloNode.h"

MonteCarloNode* searchTree(MonteCarloNode*);

playerMove monteCarloMove(GameBoard* rootGame, int playerTurn, int depth) {
	MonteCarloNode *rootNode = (new MonteCarloNode(rootGame, playerTurn));
	if (rootNode->legalMoves.empty()) {
		return playerMove{ -1,-1,0 }; //No move
	}
	return playerMove{ -1,-1,0 };
	for (int i = 0; i < depth; i++) {
		MonteCarloNode* tempNode = searchTree(rootNode);
		if (tempNode != NULL) {

		}
	}
	return playerMove{ -1,-1,0 };
}

MonteCarloNode* searchTree(MonteCarloNode* node) {
	if (node->expandToNextChild()) {
		return node->getLastChildNode();
	}
	else if (node->currentBoard->fullGame()) {
		return node;
	}

	return searchTree(node->findBestChildNode());
}

int expandTree(MonteCarloNode* node) {
	std::unique_ptr<GameBoard> tempBoard(new GameBoard());
	tempBoard->copyBoard(node->currentBoard);
	while (!tempBoard->fullGame()) {

	}
	return 0;
}