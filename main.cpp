#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include "population/population.h"
#include "configuration/configuration.h"

using namespace std;

int main(int argc, char const *argv[])
{
	// Initialisé le jeu selon les arguments donnée en paramétre
	Population jeu(argc,argv);
	jeu.init();
	/*
	jeu.affiche_matrice_bw();
	jeu.affiche_dynamique();

	jeu = jeu.next();

	jeu.affiche_matrice_bw();
	jeu.affiche_dynamique();

	jeu = jeu.next();

	jeu.affiche_matrice();
	jeu.affiche_dynamique();
	*/

	simulation(jeu);

	/* Mode Statistique à regler*/
	//fstream stat("vie.stat",ios::out | ios::app);
	//jeu.begin(stat);

	cout << endl << "############################# END OF PROG #############################" << endl;
	
	return 0;
}
