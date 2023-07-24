#include "Menu.h"
#include "Game.h"

#include <string>


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


	Scene *scene[] = {new Menu, new Game};
	
	int scene_number = 0;
	while(scene_number != 13)
	{
		scene_number = scene[scene_number]->run(h);
	}

	return 0;
}
