#include <iostream>
#include <conio.h>

#include "Display.h"
#include "Play.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");

	try {
		Display screen;
		screen.cursorShow(false);
		screen.texAttribut((WORD)027);
		screen.cls();
		Play game(screen, 80, 24, 100);

		game.logo();

		game.pak(18);

		do {
			game.loop();

		} while (game.again());

		game.goodbye();
	}
	catch (Exception& ex) {
		cerr << " " << ex.what() << endl;
	}

	return 0;
}