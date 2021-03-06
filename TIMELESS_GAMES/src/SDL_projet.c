/**
 * \file SDL_projet.c
 * \brief Fichier comprenant toutes les fonctions de manipulation de SDL
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 05 avril 2022
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
 * \param win La fenêtre qui sera manipulée
 * \param ren Le rendu qui sera manipulé
 * \param nom_img Le nom de l'image à afficher
 * \param coordx La position en abscisse de l'image
 * \param coordy La position en ordonnée de l'image
 */
void afficher_image(SDL_Window * win, SDL_Renderer * ren, char * nom_img, int coordx, int coordy) {
   SDL_Surface *image = NULL;
   SDL_Texture *texture = NULL;
   // On charge l'image souhaitée dans une surface
   image = IMG_Load(nom_img);
   if (image == NULL) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible de trouver l'image.\n");
   }
   // On crée une texture à partir d'une surface contenant l'image
   texture = SDL_CreateTextureFromSurface(ren, image);
   SDL_FreeSurface(image);
   if (texture == NULL) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible de créer la texture.\n");
   }
   // On délimite la zone où afficher l'image
   SDL_Rect rectangle;
   if (SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h)) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible de charger la texture.\n");
   }
   rectangle.x = coordx;
   rectangle.y = coordy;
   // On affiche la texture dans le rendu sans le mettre à jour pour ne pas faire de surplus
   if (SDL_RenderCopy(ren, texture, NULL, &rectangle)) {
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_ExitWithError("Impossible d'afficher la texture.\n");
   }
}

/**
 * \brief Fonction qui permet l'affichage d'un texte à une position donnée d'une certaine taille
 * \param ren Le rendu qui sera manipulé
 * \param pol La police utilisée
 * \param taille_pol La taille de la police
 * \param pos_x La position en abscisse du texte
 * \param pos_y La position en ordonnée du texte
 * \param texte Le texte a afficher
 */
void afficher_texte(SDL_Renderer * ren, char * pol, int taille_pol, int pos_x, int pos_y, char * texte) {
   TTF_Font *police;
   SDL_Rect position_txt;
   position_txt.x = pos_x;
   position_txt.y = pos_y;
   // On ouvre la police d'écriture et défini ses paramètres
   police = TTF_OpenFont(pol, taille_pol);
   TTF_SetFontStyle(police,TTF_STYLE_BOLD);
   SDL_Color couleur_police = {0, 0, 0};
   // On crée une surface d'écriture de texte
   SDL_Surface *surface_texte = TTF_RenderText_Blended(police, texte, couleur_police);
   if(surface_texte == NULL){
      SDL_DestroyRenderer(ren);
      SDL_ExitWithError("Impossible de crée la surface texte.\n");
   }
   // On crée une texture à partir de la surface de texte
   SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(ren, surface_texte);
   if(texture_texte == NULL){
      SDL_DestroyRenderer(ren);
      SDL_ExitWithError("Impossible de crée la texture texte.\n");
   }
   SDL_FreeSurface(surface_texte);
   // On indique où l'on va placer le texte et on l'affiche
   SDL_QueryTexture(texture_texte, NULL, NULL, &position_txt.w, &position_txt.h);
   SDL_RenderCopy(ren, texture_texte, NULL, &position_txt);
   TTF_CloseFont(police);
}

/**
 * \brief Fonction qui permet l'affichage d'une nombre à une position donnée d'une certaine taille
 * \param ren Le rendu qui sera manipulé
 * \param pol La police utilisée
 * \param taille_pol La taille de la police
 * \param pos_x La position en abscisse du texte
 * \param pos_y La position en ordonnée du texte
 * \param nombre le nombre a afficher
 */
void afficher_nombre(SDL_Renderer * ren, char * pol, int taille_pol, int pos_x, int pos_y, int nombre) {
   TTF_Font *police;
   SDL_Rect position_txt;
   SDL_Color couleur_police = {0, 0, 0};
   char temp[255];
   position_txt.x = pos_x;
   position_txt.y = pos_y;
   // On ouvre la police d'écriture et défini ses paramètres
   police = TTF_OpenFont(pol, taille_pol);
   TTF_SetFontStyle(police,TTF_STYLE_BOLD);
   sprintf(temp, "%i", nombre);
   // On créé une surface d'écriture de texte
   SDL_Surface *surface_texte = TTF_RenderText_Blended(police, temp, couleur_police);
   if(surface_texte == NULL){
      SDL_DestroyRenderer(ren);
      SDL_ExitWithError("Impossible de crée la surface texte.\n");
   }
   // On crée une texture à partir de la surface de texte
   SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(ren, surface_texte);
   if(texture_texte == NULL){
      SDL_DestroyRenderer(ren);
      SDL_ExitWithError("Impossible de crée la texture texte.\n");
   }
   SDL_FreeSurface(surface_texte);
   // On indique où l'on va placer le texte et on l'affiche
   SDL_QueryTexture(texture_texte, NULL, NULL, &position_txt.w, &position_txt.h);
   SDL_RenderCopy(ren, texture_texte, NULL, &position_txt);
   TTF_CloseFont(police);
}
/**
 * \brief Fonction qui libère tout ce qui a été créé
 * \param win Un pointeur sur une fenêtre
 * \param ren Un pointeur sur un rendu
 * \param tex Un pointeur sur une texture
 */
void nettoyerSDL(SDL_Window * win, SDL_Renderer * ren, SDL_Texture * tex) {
   if (tex != NULL)
      SDL_DestroyTexture(tex);
   if (ren != NULL)
      SDL_DestroyRenderer(ren);
   if (win != NULL)
      SDL_DestroyWindow(win);
}
