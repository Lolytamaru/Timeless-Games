/**
 * \file main.c
 * \brief fichier principal de Timeless Games
 * \author Christal Duclos Hugo Brochelard Thibaut Duchesne
 * \version 2.0
 * \date 05 avril 2022
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
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où l'on se trouve
 * \param joueur1 Structure qui contient les informations du joueur 1
 * \param joueur2 Structure qui contient les informations du joueur 2
 */
void gestion_event_accueil(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, t_joueur * joueur1, t_joueur * joueur2) {
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
      // Passage à la gestion des pseudos et du mode de jeu
         if (event.button.x < 750 && event.button.x > 0 && event.button.y < 500 && event.button.y > 0) {
            afficher_image(win, ren, "assets/parametres/menu_pseudo_JCJ.png", 0, 0);
            afficher_texte(ren, "assets/inter.ttf", 27, 497, 252, joueur1->pseudo);
            afficher_texte(ren, "assets/inter.ttf", 27, 497, 338, joueur2->pseudo);
            SDL_RenderPresent(ren);
            *etat_win = PSEUDO;
            break;
         }
      default: break;
   }
}

int main(int argc, char** argv) {
   // Initialisation de la fenêtre
   SDL_Window *win = NULL;
   SDL_Renderer *ren = NULL;
   // Lancement de la SDL
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
      SDL_ExitWithError("Initialisation SDL");
   // Création de la fenêtre et du rendu
   if (SDL_CreateWindowAndRenderer(750, 500, 0, &win, &ren) != 0)
      SDL_ExitWithError("Impossible de créer la fenêtre et le rendu SDL.\n");
   // Fonction qui initialise SDL_TTF
   if (TTF_Init() == -1)
		SDL_ExitWithError("Impossible d'initialiser SDL_TTF.\n");
   // Fonction qui efface tout le rendu
   if (SDL_RenderClear(ren) != 0)
      SDL_ExitWithError("Effacement du rendu échoué.\n");
   // Affichage de l'accueil
   afficher_image(win, ren, "assets/accueil.png", 0, 0);
   SDL_RenderPresent(ren);
   SDL_RenderClear(ren);
   // L'état de la fenêtre pour savoir sur laquelle on se trouve pour les évènements, les pseudos et scores des joueurs
   t_statut etat_win = ACCUEIL;
   int etat_joueur = J1;
   int mode_de_jeu = JVSJ;
   t_joueur joueur1 = {" ", 0};
   t_joueur joueur2 = {" ", 0};

   SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
   SDL_bool programme_lance = SDL_TRUE;
   SDL_Event event;
   // Tant que Timeless Games est lancé
   while (programme_lance) {
       while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            programme_lance = SDL_FALSE;
            break;
         }
         if (etat_win == ACCUEIL)
            gestion_event_accueil(win, ren, event, &etat_win, &joueur1, &joueur2);
         else if (etat_win == PSEUDO)
            gestion_event_joueur(win, ren, event, &etat_win, &mode_de_jeu, &etat_joueur, &joueur1, &joueur2);
         else if (etat_win == MENU)
            gestion_event_menu(win, ren, event, &etat_win, &mode_de_jeu, &etat_joueur, &joueur1, &joueur2);
         else if (etat_win == PENDU)
            gestion_event_pendu(win, ren, event, &etat_win, &mode_de_jeu, &etat_joueur, &joueur1, &joueur2);
         else if (etat_win == MASTERMIND)
            gestion_event_masterm(win, ren, event, &etat_win, &mode_de_jeu, &etat_joueur, &joueur1, &joueur2);
         else if (etat_win == BATNAV)
            gestion_event_batnav(win, ren, event, &etat_win, &mode_de_jeu, &etat_joueur, &joueur1, &joueur2);
         else if (etat_win == PARAM)
            gestion_event_param(win, ren, event, &etat_win, &mode_de_jeu, &etat_joueur, &joueur1, &joueur2);
      }
   }
   // Fermeture de la fenêtre
   SDL_DestroyRenderer(ren);
   SDL_DestroyWindow(win);
   TTF_Quit();
   SDL_Quit();
   return 0;
}
