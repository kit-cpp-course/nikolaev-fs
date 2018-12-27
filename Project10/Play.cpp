#include "Play.h"

// ������� ������ ����������
void clearkeys() {
	while (_kbhit())
		_getch();
}

// �����������
// _scr     - ������, �������������� ����� �� �������
// _width   - ������ �������� ���� (x)
// _height  - ������ �������� ���� (y)
// _latency - �������� ����� ���������� ������� � �������������

Play::Play(Display& _scr, int _width, int _height, int _speed) :
	scr(_scr),width(_width), height(_height), speed(_speed) {

	srand((int)(time(NULL)));

	durationOut = 0;

	// �������������� ������� ������ ���������� ����
	commands[0] = Pair(27, CMD_EXIT);   // escape key
	commands[1] = Pair(75, CMD_LEFT);  // ������� �����
	commands[2] = Pair(77, CMD_RIGHT); // ������� ������
	commands[3] = Pair(72, CMD_UP);    // ������� �����
	commands[4] = Pair(80, CMD_DOWN);  // ������� ����
}

Play::Command Play::getCommand() {
	int code;

	code = _getch();
	if (code == 0 || code == 0xe0) {
		code = _getch();
	}

	for (int i = 0; i < 5; i++) {
		if (commands[i].first == code) {
			return commands[i].second;
		}
	}
	return CMD_NOCOMMAND;
}

// ���������� ��� ����������� ��������� �������.
Coord Play::createFood() {
	Coord food;
	do {
		food.x = rand() % (width - 2) + 1;
		food.y = rand() % (height - 2) + 1;
	} while (snake.into(food));					//��������� ��� ��� ��������� �� � ����

	return food;
}


const char BORDER = '#';    // ����� ����


void Play::drawField() {

	scr.cls();

	for (int y = 0; y < height; y++) {
		if (y == 0 || y == height - 1) {
			for (int x = 0; x < width; x++)
				scr.pos(x, y, BORDER);
		}
		else {
			scr.pos(0, y, BORDER);
			scr.pos(width - 1, y, BORDER);
		}
	}
	scr.pos(0, height);
	_cprintf("Length:         Time: ");
}


void Play::Stats() {
	scr.pos(8, height);
	_cprintf("%04u", snake.size());
	scr.pos(22, height);
	_cprintf("%07.2f", durationOut);
}

void Play::pak(int y) {
	scr.posStrOut(width / 2 - 13, y, "Press any key to continue");
	_getch();
	clearkeys();
}

bool Play::again() {
	scr.posStrOut(width / 2 - 8, height - 3, "O n c e    m o r e ?");

	int ch = _getch();
	clearkeys();
	if (ch == 27)
		return false;
	return true;
}

void Play::logo() {
	scr.posStrOut(width / 2 - 7, 12, "S  N  A  K  E");
	pak(22);
}

void Play::goodbye() {
	scr.cls();
}


const char FOOD = '1';      // ������ ��� ������ ���

void Play::loop() {

	durationOut = 0;

	drawField();           // ���������� ������� ����

	snake.reset(Coord(width / 2, height / 2));     // ���������� ����: ����� 2,
													// ��������� - � �������� �������� ����,
													// ����������� - �����
	Command cmd = CMD_NOCOMMAND;
	State stt = STATE_OK;
	// delta  �������� ���������� ��������� (dx, dy) ��� ������� ����������� ���� �� ����
	Coord delta(-1, 0);                // ��������� �������� - �����
	Coord food = createFood();          // ������������� ���������� ���
	scr.pos(food.x, food.y, FOOD);      // ������� ��� �� �����

	snake.draw(scr);                    // ��������� ��������� ����

	Stats();                       // ������� ��������� ���������� ����

	clock_t time1, time2, duration;
	time1 = clock();

	do {

		if (_kbhit())                   // ���� � ������ ���������� ���� ����������,
			cmd = getCommand();        // �� ������� �������

		// ��������� ������
		switch (cmd) {
		case CMD_LEFT:
			delta = Coord(-1, 0);
			break;
		case CMD_RIGHT:
			delta = Coord(1, 0);
			break;
		case CMD_UP:
			delta = Coord(0, -1);
			break;
		case CMD_DOWN:
			delta = Coord(0, 1);
			break;
		case CMD_EXIT:
			stt = STATE_EXIT;
		default:
			break;
		};

		Coord hd = snake.head();       // ���������� ������ ����
		hd += delta;                    // ���������� ������ ���� ����� ���������� (��������� �������)
		// ���� ������ ���� ����������� � �������� ���� ��� �� ����� ����, �� ���� �������
		if (hd.x == 0 || hd.x == width - 1 || hd.y == 0 || hd.y == height - 1 || snake.into(hd))
			stt = STATE_DIED;

		if (stt == STATE_OK) {          // ���� ���� ��� ����, ��
			snake.move(delta, scr);     // �������� ���� �� delta

			if (snake.head() == food) { // ���� ���������� ������ ���� ��������� � ����������� ���, ��
				snake.grow(food, 3);    // ��������� ����� ����
				food = createFood();     // ��������� ���������� ����� ���
				scr.pos(food.x, food.y, FOOD); // ������� ��� �� �����

				// ���������� ������� ����
				time2 = clock();
				duration = time2 - time1;
				durationOut += (double)(duration) / CLOCKS_PER_SEC;
				time1 = time2;

				Stats();           // ����� ������� ���������� ����
			}
			Sleep(speed);             // �������� ����� ��������� ���������� �������
		}

	} while (stt == STATE_OK);          // ������, ���� ���� ����

	scr.posStrOut(width / 2 - 8, 10, " G a m e    o v e r ");
	clearkeys();
	_getch();
	clearkeys();
}