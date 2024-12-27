#include "fonction_bell.h"

// Déclarations globales
SnakeON snakeON;
PointON foodON;
PointON obstaclesON[MAX_OBSTACLESBE];
int numObstaclesON = 0;
int scoreON = 0;
int gameOverON = 0;
char directionON = 'd'; // d -> droite, q -> gauche, z -> haut, s -> bas
int levelON = 1;


// Menu principal
void displayMenuBE() {
    int choiceON = 0;
    char optionsON[4][30] = {
        "1. Nouvelle partie",
        "2. Choisi le niveau",
        "3. Afficher le meilleur score",
        "4. Quitter"
    };

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    setupColorsBE();

    while (1) {
        clear();
        attron(COLOR_PAIR(2));
        printw("=== SNAKE GAME ===\n");
        attroff(COLOR_PAIR(2));
        for (int iON = 0; iON < 4; iON++) {
            if (iON == choiceON) {
                attron(A_REVERSE);
            }
            printw("%s\n", optionsON[iON]);
            if (iON == choiceON) {
                attroff(A_REVERSE);
            }
        }

        int keyON = getch();
        switch (keyON) {
            case KEY_UP:
                choiceON = (choiceON - 1 + 4) % 4;
                break;
            case KEY_DOWN:
                choiceON = (choiceON + 1) % 4;
                break;
            case 10: // Touche Entrée
                endwin();
                if (choiceON == 0) {
                    startGameBE();
                } else if (choiceON == 1) {
                    chooseLevelBE();
                } else if (choiceON == 2) {
                    displayHighScoresBE();
                } else if (choiceON == 3) {
                    exit(0);
                }
                return;
        }
    }
}

// Initialisation du jeu
void initializeGameBE() {
    srand(time(NULL));
    snakeON.headON = malloc(sizeof(NodeON));
    if (!snakeON.headON) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    snakeON.headON->positionON.xON = WIDTHBE / 2;
    snakeON.headON->positionON.yON = HEIGHTBE / 2;
    snakeON.headON->nextON = NULL;
    snakeON.tailON = snakeON.headON;
    snakeON.lengthON = 1;

    generateFoodBE();
    generateObstaclesBE();
    scoreON = 0;
    gameOverON = 0;
    directionON = 'd';
}

// Générer la nourriture
void generateFoodBE() {
    do {
        foodON.xON = rand() % WIDTHBE;
        foodON.yON = rand() % HEIGHTBE;
    } while (!isPositionFreeBE(foodON.xON, foodON.yON));
}

// Générer les obstacles
void generateObstaclesBE() {
    for (int iON = 0; iON < levelON; iON++) {
        do {
            obstaclesON[iON].xON = rand() % WIDTHBE;
            obstaclesON[iON].yON = rand() % HEIGHTBE;
        } while (!isPositionFreeBE(obstaclesON[iON].xON, obstaclesON[iON].yON));
    }
    numObstaclesON = levelON;
}

// Affichage de l'aire de jeu
void displayBoardBE() {
    clear();
    printBorderBE();
    for (int yON = 0; yON < HEIGHTBE; yON++) {
        for (int xON = 0; xON < WIDTHBE; xON++) {
            if (xON == snakeON.headON->positionON.xON && yON == snakeON.headON->positionON.yON) {
                attron(COLOR_PAIR(1));
                mvprintw(yON + 1, xON, "O"); // Tête du serpent
                attroff(COLOR_PAIR(1));
            } else {
                int isBodyON = 0;
                for (NodeON* currentON = snakeON.headON->nextON; currentON != NULL; currentON = currentON->nextON) {
                    if (currentON->positionON.xON == xON && currentON->positionON.yON == yON) {
                        mvprintw(yON + 1, xON, "*"); // Corps du serpent
                        isBodyON = 1;
                        break;
                    }
                }
                if (!isBodyON) {
                    if (xON == foodON.xON && yON == foodON.yON) {
                        attron(COLOR_PAIR(3));
                        mvprintw(yON + 1, xON, "F"); // Nourriture
                        attroff(COLOR_PAIR(3));
                    } else {
                        int isObstacleON = 0;
                        for (int iON = 0; iON < numObstaclesON; iON++) {
                            if (obstaclesON[iON].xON == xON && obstaclesON[iON].yON == yON) {
                                attron(COLOR_PAIR(4));
                                mvprintw(yON + 1, xON, "#"); // Obstacles
                                attroff(COLOR_PAIR(4));
                                isObstacleON = 1;
                                break;
                            }
                        }
                        if (!isObstacleON) {
                            mvprintw(yON + 1, xON, " ");
                        }
                    }
                }
            }
        }
    }
    printBorderBE();
    mvprintw(HEIGHTBE + 2, 0, "Score: %d | Niveau: %d", scoreON, levelON);
    refresh();
}

