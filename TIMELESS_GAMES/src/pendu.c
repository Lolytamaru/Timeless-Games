/**
 * \file pendu.c
 * \brief Fichier pour le jeu du pendu
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 2.0
 * \date 31 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <pendu.h>

int tab_x_lettre[26] = {535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 571, 647}; // Tableau contenant la coordonnée x en pixels des 26 lettres de l'alphabet
int tab_y_lettre[26] = {28, 28, 28, 79, 79, 79, 130, 130, 130, 181, 181, 181, 232, 232, 232, 283, 283, 283, 334, 334, 334, 385, 385, 385, 436, 436}; // Tableau contenant la coordonnée y en pixels des 26 lettres de l'alphabet



/**
 * \brief Fonction qui initialise une partie de pendu
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param pseudoJ1 Pseudo du joueur 1
 * \param pseudoJ2 Pseudo du joueur 2
 * \param scoreJ1 Score du joueur 1
 * \param scoreJ2 Score du joueur 2
 */
void init_partie_pendu(SDL_Window * win, SDL_Renderer * ren, int * mode_de_jeu, char * pseudoJ1, char * pseudoJ2, int * scoreJ1, int * scoreJ2) {
	char i;
	pendu.pendu = (char*)malloc(sizeof(char)); // Contient le mot sur lequel on joue au pendu
	pendu.secret = (char*)malloc(sizeof(char)); // Contient le mot secret
	// Initialisation d'un tableau contenant toutes les lettres de l'alphabet
	for (i = 'a'; i <= 'z'; i++)
		pendu.alphabet[i - 'a'] = i;
	pendu.erreurs = 0;
	pendu.etat_partie = PENDU_JCJ_INIT;
	// Si le mode de jeu est joueur contre ordi
	if (*mode_de_jeu == JVSO) {
		afficher_image(win, ren, "assets/pendu/pendu.png", 0, 0);
		afficher_texte(ren, "assets/inter.ttf", 19, 15, 110, pseudoJ1);
		afficher_texte(ren, "assets/inter.ttf", 19, 15, 232, pseudoJ2);
		afficher_nombre(ren, "assets/inter.ttf", 19, 26, 148, *scoreJ1);
		afficher_nombre(ren, "assets/inter.ttf", 19, 26, 269, *scoreJ2);
		SDL_RenderPresent(ren);
		initialiser_mot_ordi(win, ren, pendu.secret, pendu.pendu);
		pendu.etat_partie = PENDUJEU;
		SDL_RenderPresent(ren);
	}
}

/**
 * \brief Initilise le mot à deviner en l'écrivant ou avec une banque de mots
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event L'évènement détecté
 * \param etat_joueur Etat du joueur
 * \param etat_partie Etat de la partie : terminée ou non
 * \param secret_ecrit Le mot entré au clavier
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param pseudoJ1 Le pseudo actuel du joueur 1
 * \param pseudoJ2 Le pseudo actuel du joueur 2
 * \param scoreJ1 Le score actuel du joueur 1
 * \param scoreJ2 Le score actuel du joueur 2
 */
