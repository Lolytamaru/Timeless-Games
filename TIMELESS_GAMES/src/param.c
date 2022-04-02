/**
 * \file param.c
 * \brief Fichier qui gère les paramètres de Timeless Games
 * \author Christal Duclos Hugo Brochelard Thibaut Duchesne
 * \version 1.0
 * \date 02 avril 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <menu.h>

typedef enum {PARAMETRES = 1, MENU_REGLES, REGLES_JEU, CREDITS} param_e; // Liste de constantes d'énumération
int param_select = PARAMETRES; // Sélection actuelle

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
void gestion_event_param(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, t_joueur * joueur1, t_joueur * joueur2) {
   // En fonction des évènements à la souris
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         // Si on est dans les crédits et que l'on clique sur la fenêtre, on retourne aux paramètres
         if (param_select == CREDITS) {
            if (event.button.x < 750 && event.button.x > 0 && event.button.y < 500 && event.button.y > 0) {
               param_select = PARAMETRES;
               afficher_image(win, ren, "assets/parametres/parametres.png", 0, 0);
            }
         // Si on est dans les règles d'un jeu en particulier et qu'on l'on clique sur la fenêtre, on retourne à la liste des règles des jeux
         } else if (param_select == REGLES_JEU) {
            if (event.button.x < 750 && event.button.x > 0 && event.button.y < 500 && event.button.y > 0) {
               param_select = MENU_REGLES;
               afficher_image(win, ren, "assets/parametres/param_jeux.png", 0, 0);
            }
         // Si on est dans la liste des règles des jeux
         } else if (param_select == MENU_REGLES) {
            // Si on clique sur QUITTER, on retourne aux paramètres
            if (event.button.x < 155 && event.button.x > 0 && event.button.y < 43 && event.button.y > 0) {
               afficher_image(win, ren, "assets/parametres/parametres.png", 0, 0);
               param_select = PARAMETRES;
            // Si on clique sur Jeu du pendu, on affiche les règles du jeu du pendu
            } else if (event.button.x < 430 && event.button.x > 200 && event.button.y < 195 && event.button.y > 135) {
               afficher_image(win, ren, "assets/parametres/regles_pendu.png", 0, 0);
               param_select = REGLES_JEU;
            // Si on clique sur Jeu du mastermind, on affiche les règles du jeu du mastermind
            } else if (event.button.x < 490 && event.button.x > 200 && event.button.y < 283 && event.button.y > 220) {
               afficher_image(win, ren, "assets/parametres/regles_masterm.png", 0, 0);
               param_select = REGLES_JEU;
            // Si on clique sur Jeu de la bataille navale, on affiche les règles du jeu de la bataille navale
            } else if (event.button.x < 555 && event.button.x > 198 && event.button.y < 368 && event.button.y > 307) {
               afficher_image(win, ren, "assets/parametres/regles_batnav.png", 0, 0);
               param_select = REGLES_JEU;
            }
         // Si on est dans la liste dans les paramètres
         } else if (param_select == PARAMETRES) {
            // Quitter
            if (event.button.x < 155 && event.button.x > 0 && event.button.y < 43 && event.button.y > 0) {
               if (*mode_de_jeu == JVSJ && *etat_joueur == J1) {
                  afficher_image(win, ren, "assets/menu_J1.png", 0, 0);
               } else if (*mode_de_jeu == JVSJ && *etat_joueur == J2) {
                  afficher_image(win, ren, "assets/menu_J2.png", 0, 0);
               } else {
                  afficher_image(win, ren, "assets/menu.png", 0, 0);
               }
               afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
               afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
               afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
               afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
     				SDL_RenderPresent(ren);
     				*etat_win = MENU;
            // Modifier les joueurs
            } else if (event.button.x < 490 && event.button.x > 200 && event.button.y < 200 && event.button.y > 141) {
               if (*mode_de_jeu == JVSJ) {
                  sprintf(joueur2->pseudo, " ");
                  afficher_image(win, ren, "assets/parametres/menu_pseudo_JCJ.png", 0, 0);
               } else {
                  afficher_image(win, ren, "assets/parametres/menu_pseudo_JCO.png", 0, 0);
               }
               sprintf(joueur1->pseudo, " ");
               afficher_texte(ren, "assets/inter.ttf", 27, 497, 252, joueur1->pseudo);
               afficher_texte(ren, "assets/inter.ttf", 27, 497, 338, joueur2->pseudo);
               SDL_RenderPresent(ren);
               *etat_win = PSEUDO;
            // Réinitialisation des scores
            } else if (event.button.x < 500 && event.button.x > 200 && event.button.y < 290 && event.button.y > 230) {
               joueur1->score = 0;
               joueur2->score = 0;
               if (*mode_de_jeu == JVSJ && *etat_joueur == J1) {
                  afficher_image(win, ren, "assets/menu_J1.png", 0, 0);
               } else if (*mode_de_jeu == JVSJ && *etat_joueur == J2) {
                  afficher_image(win, ren, "assets/menu_J2.png", 0, 0);
               } else {
                  afficher_image(win, ren, "assets/menu.png", 0, 0);
               }
               afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
               afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
               afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
               afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
               SDL_RenderPresent(ren);
               *etat_win = MENU;
            // Règles des jeux
            } else if (event.button.x < 433 && event.button.x > 200 && event.button.y < 376 && event.button.y > 317) {
               afficher_image(win, ren, "assets/parametres/param_jeux.png", 0, 0);
               param_select = MENU_REGLES;
               SDL_RenderPresent(ren);
            // Crédits
            } else if (event.button.x < 328 && event.button.x > 197 && event.button.y < 460 && event.button.y > 401) {
               afficher_image(win, ren, "assets/parametres/credits.png", 0, 0);
               param_select = CREDITS;
               SDL_RenderPresent(ren);
            }
         }
         SDL_RenderPresent(ren);
         break;
      default: break;
   }
}
