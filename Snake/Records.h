#pragma once
#include "Scene.h"

using namespace std;

class Records : public Scene
{
	struct Player
	{
		string name;
		int score;
	};

	void load();
public:
	int run(HANDLE&);
};


