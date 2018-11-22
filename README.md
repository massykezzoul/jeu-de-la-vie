# Jeu de la vie

## Information Géneral

Ce programme est l'implementation du jeu de la vie en C++.
Le jeu de la vie est le plus connu des automate cellulaire et a été imaginé par <a href="https://fr.wikipedia.org/wiki/John_Horton_Conway">Jhon Horton Conway</a> en 1970.
Malgré son nom, le jeu de la vie n'est pas un jeu au sens ludique du terme car il ne nécessite aucun joueur.
Pour plus d'information <a href="https://fr.wikipedia.org/wiki/Jeu_de_la_vie">Wikipédia</a>.<br>
Les Règles sont décrtite <a href="https://fr.wikipedia.org/wiki/Jeu_de_la_vie#R%C3%A8gles">Ici</a>.

### Remarque 
Une recherche Google des termes [`Conway's game of life`](https://www.google.com/search?q=conway%27s+game+of+life), fait apparaître un jeu de la vie en arrière-plan.

## Utilisation

L'utilisation du programme : 
- Compiler avec `make all`
- Executer sans paramètre avec `./jeu`
- Executer avec paramètre `./jeu paramètres`
- Les paramètre disponible sont précisé plus loin dans ce README ou en executant `./jeu -h` ou `./jeu --help`

Cette version prend en charge la modification :
- De la dimension du plateau de jeu.
- De la probabilité d'apparition d'une cellule vivante.
- Création d'une ou plusieurs cellule vivante à des position spécifié.

Ces modification peuvent se faire par deux méthodes, soit en appelant le programme avec des paramètres (liste des paramètre precisé un peu plus loin). Mais cette méthode ne prend pas en charge la création des cellule dans une position donnée.
Soit en écrivant dans le fichier [Config](config), puis d'appeler le programme avec la commande `./jeu -c config`.

## Liste des paramètre 

L'utilisation des paramètres du programme se font ainsi :
- `--help` ou `-h` 			: Pour afficher tout les aides du programme et quitter.
- `--version` ou `-v`       : Pour afficher la version actuel du programme et quitter
- `--config` ou `-c`		: Pour fournir un fichier de configuration au programme (doit ếtre suivit du nom du fichier).
- `--probability` ou `-p` 	: Pour fournir une probabilité par ligne de commande (doit ếtre suivit d'un nombre entre 0 et 1).
- `--dimension` ou `-d`     : Pour fournir une dimension par ligne de commande (doit ếtre suivit d'un nombre entier positif).
- `--speed` ou `-s` 		: Pour fixer le temps d'attente entre deux generations en Microsecondes. (doit ếtre suivit d'un nombre entier positif).

Example : 
-   `./jeu --probability 0.25` : Mets la probabilité à 25%.
-   `./jeu --dimension 15`     : Mets la dimension à 15 cases x 15 cases.
-   `./jeu -s 10000`           : Mets le temps d'attente à 1000000 Microsecondes (1 seconde).
-   `./jeu -p 0.25 -d 15 -s 10000` : Les 3 fonctions précedente en même temps.


## A venir
-   Affichage des Cellule sans code couleur.
-   Version qui teste plusieurs probabilité et écrit les résultat dans un fichier.
-   Affichage Graphique.
-   Autre Optimisation.
