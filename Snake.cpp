//Snake.h

#include "Snake.h"

const char SNAKE_TAIL = '@';        // символ для отрисовки сегментов тела змеи, кроме головы


Snake::Snake() {
	headS = '<';
}

void Snake::reset(Coord start_pos) {
	snk.clear();
	snk.reserve(1000);         // зарезервировть память
	snk.push_back(start_pos);  // добавить координаты головы
	snk.push_back(start_pos);  // добавить координаты хвоста
	snk[0].x++;                // координата x хвоста - на 1 правее
}

void Snake::draw(Display& scr) {
	unsigned int wsize = snk.size() - 1;
	for (unsigned int i = 0; i < wsize; i++)
		scr.pos(snk[i].x, snk[i].y, SNAKE_TAIL);
	scr.pos(snk[wsize].x, snk[wsize].y, headS);
	drawn = snk.size();
}

void Snake::move(const Coord& delta, Display& scr) {
	// При перемещении змеи перерисовывается только положение головы (и первого сегмента)
	// и положение хвоста. Остальные сегменты змеи не перерисовываются.

	// Перерисовка хвоста.
	// Длина змеи увеличивается, когда змея растёт (метод grow()),
	// но змея на экране не изменяется. Поэтому, если отрисованная длина змеи
	// совпадает с реальной длиной, то на экране затирается последний сегмент змеи (хвост).
	// В противном случае, хвост остаётся на месте, голова сдвигается на единицу,
	// а отрисованная длина увеличивается.
	if (drawn == snk.size())
		scr.pos(snk[0].x, snk[0].y, ' ');
	else
		drawn++;

	// сдвиг координат в векторе без отрисовки
	for (unsigned int i = 1; i < snk.size(); i++)
		snk[i - 1] = snk[i];

	snk[snk.size() - 1] += delta;       // координата головы изменяется на приращение

	// выбор символа для отрисовки головы в зависимости от направления движения
	if (delta.x < 0)
		headS = '<';
	else if (delta.x > 0)
		headS = '>';
	else if (delta.y < 0)
		headS = 'A';
	else // (delta.y > 0)
		headS = 'V';

	// Перерисовка головы и первого сегмента змеи.
	scr.pos(snk[snk.size() - 1].x, snk[snk.size() - 1].y, headS);
	scr.pos(snk[snk.size() - 2].x, snk[snk.size() - 2].y, SNAKE_TAIL);
}

void Snake::grow(const Coord& pos, int growbits) {
	for (int i = 0; i < growbits; ++i)
		snk.insert(snk.begin(), pos);
}

bool Snake::into(const Coord& pos) {
	for (unsigned int i = 0; i < snk.size(); i++)
		if (snk[i].x == pos.x && snk[i].y == pos.y)
			return true;
	return false;
}

Coord Snake::head() {
	return snk[snk.size() - 1];
}

int Snake::size() {
	return static_cast<int>(snk.size());
}