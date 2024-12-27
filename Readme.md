# Jeu du Serpent

## Description
Il s'agit d'un **jeu du Serpent** basé sur le terminal, écrit en C à l'aide de la bibliothèque `ncurses`. Le jeu met en scène un serpent qui s'allonge à chaque fois qu'il mange de la nourriture. L'objectif est de marquer un maximum de points tout en évitant les collisions avec les murs, les obstacles, et le corps du serpent lui-même.

## Fonctionnalités
- Déplacement en temps réel du serpent avec les **flèches directionnelles**.
- Gameplay dynamique où le serpent grandit après avoir mangé.
- Difficulté croissante avec une sélection de niveaux personnalisable.
- Suivi du score et écran interactif de fin de partie.
- Menu principal simple avec les options :
  - Démarrer le jeu.
  - Choisir le niveau de difficulté.
  - Quitter le jeu.

## Auteur
- **Nom** : Bell Aqil 
- **mail** : aqi.bell@facsciences-uy1.cm
- **Tel** : +237621215284 

## Prérequis
Avant de compiler ou d'exécuter le jeu, assurez-vous d'avoir installé les éléments suivants :
- Un compilateur C compatible GCC.
- La bibliothèque `ncurses`.

### Installation de `ncurses`
Sur les systèmes Linux, vous pouvez installer la bibliothèque avec :

    sudo apt-get install libncurses5-dev libncursesw5-dev

Compilation et Exécution

Avec le Makefile

### 1. Compiler le jeu :

        make


### 2. Lancer le jeu :

       make run


### 3. Nettoyer les fichiers compilés :

       make clean



## Sans le Makefile

Pour compiler manuellement, utilisez :

      gcc -o snake_game snake_game.c -lncurses

Lancez le jeu avec :

    ./snake_game

Contrôles

Flèches directionnelles : Déplacer le serpent.

Haut (↑) - Monter.

Bas (↓) - Descendre.

Gauche (←) - Aller à gauche.

Droite (→) - Aller à droite.


P : Mettre le jeu en pause.

Entrée : Sélectionner une option dans le menu.


Comment jouer

#### 1. Démarrez le jeu depuis le menu principal.


#### 2. Dirigez le serpent pour qu'il consomme la nourriture (F) tout en évitant :

Les bords de l'écran.

Les obstacles (#).

Le corps du serpent lui-même.



#### 3. Chaque fois que vous mangez de la nourriture :

Le serpent grandit.

Votre score augmente de 10 points.



#### 4. Survivez le plus longtemps possible pour atteindre un score élevé.



Structure des fichiers

 fonction_bell.c : Les fonctions principales du jeu.

Makefile : Un système de construction pour simplifier la compilation et l'exécution.

README.md : Ce fichier de documentation.


Remerciements

Merci à Bell Aqil pour la réalisation de ce projet.

Licence

Ce projet est open-source et libre d'utilisation à des fins éducatives. Les contributions et modifications sont les bienvenues.

---
