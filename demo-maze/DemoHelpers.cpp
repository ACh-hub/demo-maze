
#include<random>
#include<chrono>

#include"DemoHelpers.h"

std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());


int RandomInt(int lb, int ub)
{
	std::uniform_int_distribution<int> uid{ lb, ub };
	return uid(dre);
}