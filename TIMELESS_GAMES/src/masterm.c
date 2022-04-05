/**
 * \file masterm.c
 * \brief Fichier pour le jeu du mastermind
 * \author Duclos ChristaL
 * \version 2.0
 * \date 05 avril 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <masterm.h>

t_master mastermind;

/**
 * \brief Fonction qui initialise une partie de mastermind
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 */
void init_partie_masterm(int * mode_de_jeu) {
	int i;
	mastermind.propo_couleur = (char*)malloc(sizeof(char)*4); // Contient les propositions qui seront effectuées par le joueur
	mastermind.code_secret = (char*)malloc(sizeof(char)*4); // Contient le code secret de couleurs
	mastermind.position = 0; // Contient la position où sera placée la prochaine couleur
	mastermind.nb_essais = 0; // Contient le nombre d'essais de proposition du joueur
	mastermind.etat_partie= MASTERMIND_JCJ_INIT; // On entre dans la phase d'initialisation d'une partie joueur contre joueur par défaut
	for (i = 0; i < 4; i++)
		mastermind.code_secret[i] = ' ';
	// Si l'on est en mode joueur contre ordi, on joue directement
	if (*mode_de_jeu == JVSO) {
  		saisir_code_ordi(mastermind.code_secret);
		mastermind.etat_partie = MASTERMINDJEU;
	}
	for (i = 0; i < 4; i++)
		mastermind.propo_couleur[i] = ' ';
}

/**
 * \brief Tour de jeu normal quand on valide la combinaison
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param pseudoJ1 Pseudo du joueur 1
 * \param pseudoJ2 Pseudo du joueur 2
 * \param scoreJ1 Score du joueur 1
 * \param scoreJ2 Score du joueur 2
 */
