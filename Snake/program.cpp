#include "Menu.h"
#include "Game.h"
#include "Records.h"
#include <vector>
#include <string>

using namespace std;

void hide_cursor(HANDLE &h)
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 100;
	SetConsoleCursorInfo(h, &cursor);
}

void setup()
{
	system("title Snake Game");
	std::string cmd = "mode con cols=" + std::to_string(WIDTH) + " lines=" + std::to_string(HEIGHT);
	system(cmd.c_str());
}

int main()
{
	HANDLE	h = GetStdHandle(STD_OUTPUT_HANDLE);
	setup();
	hide_cursor(h);

	Scene *scene[] = {new Game, new Records, new Menu};
	
	int scene_number = 3;
	while(scene_number)
	{
		scene_number = scene[scene_number-1]->run(h);
	}

	return 0;
}
