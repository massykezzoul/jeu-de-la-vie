#include <unistd.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <exception>
#include "../cellule/cellule.h"
#include "../configuration/configuration.h"
#include "../option/option.h"
#include "population.h"

using namespace std;


#define VERIFIER_EXISTANCE(i,j) \
	if ((i >= dimension) || (j >= dimension)) { \
		cout<<"Accessing a Cell at ("<<i<<","<<j<<") out of range...";	\
		terminate(); \
	}

// revoie vrai si les deux population sont égaux
bool operator==(Population const& pop1,Population const& pop2) {
	return pop1.est_egal(pop2);
}

bool operator!=(Population const& pop1,Population const& pop2) {
	return !(pop1 == pop2);
}


const Cellule* Population::at(size_t i, size_t j) const {
  for (size_t k = 0 ; k < alive ; k++) {
    if ((T[k].get_x() == i) && (T[k].get_y() == j)) {
      return T+k;
    }
  }
  return NULL; /* La cellule n'existe pas dans le tableau */
}

Cellule* Population::at(size_t i, size_t j)  {
  for (size_t k = 0 ; k < alive ; k++) {
    if ((T[k].get_x() == i) && (T[k].get_y() == j)) {
      return T+k;
    }
  }
  return NULL; /* La cellule n'existe pas dans le tableau */
}

// Tuer une Cellule 
void Population::kill(size_t i,size_t j) {
	VERIFIER_EXISTANCE(i,j);
	Cellule* ptr=at(i,j);
	if (ptr!=NULL) {
    	size_t k=ptr-T; // retrouve la position de la cellule dans le tableau
		for ( ; k < alive - 1 ; k++) {
			T[k]=T[k+1]; // Decale la position des cellules
		}
		alive--;
	}
}
// Faire vivre une Cellule 
void Population::birth(size_t i,size_t j) {
	if (alive+1< dimension * dimension){
		VERIFIER_EXISTANCE(i,j);
		Cellule* ptr=at(i,j);
		if (ptr==NULL) {
			//la cellule n'existe pas dans le tableau
			push_back(Cellule(true,i,j));
		}
		else{
			// La cellule existe dans le tableau
			ptr->set_vivante(true);
		}
  	}
 	else {
		cerr<<"Population: Erreur -> trop de cellule vivante pour une dimension de ="<<dimension<<endl;
		cerr<<"aborting...\n";
		terminate();
	}
}

//Indique le nombre de Cellule de couleur c dans la population

size_t Population::nb_cellule(Couleur c) const {
	size_t cpt=0;
  for (size_t i = 0 ; i < alive ; i++) {
      if (CelluleEstDeLaCouleur(T[i],c)) {
		cpt++;
      }    
  }
  return cpt;
}

// Extension du tableau 
void Population::extend() {
	if (alive >= alloc){
		alloc *= 2;
		Cellule* tmp = new Cellule[alloc];
		for(size_t i = 0; i < alive; i++) {
			tmp[i] = T[i];
		}
		delete[] T;
		T = tmp;
	}
}

// Supprime une cellule du tableau
void Population::erase(Cellule* cel) {}

// Rajoute une cellule vivante au tableau
void Population::push_back(const Cellule cel) {
	extend();
	T[alive] = cel;
	++alive;
}

// Calcule les nouvelles couleur des cellules

void Population::update_color() {
	for (size_t k = 0; k < alive; ++k){
		int voisines = nb_voisines(T[k].get_x(),T[k].get_y());
		Couleur c = T[k].get_couleur();
		if(T[k].get_vivante()) {
			if (c == BLEU) {
				//La cellule vient de naitre 
				if ((voisines != 2) && 	(voisines != 3))
					T[k].set_color(JAUNE); // meurent au prochain tour
				else if ((T[k].get_age() > 0)) {
					T[k].set_color(VERT); // Age > 0
				}
			} else if ( (c == VERT) && (voisines != 2) && (voisines != 3) ) {
				//Meurent au prochain tour 
				T[k].set_color(ROUGE);
			}
		}
	}				
}

// Constructeur
// Initialisation avec les valeurs par défault
Population::Population()
	:T(new Cellule[1]),generation(1),alive(0),alloc(1),probability(0.25),dimension(10),graine(0),speed(100000) {
}

