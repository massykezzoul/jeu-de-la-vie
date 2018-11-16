#include <iostream>
#include "cellule.h"

using namespace std;

//Fonctions 

string couleur2string(Couleur couleur) {
	switch(couleur) {
		case NOIR:
			return "NOIR";
			break;
		case ROUGE:
			return "ROUGE";
			break;
		case VERT:
			return "VERT";
			break;
		case JAUNE:
			return "JAUNE";
			break;
		case BLEU:
			return "BLEU";
			break;
		default:
			return "NON_DEFINIT";
	}
}

/*
Class Cellule
 */

// Constructeur
Cellule::Cellule(bool b,size_t x,size_t y):x(x),y(y),age(0) {
	if (b)
		couleur = BLEU;
	else 
		couleur = NOIR;
}

Cellule::Cellule():x(0),y(0),age(0) {
	couleur=NOIR;
}

// Accesseur en lecture 
bool Cellule::get_vivante() const{
	if (couleur == NOIR)
		return false;
	else 
		return true;
}
bool Cellule::est_voisine(Cellule c) const {
	return (c.get_vivante()) && ( ( (x - c.get_x())*(x - c.get_x()) + (y - c.get_y())*(y - c.get_y()) ) <= 2);
}
size_t Cellule::get_x() const {
	return x;
}
size_t Cellule::get_y() const {
	return y;
}
Couleur Cellule::get_couleur() const {
	return couleur;
}
size_t Cellule::get_age() const {
	return age;
}


void Cellule::print_cell() const {
	cout << "\033[4"<<(int)couleur<<"m"<<"   "<< "\033[0m";
}

void Cellule::print_cell_bw() const {
	cout << "\033[47m"<<"   "<< "\033[0m";
}


// Spécifie si une cellule doit mourire au prochain tour --> (changement de couleur)
void Cellule::doit_mourir() {
	if (get_age() > 0)
		couleur = ROUGE;
	else 
		couleur = JAUNE;
}

bool Cellule::est_couleur(Couleur c) const {
	return couleur == c;
}

// Accesseur en Ecriture
	
void Cellule::set_vivante(bool b) {
	if (b)
		couleur = BLEU; // la gestion du JAUNE est implementé dans population.cpp (methode update_color())
	else {
		couleur = NOIR; // NOIR = Morte , age est remit à zero
		age = 0;
	}
}

void Cellule::set_x(size_t x) {
	this->x = x;
}
void Cellule::set_y(size_t y) {
	this->y = y;
}

void Cellule::age_pp() {
	++age;
}

void Cellule::set_color(Couleur c) {
	couleur = c;
}

bool CelluleEstDeLaCouleur(const Cellule &cellule, Couleur couleur) {
  return (cellule.get_couleur() == couleur);
}
