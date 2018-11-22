# Jeu de la vie

## Information Géneral

Ce programme est l'implementation du jeu de la vie en C++.
Le jeu de la vie est le plus connu des automate cellulaire et a été imaginé par <a href="https://fr.wikipedia.org/wiki/John_Horton_Conway">Jhon Horton Conway</a> en 1970.
Malgré son nom, le jeu de la vie n'est pas un jeu au sens ludique du terme car il ne nécessite aucun joueur.
Pour plus d'information <a href="https://fr.wikipedia.org/wiki/Jeu_de_la_vie">Wikipédia</a>.
Les Règles sont décrtite <a href="https://fr.wikipedia.org/wiki/Jeu_de_la_vie#R%C3%A8gles">Ici</a>

Une recherche Google des termes [`Conway's game of life`](https://www.google.com/search?q=conway%27s+game+of+life), fait apparaître un jeu de la vie en arrière-plan.

## Utilisation

L'utilisation du programme : 
- Compiler avec `make all`
- Executer sans paramètre avec `make exe`
- Executer avec paramètre `jeu paramètres`
- Les paramètre disponible sont précisé plus loin dans ce fichier ou en executant `jeu -h` ou `jeu --help`

Cette version prend en charge la modification :
- De la dimension du plateau de jeu (mais pour l'instant, doit rester inférieur à une certaine valeur définit dans [population.h](population/population.h)).
- De la probabilité d'apparition d'une cellule vivante.
- Création d'une ou plusieurs cellule vivante à des position spécifié.

Ces modification se font en écrivant dans le fichier [config](config),
la syntaxe prise en charge par ce fichier est décrite directement dans ce dernier.

## A venir

Optimisation et la prise en charge de commande suplèmentaire Tel que :
- `--help` ou `-h` 			: Pour afficher tout les aides du programme et quitter.
- `--version` ou `-v`       : Pour afficher la version actuel du programme et quitter
- `--config` ou `-c`		: Pour fournir un fichier de configuration au programme.
- `--probability` ou `-p` 	: Pour fournir une probabilité par ligne de commande.
- `--dimension` ou `-d`     : Pour fournir une dimension par ligne de commande. (Là aussi la dimension est limité)
- `--speed` ou `-s` 		: Pour fixer la vitesse de défilement des generations.
- Etc..
