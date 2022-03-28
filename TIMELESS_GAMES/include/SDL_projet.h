void SDL_ExitWithError(const char * message);
void afficher_image(char * nom_img, int coordx, int coordy, SDL_Window * win, SDL_Renderer * ren);
void afficher_texte(char * pol, int taille_pol, int pos_x, int pos_y,  char * texte, SDL_Renderer * ren);
void afficher_nombre(char * pol,int taille_pol, int pos_x, int pos_y, int nombre, SDL_Renderer * ren);
void nettoyerSDL(SDL_Window * w, SDL_Renderer * r, SDL_Texture * t);