void init_mastermind_joueur(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, char * pseudoJ1, char * pseudoJ2, int * scoreJ1, int * scoreJ2) {
	// Première case pour mettre une couleur
	if (event.button.x < 510 && event.button.x > 464 && event.button.y < 319 && event.button.y > 275)
		mastermind.position = 0;
	// Deuxième case pour mettre une couleur
	if (event.button.x < 558 && event.button.x > 512 && event.button.y < 319 && event.button.y > 275)
		mastermind.position = 1;
	// Troisième case pour mettre une couleur
	if (event.button.x < 606 && event.button.x > 560 && event.button.y < 319 && event.button.y > 275)
		mastermind.position = 2;
	// Quatrième case pour mettre une couleur
	if (event.button.x < 654 && event.button.x > 608 && event.button.y < 319 && event.button.y > 275)
   	mastermind.position = 3;
	// Proposition de la couleur rouge
	if (event.button.x < 440 && event.button.x > 387 && event.button.y < 400  && event.button.y > 347 ) {
		mastermind.code_secret[mastermind.position] = 'R'; // Affiche la couleur rouge à la position indiquée
		afficher_image(win, ren, "assets/mastermind/propositions/rouge_propo.png", 464  + (mastermind.position) * 48, 275);
		SDL_RenderPresent(ren);
		if (mastermind.position >= 3)
	      mastermind.position = 0;
	   else
	      mastermind.position++;
	}
	// Proposition de la couleur verte
	if (event.button.x < 500 && event.button.x > 445 && event.button.y < 400  && event.button.y > 347) {
		mastermind.code_secret[mastermind.position] = 'V'; // Affiche la couleur verte à la position indiquée
		afficher_image(win, ren, "assets/mastermind/propositions/vert_propo.png", 464  + (mastermind.position) * 48, 275);
		SDL_RenderPresent(ren);
		if (mastermind.position >= 3)
			mastermind.position = 0;
		else
			mastermind.position++;
	}
	// Proposition de la couleur bleue
	if (event.button.x < 559 && event.button.x > 507 && event.button.y < 400  && event.button.y > 347) {
		mastermind.code_secret[mastermind.position] = 'B'; // Affiche la couleur bleue à la position indiquée
		afficher_image(win, ren, "assets/mastermind/propositions/bleu_propo.png", 464  + (mastermind.position) * 48, 275);
		SDL_RenderPresent(ren);
		if (mastermind.position >= 3)
			mastermind.position = 0;
		else
			mastermind.position++;
	}
	// Proposition de la couleur jaune
	if(event.button.x < 618 && event.button.x > 564 && event.button.y < 400  && event.button.y > 347) {
		mastermind.code_secret[mastermind.position] = 'J'; // Affiche la couleur jaune à la position indiquée
		afficher_image(win, ren, "assets/mastermind/propositions/jaune_propo.png", 464  + (mastermind.position) * 48, 275);
		SDL_RenderPresent(ren);
		if (mastermind.position >= 3)
			mastermind.position = 0;
		else
			mastermind.position++;
	}
	// Proposition de la couleur blanche
	if (event.button.x < 679 && event.button.x > 624 && event.button.y < 400 && event.button.y > 347) {
		mastermind.code_secret[mastermind.position] = 'W'; // Affiche la couleur blanche à la position indiquée
		afficher_image(win, ren, "assets/mastermind/propositions/blanc_propo.png", 464  + (mastermind.position) * 48, 275);
		SDL_RenderPresent(ren);
		if (mastermind.position >= 3)
			mastermind.position = 0;
		else
			mastermind.position++;
	}
	// Proposition de la couleur noire
	if (event.button.x < 743 && event.button.x > 687 && event.button.y < 400 && event.button.y > 347) {
		mastermind.code_secret[mastermind.position] = 'N'; // Affiche la couleur noire à la position indiquée
		afficher_image(win, ren, "assets/mastermind/propositions/noir_propo.png", 464  + (mastermind.position) * 48, 275);
		SDL_RenderPresent(ren);
		if (mastermind.position >= 3)
			mastermind.position = 0;
		else
			mastermind.position++;
	}
	// Valider la combinaison
	if (event.button.x < 557 && event.button.x > 386 && event.button.y < 493 && event.button.y > 426 && proposition_pas_vide(mastermind.code_secret) == 1) {
		afficher_image(win, ren, "assets/mastermind/mastermind.png", 0, 0);
		afficher_texte(ren, "assets/inter.ttf", 19, 19, 110, pseudoJ1);
		afficher_texte(ren, "assets/inter.ttf", 19, 19, 218, pseudoJ2);
		afficher_nombre(ren, "assets/inter.ttf", 19, 26, 148, *scoreJ1);
		afficher_nombre(ren, "assets/inter.ttf", 19, 26, 254, *scoreJ2);
		afficher_image(win, ren, "assets/mastermind/enlever_proposition.png", 229, 448);
		SDL_RenderPresent(ren);
	   mastermind.position = 0;
		mastermind.etat_partie = MASTERMINDJEU;
	}
	// Combinaison aléatoire
	if (event.button.x < 740 && event.button.x > 564 && event.button.y < 493 && event.button.y > 426) {
		afficher_image(win, ren, "assets/mastermind/mastermind.png", 0, 0);
		afficher_texte(ren, "assets/inter.ttf", 19, 19, 110, pseudoJ1);
		afficher_texte(ren, "assets/inter.ttf", 19, 19, 218, pseudoJ2);
		afficher_nombre(ren, "assets/inter.ttf", 19, 26, 148, *scoreJ1);
		afficher_nombre(ren, "assets/inter.ttf", 19, 26, 254, *scoreJ2);
		afficher_image(win, ren, "assets/mastermind/enlever_proposition.png", 229, 448);
		SDL_RenderPresent(ren);
		saisir_code_ordi(mastermind.code_secret);
		mastermind.position = 0;
		mastermind.etat_partie = MASTERMINDJEU;
	}
}

/**
 * \brief L'ordinateur initialise au hasard le code de couleurs à trouver
 * \param code_secret Le code à initialiser
 */
void saisir_code_ordi(char * code_secret) {
   int i, c_rand;
   char couleurs[6] = {'R', 'V', 'B', 'J', 'W', 'N'};
   srand(time(NULL)); // Initialisation du hasard
   for (i = 0; i < 4; i++) {
      c_rand = rand() % (6 + 1 - 1); // Génération d'un nombre entre 0 et 5
      code_secret[i] = couleurs[c_rand];
   }
  code_secret[i] = '\0';
}

