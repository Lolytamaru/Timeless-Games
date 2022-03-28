/**
 * \file pendu.c
 * \brief Fichier pour le jeu du pendu
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 2.0
 * \date 21 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <pendu.h>

#define OK 1
#define PAS_OK 0

/**
 * \struct t_pendu Structure qui contient les variables propres au jeu du pendu
 */
typedef struct s_pendu {
	char *pendu;
	char *secret;
	char secret_ecrit[100];
	char alphabet[26];
	int erreurs;
	int etat_partie;
} t_pendu;

t_pendu pendu;

int tab_x_lettre[26] = {535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 535, 607, 679, 571, 647};
int tab_y_lettre[26] = {28, 28, 28, 79, 79, 79, 130, 130, 130, 181, 181, 181, 232, 232, 232, 283, 283, 283, 334, 334, 334, 385, 385, 385, 436, 436};

/**
 * \brief Fonction qui initialise une partie de pendu
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void init_partie_pendu(int * mode_de_jeu, SDL_Window * win, SDL_Renderer * ren, char * pseudoJ1, char * pseudoJ2, int * scorej1, int * scorej2) {
	char i;
	pendu.pendu = (char*)malloc(sizeof(char));
	pendu.secret = (char*)malloc(sizeof(char)); // Deux chaînes contenant le mot secret et le mot sur lequel on joue au pendu
	for (i = 'a'; i <= 'z'; i++)
		pendu.alphabet[i-'a'] = i;
	pendu.erreurs = 0;
	pendu.etat_partie = PENDU_JCJ_INIT;
	if(*mode_de_jeu == JVSO){
		afficher_image("assets/pendu/pendu.png", 0, 0, win, ren);
		afficher_texte("assets/inter.ttf", 19, 15, 110, pseudoJ1, ren);
		afficher_texte("assets/inter.ttf", 19, 15, 232, pseudoJ2, ren);
		afficher_nombre("assets/inter.ttf", 19, 26, 148, *scorej1, ren);
		afficher_nombre("assets/inter.ttf", 19, 26, 269, *scorej2, ren);
		SDL_RenderPresent(ren);
		initialiser_mot_ordi(pendu.secret, pendu.pendu, win, ren);
		pendu.etat_partie = PENDUJEU;
		SDL_RenderPresent(ren);
	}
}

/**
 * \brief Fonction qui établi une indication si la lettre utilisée est présente ou non dans le mot graphiquement
 * \param lettre La lettre entrée par le joueur
 * \param presence Vaut OK si la lettre appartient au mot caché
 * \param win Une fenêtre qui sera manipulée
 * \param ren Un rendu qui sera manipulé
 */
void lettre_utilisee(char lettre, int presence, SDL_Window * win, SDL_Renderer * ren) {
	// Si la lettre est présente dans le mot, on affiche une case verte, sinon rouge
	int i = lettre - 'a';
	if (presence == OK)
		afficher_image("assets/pendu/case_verte.png", tab_x_lettre[i], tab_y_lettre[i], win, ren);
	else
		afficher_image("assets/pendu/case_rouge.png", tab_x_lettre[i], tab_y_lettre[i], win, ren);
}

/**
 * \brief Fonction qui permet d'afficher la lettre désignée à une position donnée de l'écran
 * \param lettre La lettre à afficher
 * \param position La position de la lettre qu'on souhaite afficher dans le mot
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void affiche_lettre(char c, int position, SDL_Window * win, SDL_Renderer * ren) {
	char temp[255];
	sprintf(temp, "assets/pendu/lettres_pendu/%c.png", c);
 	afficher_image(temp, (95 + (position) * 47), 391, win, ren);
}

/**
 * \brief Fonction qui indique au joueur graphiquement le nombre de lettres du mot caché
 * \param longueur_mot Le nombre de lettres dans le mot
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void afficher_mystere(int longueur_mot, SDL_Window * win, SDL_Renderer * ren) {
	int i = 0, position_x = 95, position_y = 467;
	for (i = 0; i <= longueur_mot; i++) { // Affiche un trait pour chaque lettre du mot à trouver
		afficher_image("assets/pendu/trait_noir.png", position_x, position_y, win, ren);
		position_x += 47;
	}
}

/**
 * \brief Affiche un visuel de l'avancement du pendu selon le nombre d'erreurs
 * \param nb_erreur Le nombre d'erreurs actuelles du joueur
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void afficher_erreur(int nb_erreur, SDL_Window * win, SDL_Renderer * ren) {
	char temp[255];
	sprintf(temp, "assets/pendu/phases_pendu/phase%i.png", nb_erreur - 1);
	afficher_image(temp, 186, 75, win, ren);

}

/**
 * \brief Initilise au hasard le mot à deviner avec une banque de mots
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void initialiser_mot_ordi(char * secret, char * pendu, SDL_Window * win, SDL_Renderer * ren) {
   int i, nb_rand;
   FILE *listeMots = fopen("assets/pendu/mots.txt", "r");
   srand(time(NULL)); // Initialisation du hasard
   nb_rand = rand() % (598 + 1 - 1); // Génération d'un nombre entre 1 et 598, soit le nombre de mots dans le fichier txt
   // Boucle pour accéder au mot à la ligne nb_rand du fichier
   for (i = 1; i <= nb_rand; i++)
      fscanf(listeMots, "%s", secret);
   fclose(listeMots);
   // Boucle qui initialise le 2ème mot pendu utilisé pour le jeu (ex : _ _ _ _)
   for (i = 0; i<secret[i]; i++)
  		pendu[i] = '_';
 	pendu[i] = '\0';
   //Affichage SDL des _ _ _
   afficher_mystere(i-1, win, ren);
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
 * \param lettre La lettre choisie par le joueur
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param erreurs Le nombre total actuel d'erreurs
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \return bonne ou mauvaise lettre
 */
