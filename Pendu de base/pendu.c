/**
 * \file pendu.c
 * \brief Jeu du pendu
 * \author Christal Duclos
 * \version 2.0
 * \date 05 fevrier 22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Bibliothèque utile pour la fonction sleep()
#include <time.h> // Bibliothèque utile pour la fonction rand()

#define N 25 // Taille maximum des mots
#define OK 1
#define PAS_OK 0
#define JOUEUR1 "Tom" // Nom du joueur 1 à automatiser dans le menu du jeu
#define JOUEUR2 "Jerry" // Nom du joueur 2 à automatiser dans le menu du jeu

/**
 * \brief Transforme une lettre minuscule en majuscule
 * \param c Lettre minuscule
 * \return Renvoie une lettre majuscule
 */
char enMajuscule(char c) {
   return (c -= 'a' - 'A');
}

/**
 * \brief Verifie si c est une lettre
 * \param c Lettre
 * \return Renvoie 1 si c'est une lettre, 0 sinon
 */
int estLettre(char c) {
   return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * \brief Initilise le mot à trouver
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 */
void initialiserMotJoueur(char *secret, char *pendu) {
   int i, erreur;
   printf("Attention, %s ne doit pas regarder l'écran !\n", JOUEUR2);
   sleep(5); //Attends quelques secondes pour que le joueur 2 ne regarde plus l'écran
   // On recommence la saisie tant que le mot n'est pas bien saisi : exemple mettre des chiffres dans le mot
   do {
      do {
         printf("%s, saisissez un mot : ", JOUEUR1);
         scanf("%s%*c", secret);
      } while(strlen(secret) <= 2);
      erreur = PAS_OK;
      // Boucle qui initialise le 2ème mot pendu utilisé pour le jeu (ex : _ _ _ _)
      for (i = 0; i < secret[i] && erreur == PAS_OK; i++) {
         // Si la lettre est une majuscule
         if (secret[i] >= 'A' && secret[i] <= 'Z') {
            pendu[i] = '_';
         // Sinon si la lettre est une minuscule on la passe en majuscule
         } else if (secret[i] >= 'a' && secret[i] <= 'z') {
            secret[i] = enMajuscule(secret[i]);
            pendu[i] = '_';
         // Sinon le mot n'est pas correct
         } else {
            printf("Erreur dans la saisie du mot.\n\n");
            erreur = OK;
         }
      }
      pendu[i] = '\0';
   } while(erreur == OK);
   system("clear");
}

/**
 * \brief Initilise au hasard le mot à deviner avec une banque de mots
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 */
void initialiserMotOrdi(char *secret, char *pendu) {
   int i, nb_rand;
   FILE *listeMots = fopen("mots.txt", "r");
   srand(time(NULL)); // Initialisation du hasard
   nb_rand = rand() % (598 + 1 - 1); // Génération d'un nombre entre 1 et 598, soit le nombre de mots dans le fichier txt
   // Boucle pour accéder au mot à la ligne nb_rand du fichier
   for (i = 1; i <= nb_rand; i++)
      fscanf(listeMots, "%s", secret);
   fclose(listeMots);
   // Boucle qui initialise le 2ème mot pendu utilisé pour le jeu (ex : _ _ _ _)
   for (i = 0; i < secret[i]; i++)
      pendu[i] = '_';
   pendu[i] = '\0';
}

/**
 * \brief Affiche le mot en entrée à l'écran
 * \param mot Le mot à afficher
 */
void afficherMot(char *mot) {
   int i;
   for (i = 0; mot[i]; i++)
      printf("%c ", mot[i]);
   putchar('\n');
}

/**
 * \brief Affiche un visuel en console de l'avancement du pendu
 * \param erreurs Le nombre d'erreurs actuelles du joueur
 */
void afficherPendu(int erreurs) {
   switch(erreurs) {
      case 0: printf("\n"); break;
      case 1: printf("\n\n\n\n\n\n\n---------------\n");; break;
      case 2: printf("\n       |       \n       |       \n       |       \n       |       \n       |       \n       |       \n---------------\n"); break;
      case 3: printf("    ----------------\n       |       \n       |       \n       |       \n       |       \n       |       \n       |       \n---------------\n"); break;
      case 4: printf("    ----------------\n       | /      \n       |/      \n       |       \n       |       \n       |       \n       |       \n---------------\n"); break;
      case 5: printf("    ----------------\n       | /     |\n       |/      O\n       |       \n       |       \n       |       \n       |       \n---------------\n"); break;
      case 6: printf("    ----------------\n       | /     |\n       |/      O\n       |       |\n       |       |\n       |       \n       |       \n---------------\n"); break;
      case 7: printf("    ----------------\n       | /     |\n       |/      O\n       |       |/\n       |       |\n       |       \n       |       \n---------------\n"); break;
      case 8: printf("    ----------------\n       | /     |\n       |/      O\n       |      \\|/\n       |       |\n       |       \n       |       \n---------------\n"); break;
      case 9: printf("    ----------------\n       | /     |\n       |/      O\n       |      \\|/\n       |       |\n       |        \\\n       |       \n---------------\n"); break;
      case 10: printf("    ----------------\n       | /     |\n       |/      O\n       |      \\|/\n       |       |\n       |      / \\\n       |       \n---------------\n"); break;
      default : break;
   }
}

/**
 * \brief Permet au joueur de saisir un mot
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param alphabet La liste des lettres non utilisées
 * \return Renvoie le mot vérifié entré par le joueur
 */
char *saisie(char *secret, char *pendu, char *alphabet, int erreurs) {
   int i, check = OK;
   char *entree = (char*)malloc(sizeof(char)*N);
   // On recommence la saisie tant que le mot entré est incorrect
   do {
      printf("Mot : ");
      afficherMot(pendu);
      afficherPendu(erreurs);
      printf("\n\nSaisissez une lettre ou un mot : ");
      scanf("%s", entree);
      system("clear");
      // Si l'entrée est une lettre
      if (strlen(entree) == 1 && estLettre(entree[0])) {
         entree[0] = enMajuscule(entree[0]);
         check = PAS_OK;
         // On compare la lettre entrée à l'alphabet restant des lettres pas encore utilisées
         for (i = 0; i < alphabet[i]; i++) {
            // Si on trouve la lettre dans l'alphabet alors on la supprime de l'alphabet
            if (alphabet[i] == entree[0]) {
               alphabet[i] = '_';
               check = OK;
            }
         }
         // La lettre n'a pas été trouvée dans l'alphabet : elle a déjà été utilisée
         if (check == PAS_OK) {
            printf("Cette lettre a déjà été utilisée.\n");
         }
      // Si l'entrée est un mot
      } else if (strlen(entree) == strlen(secret)) {
         // Boucle qui vérifie que le mot est correctement écrit
         for (i = 0; entree[i] && check == OK; i++) {
            entree[i] = enMajuscule(entree[i]);
            if (entree[i] < 'A' || entree[i] > 'Z') {
               printf("Veuillez entrer un mot valide.\n");
               check = PAS_OK;
            } else {
               check = OK;
            }
         }
      // Sinon, l'entrée est erronée
      } else {
         printf("Entrée invalide.\n");
         check = PAS_OK;
      }
   } while(check == PAS_OK);
   return entree;
}

/**
 * \brief Regarde si la lettre entrée est dans le mot secret ou non
 * \param lettre La lettre entrée par le joueur
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \param erreurs Le nombre total actuel d'erreurs
 */
void validerLettre(char lettre, char *secret, char *pendu, int *erreurs) {
   int i, check = PAS_OK, compt = 0;
   for (i = 0; secret[i]; i++) {
      if (secret[i] == lettre) {
         pendu[i] = secret[i];
         check = OK;
         compt++;
      }
   }
   if (check != OK) {
      printf("Lettre invalide!\n");
      (*erreurs)++;
   } else {
      printf("Lettre valide %i fois !\n", compt);
   }
}

/**
 * \brief Regarde si le mot essayé est correct
 * \param secret Le mot à deviner
 * \param pendu Le mot sur lequel on joue au pendu composé au début de _ _
 * \return Renvoie OK si les deux mots sont identiques, PAS_OK si les deux mots ne sont pas identiques
 */
int validerMot(char *secret, char *pendu) {
   int i;
   for (i = 0; secret[i] && (secret[i] == pendu[i]); i++);
   // Si les deux mots sont identiques
   if (i == strlen(secret)) {
      return OK;
   // Sinon ils ne sont pas identiques
   } else {
      return PAS_OK;
   }
}

/**
 * \brief Fonction qui fait dérouler le jeu (comme un main)
 */
void jeuPendu(void) {
   // Variables
   char secret[N], pendu[N]; // Deux chaînes contenant le mot secret et le mot sur lequel on joue au pendu
   char *entree; // La lettre ou le mot que le joueur va entrer
   char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; // Un alphabet pour suivre les lettres utilisées par le joueur
   int essaiMot = 0, erreurs = 0, coups = 0, init;
   // Initialisation du choix du jeu
   do {
      system("clear");
      printf("Voulez-vous jouer contre un joueur ou contre l'ordinateur ?\n - 1 pour le joueur\n - 2 pour l'ordinateur\n");
      scanf("%i", &init);
   } while (init != 1 && init != 2);
   if (init == 1)
      initialiserMotJoueur(secret, pendu);
   else
      initialiserMotOrdi(secret, pendu);
   // Déroulement du jeu
   system("clear");
   while ((erreurs < 10) && (validerMot(secret, pendu) == PAS_OK) && (essaiMot == 0)) {
      entree = saisie(secret, pendu, alphabet, erreurs);
      if (strlen(entree) == 1) {
         validerLettre(entree[0], secret, pendu, &erreurs);
      } else {
         essaiMot = validerMot(secret, entree);
      }
      coups++;
   }
   // Fin du jeu
   afficherPendu(erreurs);
   if ((essaiMot == 1) || (validerMot(secret, pendu) == 1)) {
      printf("\nBravo ! Le mot était bien %s !\nVous avez trouvé le mot en %i coups et %i erreurs.\n\n", secret, coups, erreurs);
   } else {
      printf("\nVous êtes pendu ! Le mot était %s.\n\n", secret);
   }
}

int main() {
   jeuPendu();
   return 0;
}
