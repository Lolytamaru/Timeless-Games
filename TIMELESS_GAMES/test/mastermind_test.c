#include <all_includes.h>
#include <joueur.h>
#include <masterm.h>

/**
 * \file main.c
 * \brief Test unitaire sur la fonction proposition_pas_vide
 * \author Duclos Christal Brochelard Hugo Duchesne Thibaut
 * \version 1.0
 * \date 04 avril 2022
 */

int main(){

  char propo_couleur[4]={' ',' ',' ',' '};
   printf("\n---------Test 1: Mauvaise combinaison: combinaison( , , , )---------\n");
   if(proposition_pas_vide(propo_couleur)==1)
      printf("Proposition complète\n");
   else
      printf("Proposition incomplète\n");

   propo_couleur[0] = 'N';
   propo_couleur[1] = 'V';
   propo_couleur[2] = 'B';
   propo_couleur[3] = 'R';
   printf("\n---------Test 2: Bonne combinaison: combinaison(N,V,B,R)---------\n");
   if(proposition_pas_vide(propo_couleur)==1)
      printf("Proposition complète\n");
   else
      printf("Proposition incomplète\n");


   return 0;
 }
