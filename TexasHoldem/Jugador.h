/**
* @file Jugador.h
* @version 1.0
* @date 07/05/2016
* @author GrupoProgra: Julian Arguedas Torres B50587 - Milton Delgado Fernandez B12188 - Kenneth Walker Fernandez B37663
* @title Clase Jugador
* @brief
*/

#pragma once
#include "carta.h"
using namespace std;

class Jugador {

	friend ostream & operator<<(ostream &, Jugador &);

private:

	list <Carta*> manita;

public:

	int disponible;
	char* nombre;
	bool done;

	/**
	* @brief Constructor por parametros de Jugador
	* @param nombre Nombre que se le asignara al jugador
	* @param dinero Cantidad de dinero manejada por el jugador
	*/
	Jugador(char* nombre);
	Jugador(char* nombre, int dinero);

	/**
	* @brief Descuenta el monto apostado al jugador
	* @param monto Valor a descontar del dinero del jugador
	* @return Apuesta
	*/
	int bet(int monto);

	/**
	* @brief Incrementa el dinero del jugador
	* @param monto Valor a otorgar al dinero del jugador
	*/
	void recieveMoney(int monto);

	/**
	* @brief Da una carta al jugador
	* @param carta Puntero de la carta que recibe en jugador
	*/
	void recieve(Carta* carta);

	/**
	* @brief Estado del jugador
	* @return Disponiblidad del jugador
	*/
	bool check();

	/**
	* @brief Devuelve el dinero del jugador
	* @return Dinero disponible del Jugador
	*/
	int getMoney();

	/**
	* @brief Devuelve el nombre del jugador
	* @return Nombre del Jugador
	*/
	char* getName();

	/**
	* @brief Cambia la disponibilidad del jugador
	*/
	void finish();

	/**
	* @brief Imprime por consola al jugador
	*/
	void imprimir();

	/**
	* @brief Cambia la disponibilidad del jugador
	*/
	void reset();

	/**
	* @brief Ordena las cartas del jugador
	*/
	void sort();

	/**
	* @brief Devuelve una carta del jugador
	* @return Puntero a carta del jugador
	*/
	Carta* getCarta();

	/**
	* @brief
	* @return
	*/
	list<Carta*> returnHand();

	/**
	* @brief Destructor de Jugador
	*/
	~Jugador();
};
