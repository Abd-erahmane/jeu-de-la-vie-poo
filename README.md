Jeu de la Vie - Projet POO
Table des Matières
Description
Fonctionnalités
Modes de Fonctionnement
Règles du Jeu de la Vie
Extensions
Technologies Utilisées
Prérequis
Installation
Utilisation
Mode Console
Mode Graphique
Structure du Projet
Tests
Tests Unitaires
Contact
Remerciements
Description
Le Jeu de la Vie est un automate cellulaire proposé par le mathématicien John Conway. Il simule l’évolution d’une population de cellules sur une grille bidimensionnelle selon des règles simples mais puissantes. Ce projet consiste en une implémentation en C++ utilisant les principes de la Programmation Orientée Objet (POO). Il propose deux modes de fonctionnement : console et graphique, grâce à l'utilisation de la bibliothèque graphique SFML.

Fonctionnalités
Modes de Fonctionnement
Console :

Affichage textuel des états des cellules.
Enregistrement des itérations dans des fichiers.
Graphique :

Interface interactive affichant la grille des cellules en temps réel.
Contrôle des itérations via des boutons interactifs.
Règles du Jeu de la Vie
Naissance : Une cellule morte possédant exactement trois voisines vivantes devient vivante.
Survie : Une cellule vivante possédant deux ou trois voisines vivantes reste vivante.
Mort : Sinon, la cellule meurt (par surpopulation ou sous-population).
Extensions
Grille Torique : Les bords de la grille sont connectés, créant une surface sans frontières.
Cellules Obstacle : Certaines cellules sont des obstacles dont l’état ne change pas.
Placement de Constructions Pré-programmées : Possibilité d’ajouter des motifs spécifiques pendant la simulation.
Parallélisation : Optimisation des performances en répartissant les calculs sur plusieurs threads.
Technologies Utilisées
Langage de Programmation : C++ (Standard C++11 ou supérieur)
Bibliothèques :
SFML (Simple and Fast Multimedia Library) : Pour l’interface graphique.
Google Test : Pour les tests unitaires.
Prérequis
Compilateur C++ compatible avec le standard C++11 ou supérieur.
SFML installée sur votre système.
CMake pour la génération des fichiers de compilation.
Git pour cloner le dépôt.
Installation
Cloner le Dépôt : Utilisez Git pour obtenir une copie locale du projet.
Créer un Répertoire de Build : Organisez les fichiers de compilation dans un dossier séparé.
Générer les Fichiers de Compilation avec CMake : Configurez le projet pour votre environnement.
Compiler le Projet : Construisez les exécutables nécessaires.
Utilisation
Mode Console
Lancez le programme en mode console pour visualiser l’évolution des cellules de manière textuelle. Vous pouvez spécifier un fichier d’entrée contenant la taille de la grille et l’état initial des cellules.

Mode Graphique
Utilisez le mode graphique pour une interface interactive permettant de visualiser la grille en temps réel. Les fonctionnalités incluent :

Démarrer/Arrêter la Simulation : Contrôlez le déroulement de la simulation via des boutons.
Ajouter des Motifs : Placez des motifs pré-programmés en utilisant les touches du clavier.
Contrôler la Vitesse : Ajustez le délai entre les itérations directement dans l’interface.
Structure du Projet
makefile
Copier le code
jeu-de-la-vie-poo/
Projet_Simulation/
├── components/

│   ├── Cellule.h
│   ├── Cellule.cpp
│   ├── Grid.h
│   └── Grid.cpp
├── interfaces/
│   ├── Console.h
│   ├── Console.cpp
│   ├── Graphics.h
│   ├── Graphics.cpp
│   └── SimulationInterface.h
├── services/
│   ├── Game.h
│   └── Game.cpp
├── resources/
│   └── arial.ttf
├── main.cpp
└── ├── tests/             

Tests
Tests Unitaires
Des tests unitaires ont été implémentés avec Google Test pour assurer la fiabilité des principales classes et méthodes du projet. Ces tests couvrent :

L'initialisation de la grille.
La mise à jour des cellules selon les règles du jeu.
La détection des états stables.
Les fonctionnalités des boutons interactifs.
Contact
Pour toute question ou suggestion, veuillez contacter :

Abderrahman : bfabderahman@gmail.com
Noureddine : nounou19244@gmail.com
Remerciements
John Conway pour le concept original du Jeu de la Vie.
La Communauté Open Source pour les outils et bibliothèques utilisés dans ce projet.
Nos Encadrants pour leur soutien et leurs conseils tout au long du développement.
