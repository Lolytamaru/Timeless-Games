/**
 * \file menu.c
 * \brief fichier secondaire qui gère le menu paramètres de Timeless Games
 * \author Christal Duclos Hugo Brochelard Thibaut Duchesne
 * \version 1.0
 * \date 21 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <menu.h>

/**
 * \brief Fonction qui permet de gérer les actions à faire sur la fenêtre du menu paramètres
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où on se trouve
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé

 */
void gestion_event_param(SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, SDL_Window * win, SDL_Renderer * ren, t_joueur * Joueur1, t_joueur * Joueur2) {
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         if (event.button.x < 155 && event.button.x > 0 && event.button.y < 43 && event.button.y > 0) {
            if(*mode_de_jeu == JVSJ && *etat_joueur == J1){
               afficher_image("assets/menu_J1.png", 0, 0, win, ren);
            }else if(*mode_de_jeu == JVSJ && *etat_joueur == J2){
               afficher_image("assets/menu_J2.png", 0, 0, win, ren);
            }else{
               afficher_image("assets/menu.png", 0, 0, win, ren);
            }
            afficher_texte("assets/inter.ttf", 19, 290, 21, Joueur1->pseudo, ren);
            afficher_texte("assets/inter.ttf", 19, 530, 21, Joueur2->pseudo, ren);
            afficher_nombre("assets/inter.ttf", 19, 400, 21, Joueur1->score, ren);
            afficher_nombre("assets/inter.ttf", 19, 635, 21, Joueur2->score, ren);
  				SDL_RenderPresent(ren);
  				*etat_win = MENU;
         }
         if (event.button.x < 490 && event.button.x > 200 && event.button.y < 170 && event.button.y > 109){
            if(*mode_de_jeu == JVSJ)
               afficher_image("assets/menu_pseudo_JCJ.png", 0, 0, win, ren);
            else
               afficher_image("assets/menu_pseudo_JCO.png", 0, 0, win, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 252, Joueur1->pseudo, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 338, Joueur2->pseudo, ren);
            SDL_RenderPresent(ren);
            *etat_win = PSEUDO;
         }
         //if (event.button.x < 551 && event.button.x > 200 && event.button.y < 242 && event.button.y > 182)
         if (event.button.x < 500 && event.button.x > 200 && event.button.y < 317 && event.button.y > 259){
            Joueur1->score=0;
            Joueur2->score=0;
         }
         //if (event.button.x < 433 && event.button.x > 200 && event.button.y < 387 && event.button.y > 326)
         //if (event.button.x < 342 && event.button.x > 200 && event.button.y < 459 && event.button.y > 398)
         break;
      default: break;
    }
}