/**
 * \brief Vérifie si le joueur a rentré une proposition complète de 4 couleurs
 * \param propo_couleur La combinaison de couleurs
 * \return Renvoie 0 si la proposition n'est pas complète, 1 si elle est complète
 */
int proposition_pas_vide(char * propo_couleur) {
	int i;
	for (i = 0; i < 4; i++){
		if (propo_couleur[i] == ' ')
			return 0;
	}
	return 1;
}

/**
 * \brief Compte le nombre de bonnes couleurs entre le code secret et le code de jeu
 * \param code La proposition de couleurs
 * \param code_secret Le code secret
 * \return Renvoie le nombre de pions bien placés
 */
int nb_bonne_place(char * code, char * code_secret) {
   int i, cpt = 0;
   for (i = 0; i < 4; i++) {
      if (code[i] == code_secret[i])
         cpt++;
   }
   return cpt;
}

/**
 * \brief Compte le nombre de bonnes couleurs entre le code secret et le code de jeu
 * \param code La proposition de couleurs
 * \param code_secret Le code secret
 * \param nb_place Le nombre de pions bien placés précédemment calculés
 * \return Renvoie le nombre de pions de bonnes couleurs mal placés
 */
int nb_bonne_couleur(char * code, char * code_secret, int nb_place) {
   int i, cpt = 0;
   int nb_R = 0, nb_V = 0, nb_B = 0, nb_J = 0, nb_W = 0, nb_N = 0;
   int nb_prop_R = 0, nb_prop_V = 0, nb_prop_B = 0, nb_prop_J = 0, nb_prop_W = 0, nb_prop_N = 0;

   // Comptage de chaque couleurs du tableau de la solution
   for (i = 0; i < 4; i++) {
      switch (code_secret[i]) {
         case 'R' : nb_R++; break;
         case 'B' : nb_B++; break;
         case 'V' : nb_V++; break;
         case 'J' : nb_J++; break;
         case 'W' : nb_W++; break;
         case 'N' : nb_N++; break;
      }
   }
   // Comptage de chaque couleurs du tableau de la proposition
   for (i = 0; i < 4; i++) {
      switch(code[i]) {
         case 'R' : nb_prop_R++; break;
         case 'B' : nb_prop_B++; break;
         case 'V' : nb_prop_V++; break;
         case 'J' : nb_prop_J++; break;
         case 'W' : nb_prop_W++; break;
         case 'N' : nb_prop_N++; break;
      }
   }
   // Comptage des pions de la bonne couleur et somme des minimums
   if (nb_R <= nb_prop_R) // couleur rouge
      cpt += nb_R;
   else
      cpt += nb_prop_R;
   if (nb_V <= nb_prop_V) // couleur verte
      cpt += nb_V;
   else
      cpt += nb_prop_V;
   if (nb_B <= nb_prop_B) // couleur bleue
      cpt += nb_B;
   else
      cpt += nb_prop_B;
   if (nb_J <= nb_prop_J) // couleur jaune
      cpt += nb_J;
   else
      cpt += nb_prop_J;
   if (nb_W <= nb_prop_W) // couleur blanche
      cpt += nb_W;
   else
      cpt += nb_prop_W;
   if (nb_N <= nb_prop_N) // couleur noire
      cpt += nb_N;
   else
      cpt += nb_prop_N;
   return (cpt - nb_place); // on retire les pions bien placés
}

/**
 * \brief Affiche les couleurs choisies
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param position La position actuelle du prochain jeton à ajouter ou remplacer du plateau
 * \param propo_couleur La combinaison de couleurs proposée
 * \param couleur La couleur du pion de couleur qu'on veut afficher
 */
