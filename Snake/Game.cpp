#include "Game.h"
#include <Windows.h>
#include <list>
#include "Scene.h"
#include <conio.h>
#include <ctime>

#define countOfApple 20;
using std::list;

enum Direction
{
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
	LEFT = 4,
	STOP = 0
};

class Snake
{
	list<COORD> coord;

public:
	Snake(COORD location)
	{
		coord.push_front(location);
		COORD location123 = { location.X + 1, location.Y };
		coord.push_front(location123);
	}

	COORD delTail()
	{
		COORD temp = coord.back();
		coord.pop_back();
		return temp;
	}

	COORD getTail()
	{
		return coord.back();
	}

	COORD getHead()
	{
		return coord.front();
	}

	bool changeLoc(Direction direction)
	{
		COORD temp_coord = coord.front();

		switch (direction)
		{
		case LEFT:
			temp_coord.X -= 1;
			break;
		case RIGHT:
			temp_coord.X += 1;
			break;
		case UP:
			temp_coord.Y -= 1;
			break;
		case DOWN:
			temp_coord.Y += 1;
			break;
		}
		if (isCollision(temp_coord))
			return false;
		coord.emplace_front(temp_coord);
		return true;
	}

	bool isCollision(COORD point)
	{
		for (auto element : coord)
		{
			if (element.X == point.X && element.Y == point.Y)
				return true;
		}
		return false;
	}


	// int checkApple(COORD* ar,HANDLE& h)
	// {
	// 	COORD* apples = ar;
	// 	COORD temp = coord.front();
	// 	for (int i = 0; i < 20; ++i)
	// 	{
	// 		if (temp.X == apples[i].X && temp.Y == apples[i].Y)
	// 		{
	// 			apples[i].X = -1;
	// 			apples[i].Y = -1;
	//
	// 			SetConsoleCursorPosition(h, { 103,2 });
	// 			cout << "snake X:" << temp.X << " Y: " << temp.Y;
	// 			return i;
	//
	//
	// 		}
	// 	}
	// 	return -1;
	// }


};

class Apples
{
	static const int NUMBER_OF_APPLES = 20;
	static const char apple_char = '*';
	COORD apples[NUMBER_OF_APPLES] = {};
	HANDLE	h;

public:

	Apples(Snake *snake)
	{
		srand(time(0) + 5643);
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		initApple(snake);
	}

	void initApple(Snake *snake)
	{
		for (int i = 0; i < NUMBER_OF_APPLES; ++i)
		{
			apples[i] = createApple(snake);
		}
	}

	COORD createApple(Snake *snake)
	{
		bool pass;
		COORD coord;
		do
		{
			pass = true;
			coord.X = (rand() % (WIDTH - 21)) + 1;
			coord.Y = (rand() % (HEIGHT - 2)) + 1;
			for (int i = 0; i < NUMBER_OF_APPLES; ++i)
			{
				if(coord.X == apples[i].X && coord.Y == apples[i].Y)
				{
					pass = false;
					break;
				}
			}
		} while (!pass || snake->isCollision(coord));
		SetConsoleCursorPosition(h, coord);
		cout << apple_char;

		//cout << coord.X << ", " << coord.Y << '\n';
		return coord;
	}

	bool isNyamNyam(COORD snake_head, Snake *snake)
	{
		for (int i = 0; i < NUMBER_OF_APPLES; ++i)
		{
			if (snake_head.X == apples[i].X && snake_head.Y == apples[i].Y)
			{
				apples[i] = createApple(snake);
				return true;
			}
		}
		return false;
	}
	
};

void print_field(HANDLE& h)
{
	SetConsoleCursorPosition(h, { 0,0 });
	SetConsoleTextAttribute(h, 11);
	//top
	unsigned char v_line = 201;
	cout << static_cast<char>(201);
	v_line = 205;
	for (int i = 1; i < WIDTH - 20; ++i)
	{
		cout << v_line;
	}

	v_line = 187;
	cout << v_line;
	//mid
	v_line = 186;
	for (SHORT i = 1; i < HEIGHT - 1; ++i)
	{
		SetConsoleCursorPosition(h, { 100, i });
		cout << v_line;
		SetConsoleCursorPosition(h, { 0, i });
		cout << v_line;
	}
	//bot
	SetConsoleCursorPosition(h, { 0, HEIGHT - 1 });
	v_line = 200;
	cout << v_line;
	v_line = 205;
	for (int i = 1; i < WIDTH - 20; ++i)
	{
		cout << v_line;
	}
	v_line = 188;
	cout << v_line;

	//score & etc.
}


int Game::run(HANDLE& h)
{
	system("cls");
	print_field(h);

	int Score = 0;
	SetConsoleCursorPosition(h, { 103,1 });
	cout << "Score: " << Score;

	Direction direction = RIGHT;
	COORD pos = { 20,20 };
	Snake snk(pos);
	Apples appl(&snk);

	char key = 'd';
	while (true)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 'd':
				if (direction != LEFT)
					direction = RIGHT;
				break;
			case 'a':
				if (direction != RIGHT)
					direction = LEFT;
				break;
			case 'w':
				if (direction != DOWN)
					direction = UP;
				break;
			case 's':
				if (direction != UP)
					direction = DOWN;
				break;
			case 'p':
				direction = STOP;
			}
		}

		bool is_succes = snk.changeLoc(direction);
		COORD temp1 = snk.getHead();
		if (!is_succes || temp1.X >= WIDTH-20 || temp1.X <= 0 || temp1.Y > HEIGHT-2 || temp1.Y <= 0)
		{
			return 3;
		}
		if (appl.isNyamNyam(temp1, &snk))
		{
			++Score;
			SetConsoleCursorPosition(h, { 103,1 });
			cout << "Score: " << Score;
		}
		else
		{
			SetConsoleCursorPosition(h, snk.delTail());
			cout << " ";
		}
		
		SetConsoleCursorPosition(h, snk.getHead());
		SetConsoleTextAttribute(h, 2);
		cout << "#";
		if (direction == 1 || direction == 3)
		{
			Sleep(100);
		}
		else
		{
			Sleep(70);
		}
	}
}
