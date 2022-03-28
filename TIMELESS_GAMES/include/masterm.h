/**
 * \file masterm.h
 * \brief Fichier de prototypes pour jeu du mastermind
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 28 mars 2022
 */

#define OK 1
#define PAS_OK 0

/**
 * \struct t_master Structure qui contient les variables propres au jeu du mastermind
 */
typedef struct s_master {
	char *propo_couleur; // Proposition de combinaison de couleurs
	char *code_secret; // Code secret de couleurs
   int position; // Une des 4 positions possibles
 	int nb_essais; // Compteur de nombre d'essais allant jusqu'à 10
 	int etat_partie;
} t_master;

t_master mastermind;
void init_partie_masterm(int * mode_de_jeu);
void init_mastermind_joueur(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, char * pseudoJ1, char * pseudoJ2, int * scoreJ1, int * scoreJ2);
void saisir_code_ordi(char * code_secret);
int proposition_pas_vide(char * propo_couleur);
int nb_bonne_place(char * code, char * code_secret);
int nb_bonne_couleur(char * code, char * code_secret, int nb_place);
void affiche_propo(SDL_Window * win, SDL_Renderer * ren, int * position, char * propo_couleur, char couleur);
void afficher_essai(SDL_Window * win, SDL_Renderer * ren, int bonne_couleur, int bonne_place, int * nb_essais, char * propo_couleur, char * code_secret);
void afficher_resultat(SDL_Window * win, SDL_Renderer * ren, char * code_secret);
void mastermind_tour(SDL_Window * win, SDL_Renderer * ren, int etat_joueur, int * etat_partie, int * scoreJ1, int * scoreJ2, int * nb_essais, char * propo_couleur, char * code_secret, int * position);
void gestion_event_masterm(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2);