Population::Population(int argc,const char** argv)
	:T(new Cellule[1]),generation(1),alive(0),alloc(1),probability(0.25),dimension(10),graine(0),speed(100000) {
	Option_tab tableau;
	int i = 1;
	int j = -1;
	float proba = -1;
	int dimension = -1;
	int speed = -1;
	string config = "";

	while (i < argc) {
		j = -1;
		if (tableau.is_nom(argv[i])) {
			// Est une option avec son nom long spécifié
			j = tableau.get_option(tableau.cherche(&argv[i][2]));
		} else if (tableau.is_raccourci(argv[i])) {
			// Est une option avec son raccourci spécifié
			j = tableau.get_option(tableau.cherche(argv[i][1]));
		}

		switch (j) {
			case 0:
				/* help */
				affiche_help();
				exit(0);
				break;
			case 1:
				/* version */
				affiche_version();
				exit(0);
				break;
			case 2:
				/* dimension */
				if ( (i + 1 < argc)  &&  (argv[i+1][0] != '-') ) {
					++i; // passe à l'argument de l'option
					dimension = strtod(argv[i],NULL); // recupere l'entier
				} else {
					cerr << "Argument manquant pour '" << argv[i] <<"'"
						<< endl;
				}	
				break;
			case 3:
				/* config */
				if ((i + 1 < argc)  &&  (argv[i+1][0] != '-')) {
					++i; // passe à l'argument de l'option
					config = argv[i]; // recupere la chaine
				} else {
					cerr << "Argument manquant pour '" << argv[i] <<"'"
						<< endl;
				}	
				break;
			case 4:
				/* probability */
				if ((i + 1 < argc)  &&  (argv[i+1][0] != '-')) {
					++i; // passe à l'argument de l'option
					proba = strtod(argv[i],NULL); // recupere l'entier
				} else {
					cerr << "Argument manquant pour '" << argv[i] <<"'"
						<< endl;
				}	
				break;
			case 5:
				/* speed */
				if ((i + 1 < argc)  &&  (argv[i+1][0] != '-')) {
					++i; // passe à l'argument de l'option
					speed = strtod(argv[i],NULL); // recupere l'entier
				} else {
					cerr << "Argument manquant pour '" << argv[i] <<"'"
						<< endl;
				}	
				break;
			default:
				cerr << "L'option \"" << argv[i] 
					<< "\" n'existe pas" << endl;
				break;
			}
			++i;
	}

	if (config != "") {
		// Initialisation avec un fichier de configuration
		string ligne,cle,valeur;
		ifstream file(config.c_str());
		if(file) {
			while (getline(file,ligne))
				if ( extraire_cle_valeur(ligne,cle,valeur) )
					set_cle_valeur(*this,cle,valeur);
		} else
			cerr << "Lecture du fichier de configuration impossible" << endl;
	}

	if (proba != -1) set_probability(proba);
	if (dimension != -1) set_dimension(dimension);
	if (speed != -1) set_speed(speed);
}

/* Constructer par copie */
Population::Population(const Population& pop)
	:T(new Cellule[pop.alloc]),generation(pop.generation)
	,alive(pop.alive),alloc(pop.alloc),probability(pop.probability)
	,dimension(pop.dimension),graine(pop.graine),speed(pop.speed) {
		for (size_t i = 0;i <alive;++i) {
			T[i] = pop.T[i];
		}
	}
/* Destructeur */
Population::~Population(){
	delete[] T;
}

Population& Population::operator=(Population const& pop) {
	if (this != &pop ) {
        delete[] T;
        T = new Cellule[pop.alloc];
        generation = pop.generation;
        alive = pop.alive;
		alloc = pop.alloc;
        probability = pop.probability;
        dimension = pop.dimension;
        graine = pop.graine;
        speed = pop.speed;

        for(size_t j = 0; j < alive; ++j) {
            T[j] = pop.T[j];
        }
    }
    return *this;
}

// Initialisation de la population
void Population::init(size_t g) {
	if (g == 0)
		graine = ( time(NULL) * getpid() );
	else
		graine = g;

	srand(graine);
	size_t i,j;
	size_t nb_a_faire_vivre = (size_t) (probability * dimension * dimension);
	for (size_t k = alive; k < nb_a_faire_vivre ; ++k) {
		do { // Chercher une cellule au hazard tant que cette cellule n'est pas déjà vivante
			i = rand() % dimension;
			j = rand() % dimension;
		} while (at(i,j) != NULL);
		// Une fois la cellule trouvé lui donné la vie
		birth(i,j);
	}
	update_color();
}


