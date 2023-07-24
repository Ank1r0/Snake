#pragma once

#include <Windows.h>
#include <iostream>

#define WIDTH 120
#define HEIGHT 40

using std::cout;

class Scene
{
public:
	virtual int run(HANDLE&) = 0;
};

