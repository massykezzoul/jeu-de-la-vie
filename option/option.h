#ifndef OPTION_H
#define OPTION_H

class Option {
public:
	enum Id {
		HELP = 0,
		VERSION,
		DIMENSION,
		CONFIG,
		PROBABILITY,
		SPEED,
		NB_ID
	};

	enum Arg {
		INT = 0,
		FLOAT,
		CHAR,
		STR,
		NOPE,
		NB_ARG
	};

private:
	Id identifiant;
	std::string nom; 		 // intitulé 
	char racourci; 
	Arg argument;    		 // Le type eventuelle de son argument 
	std::string description; // Description de ce que fait l'option


public:
	Option();
	Option(Id,const std::string&,char,Arg,const std::string&);

	//Constructeur par copie
	Option(Option const &copy);

	Id get_identifiant() const;
	std::string get_nom() const;
	char get_racourci() const;
	Arg get_argument() const;

	std::string get_description() const;

	//Affiche l'option 
	void print() const;

	void set_identifiant(Id);
	void set_nom(const std::string&);
	void set_racourci(char);
	void set_argument(Arg);
	void set_description(const std::string&);

	//Surcharge de l'operateur d'affectation
	Option operator=(Option const&);

};

/* ---------------------------------------------------- */
/* La Classes Option_tab qui est un tableau d'option 	*/

#define OPTION_TAB_MAX 10

class Option_tab {
private:
	size_t nb;
	Option tab[OPTION_TAB_MAX];

public:
	// Définitions des options prise en charge
	Option_tab();

	//Permet d'ajouter une Option au tableau
	void add(const Option &opt);

	//Afficher les options enregistrées dans le tableau
	void print() const;

	//Renvoie l'identifiant de l'option dont le nom est donné en paramètre
	Option::Id cherche(const std::string &nom) const;

	//Renvoie l'identifiant de l'option dont le racourci est donné en paramètre
	Option::Id cherche(const char rac) const;

	//Renvoie Vrai si la chaine est un nom d'une option
	bool is_nom(std::string) const;

	//Renvoie Vrai si la chaine est un raccourci d'une option
	bool is_raccourci(std::string) const;

	/*Etant donné un nom (court ou long) d’option, si un argument est requis 
	et son type le cas échéant. */  
	Option::Arg get_argument(const std::string &nom) const;

    Option::Arg get_argument(const Option::Id) const;

	// Return l'index de l'option selon son identifiant (retourne -1 si n'existe pas)
	int get_option(const Option::Id id);

	// Prend la position d'une option dans le tableau et retourne cette option
	Option const &get_option(int index);

	/*
		La méthode qui sera Utilisé par le programme principal
		Donnée 	: la population, argc le nombre d'argument du programme, et argv l'ensembre des arguments du programme principal
		Resultat: Applique les modifications fournit en arguments
	*/
	void gere_parametre(int argc,char const *argv[]);

};

// Définitions des options prise en charge et retourne le tableau de ces options

#endif 