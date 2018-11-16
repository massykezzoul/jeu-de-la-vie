#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../population/population.h"

/*
	Ce fichier sert à gérer le fichier de configuration et de l'utiliser pour
		initialiser correctement la population initiale
 */


std::string nettoyer_ligne(std::string ligne);
/*
	on enleve les espaces inutiles et les commentaires de la ligne donnée en paramètre
	utilise les fonctions suivantes de la class string : 
	int find_first_of(std::string ensemble_de_carcatère) -> renvoie la premiére occurences d'un des carctère present dans ensemble_de_carcatère
												renvoie std::string::npos si non trouvé
	std::string substr(size_t debut, size_t n) -> permet de récupérer la sous-chaine formé des n caractères à
												partir de la position debut. (Rq : si on ne donne pas le nombre de caractère, 
												tous les caractères restants seront récupérés)
*/
 	
std::string get_chaine(std::string ligne,size_t i = 0);
/*
	Extrait à partir de la chaine donné en paramètre, le premier mot trouvé 
	à partir de i, (par défault i = 0)
*/
 
bool verif_valeur(std::string cle,std::string valeur);
/*
	renvoie true si la valeur est aproprié à la clé donnée
	par exemple : 	si cle = "Probability" et valeur est un float alors la methode renvoie true
					si cle = "Dimension" et valeur est un float ou un string alors la methode renvoie false 
*/
 	
bool decode_cell(std::string valeur,int& x,int& y);
/*
	Données  : 	valeur qui vient après la clé "Cell",
	Resultats: 	Vrai si est dans le format "01x02" || "01 02" || "01,02"
									Renvoie ^x=01  &&     ^y=02
 			Faux sinon
*/


bool extraire_cle_valeur(std::string ligne,std::string& cle,std::string& valeur);
/*
	Renvoie true si le couple 'cle : valeur' existe 
	renvoie false sinon et les chaines cle,valeur seront vide
*/
	
void set_cle_valeur(Population& pop,std::string const cle,std::string const valeur);
/*
	Données	:	la cle et sa valeur
	Resultat:	Applique, selon la clé, la valeur à la variable du programme qui convient
	Example : 	si cle = "Probability" alors la variable probabilité va recevoir la valeur 'valeur'
*/
	

#endif