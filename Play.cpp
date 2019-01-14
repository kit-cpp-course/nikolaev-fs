//Play.cpp

#include "Play.h"

// очистка буфера клавиатуры
void clearkeys() {
	while (_kbhit())
		_getch();
}

// Конструктор
// _scr     - объект, осуществляющий вывод на консоль
// _width   - ширина игрового поля (x)
// _height  - высота игрового поля (y)
// _latency - задержка между изменением позиции в миллисекундах

Play::Play(Display& _scr, int _width, int _height, int _speed) :
	scr(_scr),width(_width), height(_height), speed(_speed) {

	srand((int)(time(NULL)));

	durationOut = 0;

	// инициализируем таблицу команд управления змеёй
	commands[0] = Pair(27, CMD_EXIT);   // escape key
	commands[1] = Pair(75, CMD_LEFT);  // стрелка влево
	commands[2] = Pair(77, CMD_RIGHT); // стрелка вправо
	commands[3] = Pair(72, CMD_UP);    // стрелка вверх
	commands[4] = Pair(80, CMD_DOWN);  // стрелка вниз
}

Play::Command Play::getCommand() {
	int code;

	code = _getch();
	if (code == 0) {
		code = _getch();
	}

	for (int i = 0; i < 5; i++) {
		if (commands[i].first == code) {
			return commands[i].second;
		}
	}
	return CMD_NOCOMMAND;
}

// Координата еды вычисляется случайным образом.
Coord Play::createFood() {
	Coord food;
	do {
		food.x = rand() % (width - 2) + 1;
		food.y = rand() % (height - 2) + 1;
	} while (snake.into(food));					//проверяем что еда появилась не в змее

	return food;
}


const char BORDER = '#';    // рамка поля


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
}

void Play::goodbye() {
	scr.cls();
}


const char FOOD = '1';      // символ для вывода еды

void Play::loop() {

	durationOut = 0;

	drawField();           // нарисовать игровое поле

	snake.reset(Coord(width / 2, height / 2));     // установить змею: длина 2,
													// положение - в середине игрового поля,
													// направление - влево
	Command cmd = CMD_NOCOMMAND;
	State stt = STATE_OK;
	// delta  содержит приращение координат (dx, dy) для каждого перемещения змеи по полю
	Coord delta(-1, 0);                // начальное движение - влево
	Coord food = createFood();          // сгенерировать координаты еды
	scr.pos(food.x, food.y, FOOD);      // вывести еду на экран

	snake.draw(scr);                    // первичное рисование змеи

	Stats();                       // вывести начальную статистику игры

	clock_t time1, time2, duration;
	time1 = clock();

	do {

		if (_kbhit())                   // если в буфере клавиатуры есть информация,
			cmd = getCommand();        // то принять команду

		// обработка команд
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

		Coord hd = snake.head();       // координата головы змеи
		hd += delta;                    // координата головы змеи после приращения (следующая позиция)
		// если голова змеи столкнулась с границей поля или со телом змеи, то змея умирает
		if (hd.x == 0 || hd.x == width - 1 || hd.y == 0 || hd.y == height - 1 || snake.into(hd))
			stt = STATE_DIED;

		if (stt == STATE_OK) {          // если змея ещё жива, то
			snake.move(delta, scr);     // сдвинуть змею на delta

			if (snake.head() == food) { // если координата головы змеи совпадает с координатой еды, то
				snake.grow(food, 3);    // увеличить длину змеи
				food = createFood();     // вычислить координаты новой еды
				scr.pos(food.x, food.y, FOOD); // вывести еду на экран

				// Вычисление времени игры
				time2 = clock();
				duration = time2 - time1;
				durationOut += (double)(duration) / CLOCKS_PER_SEC;
				time1 = time2;

				Stats();           // вывод текущей статистики игры
			}
			Sleep(speed);             // задержка перед следующим изменением позиции
		}

	} while (stt == STATE_OK);          // играем, пока змея жива

	scr.posStrOut(width / 2 - 8, 10, " G a m e    o v e r ");
	clearkeys();
	_getch();
	clearkeys();
}