// Calcule le prochaine etat de la population
Population Population::next() const {
	Couleur c;
  	Population POP(*this);
  	for (size_t i = 0 ; i < dimension ; i++) {
    	for (size_t j = 0 ; j < dimension ; j++) {
      		size_t voisin = nb_voisines(i,j);
      		if (POP.at(i,j) != NULL )
      			c = POP.at(i,j)->get_couleur();
      		else 
      			c = NOIR;
      		// Kill && Birth && age++
      		if ((c == ROUGE) || (c == JAUNE)) // Mettre en NOIR
      			POP.kill(i,j);
      		else if ((c == NOIR) && (voisin == 3)) // Mettre en Bleu
      			POP.birth(i,j); // La mise en JAUNE se feras à la fin avec l'appel de la fonction update_color()
      		else if ((c==VERT) || (c == BLEU))
      			POP.at(i,j)->age_pp();
    	}
  	}
  	POP.update_color();
  	POP.generation_pp();
  	return POP;
}

void Population::set_probability(float const p) {
	if ((p <= 1) && (p >= 0)){
		probability = p;
	} else 
		cerr << "Erreur: " << p << " n'est une probabilité valable." << endl;
}

void Population::set_dimension(size_t const d) {
	if ((d>0)) {
		dimension = d;
	}
	else
		cerr << "Erreur: " << d << " n'est une dimension valable." << endl;
}

void Population::set_cell(size_t x,size_t y) {
	if (alive+1<dimension) {
		if ( (x <= dimension) && (y <= dimension) && (x >= 1) && (y >= 1)) {
			birth(x-1,y-1);
			/* affichage superful */
			cout << "Cell (" << x << "," << y<<") Est vivante"<< endl; 
		}
		else
			cerr << "Accessing a Cell at (" << x << "," << y << ") out of range..." << endl;
	} else 
		cerr << "Population pleine" << endl;
}

void Population::set_speed(int v) {
	if (v >= 0)
		speed = v;
}

void Population::generation_pp() {
	generation++;
}


// retourne le nombre de voisine vivante d'une cellule donné 

size_t Population::nb_voisines(size_t i,size_t j) const {
	size_t nb = 0;
	size_t m_min = i==0?i:i-1;
	size_t m_max = i==(dimension-1) ?i:i+1;
	size_t n_min = j==0?j:j-1;;
	size_t n_max = j==(dimension-1) ?j:j+1;
		for (size_t m = m_min; m <= m_max; ++m){
			for (size_t k = n_min; k <= n_max; ++k){
				if ( ( at(m,k) != NULL ) && ( (i!=m) || (j!=k))) {
					nb++;
				}
			}
		}
	return nb;
}


// Accesseur en lecture

size_t Population::get_vivante() const {
	return alive;
}
size_t Population::get_morte() const {
	return dimension * dimension - alive;
}
size_t Population::get_new_vivante() const {
	return nb_cellule(BLEU) + nb_cellule(JAUNE);
}
size_t Population::get_va_mourir() const {
	return nb_cellule(ROUGE)+nb_cellule(JAUNE);
}
size_t Population::get_generation() const {
	return generation;
}
size_t Population::get_graine() const {
	return graine;
}
size_t Population::get_dimension() const {
	return dimension;
}
float Population::get_probability() const {
	return probability;
}
int Population::get_speed() const {
	return speed;
}


//renvoie TRUE si la population courante egal à la population passé en paramètre
bool Population::est_egal(Population const& pop) const {
	size_t k = 0;
	if (alive == pop.get_vivante()) {
		while ((k < alive) && 
			(T[k].get_x() == pop.get_cellule(k).get_x() ) && 
			(T[k].get_y() == pop.get_cellule(k).get_y() ) && 
			(T[k].get_couleur() == pop.get_cellule(k).get_couleur())) 
				++k;
		return (k == alive);  
	} else {
		return false;
	}
}

// Affiche la population sous forme de matrice
void Population::affiche_matrice() const {
	cout << "\t+";
		for (size_t k = 0; k < dimension; ++k)
			cout << "---+";
	cout << endl;
	for (size_t i = 0; i < dimension; ++i){
		cout << "\t|";
		for (size_t j = 0; j < dimension; ++j){
			if (at(i,j) != NULL)
				at(i,j)->print_cell();
			else 
				cout << "\033[3"<<(int)NOIR<<"m"<<"   "<< "\033[0m";
			cout << "|";
		}
		cout << endl;
		cout << "\t+";
		for (size_t k = 0; k < dimension; ++k)
			cout << "---+";
		
		cout << endl;
	}	
}

