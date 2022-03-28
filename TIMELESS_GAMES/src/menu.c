/**
 * \file menu.c
 * \brief fichier secondaire qui gère le menu de Timeless Games
 * \author Christal Duclos Hugo Brochelard Thibaut Duchesne
 * \version 1.0
 * \date 21 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <pendu.h>
#include <param.h>
#include <masterm.h>
#include <menu.h>
#include <batnav.h>

/**
 * \brief Fonction qui permet de gérer les actions à faire sur la fenêtre du menu
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où l'on se trouve
 * \param mode_de_jeu Joueur contre Joueur ou Joueur contre ordi
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param scorej1 Le score actuel du joueur 1
 * \param scorej2 Le score actuel du joueur 2
 */
void gestion_event_menu(SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, SDL_Window *win, SDL_Renderer *ren, t_joueur * Joueur1, t_joueur * Joueur2) {
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         if (event.button.x < 392 && event.button.x > 341 && event.button.y < 280 && event.button.y > 229 && *mode_de_jeu == JVSJ && *etat_joueur == J2) {
               afficher_image("assets/menu_J1.png", 0, 0, win, ren);
               *etat_joueur = J1;
               afficher_texte("assets/inter.ttf", 19, 290, 21, Joueur1->pseudo, ren);
   				afficher_texte("assets/inter.ttf", 19, 530, 21, Joueur2->pseudo, ren);
   				afficher_nombre("assets/inter.ttf", 19, 400, 21, Joueur1->score, ren);
               afficher_nombre("assets/inter.ttf", 19, 635, 21, Joueur2->score, ren);
   				SDL_RenderPresent(ren);
            }
         if(event.button.x < 446 && event.button.x > 401 && event.button.y < 280 && event.button.y > 229 && *mode_de_jeu == JVSJ && *etat_joueur == J1) {
               afficher_image("assets/menu_J2.png", 0, 0, win, ren);
               *etat_joueur = J2;
               afficher_texte("assets/inter.ttf", 19, 290, 21, Joueur1->pseudo, ren);
   				afficher_texte("assets/inter.ttf", 19, 530, 21, Joueur2->pseudo, ren);
   				afficher_nombre("assets/inter.ttf", 19, 400, 21, Joueur1->score, ren);
               afficher_nombre("assets/inter.ttf", 19, 635, 21, Joueur2->score, ren);
   				SDL_RenderPresent(ren);
         }
 	      if (event.button.x < 337 && event.button.x > 106 && event.button.y < 272 && event.button.y > 83) {
            if(*mode_de_jeu == JVSO){
               init_partie_pendu(mode_de_jeu, win, ren, Joueur1->pseudo, Joueur2->pseudo, &(Joueur1->score), &(Joueur2->score));
               SDL_RenderPresent(ren);
            }else{
               init_partie_pendu(mode_de_jeu, win, ren, Joueur1->pseudo, Joueur2->pseudo, &(Joueur1->score), &(Joueur2->score));
               afficher_image("assets/pendu/pendujcj.png", 0, 0, win, ren);
               if(*etat_joueur ==J1){
                  afficher_texte("assets/inter.ttf", 27, 510, 80, Joueur1->pseudo, ren);
                  afficher_texte("assets/inter.ttf", 27, 510, 222, Joueur2->pseudo, ren);
               }else{
                  afficher_texte("assets/inter.ttf", 27, 510, 80, Joueur2->pseudo, ren);
                  afficher_texte("assets/inter.ttf", 27, 510, 222, Joueur1->pseudo, ren);
               }
               SDL_RenderPresent(ren);
            }
            *etat_win = PENDU;
         }
         else if (event.button.x < 684 && event.button.x > 455 && event.button.y < 272 && event.button.y > 83) {
            if(*mode_de_jeu == JVSO){
               afficher_image("assets/mastermind/mastermind.png", 0, 0, win, ren);
               afficher_texte("assets/inter.ttf", 19, 19, 110, Joueur1->pseudo, ren);
               afficher_texte("assets/inter.ttf", 19, 19, 218, Joueur2->pseudo, ren);
               afficher_nombre("assets/inter.ttf", 19, 26, 148, Joueur2->score, ren);
               afficher_nombre("assets/inter.ttf", 19, 26, 254, Joueur2->score, ren);
               afficher_image("assets/mastermind/enlever_proposition.png", 229, 448, win, ren);
               init_partie_master(mode_de_jeu);
               SDL_RenderPresent(ren);
            }else{
               init_partie_master(mode_de_jeu);
               afficher_image("assets/mastermind/masterjcj.png", 0, 0, win, ren);
               if(*etat_joueur ==J1){
                  afficher_texte("assets/inter.ttf", 27, 510, 100, Joueur1->pseudo, ren);
                  afficher_texte("assets/inter.ttf", 27, 510, 202, Joueur2->pseudo, ren);
               }else{
                  afficher_texte("assets/inter.ttf", 27, 510, 100, Joueur2->pseudo, ren);
                  afficher_texte("assets/inter.ttf", 27, 510, 202, Joueur1->pseudo, ren);
               }
               SDL_RenderPresent(ren);
            }
            *etat_win = MASTERMIND;
         }
         else if (event.button.x < 340 && event.button.x > 107 && event.button.y < 473 && event.button.y > 283) {
            if(*mode_de_jeu == JVSJ){
               afficher_image("assets/batnav/placement_violets.png", 0, 0, win, ren);
               afficher_texte("assets/inter.ttf", 19, 290, 21, Joueur1->pseudo, ren);
               afficher_texte("assets/inter.ttf", 19, 525, 21, Joueur2->pseudo, ren);
               afficher_nombre("assets/inter.ttf", 19, 400, 21, Joueur1->score, ren);
               afficher_nombre("assets/inter.ttf", 19, 635, 21, Joueur2->score, ren);
               SDL_RenderPresent(ren);
               init_partie_batnav();
               *etat_win = BATNAV;
            }
         }
         else if (event.button.x < 684 && event.button.x > 455 && event.button.y < 473 && event.button.y > 283) {
            afficher_image("assets/parametres.png", 0, 0, win, ren);
            SDL_RenderPresent(ren);
            *etat_win = PARAM;
         }
         else if (event.button.x < 296 && event.button.x > 0 && event.button.y < 49 && event.button.y > 0) {
            afficher_image("assets/accueil.png", 0, 0, win, ren);
            SDL_RenderPresent(ren);
            *etat_win = ACCUEIL;
         }
         break;
      default: break;
   }
}
