#include "MonteCarloNode.h"

MonteCarloNode::MonteCarloNode(GameBoard* start, int player) {
	currentBoard = start;
	maximizingPlayer = player;
	legalMoves = start->generateMoves();
	memset(&move, 0, sizeof(move));
	parentNode = NULL;
	nodesViewed = 0;
	nodeScore = 0;
}

MonteCarloNode::MonteCarloNode(MonteCarloNode* parent, playerMove moved) {
	currentBoard = new GameBoard(parent->currentBoard);
	currentBoard->makeMove(moved.row, moved.col, moved.player);
	maximizingPlayer = parent->maximizingPlayer;
	legalMoves = currentBoard->generateMoves();
	move = moved;
	parentNode = parent;
	nodesViewed = 0;
	nodeScore = 0;
}

MonteCarloNode::~MonteCarloNode() {
	if (parentNode) {
		delete currentBoard;
	}
	for (MonteCarloNode *it : childNodes) {
		delete it;
	}
}


bool MonteCarloNode::expandToNextChild() {
	if (legalMoves.empty()) {
		return false;
	}
	int random = rand() % legalMoves.size();
	childNodes.push_back(new MonteCarloNode(this, legalMoves[random]));
	legalMoves.erase(legalMoves.begin() + random);
	return true;
}

void MonteCarloNode::backpropagate(int score) {
	nodesViewed++;
	nodeScore += score;
	if (parentNode != NULL) {
		parentNode->backpropagate(score);
	}
}

MonteCarloNode* MonteCarloNode::findBestChildNode() {
	int currentPlayer = currentBoard->playerTurn;
	size_t index = 0;
	double max = 0;
	for(size_t i = 0; i < childNodes.size(); i++) {
		double UCB = (currentPlayer == maximizingPlayer) ? (childNodes[i]->nodeScore / childNodes[i]->nodesViewed) : ((childNodes[i]->nodesViewed -childNodes[i]->nodeScore) / childNodes[i]->nodesViewed);
		UCB += (sqrt(2*log(nodesViewed)/ childNodes[i]->nodesViewed));
		if (UCB > max) {
			max = UCB;
			index = i;
		}
	}
	return childNodes[index];
}

int MonteCarloNode::simulateMoves() {
	GameBoard tempBoard(currentBoard);
	while (true) {
		std::vector<playerMove> currentMoves = tempBoard.generateMoves();
		if (currentMoves.empty()) {
			tempBoard.playerTurn = -tempBoard.playerTurn;
		    currentMoves = tempBoard.generateMoves();
			if (currentMoves.empty()) {
				break;
			}
		}
		int randomIndex = rand() % currentMoves.size();
		tempBoard.makeMove(currentMoves[randomIndex].row, currentMoves[randomIndex].col, currentMoves[randomIndex].player);
	}
	return (tempBoard.scoreBoard(maximizingPlayer) > tempBoard.scoreBoard(-maximizingPlayer)) ? 1 : -1;
}

bool MonteCarloNode::isLeafNode() {
	return childNodes.empty() || currentBoard->fullGame();
}
