/**
 * \file masterm.c
 * \brief Fichier pour le jeu du mastermind
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 27 février 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Bibliothèque utile pour la fonction rand()
#include <unistd.h> // Bibliothèque utile pour la fonction sleep()

#define OK 1
#define PAS_OK 0
char JOUEUR1[10] = "J1"; // Variable globale du nom du joueur 1
char JOUEUR2[10] = "J2"; // Variable globale du nom du joueur 2

/**
 * \brief L'ordinateur initialise au hasard le code de couleurs à trouver
 * \param code Le code à deviner
 */
void saisir_code_ordi(char * code_secret) {
   int i, c_rand;
   char couleurs[6] = {'R', 'V', 'B', 'J', 'W', 'N'};
   srand(time(NULL)); // Initialisation du hasard
   for (i = 0; i < 4; i++) {
      c_rand = rand() % (6 + 1 - 1); // Génération d'un nombre entre 0 et 5
      code_secret[i] = couleurs[c_rand];
   }
   code_secret[i] = '\0';
}

/**
 * \brief Le joueur saisit un code de couleurs
 * \param code Le code à saisir
 * \param code Le nom du joueur qui fait la saisie
 */
void saisir_code_joueur(char * code, char * joueur) {
   int i, check;
   do {
      check = OK;
      printf("\nCouleurs disponibles :\n - R (rouge)\n - V (vert)\n - B (bleu)\n - J (jaune)\n - W (blanc)\n - N (noir)\n");
      printf("%s, saisissez un code de 4 couleurs (ex : BNJR) : ", joueur);
      scanf("%s%*c", code);
      if (strlen(code) != 4) {
         check = PAS_OK;
         system("cls"); // Linux : system("clear");
         printf("La taille du code est invalide.\n\n");
      } else {
         for (i = 0; (i < code[i]) && (check == OK); i++) {
            if (code[i] != 'R' && code[i] != 'V' && code[i] != 'B' && code[i] != 'J' && code[i] != 'W' && code[i] != 'N') {
               check = PAS_OK;
               system("cls"); // Linux : system("clear");
               printf("Une couleur au minimum est invalide.\n\n");
            }
         }
      }
   } while(check == PAS_OK);
   system("cls"); // Linux : system("clear");
}

/**
 * \brief Compte le nombre de bonnes couleurs entre le code secret et le code de jeu
 * \param code Le code de jeu
 * \param code_secret Le code secret qu'il faut deviner
 */
int nb_bonne_place(char * code, char * code_secret) {
   int i, cpt = 0;
   for (i = 0; i < 4; i++) {
      if (code[i] == code_secret[i])
         cpt++;
   }
   return cpt;
}

/**
 * \brief Compte le nombre de bonnes couleurs entre le code secret et le code de jeu
 * \param code Le code de jeu
 * \param code_secret Le code secret qu'il faut deviner
 * \param nb_place Le nombre de pions bien placés précédemment calculé
 */
int nb_bonne_couleur(char * code, char * code_secret, int nb_place) {
   int i, cpt = 0;
   int nb_R = 0, nb_V = 0, nb_B = 0, nb_J = 0, nb_W = 0, nb_N = 0;
   int nb_prop_R = 0, nb_prop_V = 0, nb_prop_B = 0, nb_prop_J = 0, nb_prop_W = 0, nb_prop_N = 0;

   // Comptage de chaque couleurs du tableau de la solution
   for (i = 0; i < 4; i++) {
      switch (code_secret[i]) {
         case 'R' : nb_R++; break;
         case 'B' : nb_B++; break;
         case 'V' : nb_V++; break;
         case 'J' : nb_J++; break;
         case 'W' : nb_W++; break;
         case 'N' : nb_N++; break;
      }
   }
   // Comptage de chaque couleurs du tableau de la proposition
   for (i = 0; i < 4; i++) {
      switch(code[i]) {
         case 'R' : nb_prop_R++; break;
         case 'B' : nb_prop_B++; break;
         case 'V' : nb_prop_V++; break;
         case 'J' : nb_prop_J++; break;
         case 'W' : nb_prop_W++; break;
         case 'N' : nb_prop_N++; break;
      }
   }
   // Comptage des pions de la bonne couleur et somme des minimums
   if (nb_R <= nb_prop_R) // couleur rouge
      cpt += nb_R;
   else
      cpt += nb_prop_R;
   if (nb_V <= nb_prop_V) // couleur verte
      cpt += nb_V;
   else
      cpt += nb_prop_V;
   if (nb_B <= nb_prop_B) // couleur bleue
      cpt += nb_B;
   else
      cpt += nb_prop_B;
   if (nb_J <= nb_prop_J) // couleur jaune
      cpt += nb_J;
   else
      cpt += nb_prop_J;
   if (nb_W <= nb_prop_W) // couleur blanche
      cpt += nb_W;
   else
      cpt += nb_prop_W;
   if (nb_N <= nb_prop_N) // couleur noire
      cpt += nb_N;
   else
      cpt += nb_prop_N;
   return (cpt - nb_place); // on retire les pions bien placés
}

void jeu_masterm() {
   //Variables
   int nb_couleur, nb_place, erreurs = 0;
   int nb_col_essai, nb_pla_essai, num_essai;
   char *code = (char*)(malloc(sizeof(char)*4));
   char *code_secret = (char*)(malloc(sizeof(char)*4));
   char *code_essai = (char*)(malloc(sizeof(char)*4 ));
   FILE *essais = NULL;

   // Vide le fichier essais s'il comportant du contenu
   essais = fopen("essais.txt", "w");
   fclose(essais);

   //Déroulement du jeu
   saisir_code_ordi(code_secret);
   saisir_code_joueur(code, JOUEUR2);
   erreurs++;
   // Tant qu'on a pas dépassé le nombre d'essais autorisés ou qu'on a pas trouvé le code
   while (erreurs < 12 && strcmp(code, code_secret) != 0) {
      // Comptages
      nb_place = nb_bonne_place(code, code_secret);
      nb_couleur = nb_bonne_couleur(code, code_secret, nb_place);
      // Stockage de l'essai actuel dans un fichier essais.txt
      essais = fopen("essais.txt", "a");
      fprintf(essais, "%i %s %i %i\n", erreurs, code, nb_place, nb_couleur);
      fclose(essais);
      // Affichage de tous les essais grâce à au stockage dans le fichier txt
      essais = fopen("essais.txt", "r");
      fscanf(essais, "%i %s %i %i[^\n]", &num_essai, code_essai, &nb_pla_essai, &nb_col_essai);
      while (! feof(essais)) {
         printf("Voici ton essai n°%i : %s. Il y a %i pions bien placés et %i pions de bonne couleur.\n", num_essai, code_essai, nb_pla_essai, nb_col_essai);
         fscanf(essais, "%i %s %i %i[^\n]", &num_essai, code_essai, &nb_pla_essai, &nb_col_essai);
      }
      fclose(essais);
      //Saisie suivante
      saisir_code_joueur(code, JOUEUR2);
      erreurs++;
   }
   // Affichage du résultat
   if (erreurs <= 12)
      printf("Gagné ! Tu as trouvé en %i coups et le mot était bien %s.\n", erreurs, code);
   else
      printf("Perdu ! Le code était %s\n", code_secret);
   // Libération de la mémoire
   free(code);
   free(code_secret);
   free(code_essai);
}

int main() {
   jeu_masterm();
   return 0;
}
