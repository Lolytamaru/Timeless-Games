/**
 * \file SDL.projet.h
 * \brief Fichier de prototypes pour le fichier contenant les fonctions SDL
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 28 mars 2022
 */

void SDL_ExitWithError(const char * message);
void afficher_image(SDL_Window * win, SDL_Renderer * ren, char * nom_img, int coordx, int coordy);
void afficher_texte(SDL_Renderer * ren, char * pol, int taille_pol, int pos_x, int pos_y, char * texte);
void afficher_nombre(SDL_Renderer * ren, char * pol, int taille_pol, int pos_x, int pos_y, int nombre);
void nettoyerSDL(SDL_Window * win, SDL_Renderer * ren, SDL_Texture * tex);
