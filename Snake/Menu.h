#pragma once

#include "Scene.h"
#include <string>
using std::string;
class Menu : public Scene
{
	HANDLE h = nullptr;
	void create_button(short, short, string, HANDLE);
	void print_menu(HANDLE, int, int, short, short);
	int menu();

public:
	int run(HANDLE &h);
};