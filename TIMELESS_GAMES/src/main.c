/**
 * \file main.c
 * \brief fichier principal de Timeless Games
 * \author Christal Duclos Hugo Brochelard Thibaut Duchesne
 * \version 2.0
 * \date 21 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <menu.h>
#include <pendu.h>
#include <param.h>
#include <masterm.h>
#include <batnav.h>




/**
 * \brief Fonction qui permet de gérer les actions à faire sur la fenêtre d'accueil
 * \param event Un détecteur d'évènements
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void gestion_event_accueil(SDL_Event event, t_statut * etat_win, SDL_Window * win, SDL_Renderer * ren, t_joueur * Joueur1, t_joueur * Joueur2) {
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         if (event.button.x < 750 && event.button.x > 0 && event.button.y < 500 && event.button.y > 0) {
            afficher_image("assets/menu_pseudo_JCJ.png", 0, 0, win, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 282, Joueur1->pseudo, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 335, Joueur2->pseudo, ren);
            SDL_RenderPresent(ren);
            *etat_win = PSEUDO;
            break;
         }
      default: break;
   }
}

int main(int argc, char** argv) {
   // Initialisation de la fenêtre
   SDL_Window *window = NULL;
   SDL_Renderer *renderer = NULL;
   // Lancement de la SDL
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
      SDL_ExitWithError("Initialisation SDL");
   // Création fenêtre + rendu
   if (SDL_CreateWindowAndRenderer(750, 500, 0, &window, &renderer) != 0)
      SDL_ExitWithError("Impossible de créer la fenêtre et le rendu SDL.\n");
   // Fonction qui initialise SDL_TTF
   if (TTF_Init() == -1)
		SDL_ExitWithError("Impossible d'initialiser SDL_TTF.\n");
   // Fonction qui efface tout sur le rendu
   if (SDL_RenderClear(renderer) != 0)
      SDL_ExitWithError("Éffacement du rendu échoué.\n");
   // Affichage de l'accueil
   afficher_image("assets/accueil.png", 0, 0, window, renderer);
   SDL_RenderPresent(renderer);
   SDL_RenderClear(renderer);
   // L'état de la fenêtre pour savoir sur laquelle on se trouve pour les évênements et les scores des joueurs
   t_statut etat_win;
   etat_win = ACCUEIL;
   int etat_joueur= J1;
   int mode_de_jeu= JVSJ;
   t_joueur Joueur1={"Joueur 1",0};
   t_joueur Joueur2={"Joueur 2",0};


   //etat_win = ACCUEIL;

   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
   SDL_bool programme_lance = SDL_TRUE;
   // Tant que Timeless Games est lancé
   while (programme_lance) {
       SDL_Event event;
       while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            programme_lance = SDL_FALSE;
            break;
         }
         if (etat_win == ACCUEIL)
            gestion_event_accueil(event, &etat_win, window, renderer, &Joueur1, &Joueur2);
         else if (etat_win == PSEUDO)
            gestion_event_joueur(event, &etat_win, &mode_de_jeu, &etat_joueur, window, renderer, &Joueur1, &Joueur2);
         else if (etat_win == MENU)
            gestion_event_menu(event, &etat_win, &mode_de_jeu, &etat_joueur, window, renderer, &Joueur1, &Joueur2);
         else if (etat_win == PENDU)
            gestion_event_pendu(event, &etat_win, &mode_de_jeu, &etat_joueur, window, renderer, &Joueur1, &Joueur2);
         else if (etat_win == MASTERMIND)
            gestion_event_masterm(event, &etat_win, &mode_de_jeu, window, renderer, &Joueur1, &Joueur2);
         else if (etat_win == BATNAV)
            gestion_event_batnav(event, &etat_win, &mode_de_jeu, window, renderer, &Joueur1, &Joueur2);
         else if (etat_win == PARAM)
            gestion_event_param(event, &etat_win, window, renderer, &Joueur1, &Joueur2);
      }
   }
   //Fermeture de la fenêtre
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   TTF_Quit();
   SDL_Quit();
   return 0;
}