void affiche_propo(SDL_Window * win, SDL_Renderer * ren, int * position, char * propo_couleur, char couleur) {
   switch (couleur) {
      case 'R':
         propo_couleur[(*position)] = 'R'; // Affiche la couleur rouge à la position indiquée
         afficher_image(win, ren, "assets/mastermind/propositions/rouge_propo.png", 229 + (*position) * 48, 448);
         break;
      case 'V':
         propo_couleur[(*position)] = 'V'; // Affiche la couleur verte à la position indiquée
         afficher_image(win, ren, "assets/mastermind/propositions/vert_propo.png", 229 + (*position) * 48, 448);
         break;
      case 'B':
         propo_couleur[(*position)] = 'B'; // Affiche la couleur bleue à la position indiquée
         afficher_image(win, ren, "assets/mastermind/propositions/bleu_propo.png", 229 + (*position) * 48, 448);
         break;
      case 'J':
         propo_couleur[(*position)] = 'J'; // Affiche la couleur jaune à la position indiquée
         afficher_image(win, ren, "assets/mastermind/propositions/jaune_propo.png", 229 + (*position) * 48, 448);
         break;
      case 'W':
         propo_couleur[(*position)] = 'W'; // Affiche la couleur blanche à la position indiquée
         afficher_image(win, ren, "assets/mastermind/propositions/blanc_propo.png", 229 + (*position) * 48, 448);
         break;
      case 'N':
         propo_couleur[(*position)] = 'N'; // Affiche la couleur noire à la position indiquée
         afficher_image(win, ren, "assets/mastermind/propositions/noir_propo.png", 229 + (*position) * 48, 448);
         break;
      default: break;
   }
   // Positionnement du jeton sur le prochain pion que l'on va modifier
   if ((*position) >= 3)
      (*position) = 0;
   else
      (*position)++;
}

/**
 * \brief Si la combinaison n'est pas celle recherchée on l'affiche et donne des informations dessus
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param bonne_couleur Le nombre de bonnes couleurs mal placées dans la combinaison proposée
 * \param bonne_place Le nombre de bonnes couleurs bien placées dans la combinaison proposée
 * \param nb_essais Le nombre actuel d'essais du joueur
 * \param propo_couleur La combinaison de couleurs proposée
 * \param code_secret Le code secret qu'il faut deviner
 */
void afficher_essai(SDL_Window * win, SDL_Renderer * ren, int bonne_couleur, int bonne_place, int * nb_essais, char * propo_couleur, char * code_secret) {
   int i;
   for (i = 0; i < 4; i++) {
      // Affiche la combinaison de l'essai dans le récapitulatif des essais
      switch(propo_couleur[i]) {
         case 'R': // Affiche la couleur rouge à la place i à la ligne de l'essai
            afficher_image(win, ren, "assets/mastermind/essais/rouge_essai.png", 258 + i * 33, 402 - (*nb_essais) * 41); break;
         case 'V': // Affiche la couleur verte à la place i à la ligne de l'essai
            afficher_image(win, ren, "assets/mastermind/essais/vert_essai.png", 258 + i * 33, 402 - (*nb_essais) * 41); break;
         case 'B': // Affiche la couleur bleue à la place i à la ligne de l'essai
            afficher_image(win, ren, "assets/mastermind/essais/bleu_essai.png", 258 + i * 33, 402 - (*nb_essais) * 41); break;
         case 'J': // Affiche la couleur jaune à la place i à la ligne de l'essai
            afficher_image(win, ren, "assets/mastermind/essais/jaune_essai.png", 258 + i * 33, 402 - (*nb_essais) * 41); break;
         case 'W': // Affiche la couleur blanche à la place i à la ligne de l'essai
            afficher_image(win, ren, "assets/mastermind/essais/blanc_essai.png", 258 + i * 33, 402 - (*nb_essais) * 41); break;
         case 'N': // Affiche la couleur noire à la place i à la ligne de l'essai
            afficher_image(win, ren, "assets/mastermind/essais/noir_essai.png", 258 + i * 33, 402 - (*nb_essais) * 41); break;
         default: break;
      }
   }
  	// Affiche le nombre de bonnes couleurs bien placées de l'essai
	char bn_place[255];
	sprintf(bn_place, "assets/mastermind/points/%ibp.png", bonne_place);
   afficher_image(win, ren, bn_place, 459, 402 - (*nb_essais) * 41);
   // Affiche le nombre de bonnes couleurs mal placées de l'essai
	char bn_couleur[255];
	sprintf(bn_couleur, "assets/mastermind/points/%ibc.png", bonne_couleur);
   afficher_image(win, ren, bn_couleur, 498, 402 - (*nb_essais) * 41);
}