void initialiser_mot_joueur(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, int * etat_joueur, int * etat_partie, char * secret_ecrit, char * secret, char * pendu, char * pseudoJ1, char * pseudoJ2, int * scoreJ1, int * scoreJ2) {
	int i, l;
	char temp[101];
	SDL_Rect txtDestRect;
	TTF_Font *police;
	SDL_Surface *texte = NULL;
	SDL_Color couleur_police = {0, 0, 0};
	SDL_Texture *texte_tex;
	// En fonction des évènements au clavier et à la souris
	switch(event.type) {
		// Gestion des appuis au clavier
		case SDL_KEYUP:
			// Si on appuie sur entrée au clavier
			if (event.key.keysym.sym == SDLK_BACKSPACE) {
				l = strlen(secret_ecrit);
				if (l > 0)
						secret_ecrit[l-1] = '\0';
				police = TTF_OpenFont("assets/inter.ttf", 27);
				TTF_SetFontStyle(police,TTF_STYLE_BOLD);
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
				SDL_RenderClear(ren);
				afficher_image(win, ren, "assets/pendu/pendujcj.png", 0, 0);
				if (*etat_joueur == J1) {
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 80, pseudoJ1);
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 222, pseudoJ2);
				} else {
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 80, pseudoJ2);
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 222, pseudoJ1);
				}
				texte = TTF_RenderUTF8_Blended(police, secret_ecrit, couleur_police);
				txtDestRect.x = 520;
				txtDestRect.y = 315;
 				texte_tex = SDL_CreateTextureFromSurface(ren, texte);
				SDL_FreeSurface(texte);
				SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
				SDL_RenderCopy(ren, texte_tex, NULL, &txtDestRect);
				TTF_CloseFont(police);
				SDL_RenderPresent(ren);
			}
			// Si on appuie sur une lettre de l'alphabet avec le clavier
			if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
				l = strlen(secret_ecrit);
				if (l < 9) {
					sprintf(temp, "%s%c", secret_ecrit, event.key.keysym.sym);
					sprintf(secret_ecrit, "%s", temp);
				}
				police = TTF_OpenFont("assets/inter.ttf", 27);
				TTF_SetFontStyle(police, TTF_STYLE_BOLD);
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
				SDL_RenderClear(ren);
				afficher_image(win, ren, "assets/pendu/pendujcj.png", 0, 0);
				if (*etat_joueur == J1) {
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 80, pseudoJ1);
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 222, pseudoJ2);
				} else {
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 80, pseudoJ2);
					afficher_texte(ren, "assets/inter.ttf", 27, 510, 222, pseudoJ1);
				}
				texte = TTF_RenderUTF8_Blended(police, secret_ecrit, couleur_police);
				txtDestRect.x = 520;
				txtDestRect.y = 315;
				texte_tex = SDL_CreateTextureFromSurface(ren, texte);
				SDL_FreeSurface(texte);
				SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
				SDL_RenderCopy(ren, texte_tex, NULL, &txtDestRect);
				TTF_CloseFont(police);
				SDL_RenderPresent(ren);
			}
			if (event.key.keysym.sym == SDLK_RETURN ) {
				sprintf(secret, "%s", secret_ecrit);
				for (i = 0; i < secret[i]; i++)
			  		secret_ecrit[i] = '\0';
				// Boucle qui initialise le 2ème mot pendu utilisé pour le jeu (ex : _ _ _ _)
			   for (i = 0; i < secret[i]; i++)
			  		pendu[i] = '_';
			   //Affichage SDL des _ _ _
				afficher_image(win, ren, "assets/pendu/pendu.png", 0, 0);
				afficher_texte(ren, "assets/inter.ttf", 19, 15, 110, pseudoJ1);
				afficher_texte(ren, "assets/inter.ttf", 19, 15, 232, pseudoJ2);
				afficher_nombre(ren, "assets/inter.ttf", 19, 26, 148, *scoreJ1);
				afficher_nombre(ren, "assets/inter.ttf", 19, 26, 269, *scoreJ2);
				SDL_RenderPresent(ren);
			   afficher_mystere(win, ren, i - 1);
				SDL_RenderPresent(ren);
				*etat_partie = PENDUJEU;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			// Si on clique sur le bouton valider avec la souris
			if (event.button.x < 557 && event.button.x > 386 && event.button.y < 443 && event.button.y > 375 && strlen(secret_ecrit) >= 4) {
				sprintf(secret, "%s", secret_ecrit);
				for (i = 0; i < secret[i]; i++)
			  		secret_ecrit[i] = '\0';
				// Boucle qui initialise le 2ème mot pendu utilisé pour le jeu (ex : _ _ _ _)
			   for (i = 0; i < secret[i]; i++)
			  		pendu[i] = '_';
			   //Affichage SDL des _ _ _
				afficher_image(win, ren, "assets/pendu/pendu.png", 0, 0);
				afficher_texte(ren, "assets/inter.ttf", 19, 15, 110, pseudoJ1);
				afficher_texte(ren, "assets/inter.ttf", 19, 15, 232, pseudoJ2);
				afficher_nombre(ren, "assets/inter.ttf", 19, 26, 148, *scoreJ1);
				afficher_nombre(ren, "assets/inter.ttf", 19, 26, 269, *scoreJ2);
				SDL_RenderPresent(ren);
			   afficher_mystere(win, ren, i - 1);
				SDL_RenderPresent(ren);
				*etat_partie = PENDUJEU;
			}
			// Si on clique sur le bouton mot aléatoire
			if (event.button.x < 739 && event.button.x > 565 && event.button.y < 443 && event.button.y > 375) {
				afficher_image(win, ren, "assets/pendu/pendu.png", 0, 0);
				afficher_texte(ren, "assets/inter.ttf", 19, 15, 110, pseudoJ1);
				afficher_texte(ren, "assets/inter.ttf", 19, 15, 232, pseudoJ2);
				afficher_nombre(ren, "assets/inter.ttf", 19, 26, 148, *scoreJ1);
				afficher_nombre(ren, "assets/inter.ttf", 19, 26, 269, *scoreJ2);
				SDL_RenderPresent(ren);
				initialiser_mot_ordi(win, ren, secret, pendu);
				*etat_partie = PENDUJEU;
				SDL_RenderPresent(ren);
			}
			break;
		default: break;
	}
}