int valider_lettre(char lettre, char * secret, char * pendu, int * erreurs, SDL_Window * win, SDL_Renderer * ren) {
   int i, check = PAS_OK;
   for (i = 0; secret[i]; i++) {
      if (secret[i] == lettre) { // Si la lettre fait partie du mot
         affiche_lettre(lettre, i, win, ren);
         pendu[i] = secret[i];
         check = OK;
      }
   }
   if (check == OK){ // Si la lettre est présente au moins une fois dans le mot
      lettre_utilisee(lettre, OK, win, ren);
		return 1;
 	} else { // Si elle n'est pas présente, cela cause une erreur supplémentaire
      lettre_utilisee(lettre, 0, win, ren);
      (*erreurs)++;
		return 0;
   }
}

/**
 * \brief Fonction qui s'occupe d'exécuter un tour de jeu dès que le joueur choisi une lettre en vérifiant si la partie est terminiée
 * \param etat_partie Etat de la partie : terminée ou non
 * \param scorej1 Le score actuel du joueur 1
 * \param scorej2 Le score actuel du joueur 2
 * \param lettre La lettre choisie par le joueur
 * \param alphabet Les lettres utilisées et non utilisées
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param secret Le mot à deviner
 * \param erreurs Le nombre total actuel d'erreurs
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void pendu_tour(int etat_joueur, int * etat_partie, int * scorej1, int * scorej2, char lettre, char * alphabet, char * pendu, char * secret, int * erreurs, SDL_Window * win, SDL_Renderer * ren) {
	int i;
	if ((*erreurs) <= 10 && (valider_mot(secret, pendu) == PAS_OK)) {
		// Vérification si on est dans une situation de fin de jeu
      if (saisie(lettre, alphabet) == OK) { // Si la lettre n'a pas encore été utilisée
     		if (valider_lettre(lettre, secret, pendu, erreurs, win, ren) == 0)
 				afficher_erreur(*erreurs, win, ren);
			SDL_RenderPresent(ren);
    	}
   }
  	if ((valider_mot(secret, pendu) == 1)) { // Si le joueur a découvert toutes les lettres (a gagné)
   	afficher_image("assets/pendu/gagne_pendu.png", 247, 7, win, ren);
    	*etat_partie = PENDUFINI;
		if(etat_joueur == J1)
			*scorej2=*scorej2 +1;
		else
			*scorej1=*scorej1 +1;
		SDL_RenderPresent(ren);
	}
   if ((*erreurs) >= 10) { // Si le joueur est pendu (a perdu)
	 	afficher_image("assets/pendu/perdu_pendu.png", 247, 7, win, ren);
		for (i = 0; secret[i]; i++) // Affichage du mot caché
			affiche_lettre(secret[i], i, win, ren);
		*etat_partie = PENDUFINI;
		if(etat_joueur == J1)
			*scorej1=*scorej1 +1;
		else
			*scorej2=*scorej2 +1;
		SDL_RenderPresent(ren);
	}
   // Met à jour l'affichage selon les manipulations précédentes
   SDL_UpdateWindowSurface(win);
}



/**
 * \brief Initilise au hasard le mot à deviner avec une banque de mots
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void initialiser_mot_joueur(int * etat_partie, int etat_joueur, SDL_Event event, SDL_Window * win, SDL_Renderer * ren, char * secret_ecrit, char * secret, char * pendu, char * pseudoJ1, char * pseudoJ2, int * scorej1, int * scorej2) {
	switch(event.type) {
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_BACKSPACE) {
				int l = strlen(secret_ecrit);
				if (l > 0)
						secret_ecrit[l-1] = '\0';
				SDL_Rect txtDestRect;
				TTF_Font *police;
				SDL_Surface *texte = NULL;
				SDL_Color couleur_police = {0, 0, 0};
				police = TTF_OpenFont("assets/inter.ttf", 27);
				TTF_SetFontStyle(police,TTF_STYLE_BOLD);
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
				SDL_RenderClear(ren);
				afficher_image("assets/pendu/pendujcj.png", 0, 0, win, ren);
				if(etat_joueur ==J1){
					afficher_texte("assets/inter.ttf", 27, 510, 80, pseudoJ1, ren);
					afficher_texte("assets/inter.ttf", 27, 510, 222, pseudoJ2, ren);
				}else{
					afficher_texte("assets/inter.ttf", 27, 510, 80, pseudoJ2, ren);
					afficher_texte("assets/inter.ttf", 27, 510, 222, pseudoJ1, ren);
				}
				texte = TTF_RenderUTF8_Blended(police, secret_ecrit, couleur_police);
				txtDestRect.x = 520;
				txtDestRect.y = 315;
				SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(ren, texte);
				SDL_FreeSurface(texte);
				SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
				SDL_RenderCopy(ren, texte_tex, NULL, &txtDestRect);
				TTF_CloseFont(police);
				SDL_RenderPresent(ren);
			}
			if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
				int l = strlen(secret_ecrit);
				if (l <7)
					sprintf(secret_ecrit,"%s%c",secret_ecrit,event.key.keysym.sym);
				SDL_Rect txtDestRect;
				TTF_Font *police;
				SDL_Surface *texte = NULL;
				SDL_Color couleur_police = {0, 0, 0};
				police = TTF_OpenFont("assets/inter.ttf", 27);
				TTF_SetFontStyle(police,TTF_STYLE_BOLD);
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
				SDL_RenderClear(ren);
				afficher_image("assets/pendu/pendujcj.png", 0, 0, win, ren);
				if(etat_joueur ==J1){
					afficher_texte("assets/inter.ttf", 27, 510, 80, pseudoJ1, ren);
					afficher_texte("assets/inter.ttf", 27, 510, 222, pseudoJ2, ren);
				}else{
					afficher_texte("assets/inter.ttf", 27, 510, 80, pseudoJ2, ren);
					afficher_texte("assets/inter.ttf", 27, 510, 222, pseudoJ1, ren);
				}
				texte = TTF_RenderUTF8_Blended(police,secret_ecrit, couleur_police);
				txtDestRect.x = 520;
				txtDestRect.y = 315;
				SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(ren, texte);
				SDL_FreeSurface(texte);
				SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
				SDL_RenderCopy(ren, texte_tex, NULL, &txtDestRect);
				TTF_CloseFont(police);
				SDL_RenderPresent(ren);
			}
			break;
		case SDL_MOUSEBUTTONUP:
				if (event.button.x < 557 && event.button.x > 386 && event.button.y < 443 && event.button.y > 375 && strlen(secret_ecrit)>=4){
					////si clique sur valider
					sprintf(secret,secret_ecrit);
					int i;
					for (i = 0; i<secret[i]; i++)
				  		secret_ecrit[i] = '\0';
					// Boucle qui initialise le 2ème mot pendu utilisé pour le jeu (ex : _ _ _ _)
				   for (i = 0; i<secret[i]; i++)
				  		pendu[i] = '_';
				   //Affichage SDL des _ _ _
					afficher_image("assets/pendu/pendu.png", 0, 0, win, ren);
					afficher_texte("assets/inter.ttf", 19, 15, 110, pseudoJ1, ren);
					afficher_texte("assets/inter.ttf", 19, 15, 232, pseudoJ2, ren);
					afficher_nombre("assets/inter.ttf", 19, 26, 148, *scorej1, ren);
					afficher_nombre("assets/inter.ttf", 19, 26, 269, *scorej2, ren);
					SDL_RenderPresent(ren);
				   afficher_mystere(i-1, win, ren);
					SDL_RenderPresent(ren);
					*etat_partie = PENDUJEU;
				}
				if (event.button.x < 739 && event.button.x > 565 && event.button.y < 443 && event.button.y > 375){
					afficher_image("assets/pendu/pendu.png", 0, 0, win, ren);
					afficher_texte("assets/inter.ttf", 19, 15, 110, pseudoJ1, ren);
					afficher_texte("assets/inter.ttf", 19, 15, 232, pseudoJ2, ren);
					afficher_nombre("assets/inter.ttf", 19, 26, 148, *scorej1, ren);
					afficher_nombre("assets/inter.ttf", 19, 26, 269, *scorej2, ren);
					SDL_RenderPresent(ren);
					initialiser_mot_ordi(secret, pendu, win, ren);
					*etat_partie = PENDUJEU;
					SDL_RenderPresent(ren);
				}
				break;
			default: break;
}

}


/**
 * \brief Fonction qui s'occupe d'exécuter un tour de jeu dès que le joueur choisit une lettre, en vérifiant si la partie est terminée
 * \param event L'évènement détecté
 * \param etat_win La fenêtre où on se trouve
 * \param mode_de_jeu Joueur contre Joueur ou Joueur contre ordi
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param scorej1 Le score actuel du joueur 1
 * \param scorej2 Le score actuel du joueur 2
 */

