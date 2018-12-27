#include "Coord.h"

Coord& Coord::operator +=(const Coord& c) {
	x += c.x;
	y += c.y;
	return *this;
}

bool operator ==(const Coord& c1, const Coord& c2) {
	return c1.x == c2.x && c1.y == c2.y;
}

Coord operator +(const Coord& c1, const Coord& c2) {
	return Coord(c1.x + c2.x, c1.y + c2.y);
}