/**
 * \brief En cas de défaite, affiche la combinaison secrète
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param code_secret Le code secret
 */
void afficher_resultat(SDL_Window * win, SDL_Renderer * ren, char * code_secret) {
   int i;
   for (i = 0; i < 4; i++) {
      switch(code_secret[i]) {
         case 'R': // Affiche la couleur rouge à la place i
            afficher_image(win, ren, "assets/mastermind/propositions/rouge_propo.png", (229 + i * 48), 448); break;
         case 'V': // Affiche la couleur verte à la place i
            afficher_image(win, ren, "assets/mastermind/propositions/vert_propo.png", (229 + i * 48), 448); break;
         case 'B': // Affiche la couleur bleue à la place i
            afficher_image(win, ren, "assets/mastermind/propositions/bleu_propo.png", (229 + i * 48), 448); break;
         case 'J': // Affiche la couleur jaune à la place i
            afficher_image(win, ren, "assets/mastermind/propositions/jaune_propo.png", (229 + i * 48), 448); break;
         case 'W': // Affiche la couleur blanche à la place i
            afficher_image(win, ren, "assets/mastermind/propositions/blanc_propo.png", (229 + i * 48), 448); break;
         case 'N': // Affiche la couleur noire à la place i
            afficher_image(win, ren, "assets/mastermind/propositions/noir_propo.png", (229 + i * 48), 448); break;
         default: break;
      }
   }
}

/**
 * \brief Tour de jeu normal quand on valide la combinaison
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param etat_joueur Etat du joueur
 * \param etat_partie Etat de la partie : terminée ou non
 * \param scoreJ1 Score du joueur 1
 * \param scoreJ2 Score du joueur 2
 * \param nb_essais Le nombre actuel d'essais du joueur
 * \param propo_couleur La combinaison de couleurs proposée
 * \param code_secret Le code secret qu'il faut deviner
 * \param position La position actuelle du prochain jeton à ajouter ou remplacer du plateau
 */
void mastermind_tour(SDL_Window * win, SDL_Renderer * ren, int mode_de_jeu, int etat_joueur, int * etat_partie, int * scoreJ1, int * scoreJ2, int * nb_essais, char * propo_couleur, char * code_secret, int * position) {
	int i;
	// Si l'on fait une proposition fausse et qu'il reste des essais
   if ((*nb_essais) < 10 && nb_bonne_place(propo_couleur, code_secret) != 4) {
      afficher_essai(win, ren, nb_bonne_couleur(propo_couleur, code_secret, nb_bonne_place(propo_couleur, code_secret)), nb_bonne_place(propo_couleur, code_secret), nb_essais, propo_couleur, code_secret);
      afficher_image(win, ren, "assets/mastermind/enlever_proposition.png", 229, 448);
      SDL_RenderPresent(ren);
      (*nb_essais)++;
      (*position) = 0;
		for (i = 0;i < 4; i++)
			propo_couleur[i] = ' ';
   }
   // Si l'on fait une proposition correcte qu'il reste des essais (= on gagne)
   if ((*nb_essais) < 10 && nb_bonne_place(propo_couleur, code_secret) == 4) {
      afficher_image(win, ren, "assets/mastermind/gagne_masterm.png", 10, 60);
      afficher_image(win, ren, "assets/mastermind/gagne_cercle.png", 215, 440);
		// Gestion des scores selon le mode de jeu
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
		*etat_partie = MASTERMINDFINI;
		afficher_resultat(win, ren, code_secret);
      SDL_RenderPresent(ren);
		for (i = 0;i < 4; i++)
			propo_couleur[i] = ' ';
		free(mastermind.propo_couleur);
		free(mastermind.code_secret);
   }
   // Si l'on a plus d'essai disponible, on perd
   if ((*nb_essais) >= 10) {
      afficher_image(win, ren, "assets/mastermind/perdu_masterm.png", 10, 60);
      afficher_image(win, ren, "assets/mastermind/perdu_cercle.png", 215, 440);
		// Gestion des scores selon le mode de jeu
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
		*etat_partie = MASTERMINDFINI;
      afficher_resultat(win, ren, code_secret);
      SDL_RenderPresent(ren);
		for (i = 0;i < 4; i++)
			propo_couleur[i] = ' ';
		free(mastermind.propo_couleur);
		free(mastermind.code_secret);
   }
}

