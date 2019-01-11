//Display.h

#pragma once

#include <windows.h>
#include <conio.h>

/*
Êëàññ èñêëþ÷åíèÿ äëÿ êëàññà Screen
*/

class Exception {
public:
	Exception(int _err) : err(_err) {}
	const char *what();         // âîçâðàùàåò ñòðîêó ñ îïèñàíèåì îøèáêè
	int err;                    // êîä îøèáêè
};


/*
Ñèñòåìà êîîðäèíàò:
	(0, 0)  -  ëåâûé âåðõíèé óãîë ýêðàíà
	îñü X   -  âïðàâî
	îñü Y   -  âíèç 
*/

class Display {
public:
	Display();
	~Display();
	void cursorShow(bool visible);                  // ïîêàçàòü/ñêðûòü êóðñîð
	void texAttribut(WORD attr);                    // óñòàíîâèòü öâåò òåêñòà/ôîíà
	void pos(int x, int y, char ch = 0);            // êîîðäèíàòû êóðñîðà è
													// âûâîä ñèìâîëà åñëè ch != 0
	void posStrOut(int x, int y, const char *str);  // êîîðäèíàòû êóðñîðà è âûâîä ñòðîêè

	void cls();                                     // î÷èñòêà ýêðàíà

private:
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO oldCursorInfo, curCursorInfo;
	WORD oldTextAttr;
};
