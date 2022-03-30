/**
 * \file batnav.c
 * \brief Fichier pour le jeu de la bataille navale
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 28 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <batnav.h>
#include <pile_batnav.h>

#define VIDE 0
#define NB_BAT 5
typedef enum {JOUEUR1 = 1, JOUEUR2, ATTAQUE_J1, ATTAQUE_J2, FIN_PARTIE} batnav_e; /* On commence l'enumération à 1 */
int bat_selec;
char direction;
batnav_t jeu;

/**
 * \brief Fonction qui initialise les plateaux de jeu de la bataille navale
 * \param l Nombre de lignes
 * \param c Nombre de colonnes
 * \return Renvoie un plateau de jeu
 */
plateau_t creer_plateau(int l, int c) {
	int i;
	plateau_t plateau_j;
	plateau_j.nb_lig = l;
	plateau_j.nb_col = c;
	case_t *la_case = malloc(sizeof(case_t) * plateau_j.nb_col * plateau_j.nb_lig);
	plateau_j.une_case = malloc(sizeof(case_t) * plateau_j.nb_lig);
	for (i = 0; i < plateau_j.nb_lig; i++)
		plateau_j.une_case[i] = la_case + (i * plateau_j.nb_col);
	return plateau_j;
}

/**
 * \brief Fonction qui initialise le stock de bateau du plateau d'un joueur
 * \param plateau_j Le plateau de jeu du joueur
 */
void init_bateaux(plateau_t * plateau_j) {
   /* Direction : horizontale */
	plateau_j->liste_bat[0].nom = "torpilleur";
	plateau_j->liste_bat[0].taille = 2;
	plateau_j->liste_bat[0].engage = 0;
	plateau_j->liste_bat[0].direction = 'h';

	plateau_j->liste_bat[1].nom = "contre_torpilleurA";
	plateau_j->liste_bat[1].taille = 3;
	plateau_j->liste_bat[1].engage = 0;
	plateau_j->liste_bat[1].direction = 'h';

	plateau_j->liste_bat[2].nom = "contre_torpilleurB";
	plateau_j->liste_bat[2].taille = 3;
	plateau_j->liste_bat[2].engage = 0;
	plateau_j->liste_bat[2].direction = 'h';

	plateau_j->liste_bat[3].nom = "croiseur";
	plateau_j->liste_bat[3].taille = 4;
	plateau_j->liste_bat[3].engage = 0;
	plateau_j->liste_bat[3].direction = 'h';

	plateau_j->liste_bat[4].nom = "porte_avions";
	plateau_j->liste_bat[4].taille = 5;
	plateau_j->liste_bat[4].engage = 0;
	plateau_j->liste_bat[4].direction = 'h';

	/* Direction : verticale */
	plateau_j->liste_bat[5].nom = "torpilleur";
	plateau_j->liste_bat[5].taille = 2;
	plateau_j->liste_bat[5].engage = 0;
	plateau_j->liste_bat[5].direction = 'v';

	plateau_j->liste_bat[6].nom = "contre_torpilleurA";
	plateau_j->liste_bat[6].taille = 3;
	plateau_j->liste_bat[6].engage = 0;
	plateau_j->liste_bat[6].direction = 'v';

	plateau_j->liste_bat[7].nom = "contre_torpilleurB";
	plateau_j->liste_bat[7].taille = 3;
	plateau_j->liste_bat[7].engage = 0;
	plateau_j->liste_bat[7].direction = 'v';

	plateau_j->liste_bat[8].nom = "croiseur";
	plateau_j->liste_bat[8].taille = 4;
	plateau_j->liste_bat[8].engage = 0;
	plateau_j->liste_bat[8].direction = 'v';

	plateau_j->liste_bat[9].nom = "porte_avions";
	plateau_j->liste_bat[9].taille = 5;
	plateau_j->liste_bat[9].engage = 0;
	plateau_j->liste_bat[9].direction = 'v';
}

/**
 * \brief Fonction qui rempli le plateau de jeu d'un joueur
 * \param plateau_j Le plateau du joueur qui doit être rempli
 */
