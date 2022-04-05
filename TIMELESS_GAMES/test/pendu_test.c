/**
 * \file pendu_test.c
 * \brief Test unitaire sur la fonction valider_mot
 * \author Duclos Christal Brochelard Hugo Duchesne Thibaut
 * \version 1.0
 * \date 05 avril 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <pendu.h>

int main() {
   // Initialisation de la fenêtre
   SDL_Window *win = NULL;
   SDL_Renderer *ren = NULL;
   t_pendu pendu;
   pendu.pendu = (char*)malloc(sizeof(char)); // Contient le mot sur lequel on joue au pendu
   pendu.secret = (char*)malloc(sizeof(char)); // Contient le mot secret
   // Lancement de la SDL
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
      SDL_ExitWithError("Initialisation SDL");
   // Création fenêtre + rendu
   if (SDL_CreateWindowAndRenderer(750, 500, 0, &win, &ren) != 0)
      SDL_ExitWithError("Impossible de créer la fenêtre et le rendu SDL.\n");
   // Fonction qui initialise SDL_TTF
   if (TTF_Init() == -1)
		SDL_ExitWithError("Impossible d'initialiser SDL_TTF.\n");
   // Fonction qui efface tout sur le rendu
   if (SDL_RenderClear(ren) != 0)
      SDL_ExitWithError("Effacement du rendu échoué.\n");
   initialiser_mot_ordi(win,ren,pendu.secret, pendu.pendu);
   printf("\n--------- Test 1 : Mauvais mot proposé : Vide ---------\n");
   if (valider_mot(pendu.secret, pendu.pendu)==1)
      printf("Mot trouvé\n");
   else
      printf("Mot incomplet\n");
   sprintf(pendu.pendu, pendu.secret);
   pendu.pendu[0]='_';
   printf("\n--------- Test 2 : Mauvais mot proposé : Bon mot pas de lettre au début ---------\n");
   if (valider_mot(pendu.secret, pendu.pendu) == 1)
      printf("Mot trouvé\n");
   else
      printf("Mot incomplet\n");
   pendu.secret= pendu.pendu;
   printf("\n--------- Test 3 : Bon mot proposé : Bon mot ---------\n");
   if (valider_mot(pendu.secret, pendu.pendu) == 1)
      printf("Mot trouvé\n");
   else
      printf("Mot incomplet\n");
   return 0;
}
