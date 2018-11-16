#ifndef CONVERT_H
#define CONVERT_H

int convert(std::string);
/*
	Convertir la chaine en un nombre entier positif
	Si la chaine ne contient pas que des entier non séparé la fonction renvoie -1 (qui est donc une erreur)
*/

/* ------------------------------------ */

int convert_char(char);
/*
	Pareil que convert(string) mais que pour un seul caractère 
*/

/* ------------------------------------ */

size_t dix_puiss(int);
/*
	Renvois 10 Puissance int
*/

/* ------------------------------------ */

int nbr_char(size_t);
/*
	Renvoie le nombre de chiffre dans l'argument donné en paramètre (arg >= 0)
*/

/* ------------------------------------ */

char inv_convert_char(int c);
/*
	Contraire de convert_char(c)
*/

/* ------------------------------------ */

/* thanks Stackoverflow */
bool isFloat( std::string myString );


#endif