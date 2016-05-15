/**
* @file Carta.h
* @version 1.0
* @date 07/05/2016
* @author GrupoProgra: Julian Arguedas Torres B50587 - Milton Delgado Fernandez B12188 - Kenneth Walker Fernandez B37663
* @title Clase Carta
* @brief
*/

#pragma once
#include "stdafx.h"
using namespace std;

class Carta {

	friend ostream & operator<<(ostream &, Carta &);

private:
	char numero;
	int valor;
	char palo;

public:
	/**
	* @brief Constructor por parametros de Carta
	* @param numero Numero de la carta
	* @param valor Valor de la carta
	* @param palo Palo de la carta
	*/
	Carta(char numero, int valor, char palo);

	/**
	* @brief Destructor de Carta
	*/
	~Carta();

	/**
	* @brief Valor de la carta
	* @return Entero con el valor de la Carta
	*/
	int getValor() const;

	/**
	* @brief Palo de la carta
	* @return Caracter con el palo de la Carta
	*/
	char getPalo() const;

	/**
	* @brief Numero de la carta
	* @return Entero con el numero de la Carta
	*/
	int getNumero() const;

	/**
	* @brief Sobrecarga del operador '<' para evaluar Carta
	*/
	bool operator<(Carta &);
};

ostream & operator<<(ostream &, Carta &);
