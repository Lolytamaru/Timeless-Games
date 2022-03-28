#ifndef __BATNAV_H__
#define __BATNAV_H__

/**
 * \struct bateau_t Structure qui contient les caractéristiques d'un bateau
 */
typedef struct s_bateau {
   char * nom;
   int taille; /* Entre 2 et 5 cases */
   int engage;
   char direction; /* Ne peut avoir que deux valeurs : h pour horizontal ou v pour vertical */
} bateau_t;

/**
 * \struct case_t Structure pour chaque case d'un plateau
 */
typedef struct s_case {
   char * num_bat;
   int etat; /* Ne peut avoir que deux valeurs : 0 = case non touchée ou 1 = case touchée */
   int occupe;
} case_t;

/**
 * \struct plateau_t Structure qui contient un plateau
 */
typedef struct s_plateau {
   case_t **une_case;
   int nb_col, nb_lig;
   bateau_t liste_bat[10]; /* Liste des 5 bateaux disponibles, x2 pour chaque direction */
} plateau_t;

/**
 * \struct batnav_t Structure qui contient les variables pour la bataille navale
 */
typedef struct s_batnav {
	plateau_t joueur1; /* Plateau du joueur 1 */
   plateau_t joueur2; /* Plateau du joueur 2 */
	int etat_partie; /* 1 = placements du joueur 1, 2 = placements du joueur 2, 3 = tour du joueur 1, 4 = tour du joueur 2, 5 = fin du jeu */
} batnav_t;

plateau_t creer_plateau(int l, int c);
void init_bateaux(plateau_t * plateau_j);
void init_etat_plateau(plateau_t * plateau_j);
void init_partie_batnav(void);
int est_valide(int i, int j, plateau_t plateau_j);
int direction_valide(plateau_t plateau_j, int x, int y, int direction, int taille_bat);
void placement_case_bat(SDL_Window * win, SDL_Renderer * ren, int x, int y, int direction, int bat_selec, int JOUEUR, char * couleur, plateau_t * plateau_j, t_joueur * joueur1, t_joueur * joueur2);
void placement_bateaux(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int JOUEUR, plateau_t * plateau_j, char * couleur, t_joueur * joueur1, t_joueur * joueur2);
void attaque_case_bat(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, plateau_t plateau_j, int x, int y, int * scorej1, int * scorej2);
void gestion_event_batnav(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur,  t_joueur * joueur1, t_joueur * joueur2);
void vider_cargaison(int taille_bat, char * immatriculation, SDL_Window * win, SDL_Renderer * ren);


#endif