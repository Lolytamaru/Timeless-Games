/**
 * \file pseudo.c
 * \brief Fichier pour le choix des pseudos et du mode de jeu
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 2.0
 * \date 27 mars 2022
 */

#include <all_includes.h>
#include <joueur.h>

/**
 * \brief Fonction qui permet de gérer les actions à faire sur la fenêtre des pseudos
 * \param event Un détecteur d'évènements
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void gestion_event_joueur(SDL_Event event, t_statut * etat_win, int * mode_de_jeu, int * etat_joueur, SDL_Window * win, SDL_Renderer * ren,  t_joueur * Joueur1, t_joueur * Joueur2) {
   switch(event.type) {
      case SDL_MOUSEBUTTONUP:
         if (event.button.x < 737 && event.button.x > 584 && event.button.y < 172 && event.button.y > 121) {
            *mode_de_jeu = JVSO;
            *etat_joueur = J1;
            sprintf(Joueur2->pseudo,"Ordi");
            afficher_image("assets/menu_pseudo_JCO.png", 0, 0, win, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 282, Joueur1->pseudo, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 335, Joueur2->pseudo, ren);
            SDL_RenderPresent(ren);
         }
         if (event.button.x < 568 && event.button.x > 415 && event.button.y < 172 && event.button.y > 121){
            *mode_de_jeu = JVSJ;
            sprintf(Joueur2->pseudo,"Joueur 2");
            afficher_image("assets/menu_pseudo_JCJ.png", 0, 0, win, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 282, Joueur1->pseudo, ren);
            afficher_texte("assets/inter.ttf", 27, 497, 335, Joueur2->pseudo, ren);
            SDL_RenderPresent(ren);
         }
         if (event.button.x < 690 && event.button.x > 443 && event.button.y < 326 && event.button.y > 276)
            *etat_joueur = J1;
         if (event.button.x < 690 && event.button.x > 443 && event.button.y < 376 && event.button.y > 339){
            if(*mode_de_jeu == JVSJ)
               *etat_joueur = J2;
         }
         if(event.button.x < 661 && event.button.x > 476 && event.button.y < 481 && event.button.y > 399){
               afficher_image("assets/menu.png", 0, 0, win, ren);
               afficher_texte("assets/inter.ttf", 19, 290, 21, Joueur1->pseudo, ren);
               afficher_texte("assets/inter.ttf", 19, 530, 21, Joueur2->pseudo, ren);
               afficher_nombre("assets/inter.ttf", 19, 400, 21, Joueur1->score, ren);
               afficher_nombre("assets/inter.ttf", 19, 635, 21, Joueur2->score, ren);
               SDL_RenderPresent(ren);
               *etat_win = MENU;
         }
      case SDL_KEYUP:
         if (event.key.keysym.sym == SDLK_BACKSPACE) {
            if(*etat_joueur == J1){
               int l = strlen(Joueur1->pseudo);
               if (l > 0)
                  Joueur1->pseudo[l-1] = '\0';
            }else {
               int l = strlen(Joueur2->pseudo);
               if (l > 0)
                  Joueur2->pseudo[l-1] = '\0';
            }
            SDL_Rect txtDestRect;
            TTF_Font *police;
            SDL_Surface *texte = NULL;
            SDL_Color couleur_police = {0, 0, 0};
            police = TTF_OpenFont("assets/inter.ttf", 27);
            TTF_SetFontStyle(police,TTF_STYLE_BOLD);
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            SDL_RenderClear(ren);
            if(*mode_de_jeu == JVSJ)
               afficher_image("assets/menu_pseudo_JCJ.png", 0, 0, win, ren);
            else
               afficher_image("assets/menu_pseudo_JCO.png", 0, 0, win, ren);
            if(*etat_joueur == J1) {
               texte = TTF_RenderUTF8_Blended(police, Joueur1->pseudo, couleur_police);
               afficher_texte("assets/inter.ttf", 27, 497, 335, Joueur2->pseudo, ren);
               txtDestRect.x = 497 ;
               txtDestRect.y = 282;
            } else {
               texte = TTF_RenderUTF8_Blended(police, Joueur2->pseudo, couleur_police);
               afficher_texte("assets/inter.ttf", 27, 497, 282, Joueur1->pseudo, ren);
               txtDestRect.x = 497 ;
               txtDestRect.y = 335;
            }
	         SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(ren, texte);
            SDL_FreeSurface(texte);
           	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
            SDL_RenderCopy(ren, texte_tex, NULL, &txtDestRect);
            TTF_CloseFont(police);
            SDL_RenderPresent(ren);
         }
         if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
            if(*etat_joueur == J1){
               int l = strlen(Joueur1->pseudo);
               if (l <= 10)
                  sprintf(Joueur1->pseudo,"%s%c",Joueur1->pseudo,event.key.keysym.sym);
            }else {
               int l = strlen(Joueur2->pseudo);
               if (l <= 10)
                  sprintf(Joueur2->pseudo,"%s%c",Joueur2->pseudo,event.key.keysym.sym);
            }
            SDL_Rect txtDestRect;
            TTF_Font *police;
            SDL_Surface *texte = NULL;
            SDL_Color couleur_police = {0, 0, 0};
            police = TTF_OpenFont("assets/inter.ttf", 27);
            TTF_SetFontStyle(police,TTF_STYLE_BOLD);
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            SDL_RenderClear(ren);
            if(*mode_de_jeu == JVSJ)
               afficher_image("assets/menu_pseudo_JCJ.png", 0, 0, win, ren);
            else
               afficher_image("assets/menu_pseudo_JCO.png", 0, 0, win, ren);
            if(*etat_joueur == J1) {
               texte = TTF_RenderUTF8_Blended(police, Joueur1->pseudo, couleur_police);
               afficher_texte("assets/inter.ttf", 27, 497, 335, Joueur2->pseudo, ren);
               txtDestRect.x = 497 ;
               txtDestRect.y = 282;
            } else {
               texte = TTF_RenderUTF8_Blended(police, Joueur2->pseudo, couleur_police);
               afficher_texte("assets/inter.ttf", 27, 497, 282, Joueur1->pseudo, ren);
               txtDestRect.x = 497 ;
               txtDestRect.y = 335;
            }
            SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(ren, texte);
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
