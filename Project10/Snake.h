#pragma once

#include <vector>

#include "Coord.h"
#include "Display.h"

using namespace std;

typedef vector<Coord> CoordVector;

class Snake {
public:
	Snake();
	void reset(Coord start_pos);                   // ����� ����
	void draw(Display& scr);                       // ��������� ��������� ���� �� ������
	void move(const Coord& delta, Display& scr);   // ������������ ���� �� ���������� ���������(delta)
	void grow(const Coord& pos, int growbits);     // ���������� ����� ����
	bool into(const Coord& pos);                   // ����� ��������� ��������� ���������� � ���� ����(��� ���)
	Coord head();                                  // ����� ���������� ���������� ������ ����
	int size();                                    // ����� ���������� ����� ����

private:
	CoordVector snk;       // ������ ��������� ��������� ���� ����
	char headS;         // ������ ��� ������ ����
	unsigned int drawn;     // ����� ������������� ���� ����
};
