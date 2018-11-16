#ifndef _CELLULE_H
#define _CELLULE_H

// Gestion de couleur
enum Couleur {
	NOIR, // Morte = 0
	ROUGE,// Va mourir en prochain tour = 1
	VERT, // En Vie = 2
	JAUNE,// Revient tout juste à la vie && Va mourir en prochain tour = 3
	BLEU, // Revient tout juste à la vie = 4
	NB_COULEUR = JAUNE - NOIR// nombre de couleur
};

std::string couleur2string(Couleur c);

class Cellule {
private:
	/* Définit aussi son etat (vivante ou morte)*/
	Couleur couleur; 
	/* la position de la cellule */
	size_t x;
	size_t y;
	/* Son age */
	size_t age;

public:
	// Constructeur
	Cellule(bool,size_t,size_t);
	Cellule(); // Morte par défault

	// Accesseur en lecture 
	bool get_vivante() const;
	bool est_voisine(Cellule) const;
	size_t get_x() const;
	size_t get_y() const;
	Couleur get_couleur() const;
	size_t get_age() const;

	//Affiche l'etat de la cellule et sa couleur 
	void print_cell() const;
	//Affiche l'etat de la cellule en noir et blanc
	void print_cell_bw() const;
 
	// Spécifie si une cellule doit mourire au prochain tour --> (changement de couleur)
	void doit_mourir();

	//Renvoi True si la Cellule est de la couleur c
	bool est_couleur(Couleur c) const;

	// Accesseur en Ecriture
	
	void set_vivante(bool);
	void set_x(size_t);
	void set_y(size_t);
	void age_pp();
	void set_color(Couleur);
};


// Renvoie vrai si la cellule est de la couleur passée en paramètre, faux sinon.
bool CelluleEstDeLaCouleur(const Cellule &cellule, Couleur couleur);


#endif