#include"EvaluationBuilder.h"
#include <iostream>
#include <fstream>

void writeResults(int generation, int pieceMulti, int unusedMulti, int neighborMulti, int movesMulti, int stableMulti) {
	std::ofstream resultsFile;
	resultsFile.open("Results", std::ios::in);
	if (resultsFile.is_open()) {
		resultsFile << generation << std::endl;

	}
	resultsFile.close();
}