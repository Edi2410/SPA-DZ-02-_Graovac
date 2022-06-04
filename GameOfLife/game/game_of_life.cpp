#include "game_of_life.h"
#include <ctime>
// #include <stdlib.h>

bool game_of_life::slucajna_vrijednost() {
	return (rand() % 4) == 0;  // 25%
}

bool game_of_life::celija_zauzeta(int i, int j) {
	if (i < 0 || i >= REDAKA) return false;
	if (j < 0 || j >= STUPACA) return false;
	return _generacija[i][j];
}

game_of_life::game_of_life() {
	srand(time(nullptr));
	for (int i = 0; i < REDAKA; ++i)
		for (int j = 0; j < STUPACA; ++j)
			_generacija[i][j] = slucajna_vrijednost();
}

void game_of_life::sljedeca_generacija() {
	const int y[8] = { -1, -1, -1,  1, 1, 1,  0, 0 };
	const int x[8] = { -1,  0,  1, -1, 0, 1, -1, 1 };
	for (int i = 0; i < REDAKA; ++i)
		for (int j = 0; j < STUPACA; ++j) {
			int brojSusjeda = 0;
			for (int k = 0; k < 8; ++k)
				brojSusjeda += +celija_zauzeta(i + y[k], j + x[k]);
			_sljedeca_generacija[i][j] = _generacija[i][j] ?
				brojSusjeda == 2 || brojSusjeda == 3 : brojSusjeda == 3;
		}
	for (int i = 0; i < REDAKA; ++i)
		for (int j = 0; j < STUPACA; ++j)
			_generacija[i][j] = _sljedeca_generacija[i][j];
}

void game_of_life::iscrtaj() {
	cout << "\033[2J\033[1;1H"; // system("cls");  
	for (int i = 0; i < REDAKA; ++i) {
		for (int j = 0; j < STUPACA; ++j)
			cout << (_generacija[i][j] ? "Z" : "m");
		cout << endl;
	}
}
