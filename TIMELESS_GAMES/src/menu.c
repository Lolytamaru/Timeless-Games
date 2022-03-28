/**
 * \file menu.c
 * \brief Fichier secondaire qui gère le menu de Timeless Games
 * \author Christal Duclos Hugo Brochelard Thibaut Duchesne
 * \version 1.0
 * \date 28 mars 2022
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
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où l'on se trouve
 * \param mode_de_jeu Joueur contre Joueur ou Joueur contre ordi
 * \param etat_joueur Etat du joueur
 * \param joueur1 Structure qui contient les informations du joueur 1
 * \param joueur2 Structure qui contient les informations du joueur 2
 */
void gestion_event_menu(SDL_Window *win, SDL_Renderer *ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2) {
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         if (event.button.x < 392 && event.button.x > 341 && event.button.y < 280 && event.button.y > 229 && *mode_de_jeu == JVSJ && *etat_joueur == J2) {
               afficher_image(win, ren, "assets/menu_J1.png", 0, 0);
               *etat_joueur = J1;
               afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
   				afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
   				afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
               afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
   				SDL_RenderPresent(ren);
            }
         if(event.button.x < 446 && event.button.x > 401 && event.button.y < 280 && event.button.y > 229 && *mode_de_jeu == JVSJ && *etat_joueur == J1) {
               afficher_image(win, ren, "assets/menu_J2.png", 0, 0);
               *etat_joueur = J2;
               afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
   				afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
   				afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
               afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
   				SDL_RenderPresent(ren);
         }
 	      if (event.button.x < 337 && event.button.x > 106 && event.button.y < 272 && event.button.y > 83) {
            if(*mode_de_jeu == JVSO){
               init_partie_pendu(win, ren, mode_de_jeu, joueur1->pseudo, joueur2->pseudo, &(joueur1->score), &(joueur2->score));
               SDL_RenderPresent(ren);
            }else{
               init_partie_pendu(win, ren, mode_de_jeu, joueur1->pseudo, joueur2->pseudo, &(joueur1->score), &(joueur2->score));
               afficher_image(win, ren, "assets/pendu/pendujcj.png", 0, 0);
               if(*etat_joueur ==J1){
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 80, joueur1->pseudo);
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 222, joueur2->pseudo);
               }else{
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 80, joueur2->pseudo);
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 222, joueur1->pseudo);
               }
               SDL_RenderPresent(ren);
            }
            *etat_win = PENDU;
         }
         else if (event.button.x < 684 && event.button.x > 455 && event.button.y < 272 && event.button.y > 83) {
            if (*mode_de_jeu == JVSO) {
               afficher_image(win, ren, "assets/mastermind/mastermind.png", 0, 0);
               afficher_texte(ren, "assets/inter.ttf", 19, 19, 110, joueur1->pseudo);
               afficher_texte(ren, "assets/inter.ttf", 19, 19, 218, joueur2->pseudo);
               afficher_nombre(ren, "assets/inter.ttf", 19, 26, 148, joueur2->score);
               afficher_nombre(ren, "assets/inter.ttf", 19, 26, 254, joueur2->score);
               afficher_image(win, ren, "assets/mastermind/enlever_proposition.png", 229, 448);
               init_partie_masterm(mode_de_jeu);
               SDL_RenderPresent(ren);
            } else {
               init_partie_masterm(mode_de_jeu);
               afficher_image(win, ren, "assets/mastermind/masterjcj.png", 0, 0);
               if (*etat_joueur == J1) {
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 100, joueur1->pseudo);
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 202, joueur2->pseudo);
               } else {
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 100, joueur2->pseudo);
                  afficher_texte(ren, "assets/inter.ttf", 27, 510, 202, joueur1->pseudo);
               }
               SDL_RenderPresent(ren);
            }
            *etat_win = MASTERMIND;
         }
         else if (event.button.x < 340 && event.button.x > 107 && event.button.y < 473 && event.button.y > 283) {
            if (*mode_de_jeu == JVSJ) {
               afficher_image(win, ren, "assets/batnav/placement_violets.png", 0, 0);
               afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
               afficher_texte(ren, "assets/inter.ttf", 19, 525, 21, joueur2->pseudo);
               afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
               afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
               SDL_RenderPresent(ren);
               init_partie_batnav();
               *etat_win = BATNAV;
            }
         }
         else if (event.button.x < 684 && event.button.x > 455 && event.button.y < 473 && event.button.y > 283) {
            afficher_image(win, ren, "assets/parametres/parametres.png", 0, 0);
            SDL_RenderPresent(ren);
            *etat_win = PARAM;
         }
         else if (event.button.x < 296 && event.button.x > 0 && event.button.y < 49 && event.button.y > 0) {
            afficher_image(win, ren, "assets/accueil.png", 0, 0);
            SDL_RenderPresent(ren);
            *etat_win = ACCUEIL;
         }
         break;
      default: break;
   }
}
