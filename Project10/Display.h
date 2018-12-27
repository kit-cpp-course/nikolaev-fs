#pragma once

#include <windows.h>
#include <conio.h>

/*
Класс исключения для класса CScreen
*/

class Exception {
public:
	Exception(int _err) : err(_err) {}
	const char *what();         // возвращает строку с описанием ошибки
	int err;                    // код ошибки
};


/*
Система координат:
	(0, 0)  -  левый верхний угол экрана
	ось X   -  вправо
	ось Y   -  вниз 
*/

class Display {
public:
	Display();
	~Display();
	void cursorShow(bool visible);                  // показать/скрыть курсор
	void texAttribut(WORD attr);                    // установить цвет текста/фона
	void pos(int x, int y, char ch = 0);            // координаты курсора и
													// вывод символа если ch != 0
	void posStrOut(int x, int y, const char *str);  // координаты курсора и вывод строки

	void cls();                                     // очистка экрана

private:
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO oldCursorInfo, curCursorInfo;
	WORD oldTextAttr;
};