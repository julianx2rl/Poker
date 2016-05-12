#include "stdafx.h"
#include "Administrador.h"
#include <iostream>

using namespace std;

Administrador::Administrador()
{
}

void Administrador::iniciarJuego(int numero) {
	if (numero < 2) {
		numero = 2;
		cout << "al menos 2 jugadores son requeridos" << endl;
	}
	if (numero > 10) {
		numero = 10;
		cout << "Solo un maximo de 10 jugadores pueden unirse" << endl;
	}
	list<Jugador*> juego;
	list <Carta*> mesa;
	int value = numero;
	Baraja mano;
	mano.barajarCartas();
	for (int j = 0; j < value; ++j) {
		juego.push_front(new Jugador());
	}
}

void Administrador::reparto() {

for (int j = 0; j < 10; ++j) { //Pasa por los diez jugadores.
		for (int i = 0; i < 2; ++i) { //Le da dos cartas a cada uno
			Carta* tmp = mano.getCarta();
			list<Jugador*>::iterator it = juego.begin();
			advance(it, j);
			(*it) -> recieve(tmp);
		}
	}
}

void Administrador::imprimir() {
	for (list<Carta *>::iterator it = mesa.begin(); it != mesa.end(); ++it) {
		cout << **it;
	}
}

void Administrador::jugar() {
	for (int j = 0; j < 3; ++j) {
		poner();
	}
	preguntar();
	poner();
	preguntar();
	poner();
	preguntar();

	Jugador* winner = calcular();
	cout << "The winner is: " << (winner)->getName() << "° Player";
}

void Administrador::poner() {
	Carta* tmp = mano.getCarta();
	mesa.push_front(tmp);
}

void Administrador::preguntar() {
	int opcion = 0;
	this->imprimir();
	bool settled = true;
	int j = juego.size();
	while (settled = false) {
		for (int i = 0; i < j; ++i) {
			list<Jugador*>::iterator it = juego.begin();
			advance(it, i);
			bool done = (*it)->check();
			if (done = false) {
				cout << "What will you do? player " << (*it)->getName() << " 0 = bet, 1 = check, 2 = fold, - Your money is" << (*it)->getMoney() << "and your deck is:" << endl;
				(*it)->imprimir();
				this->imprimir();
				cout << endl;
				cin >> opcion;
				switch (opcion) {
				case 0:
				{
					int bet = 0;
					cout << "How much will you bet?" << j << "The minimum is" << apuestaMinima;
					cin >> bet;
					int tol = (*it)->bet(bet);
					if (tol >= apuestaMinima) {
						lote = lote + bet;
						(*it)->finish();
					}
					else {
						if ((*it)->getMoney() > (apuestaMinima - 1)) {
							cout << "You have to deal more than that!";
							(*it)->recieveMoney(bet);
							(*it)->bet(apuestaMinima);
							lote = lote + bet;
							(*it)->finish();
						}
						else {
							cout << "You're out" << j;
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
					cout << "Good Bye..." << j;
					juego.erase(it);
				}
				break;
				}
			}
		}
		for (int p = 0; p < j; ++p) {
			list<Jugador*>::iterator it = juego.begin();
			advance(it, p);
			settled = (*it)->check();
			if (settled = false) {
				break;
			}
		}
	}
}

Jugador* Administrador::calcular()
{
	int winner = 0;
	list<Jugador*>::iterator tamizake = juego.begin();
	Jugador* tam = (*tamizake);
	list<Carta*> manotmp;
	Carta* tmp;
	mesa.sort();
	for (int i = 0; i < 3; ++i) {
		list<Carta*>::iterator it = mesa.begin();
		advance(*it, i);
		tmp = (*it);
		manotmp.push_front(tmp);
	}
	for (int j = 0; j < 10; ++j) {
		list<Jugador*>::iterator ito = juego.begin();
		advance(ito, j);
		list<Carta*> manitatmp = (*ito)->returnHand();

		for (list<Carta*>::iterator ite = manitatmp.begin(); ite != manitatmp.end(); ++ite) {
			tmp = (*ite);
			manotmp.push_front(tmp);
		}
		manotmp.sort();
		int fag = valorJugada(manotmp);
		if (fag > winner) {
			tam = (*ito);
			winner = fag;
			list<Carta*>::iterator killer = manotmp.begin();
			for (int u = 0; u < 3; ++u) {
				manotmp.erase(killer);
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
		advance(it2, k+1);
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