/**
 * \brief Initilise au hasard le mot à deviner avec une banque de mots
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 */
void initialiser_mot_ordi(SDL_Window * win, SDL_Renderer * ren, char * secret, char * pendu) {
   int i, nb_rand;
   FILE *listeMots = fopen("assets/pendu/mots.txt", "r"); // Fichier contenant 598 mots
   srand(time(NULL)); // Initialisation du hasard
   nb_rand = rand() % (540 + 1 - 1); // Génération d'un nombre entre 1 et 598
   // Boucle pour accéder au mot à la ligne nb_rand du fichier
   for (i = 1; i <= nb_rand; i++)
      fscanf(listeMots, "%s", secret);
   fclose(listeMots);
   // Boucle qui initialise le 2ème mot pendu utilisé pour le jeu (ex : _ _ _ _)
   for (i = 0; i < secret[i]; i++)
  		pendu[i] = '_';
 	pendu[i] = '\0';
   //Affichage SDL des _ _ _
   afficher_mystere(win, ren, i-1);
}

/**
 * \brief Fonction qui établi une indication si la lettre utilisée est présente ou non dans le mot graphiquement
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param lettre La lettre entrée par le joueur
 * \param presence Vaut OK si la lettre appartient au mot caché
 */
void lettre_utilisee(SDL_Window * win, SDL_Renderer * ren, char lettre, int presence) {
	// Si la lettre est présente dans le mot, on affiche une case verte, sinon rouge
	if (presence == OK)
		afficher_image(win, ren, "assets/pendu/case_verte.png", tab_x_lettre[lettre - 'a'], tab_y_lettre[lettre - 'a']);
	else
		afficher_image(win, ren, "assets/pendu/case_rouge.png", tab_x_lettre[lettre - 'a'], tab_y_lettre[lettre - 'a']);
}

/**
 * \brief Fonction qui permet d'afficher la lettre désignée à une position donnée de l'écran
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param c La lettre à afficher
 * \param position La position de la lettre qu'on souhaite afficher dans le mot
 */
void affiche_lettre(SDL_Window * win, SDL_Renderer * ren, char c, int position) {
	char temp[255];
	sprintf(temp, "assets/pendu/lettres_pendu/%c.png", c);
 	afficher_image(win, ren, temp, (95 + (position) * 47), 391);
}

/**
 * \brief Fonction qui indique au joueur graphiquement le nombre de lettres du mot caché
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param longueur_mot Le nombre de lettres dans le mot
 */
void afficher_mystere(SDL_Window * win, SDL_Renderer * ren, int longueur_mot) {
	int i = 0, position_x = 95, position_y = 467;
	// Affiche un trait pour chaque lettre du mot à trouver
	for (i = 0; i <= longueur_mot; i++) {
		afficher_image(win, ren, "assets/pendu/trait_noir.png", position_x, position_y);
		position_x += 47;
	}
}

/**
 * \brief Affiche un visuel de l'avancement du pendu selon le nombre d'erreurs
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param nb_erreur Le nombre d'erreurs actuelles du joueur
 */
void afficher_erreur(SDL_Window * win, SDL_Renderer * ren, int nb_erreur) {
	char temp[255];
	sprintf(temp, "assets/pendu/phases_pendu/phase%i.png", nb_erreur - 1);
	afficher_image(win, ren, temp, 186, 75);
}

