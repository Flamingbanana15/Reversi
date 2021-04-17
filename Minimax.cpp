#include "Minimax.h"

int minValue(GameBoard* oldBoard, int player, int alpha, int beta, int depth, int maxDepth, time_t startingTime) {
	std::unique_ptr<GameBoard> tempBoard(new GameBoard());
	tempBoard->copyBoard(oldBoard);

	int bestValue = MAX_NUMBER;
	int tempValue;
	//Stops when gets to maxDepth or when game is over
	time_t now;
	time(&now);

	if (depth == maxDepth || difftime(now, startingTime) >= COMPUTING_TIME || !(oldBoard->canMove(-player))) {
		return oldBoard->evaluateBoard(player);
	}
	if (oldBoard->fullGame() || (!(oldBoard->canMove(player)) && !(oldBoard->canMove(-player)))) {
		int score = oldBoard->scoreBoard(player);
		int score2 = oldBoard->scoreBoard(-player);
		if (score == score2) {
			return 0;
		}
		else if (score > score2) {
			return MAX_NUMBER;
		}
		else {
			return -MAX_NUMBER;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (oldBoard->validateMove(i, j, -player)) {
				if (oldBoard->makeMove(i, j, -player)) {
					tempValue = maxValue(oldBoard, player, alpha, beta, depth++, maxDepth, startingTime);

					bestValue = std::min(bestValue, tempValue);

					//Alpha-beta pruning
					beta = std::min(bestValue, beta);

					if (beta <= alpha) {
						return bestValue;
					}

					//Reset board
					oldBoard->copyBoard(tempBoard.get());
				}
			}
		}
	}
	return bestValue;
}

int maxValue(GameBoard* oldBoard, int player, int alpha, int beta, int depth, int maxDepth, time_t startingTime) {
	std::unique_ptr<GameBoard> tempBoard(new GameBoard());
	tempBoard->copyBoard(oldBoard);

	int bestValue = -MAX_NUMBER;
	int tempValue;
	//Stops when gets to maxDepth or when game is over
	time_t now;
	time(&now);
	//A limit on turns otherwise the starting game takes a long time
	if (depth == maxDepth || difftime(now, startingTime) >= COMPUTING_TIME || !(oldBoard->canMove(player))) {
		return oldBoard->evaluateBoard(player); //Something needs to go here
	}
	if (oldBoard->fullGame() || (!(oldBoard->canMove(player)) && !(oldBoard->canMove(-player)))) {
		int score = oldBoard->scoreBoard(player);
		int score2 = oldBoard->scoreBoard(-player);
		if (score == score2) {
			return 0;
		}
		else if (score > score2) {
			return MAX_NUMBER;
		}
		else {
			return -MAX_NUMBER;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (oldBoard->validateMove(i, j, -player)) {
				if (oldBoard->makeMove(i, j, -player)) {
					tempValue = minValue(oldBoard, player, alpha, beta, depth++, maxDepth, startingTime);

					bestValue = std::max(bestValue, tempValue);

					//Alpha=Beta pruning
					alpha = std::max(bestValue, alpha);

					if (beta <= alpha) {
						return bestValue;
					}

					//Reset board
					oldBoard->copyBoard(tempBoard.get());
				}
			}
		}
	}
	return bestValue;
}


std::pair<int, int> minimax(GameBoard* game, int player) {
	GameBoard* tempBoard = new GameBoard();
	tempBoard->copyBoard(game);

	int tempValue, maxX, maxY;


	int maximumValue = -32768;

	bool pass = true;
	int maxDepth = 0;

	time_t start;
	time_t now;
	time(&start);
	std::pair<int, int> coords;
	while (true) {
		maxDepth++;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tempBoard->validateMove(i, j, player)) {
					if (tempBoard->makeMove(i, j, player)) {

						tempValue = maxValue(tempBoard, player, -32768, 32768, 1, maxDepth, start);
						if (tempValue != 0)
							if (tempValue >= maximumValue && tempValue < 32768) {
								//std::cout << i << ", " << j << ": " << tempValue << std::endl;
								pass = false;
								maxX = i;
								maxY = j;
								maximumValue = tempValue;
							}
						tempBoard->copyBoard(game);
					}
				}
			}
		}
		std::cout << maxX << ", " << maxY << std::endl;
		time(&now);
		if (difftime(now, start) >= COMPUTING_TIME || maxDepth > (game->scoreBoard(0)))
			break;
	}

	if (pass) {
		pass = false;
		maxX = -1; // just return something so comp can pass
		maxY = -1;
	}

	coords.first = maxX;
	coords.second = maxY;
	return coords;
}