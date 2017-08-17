//
//  File:			DemoDelpers.h
//  Description:	Exception handling, other functions
//  Created:		11-08-2017
//  Author:			Aleksandra Chrapkowska
//  mail:			amchrapkowska@gmail.com
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)
//

#pragma once
#include <stdexcept>

int RandomInt(int lb, int ub);

class DemoException : public std::runtime_error
{
public:
	DemoException(std::string what_went_wrong);

};