void init_etat_plateau(plateau_t * plateau_j) {
   int i, j;
   for (i = 0; i < plateau_j->nb_lig; i++)
      for (j = 0; j < plateau_j->nb_col; j++) {
         plateau_j->une_case[i][j].occupe = 0;
         plateau_j->une_case[i][j].etat = 0;
      }
}

/**
 * \brief Fonction qui initialise une partie de la bataille navale
 */
void init_partie_batnav(void) {
	jeu.etat_partie = JOUEUR1;
   jeu.joueur1 = creer_plateau(10, 10);
   jeu.joueur2 = creer_plateau(10, 10);
   init_etat_plateau(&jeu.joueur1);
   init_etat_plateau(&jeu.joueur2);
   init_bateaux(&jeu.joueur1);
   init_bateaux(&jeu.joueur2);
	init_pile();
}

/**
 * \brief Fonction qui vérifie si les coordonnées sont dans la matrice
 * \param plateau_j Le plateau du joueur
 * \param x Coordonnée x de la case
 * \param y Coordonnée y de la case
 * \return Renvoie 1 si les coordonnées sont valides, 0 sinon
 */
int est_valide(plateau_t * plateau_j, int x, int y) {
	return ((x + 1 >= 0 && x <= plateau_j->nb_lig) && (y + 1 >= 0 && y <= plateau_j->nb_col));
}

/**
 * \brief Fonction qui regarde si les cases qui vont être occupées dans une direction sont toutes libres et valides
 * \param plateau_j Plateau du joueur que l'on cherche à remplir
 * \param x Coordonnée x de la case sélectionnée
 * \param y Coordonnée y de la case sélectionnée
 * \param taille_bat Taille du bateau que l'on souhaite placer
 * \return Retourne 1 si la direction est valide, 0 sinon
 */
int direction_valide(plateau_t * plateau_j, int x, int y, int direction, int taille_bat) {
   int max = 0, min = 0, cpt = 0;
   switch(direction) {
		// L'utilisateur clique sur un bateau horizontal
   	case 'h':
         max = taille_bat + x - 1;
         if (max < plateau_j->nb_col) {
            while (x <= max) {
					if (plateau_j->une_case[x][y].occupe == 0)
                  cpt += est_valide(plateau_j, x, y);
               x++;
            }
         } else {
            return 0;
			}
         if (cpt == taille_bat)
            return 1;
         break;
		// L'utilisateur clique sur un bateau vertical
      case 'v':
         min = y - taille_bat + 1;
         if (min >= 0) {
            while (y >= min) {
					if (plateau_j->une_case[x][y].occupe == 0)
                  cpt += est_valide(plateau_j, x, y);
               y--;
            }
         } else {
            return 0;
			}
         if (cpt == taille_bat)
            return 1;
         break;
      default:
			return 0;
			break;
   }
   return 0;
}

/**
 * \brief Fonction qui s'occupe du placement des bateaux de l'ordinateur
 * \param plateau_ordi Plateau de l'ordi que l'on cherche à remplir
 */
void placement_bateaux_ordi(plateau_t * plateau_ordi) {
	int bateau_place = 0, bat_encours, x, y, i, place =0;
	srand(time(NULL)); // Initialisation du hasard
	x = rand() % (10 + 1 - 1);
	y = rand() % (10 + 1 - 1);
	do {
		bat_encours = rand() % (10 + 1 - 1);
		if (plateau_ordi->liste_bat[bat_encours].engage == 0) {
			do {
				if (direction_valide(plateau_ordi, x, y, plateau_ordi->liste_bat[bat_encours].direction, plateau_ordi->liste_bat[bat_encours].taille)) {
					if (plateau_ordi->liste_bat[bat_encours].direction == 'h') {
						for (i = x; i < x + plateau_ordi->liste_bat[bat_encours].taille; i++) {
						 	plateau_ordi->une_case[i][y].num_bat = plateau_ordi->liste_bat[bat_encours].nom;
						 	plateau_ordi->une_case[i][y].occupe = 1;
					 	}
						plateau_ordi->liste_bat[bat_encours].engage = 1;
				     	plateau_ordi->liste_bat[bat_encours + NB_BAT].engage = 1;
						place++;
					} else {
						for (i = y; i > y - plateau_ordi->liste_bat[bat_encours].taille; i--) {
					 		plateau_ordi->une_case[x][i].num_bat = plateau_ordi->liste_bat[bat_encours].nom;
						 	plateau_ordi->une_case[x][i].occupe = 1;
						}
						plateau_ordi->liste_bat[bat_encours].engage = 1;
		 	         plateau_ordi->liste_bat[bat_encours - NB_BAT].engage = 1;
						place++;
					}
				} else {
						x = rand() % (10 + 1 - 1);
						y = rand() % (10 + 1 - 1);
				}
			} while(place == 0);
			place = 0;
			bateau_place++;
		}
	} while(bateau_place < 5);
}

