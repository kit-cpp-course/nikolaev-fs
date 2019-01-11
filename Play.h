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
	void loop();				// îñíîâíîé öèêë èãðû т
	bool again();				// âûâîä çàïðîñà è ïðè¸ì îòâåòà îò èãðîêà
	void pak(int y);            // "Press any key to continue"
	void logo();                // âûâîä çàñòàâêè èãðû
	void goodbye();             // ââîä ïðè ïîðàæåíèè

private:
	enum Command { CMD_NOCOMMAND = 0, CMD_EXIT, CMD_LEFT, CMD_RIGHT, CMD_UP, CMD_DOWN };
	enum State { STATE_OK, STATE_EXIT, STATE_DIED };

	typedef pair<int, Command> Pair;

	int width, height;      // øèðèíà è âûñîòà èãðîâîãî ïîëÿ
	int speed;            // çàäåðæêà ìåæäó èçìåíåíèåì ïîçèöèè â ìèëëèñåêóíäàõ
	Display scr;            // ïîäñèñòåìà âèçóàëèçàöèè
	Snake snake;           // çìåÿ
	double durationOut;   // äëèòåëüíîñòü èãðû
	Pair commands[5];   // òàáëèöà êîìàíä óïðàâëåíèÿ èãðîé
	void drawField();      // ïðîðèñîâêà èãðîâîãî ïîëÿ
	Coord createFood();     // ãåíåðàöèÿ ïîçèöèè äëÿ åäû
	void Stats();      // âûâîä ñòàòèñòèêè, îáíîâëÿåòñÿ ïðè óâèëè÷åíèè äëèíû çìåè
	Command getCommand();  // ïðè¸ì êîìàíäû ñ êëàâèàòóðû
};
