//Play.h

#pragma once

#include <time.h>
#include <utility>
#include <iostream>
#include <cstring>
#include <conio.h>

#include "Display.h"
#include "Snake.h"
#include "Coord.h"

using namespace std;

class Play {
public:
	Play(Display& _scr, int _width , int _height , int _latency );
	void loop();				// основной цикл игры
	bool again();				// вывод запроса и приём ответа от игрока
	void logo();                // вывод заставки игры
	void goodbye();             // ввод при поражении

private:
	enum Command { CMD_NOCOMMAND = 0, CMD_EXIT, CMD_LEFT, CMD_RIGHT, CMD_UP, CMD_DOWN };
	enum State { STATE_OK, STATE_EXIT, STATE_DIED };

	typedef pair<int, Command> Pair;

	int width, height;      // ширина и высота игрового поля
	int speed;            // задержка между изменением позиции в миллисекундах
	Display scr;            // подсистема визуализации
	Snake snake;           // змея
	double durationOut;   // длительность игры
	Pair commands[5];   // таблица команд управления игрой
	void drawField();      // прорисовка игрового поля
	Coord createFood();     // генерация позиции для еды
	void Stats();      // вывод статистики, обновляется при увиличении длины змеи
	Command getCommand();  // приём команды с клавиатуры
};