/**
 * \brief Fonction qui s'occupe du placement des bateaux en les cachants si ils sont valides
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param taille_bat Taille du bateau déjà placé
 * \param immatriculation Nom du bateau déjà placé
 */
void vider_cargaison(SDL_Window * win, SDL_Renderer * ren, int taille_bat, char * immatriculation) {
	switch(taille_bat) {
		case 2:
			afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_2_h.png", 535, 96);
			afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_2_v.png", 535, 286);
			break;
		case 3:
			if (strcmp(immatriculation,"contre_torpilleurA") == 0) {
				afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_3_h.png", 624, 96);
				afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_3_v.png", 535, 373);
			} else {
				afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_3_h.png", 535, 142);
				afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_3_v.png", 586, 286);
			}
			break;
		case 4:
			afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_4_h.png", 535, 187);
			afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_4_v.png", 643, 286);
			break;
		case 5:
			afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_5_h.png", 535, 233);
			afficher_image(win, ren, "assets/batnav/bateaux/suppression_cargaison/taille_5_v.png", 701, 286);
			break;
		default: break;
	}
	SDL_RenderPresent(ren);
}

/**
 * \brief Fonction qui s'occupe du placement des bateaux si leur placement est valide
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param x Coordonnée x de la case sélectionnée
 * \param y Coordonnée y de la case sélectionnée
 * \param bat_selec Bateau sélectionné par le joueur pour le placer
 * \param JOUEUR Joueur qui place son bateau
 * \param couleur Couleur du joueur
 * \param plateau_j Plateau du joueur que l'on cherche à remplir
 * \param joueur1 Structure du pseudo et du score du joueur 1
 * \param joueur2 Structure du pseudo et du score du joueur 2
 */
