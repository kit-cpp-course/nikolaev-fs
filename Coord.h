//Coord.h

#pragma once

class Coord {
public:
	int x, y;
	Coord() : x(0), y(0) {}
	Coord(int _x, int _y) : x(_x), y(_y) {}
	Coord& operator +=(const Coord& op);
};

bool operator ==(const Coord& c1, const Coord& c2);

Coord operator +(const Coord& c1, const Coord& c2);