void gestion_event_pendu(SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, SDL_Window * win, SDL_Renderer * ren, t_joueur * Joueur1, t_joueur * Joueur2) {
	switch(event.type) {
		case SDL_MOUSEBUTTONUP: // Relâchement du clic pour la non redondance de l'évènement
			// Bouton [QUITTER]
			if (event.button.x < 155 && event.button.x > 0 && event.button.y < 43 && event.button.y > 0) {
				if(*mode_de_jeu == JVSJ && *etat_joueur == J1){
               afficher_image("assets/menu_J1.png", 0, 0, win, ren);
            }else if(*mode_de_jeu == JVSJ && *etat_joueur == J2){
               afficher_image("assets/menu_J2.png", 0, 0, win, ren);
            }else{
               afficher_image("assets/menu.png", 0, 0, win, ren);
            }
				afficher_texte("assets/inter.ttf", 19, 290, 21, Joueur1->pseudo, ren);
				afficher_texte("assets/inter.ttf", 19, 530, 21, Joueur2->pseudo, ren);
				afficher_nombre("assets/inter.ttf", 19, 400, 21, Joueur1->score, ren);
            afficher_nombre("assets/inter.ttf", 19, 635, 21, Joueur2->score, ren);
				SDL_RenderPresent(ren);
				*etat_win = MENU;
			}
			// Partie en cours
			if (pendu.etat_partie == PENDUJEU) {
			// Les lettres à proposer
			// Une zone définie correspondant à une lettre et réalisant un tour de jeu avec celle qui correspond
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 69 && event.button.y > 28)
					pendu_tour(*etat_joueur, &(pendu.etat_partie),  &(Joueur1->score),  &(Joueur2->score), 'a', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 69 && event.button.y > 28)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'b', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 69 && event.button.y > 28)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'c', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 120 && event.button.y > 79)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'd', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 120 && event.button.y > 79)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'e', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 120 && event.button.y > 79)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'f', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 171 && event.button.y > 130)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'g', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 171 && event.button.y > 130)
					 pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'h', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 171 && event.button.y > 130)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'i', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 222 && event.button.y > 181)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'j', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 222 && event.button.y > 181)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'k', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 222 && event.button.y > 181)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'l', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 273 && event.button.y > 232)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'm', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 273 && event.button.y > 232)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'n', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 273 && event.button.y > 232)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'o', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 324 && event.button.y > 283)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'p', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 324 && event.button.y > 283)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'q', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 324 && event.button.y > 283)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'r', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 375 && event.button.y > 334)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 's', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 375 && event.button.y > 334)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 't', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 375 && event.button.y > 334)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'u', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 603 && event.button.x > 535 && event.button.y < 426 && event.button.y > 385)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'v', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 675 && event.button.x > 607 && event.button.y < 426 && event.button.y > 385)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'w', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 747 && event.button.x > 679 && event.button.y < 426 && event.button.y > 385)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'x', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 639 && event.button.x >571 && event.button.y < 477 && event.button.y > 436)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'y', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
				if (event.button.x < 715 && event.button.x >647 && event.button.y < 477 && event.button.y > 436)
					pendu_tour(*etat_joueur, &(pendu.etat_partie), &(Joueur1->score),  &(Joueur2->score), 'z', pendu.alphabet, pendu.pendu, pendu.secret, &(pendu.erreurs), win, ren);
			}
			break;
		default: break;
	}
	if(pendu.etat_partie == PENDU_JCJ_INIT){
		initialiser_mot_joueur(&(pendu.etat_partie),*etat_joueur,event, win, ren,pendu.secret_ecrit,pendu.secret, pendu.pendu, Joueur1->pseudo, Joueur2->pseudo,&(Joueur1->score),  &(Joueur2->score));
	}
}
