#include "Display.h"

const char *msgs[] = {
	"Failed GetConsoleCursorInfo()",
	"Failed SetConsoleCursorInfo()",
	"Failed SetConsoleCursorPosition()"
};

const char *Exception::what() {
	return msgs[err];
}

Display::Display() {
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleCursorInfo(hConsoleOutput, &oldCursorInfo))
		throw Exception(1);
	curCursorInfo.dwSize = oldCursorInfo.dwSize;
	curCursorInfo.bVisible = oldCursorInfo.bVisible;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
	oldTextAttr = csbi.wAttributes;
}

Display::~Display() {
	SetConsoleCursorInfo(hConsoleOutput, &oldCursorInfo);
	SetConsoleTextAttribute(hConsoleOutput, oldTextAttr);
}

void Display::cursorShow(bool visible) {
	curCursorInfo.bVisible = visible;
	if (!SetConsoleCursorInfo(hConsoleOutput, &curCursorInfo))
		throw Exception(2);
}

void Display::texAttribut(WORD attr) {
	SetConsoleTextAttribute(hConsoleOutput, attr);
}

void Display::pos(int x, int y, char ch) {
	COORD point;
	point.X = x;
	point.Y = y;
	if (!SetConsoleCursorPosition(hConsoleOutput, point))
		throw Exception(3);
	if (ch > 0)
		_putch(ch);
}

void Display::posStrOut(int x, int y, const char *str) {
	pos(x, y);
	_cprintf("%s", str);
}

void Display::cls() {
	system("cls");
}