void placement_case_bat(SDL_Window * win, SDL_Renderer * ren, int * mode_de_jeu, int x, int y, int direction, int bat_selec, int JOUEUR, char * couleur, plateau_t * plateau_j, t_joueur * joueur1, t_joueur * joueur2) {
  	char bateau[200];
  	int i, cpt = 0;
  	int taille_bat = plateau_j->liste_bat[bat_selec].taille;
   if (jeu.etat_partie == JOUEUR && direction_valide(plateau_j, x, y, direction, taille_bat)) {
      sprintf(bateau, "assets/batnav/bateaux/%s/taille_%i_%c_%s.png", couleur, taille_bat, direction, couleur);
      if (direction == 'h') {
         afficher_image(win, ren, bateau, (x * 41) + 72, (y * 41) + 85);
         for (i = x; i < x + taille_bat; i++) {
            plateau_j->une_case[i][y].num_bat = plateau_j->liste_bat[bat_selec].nom;
            plateau_j->une_case[i][y].occupe = 1;
				plateau_j->une_case[i][y].direction = plateau_j->liste_bat[bat_selec].direction;
         }
         plateau_j->liste_bat[bat_selec].engage = 1;
         plateau_j->liste_bat[bat_selec + NB_BAT].engage = 1;
      } else {
         afficher_image(win, ren, bateau, (x * 41) + 72, (y * 41) + 44 - 41 *(taille_bat - 2));
         for (i = y; i > y - taille_bat; i--) {
            plateau_j->une_case[x][i].num_bat = plateau_j->liste_bat[bat_selec].nom;
            plateau_j->une_case[x][i].occupe = 1;
				plateau_j->une_case[x][i].direction = plateau_j->liste_bat[bat_selec].direction;
         }
         plateau_j->liste_bat[bat_selec].engage = 1;
         plateau_j->liste_bat[bat_selec - NB_BAT].engage = 1;
      }
      SDL_RenderPresent(ren);
		vider_cargaison(win, ren, taille_bat, plateau_j->liste_bat[bat_selec].nom);

   }
   if (jeu.etat_partie == JOUEUR) {
      for (i = 0; i < 10; i++)
         if (plateau_j->liste_bat[i].engage == 1)
            cpt++;
   }
   if (cpt == 10) {
      if (jeu.etat_partie == JOUEUR1) {
			if(*mode_de_jeu == JVSJ){
         	jeu.etat_partie = JOUEUR2;
				SDL_Delay(2000);
         	afficher_image(win, ren, "assets/batnav/placement_verts.png", 0, 0);
         	afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
         	afficher_texte(ren, "assets/inter.ttf", 19, 525, 21, joueur2->pseudo);
         	afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
         	afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
         	SDL_RenderPresent(ren);
			}
			if(*mode_de_jeu == JVSO){
				init_bateaux(plateau_j);
				placement_bateaux_ordi(plateau_j);
				jeu.etat_partie = 3;
				SDL_Delay(2000);
				afficher_image(win, ren, "assets/batnav/jeu.png", 0, 0);
		      afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
				afficher_texte(ren, "assets/inter.ttf", 19, 525, 21, joueur2->pseudo);
				afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
				afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
				afficher_image(win, ren, "assets/batnav/tour_violet.png", 462, 70);
				afficher_texte(ren, "assets/inter.ttf", 19, 250, 80, "AU TOUR DU JOUEUR: ");
				SDL_RenderPresent(ren);
			}
      }
      else if (jeu.etat_partie == JOUEUR2) {
			jeu.etat_partie = 3;
			SDL_Delay(2000);
			afficher_image(win, ren, "assets/batnav/jeu.png", 0, 0);
	      afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
			afficher_texte(ren, "assets/inter.ttf", 19, 525, 21, joueur2->pseudo);
			afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
			afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
			afficher_image(win, ren, "assets/batnav/tour_violet.png", 462, 70);
			afficher_texte(ren, "assets/inter.ttf", 19, 250, 80, "AU TOUR DU JOUEUR: ");
			SDL_RenderPresent(ren);
      }
   }
}

/**
 * \brief Fonction qui gère les évènements SDL liés au placement des bateaux
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé* \param event Un détecteur d'évènements
 * \param event Un évènement SDL
 * \param etat_win La fenêtre où on se trouve
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param JOUEUR Joueur qui place son bateau
 * \param plateau_j Plateau du joueur que l'on cherche à remplir
 * \param couleur Couleur du joueur qui place son bateau
 * \param joueur1 Structure du pseudo et du score du joueur 1
 * \param joueur2 Structure du pseudo et du score du joueur 2
 */
