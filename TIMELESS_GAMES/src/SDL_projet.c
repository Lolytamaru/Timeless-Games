/**
 * \file SDL_projet.c
 * \brief Fichier comprenant toutes les fonctions de manipulation de SDL
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 21 mars 2022
 */

#include <all_includes.h>

/**
 * \brief Protocole en cas de détection d'une erreur liée à la SDL
 * \param message Message d'erreur qu'on souhaite signaler
 */
void SDL_ExitWithError(const char *message) {
   SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
   SDL_Quit();
   exit(EXIT_FAILURE);
}

/**
 * \brief Fonction qui permet l'affichage d'une image à une position donnée
 * \param nom_img  Le nom de l'image à afficher
 * \param coordx La position en abscisse de l'image
 * \param coordy La position en ordonnée de l'image
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 */
void afficher_image(char * nom_img, int coordx, int coordy, SDL_Window * win, SDL_Renderer * ren) {
   SDL_Surface *image = NULL;
   SDL_Texture *texture = NULL;

   image = IMG_Load(nom_img);
   if (image == NULL) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible de trouver l'image.\n");
   }
   texture = SDL_CreateTextureFromSurface(ren, image);
   SDL_FreeSurface(image);
   if (texture == NULL) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible de créer la texture.\n");
   }
   SDL_Rect rectangle;
   if (SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h)) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible de charger la texture.\n");
   }
   rectangle.x = coordx;
   rectangle.y = coordy;
   if (SDL_RenderCopy(ren, texture, NULL, &rectangle)) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible d'afficher la texture.\n");
   }
}

/**
 * \brief Fonction qui permet l'affichage d'un texte à une position donnée d'une certaine taille
 * \param pol La police utilisée
 * \param taille_pol La taille de la police
 * \param pos_x La position en abscisse du texte
 * \param pos_y La position en ordonnée du texte
 * \param texte Le texte a afficher
 * \param ren Le rendu qui sera manipulé
 */
void afficher_texte(char * pol, int taille_pol, int pos_x, int pos_y, char * texte, SDL_Renderer * ren) {
   TTF_Font *police;
   SDL_Rect position_txt;
   position_txt.x = pos_x;
   position_txt.y = pos_y;
   police = TTF_OpenFont(pol, taille_pol);
   TTF_SetFontStyle(police,TTF_STYLE_BOLD);
   SDL_Color couleur_police = {0, 0, 0};
   SDL_Surface *surface_texte = TTF_RenderText_Blended(police, texte, couleur_police);
   SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(ren, surface_texte);
   SDL_FreeSurface(surface_texte);
   SDL_QueryTexture(texture_texte, NULL, NULL, &position_txt.w, &position_txt.h);
   SDL_RenderCopy(ren, texture_texte, NULL, &position_txt);
   TTF_CloseFont(police);
}

/**
 * \brief Fonction qui permet l'affichage d'une nombre à une position donnée d'une certaine taille
 * \param pol La police utilisée
 * \param taille_pol La taille de la police
 * \param pos_x La position en abscisse du texte
 * \param pos_y La position en ordonnée du texte
 * \param nombre le nombre a afficher
 * \param ren Le rendu qui sera manipulé
 */
void afficher_nombre(char * pol,int taille_pol, int pos_x, int pos_y, int nombre, SDL_Renderer * ren){
   TTF_Font *police;
   SDL_Rect position_txt;
   position_txt.x = pos_x;
   position_txt.y = pos_y;
   police = TTF_OpenFont(pol, taille_pol);
   TTF_SetFontStyle(police,TTF_STYLE_BOLD);
   SDL_Color couleur_police = {0, 0, 0};
   char temp[255];
   sprintf(temp,"%i",nombre);
   SDL_Surface *surface_texte = TTF_RenderText_Blended(police, temp, couleur_police);
   SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(ren, surface_texte);
   SDL_FreeSurface(surface_texte);
   SDL_QueryTexture(texture_texte, NULL, NULL, &position_txt.w, &position_txt.h);
   SDL_RenderCopy(ren, texture_texte, NULL, &position_txt);
   TTF_CloseFont(police);
}
/**
 * \brief Fonction qui libère tout ce qui a été créé
 * \param w Un pointeur sur une fenêtre
 * \param r Un pointeur sur un rendu
 * \param t Un pointeur sur une texture
 */
void nettoyerSDL(SDL_Window * w, SDL_Renderer * r, SDL_Texture * t) {
   if (t != NULL)
      SDL_DestroyTexture(t);
   if (r != NULL)
      SDL_DestroyRenderer(r);
   if (w != NULL)
      SDL_DestroyWindow(w);
}
