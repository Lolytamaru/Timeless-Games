/**
 * \file joueur.c
 * \brief Fichier pour le choix des pseudos et du mode de jeu
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 02 avril 2022
 */

#include <all_includes.h>
#include <joueur.h>

/**
 * \brief Fonction qui permet de gérer les actions à faire sur la fenêtre des pseudos
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param event Un détecteur d'évènements
 * \param event Un détecteur d'évènements
 * \param etat_win La fenêtre où on se trouve
 * \param mode_de_jeu Soit joueur contre joueur, soit joueur contre ordi
 * \param etat_joueur Etat du joueur
 * \param joueur1 Structure qui contient les informations du joueur 1
 * \param joueur2 Structure qui contient les informations du joueur 2
 */
void gestion_event_joueur(SDL_Window * win, SDL_Renderer * ren, SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur,  t_joueur * joueur1, t_joueur * joueur2) {
   int l;
   char temp[101];
   SDL_Rect txtDestRect;
   TTF_Font *police;
   SDL_Surface *texte = NULL;
   SDL_Color couleur_police = {0, 0, 0};
   SDL_Texture *texte_tex;
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         // Si on clique sur J1 VS Ordi
         if (event.button.x < 737 && event.button.x > 584 && event.button.y < 172 && event.button.y > 121) {
            *mode_de_jeu = JVSO;
            *etat_joueur = J1;
            sprintf(joueur1->pseudo, " ");
            sprintf(joueur2->pseudo, "ordi");
            joueur1->score = 0;
            joueur2->score = 0;
            afficher_image(win, ren, "assets/parametres/menu_pseudo_JCO.png", 0, 0);
            afficher_texte(ren, "assets/inter.ttf", 27, 505, 252, joueur1->pseudo);
            afficher_texte(ren, "assets/inter.ttf", 27, 505, 338, joueur2->pseudo);
            SDL_RenderPresent(ren);
         }
         // Si on clique sur J1 VS J2
         if (event.button.x < 568 && event.button.x > 415 && event.button.y < 172 && event.button.y > 121) {
            *mode_de_jeu = JVSJ;
            sprintf(joueur1->pseudo, " ");
            sprintf(joueur2->pseudo, " ");
            joueur1->score = 0;
            joueur2->score = 0;
            afficher_image(win, ren, "assets/parametres/menu_pseudo_JCJ.png", 0, 0);
            afficher_texte(ren, "assets/inter.ttf", 27, 505, 252, joueur1->pseudo);
            afficher_texte(ren, "assets/inter.ttf", 27, 505, 338, joueur2->pseudo);
            SDL_RenderPresent(ren);
         }
         // Si on clique sur la case de saisie du pseudo du joueur 1
         if (event.button.x < 721 && event.button.x > 438 && event.button.y < 294 && event.button.y > 239)
            *etat_joueur = J1;
         // Si on clique sur la case de saisie du pseudo du joueur 2, en étant dans le mode joueur contre joueur
         if (event.button.x < 721 && event.button.x > 438 && event.button.y < 380 && event.button.y > 324) {
            if (*mode_de_jeu == JVSJ)
               *etat_joueur = J2;
         }
         if (event.button.x < 661 && event.button.x > 476 && event.button.y < 481 && event.button.y > 399) {
            if (*mode_de_jeu == JVSJ && *etat_joueur == J1) {
               if (strcmp(joueur1->pseudo, " ") == 0)
                  sprintf(joueur1->pseudo, "joueur 1");
               if (strcmp(joueur2->pseudo, " ") == 0)
                  sprintf(joueur2->pseudo, "joueur 2");
               afficher_image(win, ren, "assets/menu_J1.png", 0, 0);
            } else if (*mode_de_jeu == JVSJ && *etat_joueur == J2) {
               if(strcmp(joueur1->pseudo," ")==0)
                  sprintf(joueur1->pseudo,"joueur 1");
               if(strcmp(joueur2->pseudo," ")==0)
                  sprintf(joueur2->pseudo,"joueur 2");
               afficher_image(win, ren, "assets/menu_J2.png", 0, 0);
            } else {
               if(strcmp(joueur1->pseudo," ")==0)
                  sprintf(joueur1->pseudo,"joueur 1");
               afficher_image(win, ren, "assets/menu.png", 0, 0);
            }
            afficher_texte(ren, "assets/inter.ttf", 19, 290, 21, joueur1->pseudo);
            afficher_texte(ren, "assets/inter.ttf", 19, 530, 21, joueur2->pseudo);
            afficher_nombre(ren, "assets/inter.ttf", 19, 400, 21, joueur1->score);
            afficher_nombre(ren, "assets/inter.ttf", 19, 635, 21, joueur2->score);
            SDL_RenderPresent(ren);
            *etat_win = MENU;
         }
      case SDL_KEYUP:
         if (event.key.keysym.sym == SDLK_BACKSPACE) {
            if (*etat_joueur == J1) {
               l = strlen(joueur1->pseudo);
               if (l > 0)
                  joueur1->pseudo[l-1] = '\0';
            } else {
               l = strlen(joueur2->pseudo);
               if (l > 0)
                  joueur2->pseudo[l-1] = '\0';
            }
            police = TTF_OpenFont("assets/inter.ttf", 27);
            TTF_SetFontStyle(police, TTF_STYLE_BOLD);
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            SDL_RenderClear(ren);
            if(*mode_de_jeu == JVSJ)
               afficher_image(win, ren, "assets/parametres/menu_pseudo_JCJ.png", 0, 0);
            else
               afficher_image(win, ren, "assets/parametres/menu_pseudo_JCO.png", 0, 0);
            if (*etat_joueur == J1) {
               texte = TTF_RenderUTF8_Blended(police, joueur1->pseudo, couleur_police);
               afficher_texte(ren, "assets/inter.ttf", 27, 505, 338, joueur2->pseudo);
               txtDestRect.x = 505 ;
               txtDestRect.y = 252;
            } else {
               texte = TTF_RenderUTF8_Blended(police, joueur2->pseudo, couleur_police);
               afficher_texte(ren, "assets/inter.ttf", 27, 505, 252, joueur1->pseudo);
               txtDestRect.x = 505 ;
               txtDestRect.y = 338;
            }
	         texte_tex = SDL_CreateTextureFromSurface(ren, texte);
            SDL_FreeSurface(texte);
           	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
            SDL_RenderCopy(ren, texte_tex, NULL, &txtDestRect);
            TTF_CloseFont(police);
            SDL_RenderPresent(ren);
         }
         if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
            if (*etat_joueur == J1) {
               l = strlen(joueur1->pseudo);
               if (l <= 8){
                  sprintf(temp, "%s%c", joueur1->pseudo, event.key.keysym.sym);
                  sprintf(joueur1->pseudo, "%s", temp);
               }
            } else {
               l = strlen(joueur2->pseudo);
               if (l <= 8){
                  sprintf(temp,"%s%c", joueur2->pseudo, event.key.keysym.sym);
                  sprintf(joueur2->pseudo, "%s", temp);
               }
            }
            police = TTF_OpenFont("assets/inter.ttf", 27);
            TTF_SetFontStyle(police,TTF_STYLE_BOLD);
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            SDL_RenderClear(ren);
            if (*mode_de_jeu == JVSJ)
               afficher_image(win, ren, "assets/parametres/menu_pseudo_JCJ.png", 0, 0);
            else
               afficher_image(win, ren, "assets/parametres/menu_pseudo_JCO.png", 0, 0);
            if (*etat_joueur == J1) {
               texte = TTF_RenderUTF8_Blended(police, joueur1->pseudo, couleur_police);
               afficher_texte(ren, "assets/inter.ttf", 27, 505, 338, joueur2->pseudo);
               txtDestRect.x = 505 ;
               txtDestRect.y = 252;
            } else {
               texte = TTF_RenderUTF8_Blended(police, joueur2->pseudo, couleur_police);
               afficher_texte(ren, "assets/inter.ttf", 27, 505, 252, joueur1->pseudo);
               txtDestRect.x = 505 ;
               txtDestRect.y = 338;
            }
            texte_tex = SDL_CreateTextureFromSurface(ren, texte);
            SDL_FreeSurface(texte);
           	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
            SDL_RenderCopy(ren, texte_tex, NULL, &txtDestRect);
            TTF_CloseFont(police);
            SDL_RenderPresent(ren);
         }
         break;
   default: break;
   }
}
