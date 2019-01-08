//Snake.h

#include "Snake.h"

const char SNAKE_TAIL = '@';        // ������ ��� ��������� ��������� ���� ����, ����� ������


Snake::Snake() {
	headS = '<';
}

void Snake::reset(Coord start_pos) {
	snk.clear();
	snk.reserve(1000);         // �������������� ������
	snk.push_back(start_pos);  // �������� ���������� ������
	snk.push_back(start_pos);  // �������� ���������� ������
	snk[0].x++;                // ���������� x ������ - �� 1 ������
}

void Snake::draw(Display& scr) {
	unsigned int wsize = snk.size() - 1;
	for (unsigned int i = 0; i < wsize; i++)
		scr.pos(snk[i].x, snk[i].y, SNAKE_TAIL);
	scr.pos(snk[wsize].x, snk[wsize].y, headS);
	drawn = snk.size();
}

void Snake::move(const Coord& delta, Display& scr) {
	// ��� ����������� ���� ���������������� ������ ��������� ������ (� ������� ��������)
	// � ��������� ������. ��������� �������� ���� �� ����������������.

	// ����������� ������.
	// ����� ���� �������������, ����� ���� ����� (����� grow()),
	// �� ���� �� ������ �� ����������. �������, ���� ������������ ����� ����
	// ��������� � �������� ������, �� �� ������ ���������� ��������� ������� ���� (�����).
	// � ��������� ������, ����� ������� �� �����, ������ ���������� �� �������,
	// � ������������ ����� �������������.
	if (drawn == snk.size())
		scr.pos(snk[0].x, snk[0].y, ' ');
	else
		drawn++;

	// ����� ��������� � ������� ��� ���������
	for (unsigned int i = 1; i < snk.size(); i++)
		snk[i - 1] = snk[i];

	snk[snk.size() - 1] += delta;       // ���������� ������ ���������� �� ����������

	// ����� ������� ��� ��������� ������ � ����������� �� ����������� ��������
	if (delta.x < 0)
		headS = '<';
	else if (delta.x > 0)
		headS = '>';
	else if (delta.y < 0)
		headS = 'A';
	else // (delta.y > 0)
		headS = 'V';

	// ����������� ������ � ������� �������� ����.
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