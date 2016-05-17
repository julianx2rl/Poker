// TexasHoldem.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Baraja.h"
#include "Administrador.h"
#include <iostream>

using namespace std;

int main() {
	Administrador * juego = new Administrador();
	bool replay = true;
	bool choosen = false;
	while (replay) {
		juego->iniciarJuego();
		juego->reparto();
		juego->jugar();
		while (!choosen) {
			int yo = 0;
			cout << "You want to play again, or what? 0- Yes / 1- No";
			cin >> yo;
			replay = yo == 0;
			choosen = yo == 0 || yo == 1;
			if (!choosen) {
				cout << "Choose again!";
			}
		}
	}

	delete juego;
	return 0;
}