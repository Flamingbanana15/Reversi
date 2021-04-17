#include "MonteCarloNode.h"

MonteCarloNode::MonteCarloNode(GameBoard* start, int playerTurn, MonteCarloNode* parent = NULL, playerMove moved = playerMove{ -1,-1,0 }) {
	currentBoard = start;
	player = playerTurn;
	legalMoves = *(new std::vector<playerMove>);
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (start->validateMove(row, col, player)) {
				legalMoves.push_back(playerMove{row, col, player});
			}
		}
	}
	move = moved;
	parentNode = parentNode;
	childNodes = *(new std::vector<MonteCarloNode*>);
	nodesViewed = 0;
	nodeScore = 0;
}

MonteCarloNode* MonteCarloNode::getMonteCarloNodeChild(MonteCarloNode* parent, playerMove move, int playerTurn) {
	parent->currentBoard->makeMove(move.row, move.col, move.player);
	return (new MonteCarloNode(parent->currentBoard, playerTurn, parent, move));
}

bool MonteCarloNode::expandToNextChild() {
	if (childNodes.size() < legalMoves.size()) {
		childNodes.push_back((getMonteCarloNodeChild(this, legalMoves[childNodes.size()], -player)));
		return true;
	}
	return false;
}

MonteCarloNode* MonteCarloNode::getLastChildNode() {
	return childNodes.back();
}

bool MonteCarloNode::getGameState() {
	return currentBoard->fullGame();
}

void MonteCarloNode::stepBack(int score) {
	nodesViewed++;
	nodeScore += score;
	if (parentNode != NULL) {
		parentNode->stepBack(score);
	}
}

double MonteCarloNode::findAverage() {
	return (double)nodeScore / (double)nodesViewed;
}

MonteCarloNode* MonteCarloNode::findBestChildNode() {
	int index = 0;
	double max = childNodes[0]->findAverage();
	for (int i = 0; i < childNodes.size(); i++) {
		double next = childNodes[i]->findAverage();
		if (next > max) {
			index = i;
			max = next;
		}
	}
	return childNodes[index];
}