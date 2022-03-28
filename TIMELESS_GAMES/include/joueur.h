/**
 * \file joueur.h
 * \brief Fichier de prototypes pour le fichier joueur.c
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 28 mars 2022
 */

#ifndef __JOUEUR_H__
#define __JOUEUR_H__

/**
 * \struct bateau_t Structure qui contient les caractéristiques d'un joueur
 */
typedef struct s_joueur {
   char pseudo[100]; // Pseudo d'un joueur
   int score; // Score d'un joueur
} t_joueur;

void gestion_event_joueur(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur,  t_joueur * joueur1, t_joueur * joueur2);

#endif