void placement_bateaux(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int JOUEUR, plateau_t * plateau_j, char * couleur, t_joueur * joueur1, t_joueur * joueur2) {
   if (jeu.etat_partie == JOUEUR) {
      if (plateau_j->liste_bat[bat_selec].taille != VIDE) {
         if (event.button.x < 482 && event.button.x > 72 && event.button.y < 495 && event.button.y > 85) {
            placement_case_bat(win, ren, mode_de_jeu, (event.button.x - 72) / 41, (event.button.y - 85) / 41, direction, bat_selec, JOUEUR, couleur, plateau_j, joueur1, joueur2);
            bat_selec = -1;
         }
      }
		/* Emplacement du bateau de taille 2 et de direction horizontale */
		if (event.button.x < 618 && event.button.x > 535 && event.button.y < 138 && event.button.y > 96) {
         if (plateau_j->liste_bat[0].engage == 0) {
            direction = plateau_j->liste_bat[0].direction;
            bat_selec = 0;
         }
      }
		/* Emplacement du bateau de taille 3 et de direction horizontale */
      if (event.button.x < 748 && event.button.x > 624 && event.button.y < 138 && event.button.y > 96) {
         if (plateau_j->liste_bat[1].engage == 0) {
            direction = plateau_j->liste_bat[1].direction;
            bat_selec = 1;
         }
      }
		/* Emplacement du bateau (numéro 2) de taille 3 et de direction horizontale */
      if (event.button.x < 659 && event.button.x > 535 && event.button.y < 184 && event.button.y > 142) {
         if (plateau_j->liste_bat[2].engage == 0) {
            direction = plateau_j->liste_bat[2].direction;
            bat_selec = 2;
         }
      }
		/* Emplacement du bateau de taille 4 et de direction horizontale */
      if (event.button.x < 700 && event.button.x > 535 && event.button.y < 229 && event.button.y > 187) {
         if (plateau_j->liste_bat[3].engage == 0) {
          direction = plateau_j->liste_bat[3].direction;
          bat_selec = 3;
         }
      }
		/* Emplacement du bateau de taille 5 et de direction horizontale */
      if (event.button.x < 741 && event.button.x > 535 && event.button.y < 275 && event.button.y > 233) {
         if (plateau_j->liste_bat[4].engage == 0) {
            direction = plateau_j->liste_bat[4].direction;
            bat_selec = 4;
         }
      }
		/* Emplacement du bateau de taille 2 et de direction verticale */
      if (event.button.x < 577 && event.button.x > 535 && event.button.y < 369 && event.button.y > 286) {
         if (plateau_j->liste_bat[5].engage == 0) {
            direction = plateau_j->liste_bat[5].direction;
            bat_selec = 5;
         }
      }
		/* Emplacement du bateau de taille 3 et de direction verticale */
      if (event.button.x < 577 && event.button.x > 535 && event.button.y < 497 && event.button.y > 373) {
         if (plateau_j->liste_bat[6].engage == 0) {
            direction = plateau_j->liste_bat[6].direction;
            bat_selec = 6;
         }
      }
		/* Emplacement du bateau de taille 3 et de direction verticale */
      if (event.button.x < 628 && event.button.x > 586 && event.button.y < 410 && event.button.y > 286) {
         if (plateau_j->liste_bat[7].engage == 0) {
            direction = plateau_j->liste_bat[7].direction;
            bat_selec = 7;
         }
      }
		/* Emplacement du bateau de taille 4 et de direction verticale */
      if (event.button.x < 685 && event.button.x > 643 && event.button.y < 451 && event.button.y > 286) {
         if (plateau_j->liste_bat[8].engage == 0) {
            direction = plateau_j->liste_bat[8].direction;
            bat_selec = 8;
         }
      }
		/* Emplacement du bateau de taille 5 et de direction verticale */
      if (event.button.x < 743 && event.button.x > 701 && event.button.y < 492 && event.button.y > 286) {
         if (plateau_j->liste_bat[9].engage == 0) {
            direction = plateau_j->liste_bat[9].direction;
            bat_selec = 9;
         }
      }
   }
}

/**
 * \brief Fonction qui s'occupe de savoir si toutes les cases d'un bateau sont coulés
 * \param plateau_j Plateau du joueur que l'on cherche à remplir
 * \param bat_selec Bateau sélectionné par le joueur pour le placer
 */

int bateau_est_coule(plateau_t * plateau_j, char * bat_selec) {
   int i, j, cpt = 0;
   for (i = 0;i < plateau_j->nb_col; i++) {
      for (j = 0; j < plateau_j->nb_lig; j++) {
         if (plateau_j->une_case[i][j].num_bat == bat_selec && plateau_j->une_case[i][j].etat == 1 && plateau_j->une_case[i][j].occupe == 1)
            cpt++;
      }
   }
   return cpt;
}

/**
 * \brief Fonction qui s'occupe de la partie affrontement de la bataille navale
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param plateau_j Plateau de jeu du joueur
 * \param x Coordonnée x de la case sélectionnée
 * \param y Coordonnée y de la case sélectionnée
 * \param scoreJ1 Score du joueur 1
 * \param scoreJ2 Score du joueur 2
 * \param couleur Couleur du joueur
 */
