#pragma once

#include <windows.h>
#include <conio.h>

/*
����� ���������� ��� ������ CScreen
*/

class Exception {
public:
	Exception(int _err) : err(_err) {}
	const char *what();         // ���������� ������ � ��������� ������
	int err;                    // ��� ������
};


/*
������� ���������:
	(0, 0)  -  ����� ������� ���� ������
	��� X   -  ������
	��� Y   -  ���� 
*/

class Display {
public:
	Display();
	~Display();
	void cursorShow(bool visible);                  // ��������/������ ������
	void texAttribut(WORD attr);                    // ���������� ���� ������/����
	void pos(int x, int y, char ch = 0);            // ���������� ������� �
													// ����� ������� ���� ch != 0
	void posStrOut(int x, int y, const char *str);  // ���������� ������� � ����� ������

	void cls();                                     // ������� ������

private:
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO oldCursorInfo, curCursorInfo;
	WORD oldTextAttr;
};