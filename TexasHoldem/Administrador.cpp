#include "stdafx.h"
#include "Administrador.h"
#include <iostream>

using namespace std;

Administrador::Administrador()
{
}

void Administrador::iniciarJuego() {
	cout << "Super Poker Stars - Battle Royale. - Inserta cualquier valor!" << endl;
	int efectivo = 0;
	cin >> efectivo;
	cout << "Elige la cantidad de dinero de cada jugador - Mínimo de 100." << endl;
	cin >> efectivo;
	if (efectivo < 100) {
		efectivo = 100;
		cout << "al menos un valor de 100 es requerido." << endl;
	}
	int numero = 0;
	cout << "Elige la cantidad de jugadores." << endl;
	cin >> numero;
	if (numero < 2) {
		numero = 2;
		cout << "al menos 2 jugadores son requeridos." << endl;
	}
	else {
		if (numero > 10) {
			numero = 10;
			cout << "Solo un maximo de 10 jugadores pueden unirse." << endl;
		}
	}
	cout << "Elige los nombres de jugadores." << endl;
	char* nombre = "";
	for (int i = 0; i < numero; ++i) {
		cout << "Numero " << (i+1) << endl;
		cin >> nombre;
		this->juego.push_front(new Jugador(nombre, efectivo));
	}
	int value = numero;
	this->mano = new Baraja();
	mano->barajarCartas();
}

void Administrador::reparto() {
	for (list<Jugador*>::iterator it = this->juego.begin(); it != this->juego.end(); ++it) { //Pasa por los diez jugadores.
		for (int i = 0; i < 2; ++i) { //Le da dos cartas a cada uno
			Carta * tmp = this->mano->getCarta();
			(*it)->recieve(tmp);
		}
	}
}

void Administrador::imprimir() {
	for (list<Carta *>::iterator it = this->mesa.begin(); it != this->mesa.end(); ++it) {
		cout << **it;
	}
}

void Administrador::jugar() {

	//
	for (int j = 0; j < 3; ++j) {
		poner();
	}

	for (int j = 0; j < 3; ++j) {
		preguntar();
		if (j <= 1) {
		poner();
	}
		if (juego.size() <= 1) {
			break;
		}
	}

	Jugador* winner = calcular();
	cout << "The winner is: " << (winner)->getName() << " con:" << endl;
	this->imprimir();
	(winner)->imprimir();
	juego.clear();
	mesa.clear();
	delete mano;
}

void Administrador::poner() {
	Carta* tmp = this->mano->getCarta();
	mesa.push_front(tmp);
	for (list<Jugador *>::iterator it = this->juego.begin(); it != this->juego.end(); ++it) {
		(*it)->reset();
	}
}

void Administrador::preguntar() {
	int opcion = 0;
	cout << "La mesa es:" << endl;
	this->imprimir();
	bool settled = false;
	int j = juego.size();
	while (settled == false) {
		for (list<Jugador *>::iterator it = this->juego.begin(); it != this->juego.end(); ++it) {
			bool done = (*it)->check();
			if (done == false) {
				cout << "What will you do? player " << (*it)->getName() << " 0 = bet, 1 = check, 2 = fold, - Your money is " << (*it)->getMoney() << " - The mimimum deal is: " << apuestaMinima << " - and your deck is:" << endl;
				(*it)->imprimir();
				this->imprimir();
				cout << endl;
				cin >> opcion;
				switch (opcion) {
				case 0:
				{
					int bet = 0;
					cout << "How much will you bet? " << (*it)->getName() << " - The minimum is " << apuestaMinima << endl;
					cin >> bet;
					int tol = (*it)->bet(bet);
					if (tol >= apuestaMinima) {
						apuestaMinima = bet;
						lote = lote + bet;
						(*it)->finish();
					}
					else {
						if ((*it)->getMoney() > (apuestaMinima - 1)) {
							cout << "You have to deal more than that!" << endl;
							(*it)->recieveMoney(bet);
							(*it)->bet(apuestaMinima);
							lote = lote + apuestaMinima;
							(*it)->finish();
						}
						else {
							cout << "You're out" << (*it)->getName() << endl;
							juego.erase(it);
						}
					}
					break;
				}
				case 1:
				{
				}
				case 2:
				{
					cout << "Good Bye..." << (*it)->getName()<< endl;
					juego.erase(it);
				}
				break;
				}
			}
		}
		for (list<Jugador *>::iterator it = this->juego.begin(); it != this->juego.end(); ++it) {
			settled = (*it)->check();
			if (settled == false) {
				break;
			}
		}
	}
}