void attaque_case_bat(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, plateau_t * plateau_j, int x, int y, int * scoreJ1, int * scoreJ2, char * couleur) {
	char bateau[200];
   int numero_bat = 0;
   int nbr = 0;
	int i, j, cpt;
   if (plateau_j->une_case[x][y].etat == 0 && plateau_j->une_case[x][y].occupe == 1) {
      if (jeu.etat_partie == ATTAQUE_J1) {
			plateau_j->une_case[x][y].etat = 1;
			afficher_image(win, ren, "assets/batnav/touche.png", x * 33 + 35, y * 33 + 159);
			afficher_image(win, ren, "assets/batnav/tour_vert.png", 462, 70);
			SDL_RenderPresent(ren);
			jeu.etat_partie = ATTAQUE_J2;
      } else {
			plateau_j->une_case[x][y].etat = 1;
			afficher_image(win, ren, "assets/batnav/touche.png", x * 33 + 416, y * 33 + 159);
			afficher_image(win, ren, "assets/batnav/tour_violet.png", 462, 70);
			SDL_RenderPresent(ren);
			jeu.etat_partie = ATTAQUE_J1;
      }
   } else if (plateau_j->une_case[x][y].etat == 0) {
      if (jeu.etat_partie == ATTAQUE_J1) {
        plateau_j->une_case[x][y].etat = 1;
        afficher_image(win, ren, "assets/batnav/pas_touche_bateau.png", x * 33 + 35, y * 33 + 159);
		  afficher_image(win, ren, "assets/batnav/tour_vert.png",462,70);
        SDL_RenderPresent(ren);
        jeu.etat_partie = ATTAQUE_J2;
      } else {
        plateau_j->une_case[x][y].etat = 1;
        afficher_image(win, ren, "assets/batnav/pas_touche_bateau.png", x * 33 + 417, y * 33 + 159);
		  afficher_image(win, ren, "assets/batnav/tour_violet.png", 462, 70);
        SDL_RenderPresent(ren);
        jeu.etat_partie = ATTAQUE_J1;
	  }
   }
	if (plateau_j->une_case[x][y].etat == 1 && plateau_j->une_case[x][y].occupe == 1) {
		cpt = bateau_est_coule(plateau_j, plateau_j->une_case[x][y].num_bat);
		for (i = 0; i < 10; i++)
		  	if (plateau_j->une_case[x][y].num_bat == plateau_j->liste_bat[i].nom && plateau_j->une_case[x][y].direction == plateau_j->liste_bat[i].direction)
				numero_bat = i;
		if (cpt == plateau_j->liste_bat[numero_bat].taille) {
			sprintf(bateau, "assets/batnav/bateaux/casses/bat%d_%c_%s_casse.png", plateau_j->liste_bat[numero_bat].taille, plateau_j->liste_bat[numero_bat].direction, couleur);
			if (plateau_j->une_case[x][y].direction == 'h') {
				for (j = x; j >= 0; j--) {
					if (plateau_j->une_case[x][y].num_bat == plateau_j->une_case[j][y].num_bat && est_valide(plateau_j, j, y))
						nbr++;
				}
				if (jeu.etat_partie == ATTAQUE_J2) {
					afficher_image(win, ren, bateau, (x - nbr + 1) * 33 + 34, y * 33 + 158);
					SDL_RenderPresent(ren);
				} else {
					afficher_image(win, ren, bateau, (x - nbr + 1) * 33 + 416, y * 33 + 158);
					SDL_RenderPresent(ren);
				}
			}
			if (plateau_j->une_case[x][y].direction == 'v') {
				for (j = y; j >= 0; j--)
					if (plateau_j->une_case[x][y].num_bat == plateau_j->une_case[x][j].num_bat && est_valide(plateau_j, x, j))
						nbr++;
				if (jeu.etat_partie == ATTAQUE_J2) {
					afficher_image(win, ren, bateau, x * 33 + 34, (y - nbr + 1) * 33 + 158);
					SDL_RenderPresent(ren);
				} else {
					afficher_image(win, ren, bateau, x * 33 + 416, (y - nbr + 1) * 33 + 158);
					SDL_RenderPresent(ren);
				}
			}
		}
	}
	cpt = 0;
   /* Fin de la partie */
   for (i = 0; i < 10; i++) {
     	for (j = 0; j < 10; j++)
      	if (plateau_j->une_case[i][j].etat == 1 && plateau_j->une_case[i][j].occupe == 1)
         	cpt++;
	}
   if (cpt == 17) {
		if (jeu.etat_partie == ATTAQUE_J1) {
			*scoreJ1 = *scoreJ1 + 1;
			afficher_image(win, ren, "assets/batnav/gagne_batnav.png", 47, 60);
			afficher_image(win, ren, "assets/batnav/perdu_batnav.png", 563, 60);
			SDL_RenderPresent(ren);
   	} else {
			*scoreJ2 = *scoreJ2 + 1;
			afficher_image(win, ren, "assets/batnav/gagne_batnav.png", 563, 60);
			afficher_image(win, ren, "assets/batnav/perdu_batnav.png", 47, 60);
			SDL_RenderPresent(ren);
   	}
   	jeu.etat_partie = FIN_PARTIE;
   }
}

