/**
 * \file bataille_navale_test.c
 * \brief Test unitaire sur la fonction vider_cargaison
 * \author Duclos Christal Brochelard Hugo Duchesne Thibaut
 * \version 1.0
 * \date 05 avril 2022
 */

#include <all_includes.h>
#include <joueur.h>
#include <batnav.h>

int main() {
   // Initialisation de la fenêtre
   SDL_Window *win = NULL;
   SDL_Renderer *ren = NULL;
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
    init_partie_batnav();

   printf("\n--------- Test 1 : Bon bateau : Torpilleur de taille 2 ---------\n");
   if (vider_cargaison(win, ren, 2, "Torpilleur"))
      printf("Bateau vidé\n");
   else
      printf("Bateau inexistant\n");

   printf("\n--------- Test 2 : Mauvaise taille de bateau : Torpilleur de taille 11 ---------\n");
   if (vider_cargaison(win, ren, 11, "Torpilleur"))
      printf("Bateau vidé\n");
   else
      printf("Bateau inexistant\n");

   printf("\n--------- Test 3 : Mauvaise taille de bateau : Torpilleur de taille 0 ---------\n");
   if (vider_cargaison(win, ren, 0, "Torpilleur"))
      printf("Bateau vidé\n");
   else
      printf("Bateau inexistant\n");
   return 0;
}
