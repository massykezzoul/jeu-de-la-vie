#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cctype>
#include "convert/convert.h"
#include "../population/population.h"
#include "configuration.h"

using namespace std;

/* -------------------------------------------------------------------------- */

/* testé maybe */
string nettoyer_ligne(string ligne) {
	// ligne sans commentaire
	string sans_comment = ligne;
	sans_comment = sans_comment.substr(0,sans_comment.find_first_of("#"));
	//supprimer les espaces en plus
	//supprimer les espaces en debut de chaine
	while (sans_comment[0] == ' ')
		sans_comment.erase(0,1);

	//supprimer les espaces au mileux de chaine
	unsigned int i = 1;
	while (i < sans_comment.size()) {
		if ((sans_comment[i] == ' ') && (sans_comment[i-1] == ' '))
			sans_comment.erase(i,1);
		else 
			++i;
	}

	//suprimer les espaces en fin de chaine 
	while (sans_comment[sans_comment.size()-1] == ' ')
		sans_comment.erase(sans_comment.size()-1,1);

	return sans_comment;
}

/* -------------------------------------------------------------------------- */

/* Testé */
string get_chaine(string ligne,size_t i) {
	size_t debut,fin;
	debut = i;
	while(ligne[debut] == ' ')
		++debut;

	fin = ligne.find_first_of(" ",debut);
	return ligne.substr(debut,fin-debut);
}

/* -------------------------------------------------------------------------- */

/* testé */
bool verif_valeur(string cle,string valeur) {
	int x,y;
	if ((cle == "Probability") && (isFloat(valeur)))
		return true;
	else if ((cle == "Dimension" && (convert(valeur) > 0)))
		return true;
	else if ((cle == "Cell" && (decode_cell(valeur,x,y))))
		return true;
	else 
		return false;
}

/* -------------------------------------------------------------------------- */

/* Testé */
bool decode_cell(string valeur,int& x,int& y) {
	int i= 0;

	if (!isdigit(valeur[0]))
		return false;

	++i;

	while( (i<valeur.size() ) && (isdigit(valeur[i])))
		++i;
	
	x = convert(valeur.substr(0,i));

	if( (valeur[i] != 'X') && (valeur[i] != ',') && (valeur[i] != 'x') && (valeur[i] != ' '))
		return false;
	else {

		y = convert(valeur.substr(++i));

		if (y == -1)
			return false;
		else 
			return true;	
	}
}

/* -------------------------------------------------------------------------- */

bool extraire_cle_valeur(string ligne,string& cle,string& valeur) {
	ligne = nettoyer_ligne(ligne);
	/* trouver la clé */
	cle = get_chaine(ligne);
	/* Il faut vérifié que la clé est conforme */
	/* trouver les deux points */
	if (get_chaine(ligne,cle.size()) != ":") {
		cle = "";
		valeur = "";
		return false;
	} else {
		int debut = cle.size()+ 3;
		valeur = ligne.substr(debut,ligne.find_first_of(debut)-debut);
		/* il faut verifier que la valeur est correcte par rapport à la clé */
		if (verif_valeur(cle,valeur)) {
			return true;
		} else {
			cle = "";
			valeur = "";
			return false;
		}
	}
}

/* -------------------------------------------------------------------------- */

void set_cle_valeur(Population& pop,string const cle,string const valeur) {
	if (cle == "Probability")
		pop.set_probability(atof(valeur.c_str()));
	else if (cle == "Dimension")
		pop.set_dimension(convert(valeur));
	else if (cle == "Cell") {
		int x,y;
		if (decode_cell(valeur,x,y))
			pop.set_cell(x,y);
	}
}
/* -------------------------------------------------------------------------- */