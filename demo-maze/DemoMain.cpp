#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//
//  File:        DemoMain.cpp
//  Created:     11-08-2017
//  Author:      Aleksandra Chrapkowska
//  mail:        amchrapkowska@gmail.com
//



#include"Demo.h"
#include"GenerateMazeState.h"
#include "ErrorState.h"

int main()
{
	Demo demo(600, 600);

	demo.PushState(new MenuState(&demo));
	demo.RunDemo();
}