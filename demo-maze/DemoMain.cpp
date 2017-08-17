#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//
//  File:        DemoMain.cpp
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//
//
// (c) 2017 Aleksandra Chrapkowska
// This code is licensed under MIT license (see LICENSE.txt for details)


#include"Demo.h"
#include"GenerateMazeState.h"
#include "ErrorState.h"

int main()
{
	Demo demo(600, 600);

	try
	{
		demo.PushState(new MenuState(&demo));
	}
	catch (DemoException const& exception)
	{
		demo.PushState(new ErrorState(&demo));
	}
	demo.RunDemo();

}