/**
 * \brief Fonction qui s'occupe de la partie affrontement de la bataille navale
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param plateau_ordi Plateau de jeu de l'ordi
 * \param joueur1 Structure du pseudo et du score du joueur 1
 * \param ordi Structure du pseudo et du score de l'ordi
 */
void tour_ordi_mode_IA(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, plateau_t * plateau_ordi, t_joueur * joueur1, t_joueur * ordi) {
	int touche = 0, i, j, cpt;
	coord_ordi_t coord_case;
	SDL_Delay(500);
	srand(time(NULL)); // Initialisation du hasard
	if (pile_vide()) {
		do {
			coord_case.x = rand() % (9 + 1 - 1);
			coord_case.y = rand() % (9 + 1 - 1);
		} while (plateau_ordi->une_case[coord_case.x][coord_case.y].etat == 1);
		attaque_case_bat(win, ren, event, plateau_ordi, coord_case.x, coord_case.y, &(joueur1->score), &(ordi->score), "vert");
		empiler(coord_case);
	} else {
		while (touche == 0 && !pile_vide()) {
			coord_case = lire_sommet();
			if (plateau_ordi->une_case[coord_case.x][coord_case.y].occupe == 1) {
				if (plateau_ordi->une_case[coord_case.x-1][coord_case.y].etat == 0 && est_valide(plateau_ordi, (coord_case.x - 1), (coord_case.y))) {
					attaque_case_bat(win, ren, event, plateau_ordi, (coord_case.x - 1), coord_case.y, &(joueur1->score), &(ordi->score), "vert");
					touche = 1;
					(coord_case.x)--;
					empiler(coord_case);
				} else if (plateau_ordi->une_case[coord_case.x][coord_case.y + 1].etat == 0 && est_valide(plateau_ordi, (coord_case.x), (coord_case.y + 1))) {
					attaque_case_bat(win, ren, event, plateau_ordi, coord_case.x, (coord_case.y + 1), &(joueur1->score), &(ordi->score), "vert");
					touche = 1;
					(coord_case.y)++;
					empiler(coord_case);
				} else if (plateau_ordi->une_case[coord_case.x + 1][coord_case.y].etat == 0 && est_valide(plateau_ordi, (coord_case.x + 1), (coord_case.y))) {
					attaque_case_bat(win, ren, event, plateau_ordi, (coord_case.x + 1), coord_case.y, &(joueur1->score), &(ordi->score), "vert");
					touche = 1;
					(coord_case.x)++;
					empiler(coord_case);
				} else if (plateau_ordi->une_case[coord_case.x][coord_case.y - 1].etat == 0 && est_valide(plateau_ordi, (coord_case.x), (coord_case.y - 1))) {
					attaque_case_bat(win, ren, event, plateau_ordi, coord_case.x, (coord_case.y - 1), &(joueur1->score), &(ordi->score), "vert");
					touche = 1;
					empiler(coord_case);
				} else {
					depiler(&coord_case);
				}
			} else {
				depiler(&coord_case);
			}
		}
		if (pile_vide()) {
			do {
				coord_case.x = rand() % (10 + 1 - 1);
				coord_case.y = rand() % (10 + 1 - 1);
			} while (plateau_ordi->une_case[coord_case.x][coord_case.y].etat == 1);
			attaque_case_bat(win, ren, event, plateau_ordi, coord_case.x, coord_case.y, &(joueur1->score), &(ordi->score), "vert");
			empiler(coord_case);
		}
		afficher_image(win, ren, "assets/batnav/tour_violet.png", 462, 70);
		SDL_RenderPresent(ren);
		jeu.etat_partie = ATTAQUE_J1;
		/* Fin de la partie */
	   for (i = 0; i < 10; i++)
	     	for (j = 0; j < 10; j++)
	      	if (plateau_ordi->une_case[i][j].etat == 1 && plateau_ordi->une_case[i][j].occupe == 1)
	         	cpt++;
	   if (cpt == 17) {
			// Le joueur a gagné
			if (jeu.etat_partie == ATTAQUE_J1) {
				joueur1->score += 1;
				afficher_image(win, ren, "assets/batnav/gagne_batnav.png", 47, 60);
				afficher_image(win, ren, "assets/batnav/perdu_batnav.png", 563, 60);
				SDL_RenderPresent(ren);
			// L'ordinateur a gagné
			} else {
				ordi->score += 1;
				afficher_image(win, ren, "assets/batnav/gagne_batnav.png", 563, 60);
				afficher_image(win, ren, "assets/batnav/perdu_batnav.png", 47, 60);
				SDL_RenderPresent(ren);
	   	}
	   	jeu.etat_partie = FIN_PARTIE;
	   }
	}
}

