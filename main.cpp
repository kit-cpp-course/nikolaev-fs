//main.cpp

#include "Display.h"
#include "Play.h"

int main() {

	setlocale(LC_ALL, "Russian");

	try {
		Display screen;
		screen.cursorShow(false);
		screen.texAttribut((WORD)027);
		screen.cls();
		Play game(screen, 80, 24, 100);

		game.logo();

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