/**
 * \brief Regarde si le mot essayé est correct
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \return Renvoie OK si les deux mots sont identiques, PAS_OK si les deux mots ne sont pas identiques
 */
int valider_mot(char * secret, char * pendu) {
	int i, j;
   for (i = 0; secret[i] && (secret[i] == pendu[i]); i++) {}
	for (j = 0; secret[j]; j++) {}
   if (i == j) // Si les deux mots sont identiques
      return OK;
   else // Sinon ils ne sont pas identiques
      return PAS_OK;
}

/**
 * \brief Vérifie la lettre selectionnée par le joueur
 * \param entree la lettre choisie
 * \param alphabet Les lettres utilisées et non utilisées
 * \return Renvoie l'état de check selon si la lettre a déjà été utilisée ou non
 */
int saisie(char entree, char * alphabet) {
   int i, check = PAS_OK;
	char test[] = {entree};
   // On compare la lettre entrée à l'alphabet restant des lettres pas encore utilisées
   for (i = 0; i < alphabet[i]; i++) {
     // Si on trouve la lettre dans l'alphabet alors on la supprime de l'alphabet
      if (alphabet[i] == test[0]) {
         alphabet[i] = '_';
         check = OK;
      }
   }
   return check;
}

/**
 * \brief Regarde si la lettre entrée est dans le mot secret ou non
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param lettre La lettre choisie par le joueur
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param erreurs Le nombre total actuel d'erreurs
 * \return 1 si bonne lettre, 0 si mauvaise lettre
 */
int valider_lettre(SDL_Window * win, SDL_Renderer * ren, char lettre, char * secret, char * pendu, int * erreurs) {
   int i, check = PAS_OK;
   for (i = 0; secret[i]; i++) {
	    // Si la lettre fait partie du mot
      if (secret[i] == lettre) {
         affiche_lettre(win, ren, lettre, i);
         pendu[i] = secret[i];
         check = OK;
      }
   }
   if (check == OK) { // Si la lettre est présente au moins une fois dans le mot
      lettre_utilisee(win, ren, lettre, OK);
		return 1;
 	} else { // Si elle n'est pas présente, cela cause une erreur supplémentaire
      lettre_utilisee(win, ren, lettre, 0);
      (*erreurs)++;
		return 0;
   }
}

/**
 * \brief Fonction qui s'occupe d'exécuter un tour de jeu dès que le joueur choisi une lettre en vérifiant si la partie est terminiée
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param etat_joueur Etat du joueur
 * \param etat_partie Etat de la partie : terminée ou non
 * \param scoreJ1 Le score actuel du joueur 1
 * \param scoreJ2 Le score actuel du joueur 2
 * \param lettre La lettre choisie par le joueur
 * \param alphabet Les lettres utilisées et non utilisées
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param secret Le mot à deviner
 * \param erreurs Le nombre total actuel d'erreurs
 */
void pendu_tour(SDL_Window * win, SDL_Renderer * ren, int mode_de_jeu, int etat_joueur, int * etat_partie, int * scoreJ1, int * scoreJ2, char lettre, char * alphabet, char * pendu, char * secret, int * erreurs) {
	int i;
	// Vérification si on est dans une situation de fin de jeu
	if ((*erreurs) <= 10 && (valider_mot(secret, pendu) == PAS_OK)) {
      // Si la lettre n'a pas encore été utilisée
		if (saisie(lettre, alphabet) == OK) {
     		if (valider_lettre(win, ren, lettre, secret, pendu, erreurs) == 0)
 				afficher_erreur(win, ren, *erreurs);
			SDL_RenderPresent(ren);
    	}
   }
	// Si le joueur a découvert toutes les lettres (a gagné)
  	if ((valider_mot(secret, pendu) == 1)) {
   	afficher_image(win, ren, "assets/pendu/gagne_pendu.png", 247, 7);
    	*etat_partie = PENDUFINI;
		if(mode_de_jeu == JVSJ) {
			if (etat_joueur == J1)
				(*scoreJ2)++;
			else
				(*scoreJ1)++;
		} else {
			if (etat_joueur == J1)
				(*scoreJ1)++;
			else
				(*scoreJ2)++;
		}
		SDL_RenderPresent(ren);
		free(pendu);
	}
	// Si le joueur est pendu (a perdu)
   if ((*erreurs) >= 10) {
	 	afficher_image(win, ren, "assets/pendu/perdu_pendu.png", 247, 7);
		for (i = 0; secret[i]; i++) // Affichage du mot caché
			affiche_lettre(win, ren, secret[i], i);
		*etat_partie = PENDUFINI;
		if(mode_de_jeu == JVSJ) {
			if (etat_joueur == J1)
				(*scoreJ1)++;
			else
				(*scoreJ2)++;
		} else {
			if (etat_joueur == J1)
				(*scoreJ2)++;
			else
				(*scoreJ1)++;
		}
		SDL_RenderPresent(ren);
		free(pendu);
	}
   // Met à jour l'affichage selon les manipulations précédentes
   SDL_UpdateWindowSurface(win);
}

