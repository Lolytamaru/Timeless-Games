#ifndef __JOUEUR_H__
#define __JOUEUR_H__

typedef struct s_joueur {
   char pseudo[100];
   int score;
} t_joueur;

void gestion_event_joueur(SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, SDL_Window * win, SDL_Renderer * ren, t_joueur * Joueur1, t_joueur * Joueur2);

#endif
