#ifndef POPULATION_H
#define POPULATION_H

#include "../cellule/cellule.h"

// Largeur de la platforme maximal
#define NB 40	
// Nombre de cellule vivante maximal
#define N NB*NB

class Population {
private:
/* Attributs */

	/* Tableau de celulle contenant que les cellule vivante, les autres sont automatiquement morte */
	Cellule T[N]; 
	/* La generation de la population */
	size_t generation;
	/* Nombre de Cellule Vivante */
	size_t alive;
	/* Probability d'apparition d'une cellule vivante*/
	float probability;
	/* Dimension de la plateforme de Jeu (Dimension * Dimension) */
	size_t dimension;
	/* La graine sert à reproduire d'une simulation précedente	*/
	size_t graine;

/* Methode Privé */

	//Retourne la cellule qui est a la position (i,j)
	Cellule* at(size_t i ,size_t j);
	const Cellule* at(size_t i, size_t j)const;


	//Tue la cellule à la position (i,j)
	void kill(size_t i,size_t j);

	//la cellule à la position (i,j) revient à la vie
	void birth(size_t i,size_t j);

	//Indique le nombre de Cellule de couleur c dans la population
	size_t nb_cellule(Couleur c) const;

	/* 
		Calcule les nouvelles couleur des cellules
	   	Ne gere pas le cellule qui vont mourir et celles qui vont ranaitre
   	 	ceux-là sont géré par la methode next();
	    RQ : update_color() ne fait que mettre en (JAUNE,ROUGE,VERT) si les conditions sont réunis
	*/
	void update_color();
	

public:
/* Methode Publique */
	
	//Constructeur
	Population();

	// Initialiser la population avec un fichier de configuration
	Population(std::ifstream &config);

	//Initialise la population selon la probabilité et la dimension
	void init(size_t graine = 0);

	// Calcule le prochaine etat de la population
	Population next() const;	

	//Setteurs
	void set_dimension(size_t const);

	void set_probability(float const);

	void set_cell(size_t,size_t);

	// increment la variable generation
	void generation_pp();

	//Renvoie le nombre de voisines vivantes d'une cellule donné (i et j etant sa position dans la matrice)
	size_t nb_voisines(size_t i,size_t j) const;

	//Accesseur en lecture
	size_t get_vivante() const;
	size_t get_morte() const;
	size_t get_new_vivante() const;
	size_t get_va_mourir() const;
	size_t get_generation() const;
	size_t get_graine() const;
	size_t get_dimension() const;
	float get_probability() const;

	// Retourne la reference const d'une cellule selon sa position donné en paramètre
	Cellule get_cellule(size_t,size_t) const;
	Cellule get_cellule(size_t k) const;

	//renvoie TRUE si la population courante egal à la population passé en paramètre
	bool est_egal(Population const&) const;

	// Affiche la population sous forme de matrice
	void affiche_matrice() const;
	// Affiche la population sous forme de matrice sans couleur
	void affiche_matrice_bw() const;
	
	// Affiche la cellule à la position (i,j)
	void print_cell(size_t i,size_t j);
};


// Affiche L'evolution de la population jusqu'à sa stabilité
void simulation(Population&,size_t = 300000);
/* Lancement d'une simulation pour des statistiques (aucun affichage) */
void simulation(Population &popu,std::fstream& stat);

// revoie vrai si les deux population sont égaux
bool operator==(Population const& a,Population const& b);
// revoie vrai si les deux population sont différente
bool operator!=(Population const& a,Population const& b);

#endif