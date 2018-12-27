#pragma once

#include <vector>

#include "Coord.h"
#include "Display.h"

using namespace std;

typedef vector<Coord> CoordVector;

class Snake {
public:
	Snake();
	void reset(Coord start_pos);                   // сброс змеи
	void draw(Display& scr);                       // первичная отрисовка змеи на экране
	void move(const Coord& delta, Display& scr);   // передвижение змеи на приращение координат(delta)
	void grow(const Coord& pos, int growbits);     // увеличение длины змеи
	bool into(const Coord& pos);                   // метод проверяет попадание координаты в тело змеи(для еды)
	Coord head();                                  // метод возвращает координаты головы змеи
	int size();                                    // метод возвращает длину змеи

private:
	CoordVector snk;       // вектор координат сегментов тела змеи
	char headS;         // символ для головы змеи
	unsigned int drawn;     // длина отрисованного тела змеи
};