// Affiche la population sous forme de matrice en noir et blanc
void Population::affiche_matrice_bw() const {
	cout << "\t+";
		for (size_t k = 0; k < dimension; ++k)
			cout << "---+";
	cout << endl;
	for (size_t i = 0; i < dimension; ++i){
		cout << "\t|";
		for (size_t j = 0; j < dimension; ++j){
			if (at(i,j) != NULL)
				at(i,j)->print_cell_bw();
			else 
				cout << "\033[3"<<(int)NOIR<<"m"<<"   "<< "\033[0m";
			cout << "|";
		}
		cout << endl;
		cout << "\t+";
		for (size_t k = 0; k < dimension; ++k)
			cout << "---+";
		
		cout << endl;
	}	
}

// Retourne la reference const d'une cellule selon sa position donné en paramètre

Cellule Population::get_cellule(size_t i,size_t j) const {
	VERIFIER_EXISTANCE(i,j);
	const Cellule* ptr = at(i,j);
	if (ptr == NULL)
		return Cellule(false,i,j);
	else
		return *ptr;
}

Cellule Population::get_cellule(size_t k) const {
	return T[k];
}


// Affiche L'evolution de la population jusqu'à sa stabilité
void simulation(Population &popu) {
	size_t vivant_debut = popu.get_vivante();
	size_t dimension = popu.get_dimension();
	int temps_pose = popu.get_speed();
	while ( (popu != popu.next()) && (popu != popu.next().next()) )  {
		cout << "Voici La population de Départ : " << endl << endl;
		popu.affiche_matrice();

		cout << "Pourcentage de vie : " << popu.get_vivante()*100 / (dimension*dimension) <<"%" << endl
			<< "Generation : " << popu.get_generation() << endl
			<< "Matrice de taille : " << dimension << "x" << dimension << endl;
		
		if (popu.get_generation() == 1) {
			cout << "Qliquer sur Entrée pour commencer la Simulation ..." << endl;
			getchar();
		}
		

		popu = popu.next();

		usleep(temps_pose);
	}

	cout << "########################## END OF SIMULATION ##########################" << endl << endl;

	popu.next().affiche_matrice();

	cout << "Fin de la simuation après : " << popu.get_generation() << " Generations."<<endl;
	if (popu.get_vivante() == 0) 
		cout << "Les cellules sont toutes Morte à la fin de cette simulation." << endl;
	else 
		cout << popu.get_vivante() << " Cellule vivantes à la fin." << endl;
	cout << "Soit un Taux d'environ " << (popu.get_vivante()*100) / (dimension*dimension) << "% de vie." << endl;
	cout << endl << "Au Debut de la simulation : " << endl;
 	cout << "La Graine étais : " << popu.get_graine() <<"."<< endl;
	cout << "Matrice de "<<dimension<<"x"<<dimension<<" cases, Soit un total de "<< dimension*dimension<<" Cellules" << endl;
	cout << "Avec "<< vivant_debut <<" Cellule vivante au debut, Contre " << (dimension*dimension) - vivant_debut << " Cellule Morte." << endl;
	cout << "Soit un Taux d'environ " << (vivant_debut*100) / (dimension*dimension) << "% de vie." << endl;
}

/* Lancement d'une simulation pour des statistiques (aucun affichage) */
void simulation(Population &popu,fstream& stat) {
	if (stat) {
		time_t t = time(0);   // get time now
    	tm* now = localtime(&t);
    	stat << "Simulation : " << (now->tm_year + 1900) << '-' 
         		<< (now->tm_mon + 1) << '-'
         		<<  now->tm_mday
         		<< "\n";

		for (int i = 1; i < 100; ++i) {
			popu.init();
			popu.set_probability((float)((float)i/100.0));
			size_t vivant_debut = popu.get_vivante();
			size_t dimension = popu.get_dimension();
			while ( (popu != popu.next()) && (popu != popu.next().next()) )  {
				popu = popu.next();
			}
			stat << dimension << "x" << dimension << " : "
					<< (vivant_debut*100) / (dimension*dimension) << "%\t-> "
					<< popu.get_vivante()*100 / (dimension*dimension) << "%\t,"
					<< "generation = " << popu.get_generation() 
					<< "\t,graine = " << popu.get_graine() << endl;
		}
	} else 
		cerr << "Erreur d'ouverture du fichier " << endl;
}

// affiche les aides du programme
void affiche_help() {
	cout << "Utilisationn: jeu [OPTION] [ARGUMENT] " << endl
		<< "Help à venir..." << endl;
}

// affiche la version du programme
void affiche_version() {
	cout << "jeu_de_la_vie 1.0.0"<< endl;
}
