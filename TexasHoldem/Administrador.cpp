#include "stdafx.h"
#include "Administrador.h"
#include <iostream>

using namespace std;

Administrador::Administrador()
{
}

void Administrador::iniciarJuego() {
	bool hecho = false;
	cout << "Super Poker Stars - Battle Royale. - Inserta cualquier valor numerico!" << endl;
	int efectivo = 0;
	while (hecho == false) {
		cin >> efectivo;
		if (cin.fail()) {
			cout << "Por favor usa un numero entero." << endl;
		}
		else {
			hecho = true;
		}
	}
	hecho = false;
	cout << ("Elige la cantidad de dinero de cada jugador - Minimo de 100.") << endl;
	while (hecho == false) {
		cin >> efectivo;
		if (cin.fail()) {
			cout << "Por favor usa un numero entero." << endl;
		}
		else if (efectivo < 100) {
			cout << "al menos un valor de 100 es requerido." << endl;
		}
		else {
			hecho = true;
		}
	}
	hecho = false;
	int numero = 0;
	bool terminado = false;
	while (terminado == false) {
		cout << "Elige la cantidad de jugadores." << endl;
		while (hecho == false) {
			cin >> numero;
			if (cin.fail()) {
				cout << "Por favor usa un numero entero." << endl;
			}
			else {
				hecho = true;
			}
		}
		hecho = false;
		if (numero < 2) {
			cout << "al menos 2 jugadores son requeridos." << endl;
		}
		else {
			if (numero > 10) {
				cout << "Solo un maximo de 10 jugadores pueden unirse." << endl;
			}
		}
		if (numero >= 2 && numero <= 10) {
			terminado = true;
		}
	}
	char nombre[200];
	char *p = nombre;
	cin.getline(p, 200);
	cout << "Elege el nombre de los jugadores." << endl;
	for (int i = 0; i < numero; ++i) {
		cout << "Jugador: " << i+1 << endl;
		p = nombre;
		cin.getline(p, 200);
		this->juego.push_back(new Jugador(nombre, efectivo));
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

	for (int j = 0; j < 3 && juego.size() > 1; ++j) {
		preguntar();
		if (j <= 1) {
			poner();
		}
	}

	Jugador* winner = calcular();
	cout << "El ganador es: " << winner->getName() << " con:" << endl;
	this->imprimir();
	winner->imprimir();
	this->juego.clear();
	this->mesa.clear();
	delete mano;
}

void Administrador::poner() {
	Carta* tmp = this->mano->getCarta();
	this->mesa.push_front(tmp);
	for (list<Jugador *>::iterator it = this->juego.begin(); it != this->juego.end(); ++it) {
		(*it)->reset();
	}
	this->mesa.sort();
}

void Administrador::preguntar() {
	int opcion = 0;
	bool settled = false;
	int j = juego.size();
	while (settled == false) {
		for (list<Jugador *>::iterator it = this->juego.begin(); it != this->juego.end(); ++it) {
			bool done = (*it)->check();
			if (!done) {

				// TODO Esto debería ser parte de un jugador humano!!!

				if ((*it)->getMoney() > (apuestaMinima - 1)) {
					cout << "Que vas a hacer? " << (*it)->getName() << " - 0 = Apostar, 1 = Salir, inserta cualquier otro numero para suspender, - Dinero: " << (*it)->getMoney() << " - El mimimo es: " << apuestaMinima << " - Tus cartas:" << endl;
					(*it)->imprimir();
					cout << " - Mesa: ";
					this->imprimir();
					cout << endl;
					cin >> opcion;
					switch (opcion) {
					case 0:
					{
						(this)->apostar(*it);
						(*it)->finish();
						break;
					}
					case 1:
					{
						cout << "Adios... - " << (*it)->getName() << endl;
						juego.erase(it);
						it = juego.begin();
						break;
					}
					}
				}
				else {
					cout << "Se te acabo el dinero, estas fuera!" << (*it)->getName() << endl;
					juego.erase(it);
					it = juego.begin();
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

void Administrador::apostar(Jugador* it) {
	int bet = 0;
	cout << "Cuanto apostaras? " << (it)->getName() << " - El minimo es " << apuestaMinima << endl;
	bool hecho = false;
	while (hecho == false) {
		cin >> bet;
		if (bet >= apuestaMinima) {
			(it)->bet(bet);
			apuestaMinima = bet;
			lote = lote + bet;
			hecho = true;
		}
		else {
			cout << "Debes apostar una suma mayor!" << endl;
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
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();

	int flush = 0;
	int straight = 0;
	int four = 0;
	int three = 0;
	int two = 0;
	int full = 0;
	int big = 0;
	int k = 0;

	/*checks for flush*/
	flush = this->flush(mano);

	/* checks for straight*/
	straight = this->straight(mano);

	/* checks for fours */
	four = this->four(mano);
		if (four == 1) {
			big = this->big(mano, 4);
		}

	/* checks for threes */
	if (!four) {
		three = this->full(mano);
		if (three == 1) {
			big = this->big(mano, 3);
		}
	}

	/* checks for fullhouse */
	if (three == 1) {
		full = this->full(mano);
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
	two = this->pair(mano);
	if (two != 0) {
		for (k = 0;k<4;k++) {
			it1 = mano.begin();
			it2 = mano.begin();
			advance(it1, k);
			advance(it2, k + 1);
			if ((*it1)->getValor() == (*it2)->getValor()) {
				if ((*it1)->getValor() > big) {
					big = (*it1)->getValor();
				}
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

int Administrador::straight(list<Carta*> mano) {
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	int straight = 0;
	int k = 0;
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
	return straight;
}

int Administrador::four(list<Carta*> mano) {
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	int k = 0;
	int four = 0;
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
		}
	}

	return four;
}

int Administrador::big(list<Carta*> mano, int numero) {
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	//four
	int big = 0;
	int k = 0;
	if (numero == 4) {
		for (int i = 0;i < 2;i++) {
			k = i;
			while (k < i + 3 && ((*it1)->getValor() == (*it2)->getValor()) - 1)
				k++;
			it1 = mano.begin();
			it2 = mano.begin();
			advance(it1, k);
			advance(it2, k + 1);
			if (k == i + 3) {
				it1 = mano.begin();
				advance(it1, i);
				big = (*it1)->getValor();
			}
		}
	}

	//three
	if (numero == 3) {
		for (int i = 0;i < 3;i++) {
			k = i;
			it1 = mano.begin();
			it2 = mano.begin();
			advance(it1, k);
			advance(it2, k + 1);
			while (k < (i + 2) && ((*it1)->getValor() == (*it2)->getValor()))
				k++;
			if (k == i + 2) {
				it1 = mano.begin();
				advance(it1, i);
				big = (*it1)->getValor();
			}
		}
	}
	return big;
}

int Administrador::three(list<Carta*> mano) {
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	int k = 0;
	int three = 0;
	k = 0;
	it1 = mano.begin();
	it2 = mano.begin();
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
		}
	}
	return three;
}

int Administrador::full(list<Carta*> mano) {
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	int full = 0;
	int k = 0;
	mano.sort();
	for (int i = 0;i<3;i++) { // TODO <-- Usar un iterator
		k = i;
		it1 = mano.begin();
		it2 = mano.begin();
		advance(it1, k); // TODO Avanzar con ++
		advance(it2, k + 1);
		while (k<(i + 2) && ((*it1)->getValor() == (*it2)->getValor()))
		++k;
		if (k == i + 2) {
			//three
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
	return full;
}

int Administrador::flush(list<Carta*> mano) {
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	int k = 0;
	int flush = 0;
	++it2;
	while (k<4 && ((*it1)->getPalo() == (*it2)->getPalo())) {
		k++;
		++it1;
		++it2;
		if (k == 4)
			flush = 1;
		break;
	}
	return flush;
}

int Administrador::pair(list<Carta*> mano) {
	list<Carta*>::iterator it1 = mano.begin();
	list<Carta*>::iterator it2 = mano.begin();
	int two = 0;
	int k = 0;
	for (k = 0;k<4;k++) {
		it1 = mano.begin();
		it2 = mano.begin();
		advance(it1, k);
		advance(it2, k + 1);
		if ((*it1)->getValor() == (*it2)->getValor()) {
			two++;
		}
	}
	return two;
}

Administrador::~Administrador() {

}