/**
 * \brief Si la combinaison n'est pas celle recherchée, on l'affiche et on donne des informations dessus
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où on se trouve
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param etat_joueur Etat du joueur
 * \param joueur1 Structure qui contient les informations du joueur 1
 * \param joueur2 Structure qui contient les informations du joueur 2
 */
 void gestion_event_masterm(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2) {
   switch (event.type) {
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
       	if (mastermind.etat_partie == MASTERMINDJEU) {
       		// Bouton VALIDER COMBINAISON
				if (proposition_pas_vide(mastermind.propo_couleur) == 1) {
       			if (event.button.x < 148 && event.button.x > 9 && event.button.y < 392 && event.button.y > 326) {
         			mastermind_tour(win, ren, *mode_de_jeu, *etat_joueur, &(mastermind.etat_partie), &(joueur1->score), &(joueur2->score), &(mastermind.nb_essais), mastermind.propo_couleur, mastermind.code_secret, &(mastermind.position));
       			}
				}
       		// Sélection de l'endroit pour la couleur à placer
       		if (event.button.x < 274 && event.button.x > 229 && event.button.y < 493 && event.button.y > 448) {
         		mastermind.position = 0;
       		}
       		if (event.button.x < 322 && event.button.x > 277 && event.button.y < 493 && event.button.y > 448) {
         		mastermind.position = 1;
       		}
       		if (event.button.x < 371 && event.button.x > 326 && event.button.y < 493 && event.button.y > 448) {
         		mastermind.position = 2;
       		}
       		if(event.button.x < 420 && event.button.x > 375 && event.button.y < 493 && event.button.y > 448) {
         		mastermind.position = 3;
       		}
       		// Proposition de la couleur rouge
       		if (event.button.x < 700 && event.button.x > 621 && event.button.y < 83 && event.button.y > 9) {
		         affiche_propo(win, ren, &(mastermind.position), mastermind.propo_couleur, 'R');
		         SDL_RenderPresent(ren);
       		}
         	// Proposition de la couleur verte
       		if (event.button.x < 700 && event.button.x > 621 && event.button.y < 159 && event.button.y > 88) {
		         affiche_propo(win, ren, &(mastermind.position), mastermind.propo_couleur, 'V');
		         SDL_RenderPresent(ren);
		      }
		      // Proposition de la couleur bleue
		      if (event.button.x < 700 && event.button.x > 621 && event.button.y < 236 && event.button.y > 167) {
		         affiche_propo(win, ren, &(mastermind.position), mastermind.propo_couleur, 'B');
		         SDL_RenderPresent(ren);
		      }
		      // Proposition de la couleur jaune
		      if(event.button.x < 700 && event.button.x > 621 && event.button.y < 312 && event.button.y > 242) {
		         affiche_propo(win, ren, &(mastermind.position), mastermind.propo_couleur, 'J');
		         SDL_RenderPresent(ren);
		      }
		      // Proposition de la couleur blanche
		      if (event.button.x < 700 && event.button.x > 621 && event.button.y < 392 && event.button.y > 319) {
		         affiche_propo(win, ren, &(mastermind.position), mastermind.propo_couleur, 'W');
		         SDL_RenderPresent(ren);
		      }
				// Proposition de la couleur noire
		      if (event.button.x < 700 && event.button.x > 621 && event.button.y < 474 && event.button.y > 402) {
					affiche_propo(win, ren, &(mastermind.position), mastermind.propo_couleur, 'N');
		         SDL_RenderPresent(ren);
		      }
     		}
			// Si l'on doit permettre au joueur d'entrer la combinaison secrète
			if (mastermind.etat_partie == MASTERMIND_JCJ_INIT)
				init_mastermind_joueur(win, ren, event, joueur1->pseudo, joueur2->pseudo, &(joueur1->score), &(joueur2->score));
       	break;
     	default: break;
   }
}
