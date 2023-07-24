#include "Menu.h"
#include <conio.h>
#include <vector>

using std::string;

void Menu::create_button(short colomn, short row, string text, HANDLE h)
{
	unsigned char symbol;
	SetConsoleCursorPosition(h, { colomn ,row - 1 });
	symbol = 218;
	cout << symbol;
	symbol = 196;
	for (int i = 0; i < 14; ++i)
	{
		cout << symbol;
	}
	symbol = 191;
	cout << symbol;
	//mid
	SetConsoleCursorPosition(h, { colomn,row });
	symbol = 179;
	cout << symbol;
	symbol = ' ';
	for (int i = 0; i < 14; ++i)
	{
		if (i < text.length())
		{
			cout << text[i];
		}
		else
		{
			cout << symbol;
		}
	}
	symbol = 179;
	cout << symbol;
	//bot
	SetConsoleCursorPosition(h, { colomn ,++row });
	symbol = 192;
	cout << symbol;
	symbol = 196;
	for (int i = 0; i < 14; ++i)
	{
		cout << symbol;
	}
	symbol = 217;
	cout << symbol;
}

void Menu::print_menu(HANDLE h, int height, int width, short x, short y)
{	//top
	SetConsoleCursorPosition(h, { x,y });
	cout << (char)218;
	width -= 2;
	height -= 2;
	for (int i = 0; i < width; ++i)
	{
		cout << char(196);
	}
	cout << char(191) << '\n';
	//mid
	for (int i = 0; i < height; ++i)
	{
		cout << char(179);
		for (int j = 0; j < width; ++j)
		{
			cout << ' ';
		}
		cout << char(179) << '\n';
	}
	//bot
	cout << char(192);
	for (int i = 0; i < width; ++i)
	{
		cout << char(196);
	}
	cout << char(217);
}

int Menu::run(HANDLE &h)
{
	print_menu(h, 30, 55, 0, 0);
	SHORT choice = 0;
	SHORT need_erase = -1;
	std::vector<string> elements = { "New game", "Top 10", "Credits", "Exit" };

	SHORT y = 10;
	for (SHORT i = 0; i < elements.size(); ++i)
	{
		create_button(20, y + i * 3, elements[i], h);
	}

	while (true)
	{
		char key = _getch();
		if (key == 'w' && choice > 0)
		{
			need_erase = choice;
			--choice;
		}
		if (key == 's' && choice < elements.size() - 1)
		{
			need_erase = choice;
			++choice;
		}
		if (need_erase > -1)
		{
			SetConsoleCursorPosition(h, { 15,y + need_erase * 3 });
			cout << "   ";
			need_erase = -1;
		}
		SetConsoleCursorPosition(h, { 15,y + choice * 3 });
		cout << "=>";
		if (key == 13)
		{
			return (choice == elements.size() - 1) ? 0 : choice + 1;
		}
	}

	return 0;
}
