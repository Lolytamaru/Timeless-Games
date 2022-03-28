/**
 * \file menu.c
 * \brief fichier secondaire qui gère le menu paramètres de Timeless Games
 * \author Christal Duclos Hugo Brochelard Thibaut Duchesne
 * \version 1.0
 * \date 28 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <menu.h>

/**
 * \brief Fonction qui permet de gérer les actions à faire sur la fenêtre du menu paramètres
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où on se trouve
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param etat_joueur Etat du joueur
 * \param joueur1 Structure qui contient les informations du joueur 1
 * \param joueur2 Structure qui contient les informations du joueur 2

 */
void gestion_event_param( SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2) {
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         if (event.button.x < 155 && event.button.x > 0 && event.button.y < 43 && event.button.y > 0) {
            afficher_image(win, ren, "assets/menu.png", 0, 0);
            afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
            afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
            afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
            afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
  				SDL_RenderPresent(ren);
  				*etat_win = MENU;
         }
         if (event.button.x < 490 && event.button.x > 200 && event.button.y < 170 && event.button.y > 109) {
            if (*mode_de_jeu == JVSJ)
               afficher_image(win, ren, "assets/menu_pseudo_JCJ.png", 0, 0);
            else
               afficher_image(win, ren, "assets/menu_pseudo_JCO.png", 0, 0);
            afficher_texte(ren, "assets/inter.ttf", 27, 497, 252, joueur1->pseudo);
            afficher_texte(ren, "assets/inter.ttf", 27, 497, 338, joueur2->pseudo);
            SDL_RenderPresent(ren);
            *etat_win = PSEUDO;
         }
         //if (event.button.x < 551 && event.button.x > 200 && event.button.y < 242 && event.button.y > 182)
         if (event.button.x < 500 && event.button.x > 200 && event.button.y < 317 && event.button.y > 259) {
            joueur1->score = 0;
            joueur2->score = 0;
         }
         //if (event.button.x < 433 && event.button.x > 200 && event.button.y < 387 && event.button.y > 326)
         //if (event.button.x < 342 && event.button.x > 200 && event.button.y < 459 && event.button.y > 398)
         break;
      default: break;
    }
}
