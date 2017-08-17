//
//  File:			DemoHelpers.cpp
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
//

#include<random>
#include<chrono>

#include"DemoHelpers.h"

std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());


int RandomInt(int lb, int ub)
{
	std::uniform_int_distribution<int> uid{ lb, ub };
	return uid(dre);
}

DemoException::DemoException(std::string what_went_wrong)
	:
	std::runtime_error(what_went_wrong)
{
}

