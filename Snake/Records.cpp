#include "Records.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void Records::load()
{
	system("cls");

	vector<Player> players;
	Player player;
	ifstream ifs("records.txt");
	while (!ifs.eof())
	{
		ifs >> player.name;
		ifs >> player.score;
		players.push_back(player);
	}

	for (auto p : players)
	{
		cout << "Name: " << p.name << " Score: " << p.score << '\n';
	}


	ifs.close();
	system("pause");
}


int Records::run(HANDLE &h)
{
	system("cls");
	std::cout << "This is Records!\n";
	load();

	system("pause");
	return 3;
}

