#include "stdafx.h"
#include "Juego.h"

Juego::Juego(){
}


Juego::~Juego(){
}

void Juego::jugar(){
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

}