/**
 * \brief Fonction qui s'occupe d'exécuter un tour de jeu dès que le joueur choisit une lettre, en vérifiant si la partie est terminée
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event L'évènement détecté
 * \param etat_win La fenêtre où on se trouve
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param joueur1 Structure qui contient les informations du joueur 1
 * \param joueur2 Structure qui contient les informations du joueur 2
 */

void gestion_event_pendu(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2) {
	switch(event.type) {
		// Clics à la souris
		case SDL_MOUSEBUTTONUP: // Relâchement du clic pour la non redondance de l'évènement
			// Bouton [QUITTER]
			if (event.button.x < 155 && event.button.x > 0 && event.button.y < 43 && event.button.y > 0) {
				if (*mode_de_jeu == JVSJ && *etat_joueur == J1)
               afficher_image(win, ren, "assets/menu_J1.png", 0, 0);
            else if (*mode_de_jeu == JVSJ && *etat_joueur == J2)
               afficher_image(win, ren, "assets/menu_J2.png", 0, 0);
            else
               afficher_image(win, ren, "assets/menu.png", 0, 0);
            afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
				afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
				afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
            afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
				SDL_RenderPresent(ren);
				*etat_win = MENU;
			}
			// Partie en cours
			if (pendu.etat_partie == PENDUJEU) {
			// Les lettres à proposer
			// Une zone définie correspondant à une lettre et réalisant un tour de jeu avec celle qui correspond
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 69 && event.button.y > 28)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie),  &(joueur1->score),  &(joueur2->score), 'a', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 69 && event.button.y > 28)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'b', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 69 && event.button.y > 28)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'c', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 120 && event.button.y > 79)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'd', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 120 && event.button.y > 79)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'e', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 120 && event.button.y > 79)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'f', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 171 && event.button.y > 130)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'g', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 171 && event.button.y > 130)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'h', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 171 && event.button.y > 130)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'i', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 222 && event.button.y > 181)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'j', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 222 && event.button.y > 181)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'k', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 222 && event.button.y > 181)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'l', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 273 && event.button.y > 232)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'm', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 273 && event.button.y > 232)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'n', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 273 && event.button.y > 232)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'o', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 324 && event.button.y > 283)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'p', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 324 && event.button.y > 283)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'q', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 324 && event.button.y > 283)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'r', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 375 && event.button.y > 334)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 's', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 375 && event.button.y > 334)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 't', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 375 && event.button.y > 334)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'u', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 426 && event.button.y > 385)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'v', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 426 && event.button.y > 385)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'w', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 426 && event.button.y > 385)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'x', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 639 && event.button.x >571 && event.button.y < 477 && event.button.y > 436)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'y', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
				if (event.button.x < 715 && event.button.x >647 && event.button.y < 477 && event.button.y > 436)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), 'z', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
			}
			break;
		// Saisies au clavier
		case SDL_KEYUP:
         if (pendu.etat_partie == PENDUJEU) {
				if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
					pendu_tour(win, ren, *mode_de_jeu, *etat_joueur, &(pendu.etat_partie), &(joueur1->score),  &(joueur2->score), event.key.keysym.sym, pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs));
			}
			break;
		default: break;
	}
	if (pendu.etat_partie == PENDU_JCJ_INIT) {
		initialiser_mot_joueur(win, ren, event, etat_joueur, &(pendu.etat_partie), pendu.secret_ecrit, pendu.secret, pendu.pendu, joueur1->pseudo, joueur2->pseudo, &(joueur1->score), &(joueur2->score));
	}
}