// Déplacer le serpent
void moveSnakeBE() {
	static int keyPressedON = 0; // Garde une trace de la derniere touche appuyee
	PointON nextPositionON = snakeON.headON->positionON;
	
	// Modifier la direction en fonction de la touche pressee
	int keyON = getch();
	if (keyON != ERR){
		keyPressedON = keyON;
		switch (keyON) {
			case KEY_UP: 
				if (directionON != 's') directionON = 'z'; // Empeche le retour immedia en arriere
				break;
			case KEY_DOWN:
				if (directionON != 'z') directionON = 's';
				break;
			case KEY_LEFT:
				if (directionON != 'd') directionON = 'q';
				break;
			case KEY_RIGHT:
				if (directionON != 'q') directionON = 'd';
				break;
		}
	}

	
	// Calcul de la nouvelle position de la tete en fonction de la direction
	if (directionON == 'z') nextPositionON.yON--;
	else if (directionON == 's') nextPositionON.yON++;
	else if (directionON == 'q') nextPositionON.xON--;
	else if (directionON == 'd') nextPositionON.xON++;
	
	// Verifier si le serpent mange la nourriture
	int ateFoodON = (nextPositionON.xON == foodON.xON && nextPositionON.yON == foodON.yON);
	
	// Creer un nouveau noeud por la nouvelle tete
	NodeON* newHeadON = malloc(sizeof(NodeON));
	if (!newHeadON){
		endwin();
		printf("Memory allocation failed.\n");
		exit(1);
	}
	newHeadON->positionON = nextPositionON;
	newHeadON->nextON = snakeON.headON;
	snakeON.headON = newHeadON;
	snakeON.lengthON++;
	
	// verifier si le serpent mange la nourriture
	if (ateFoodON) {
		scoreON += 1;
		generateFoodBE();
	} else {
		// Supprimer la queue du serpent si pas de nourriture mangee
		NodeON* currentON = malloc(sizeof(NodeON));
		currentON = snakeON.headON;
		while (currentON->nextON && currentON->nextON->nextON) {
			currentON = currentON->nextON;
		}
		if (currentON->nextON) {
			free(currentON->nextON);
			currentON->nextON = NULL;
		}
		snakeON.lengthON--;
	}
}

// Vérification des collisions
void checkCollisionBE() {
	
    if(snakeON.headON == NULL) {
    	gameOverON = 1;
    	return;
    }	
	
    PointON headON = snakeON.headON->positionON;

    // Collision avec les murs
    if (headON.xON < 0 || headON.xON >= WIDTHBE || headON.yON < 0 || headON.yON >= HEIGHTBE) {
        gameOverON = 1;
        return;
    }
    
    NodeON* currentON = malloc(sizeof(NodeON));

    // Collision avec le corps
    for (currentON = snakeON.headON->nextON; currentON != NULL; currentON = currentON->nextON) {
        if (currentON != NULL && currentON->positionON.xON == headON.xON && currentON->positionON.yON == headON.yON) {
            gameOverON = 1;
            return;
        }
    }

    // Collision avec les obstacles
    for (int iON = 0; iON < numObstaclesON; iON++) {
        if (obstaclesON[iON].xON == headON.xON && obstaclesON[iON].yON == headON.yON) {
            gameOverON = 1;
            return;
        }
    }
}

