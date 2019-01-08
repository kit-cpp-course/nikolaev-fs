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
	void loop();				// �������� ���� ����
	bool again();				// ����� ������� � ���� ������ �� ������
	void pak(int y);            // "Press any key to continue"
	void logo();                // ����� �������� ����
	void goodbye();             // ���� ��� ���������

private:
	enum Command { CMD_NOCOMMAND = 0, CMD_EXIT, CMD_LEFT, CMD_RIGHT, CMD_UP, CMD_DOWN };
	enum State { STATE_OK, STATE_EXIT, STATE_DIED };

	typedef pair<int, Command> Pair;

	int width, height;      // ������ � ������ �������� ����
	int speed;            // �������� ����� ���������� ������� � �������������
	Display scr;            // ���������� ������������
	Snake snake;           // ����
	double durationOut;   // ������������ ����
	Pair commands[5];   // ������� ������ ���������� �����
	void drawField();      // ���������� �������� ����
	Coord createFood();     // ��������� ������� ��� ���
	void Stats();      // ����� ����������, ����������� ��� ���������� ����� ����
	Command getCommand();  // ���� ������� � ����������
};