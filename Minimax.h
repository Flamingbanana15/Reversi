#pragma once
#include "Reversi Game.h"
#include <time.h>
#include <iostream>

#define COMPUTING_TIME 30
#define MAX_NUMBER 8192

int minValue(GameBoard* oldBoard, int player, int alpha, int beta, int depth, int maxDepth, time_t startingTime);
int maxValue(GameBoard* oldBoard, int player, int alpha, int beta, int depth, int maxDepth, time_t startingTime);
std::pair<int, int> minimax(GameBoard* game, int player);