// Vérifier si une position est libre
int isPositionFreeBE(int xON, int yON) {
    if (xON < 0 || xON >= WIDTHBE || yON < 0 || yON >= HEIGHTBE) return 0;

    for (NodeON* currentON = snakeON.headON; currentON != NULL; currentON = currentON->nextON) {
        if (currentON->positionON.xON == xON && currentON->positionON.yON == yON) return 0;
    }

    for (int iON = 0; iON < numObstaclesON; iON++) {
        if (obstaclesON[iON].xON == xON && obstaclesON[iON].yON == yON) return 0;
    }
    return 1;
}

// Libérer la mémoire du serpent
void freeSnakeBE() {
    while (snakeON.headON != NULL) {
        NodeON* tempON = snakeON.headON;
        snakeON.headON = snakeON.headON->nextON;
        free(tempON);
    }
}

// Choisir le niveau
void chooseLevelBE() {
    initscr();
    clear();
    printw("Choisi le niveau (1-10): ");
    scanw("%d", &levelON);
    if (levelON < 1) levelON = 1;
    if (levelON > 10) levelON = 10;
    endwin();
}

// Sauvegarder les scores
void saveScoreBE() {
    FILE *fileON = fopen("highscoresBE.txt", "a");
    if (fileON) {
        fprintf(fileON, "Score: %d | Niveau: %d\n", scoreON, levelON);
        fclose(fileON);
    }
}

// Afficher les meilleurs scores
void displayHighScoresBE() {
    initscr();
    clear();
    printw("=== Meilleur Score ===\n");

    FILE *fileON = fopen("highscoresBE.txt", "r");
    if (fileON) {
        char lineON[100];
        while (fgets(lineON, sizeof(lineON), fileON)) {
            printw("%s", lineON);
        }
        fclose(fileON);
    } else {
        printw("Pas de meilleur score.\n");
    }

    printw("\nAppuyez n'importe quelle touche pour retourer au menu...");
    getch();
    endwin();
}

// Début du jeu
void startGameBE() {
    initializeGameBE();
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    timeout(150 - (levelON * 5)); // Vitesse du jeu basée sur le niveau

    while (!gameOverON) {
        displayBoardBE();
        int keyON = getch();
        switch (keyON) {
            case KEY_UP:
                if (directionON != 's') directionON = 'z';
                break;
            case KEY_DOWN:
                if (directionON != 'z') directionON = 's';
                break;
            case KEY_LEFT:
                if (directionON != 'd') directionON = 'q';
                break;
            case KEY_RIGHT:
                if (directionON != 'q') directionON = 'd';
                break;
        }
        moveSnakeBE();
        checkCollisionBE();
    }

    // Afficher l'écran de fin de partie
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(HEIGHTBE / 2, (WIDTHBE - 10) / 2, "GAME OVER");
    attroff(COLOR_PAIR(2));
    mvprintw(HEIGHTBE / 2 + 1, (WIDTHBE - 20) / 2, "Votre Score: %d", scoreON);
    saveScoreBE();
    mvprintw(HEIGHTBE / 2 + 2, (WIDTHBE - 25) / 2, "Appuyez n'importe quelle touche...");
    getch();
    endwin();
    freeSnakeBE();
}

// Dessiner les bordures
void printBorderBE() {
    for (int xON = 0; xON < WIDTHBE + 2; xON++) mvprintw(0, xON, "-");
    for (int xON = 0; xON < WIDTHBE + 2; xON++) mvprintw(HEIGHTBE + 1, xON, "-");
    for (int yON = 0; yON < HEIGHTBE + 1; yON++) {
        mvprintw(yON, 0, "|");
        mvprintw(yON, WIDTHBE + 1, "|");
    }
}

// Configurer les couleurs
void setupColorsBE() {
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color.\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Tête du serpent
    init_pair(2, COLOR_RED, COLOR_BLACK);   // Texte important
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Nourriture
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Obstacles
}
// ONDO JEAN KAREL 22U2381