Jugador* Administrador::calcular()
{
	int winner = 0;
	list<Jugador*>::iterator tamizake = this->juego.begin();
	Jugador* tam = (*tamizake);
	list<Carta*> manotmp;
	Carta* tmp;
	mesa.sort();
	for (list<Carta *>::iterator it = this->mesa.begin(); it != this->mesa.end(); ++it) {
		tmp = (*it);
		manotmp.push_front(tmp);
	}
	for (list<Jugador *>::iterator it = this->juego.begin(); it != this->juego.end(); ++it) {
		list<Carta*> manitatmp = (*it)->returnHand();

		for (list<Carta*>::iterator ite = manitatmp.begin(); ite != manitatmp.end(); ++ite) {
			tmp = (*ite);
			manotmp.push_front(tmp);
		}
		manotmp.sort();
		int fag = valorJugada(manotmp);
		if (fag > winner) {
			tam = (*it);
			winner = fag;
			// Mata las cartas del jugador, no usa clear para no meter las cartas de mesa otra vez.
			list<Carta*>::iterator killer = manotmp.begin();
			for (int u = 0; u < 2; ++u) {
				manotmp.pop_front();
			}
		}
	}
	return tam;
}

int Administrador::valorJugada(list<Carta*> mano)
{
	int flush = 0;
	int straight = 0;
	int four = 0;
	int three = 0;
	int two = 0;
	int full = 0;
	int big = 0;
	int k = 0;

	/*checks for flush*/
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	advance(it2, 1);
	while (k<4 && ((*it1)->getPalo() == (*it2)->getPalo())) {
		k++;
		it1 = mano.begin();
		it2 = mano.begin();
		advance(it1, k);
		advance(it2, k + 1);
		if (k == 4)
			flush = 1;
		break;
	}

	/* checks for straight*/
	k = 0;
	it1 = mano.begin();
	it2 = mano.begin();
	advance(it2, 1);
	while (k < 4 && ((*it1)->getValor() == (*it2)->getValor()) - 1) {
		k++;
		it1 = mano.begin();
		it2 = mano.begin();
		advance(it1, k);
		advance(it2, k + 1);
		if (k == 4) {
			straight = 1;
			break;
		}
	}

	/* checks for fours */
	for (int i = 0;i<2;i++) {
		k = i;
		while (k<i + 3 && ((*it1)->getValor() == (*it2)->getValor()) - 1)
			k++;
		it1 = mano.begin();
		it2 = mano.begin();
		advance(it1, k);
		advance(it2, k + 1);
		if (k == i + 3) {
			four = 1;
			it1 = mano.begin();
			advance(it1, i);
			big = (*it1)->getValor();
		}
	}

	/*checks for threes and fullhouse*/
	k = 0;
	it1 = mano.begin();
	it2 = mano.begin();
	if (!four) {
		for (int i = 0;i<3;i++) {
			k = i;
			it1 = mano.begin();
			it2 = mano.begin();
			advance(it1, k);
			advance(it2, k + 1);
			while (k<(i + 2) && ((*it1)->getValor() == (*it2)->getValor()))
				k++;
			if (k == i + 2) {
				three = 1;
				it1 = mano.begin();
				advance(it1, i);
				big = (*it1)->getValor();
				if (i == 0) {
					it1 = mano.begin();
					it2 = mano.begin();
					advance(it1, 3);
					advance(it2, 4);
					if ((*it1)->getValor() == (*it2)->getValor())
						full = 1;
				}
				else if (i == 1) {
					it1 = mano.begin();
					it2 = mano.begin();
					advance(it1, 0);
					advance(it2, 4);
					if ((*it1)->getValor() == (*it2)->getValor())
						full = 1;
				}
				else {
					it1 = mano.begin();
					it2 = mano.begin();
					advance(it1, 0);
					advance(it2, 1);
					if ((*it1)->getValor() == (*it2)->getValor())
						full = 1;
				}
			}
		}
	}

	if (straight&&flush) {
		it1 = mano.begin();
		advance(it1, 4);
		return 170 + (*it1)->getValor();
	}
	else if (four) {
		return 150 + big;
	}
	else if (full) {
		return 130 + big;
	}
	else if (flush) {
		return 110;
	}
	else if (straight) {
		it1 = mano.begin();
		advance(it1, 4);
		return 90 + (*it1)->getValor();
	}
	else if (three) {
		return 70 + big;
	}

	/* checks for pairs*/
	for (k = 0;k<4;k++) {
		it1 = mano.begin();
		it2 = mano.begin();
		advance(it1, k);
		advance(it2, k + 1);
		if ((*it1)->getValor() == (*it2)->getValor()) {
			two++;
			if ((*it1)->getValor() > big) {
				big = (*it1)->getValor();
			}
		}
	}

	if (two == 2) {
		return 50 + big;
	}
	else if (two) {
		return 30 + big;
	}
	else {
		it1 = mano.begin();
		advance(it1, 4);
		return (*it1)->getValor();
	}
}

Administrador::~Administrador() {

}