#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include "population/population.h"
#include "configuration/configuration.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/*
		Lecture du fichier de configuration
	 */
	string nom_fichier("config");

	ifstream file(nom_fichier.c_str(),ios::in);

	Population jeu(file);
	
	/* Mode affichage */
	jeu.init();
	simulation(jeu,100000);

	/* Mode Statistique à regler*/
	//fstream stat("vie.stat",ios::out | ios::app);
	//jeu.begin(stat);

	cout << endl << "############################# END OF PROG #############################" << endl;
	
	return 0;
}
