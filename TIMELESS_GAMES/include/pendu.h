/**
 * \file pendu.h
 * \brief Fichier de prototypes pour le jeu du pendu
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 02 avril 2022
 */

#define OK 1
#define PAS_OK 0

/**
 * \struct t_pendu Structure qui contient les variables propres au jeu du pendu
 */
typedef struct s_pendu {
 	char *pendu; // Mot sur lequel on joue
 	char *secret; // Mot secret à deviner
 	char secret_ecrit[100]; // Variable pour saisir un mot secret au clavier
 	char alphabet[26]; // Contient les 26 lettres de l'alphabet
 	int erreurs; // Compteur d'erreurs allant jusqu'à 12
 	int etat_partie;
} t_pendu;

t_pendu pendu;

void init_partie_pendu(SDL_Window * win, SDL_Renderer * ren, int * mode_de_jeu, char * pseudoJ1, char * pseudoJ2, int * scoreJ1, int * scoreJ2);
void initialiser_mot_joueur(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, int * etat_joueur, int * etat_partie, char * secret_ecrit, char * secret, char * pendu, char * pseudoJ1, char * pseudoJ2, int * scoreJ1, int * scoreJ2);
void initialiser_mot_ordi(SDL_Window * win, SDL_Renderer * ren, char * secret, char * pendu);
void lettre_utilisee(SDL_Window * win, SDL_Renderer * ren, char lettre, int presence);
void affiche_lettre(SDL_Window * win, SDL_Renderer * ren, char c, int position);
void afficher_mystere(SDL_Window * win, SDL_Renderer * ren, int longueur_mot);
void afficher_erreur(SDL_Window * win, SDL_Renderer * ren, int nb_erreur);
int valider_mot(char * secret, char * pendu);
int saisie(char entree, char * alphabet);
int valider_lettre(SDL_Window * win, SDL_Renderer * ren, char lettre, char * secret, char * pendu, int * erreurs);
void pendu_tour(SDL_Window * win, SDL_Renderer * ren, int mode_de_jeu, int etat_joueur, int * etat_partie, int * scoreJ1, int * scoreJ2, char lettre, char * alphabet, char * pendu, char * secret, int * erreurs);
void gestion_event_pendu(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2);