/**
 * \brief Fonction qui s'occupe des évènements d'une partie de bataille navale (joueur contre joueur)
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où on se trouve
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param etat_joueur à qui le tour
 * \param joueur1 Structure du pseudo et du score du joueur 1
 * \param joueur2 Structure du pseudo et du score du joueur 2
 */
void gestion_event_batnav(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2) {
   switch (event.type) {
      case SDL_MOUSEBUTTONUP:
         if (event.button.x < 127 && event.button.x > 0 && event.button.y < 40 && event.button.y > 0) {
				if (*mode_de_jeu == JVSJ && *etat_joueur == J1) {
               afficher_image(win, ren, "assets/menu_J1.png", 0, 0);
            } else if (*mode_de_jeu == JVSJ && *etat_joueur == J2) {
               afficher_image(win, ren, "assets/menu_J2.png", 0, 0);
            } else {
               afficher_image(win, ren, "assets/menu.png", 0, 0);
            }
            afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
            afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
            afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
            afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
            SDL_RenderPresent(ren);
            *etat_win = MENU;
            break;
         }
         placement_bateaux(win, ren, event, etat_win, mode_de_jeu, JOUEUR1, &jeu.joueur1, "violet", joueur1, joueur2);
         placement_bateaux(win, ren, event, etat_win, mode_de_jeu, JOUEUR2, &jeu.joueur2, "vert", joueur1, joueur2);
         if (jeu.etat_partie == ATTAQUE_J1)
            if (event.button.x < 364 && event.button.x > 35 && event.button.y < 488 && event.button.y > 160)
               attaque_case_bat(win, ren, event, &jeu.joueur2,(event.button.x - 35) / 33, (event.button.y - 160) / 33, &(joueur1->score), &(joueur2->score), "violet");
         if (jeu.etat_partie == ATTAQUE_J2) {
				if (*mode_de_jeu == JVSJ) {
            	if (event.button.x < 746 && event.button.x > 416 && event.button.y < 488 && event.button.y > 158)
               	attaque_case_bat(win, ren, event, &jeu.joueur1, (event.button.x - 416) / 33, (event.button.y - 158) / 33, &(joueur1->score), &(joueur2->score), "vert");
				} else {
					tour_ordi_mode_IA(win, ren, event, &jeu.joueur1, joueur1, joueur2);
				}
			}
			break;
      default: break;
   }
}
