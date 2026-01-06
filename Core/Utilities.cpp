#include "Utilities.h"
#include <random>
int Utilities::GenerateRandomValue(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}