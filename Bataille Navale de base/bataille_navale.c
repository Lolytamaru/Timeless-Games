#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <bataille_navale.h>

mat_t creer_mat(int l, int c) {
	mat_t m;
	int i;
	m.nbl = l + 1;
	m.nbc = c + 1;
	case_t *data = malloc(sizeof(case_t) * m.nbc * m.nbl);
	m.data = malloc(sizeof(case_t) * m.nbl);
	for (i = 0; i < m.nbl; i++)
		m.data[i] = data + (i * m.nbc);
	return m;
}

void remplissage_bateau_depart(bateau_t * J) {
   bateau_t torpilleur;
   torpilleur.immat = 'A';
   torpilleur.taille = 2;
   torpilleur.engager = 0;
   J[0] = torpilleur;

   bateau_t contre_torpilleur1;
   contre_torpilleur1.immat = 'A';
   contre_torpilleur1.taille = 3;
   contre_torpilleur1.engager = 0;
   J[1] = contre_torpilleur1;

   bateau_t contre_torpilleur2;
   contre_torpilleur2.immat = 'B';
   contre_torpilleur2.taille = 3;
   contre_torpilleur2.engager = 0;
   J[2] = contre_torpilleur2;

   bateau_t croiseur;
   croiseur.immat = 'A';
   croiseur.taille = 4;
   croiseur.engager = 0;
   J[3] = croiseur;

   bateau_t porte_avions;
   porte_avions.immat = 'A';
   porte_avions.taille = 5;
   porte_avions.engager = 0;
   J[4] = porte_avions;
}

void afficher_mat(mat_t mat) {
   int i, j;
   for (i = 1; i < mat.nbc; i++) {
      for (j = 1; j < mat.nbl; j++) {
         if (mat.data[j][i].occuper == 0) {
            printf("   |");
         } else {
            printf(" X |");
         }
      }
      printf("\n");
   }
}

int est_valide(int i, int j, mat_t mat) {
  return ((i >= 1 && i < mat.nbl) && (j >= 1 && j < mat.nbc));
}

void placement_bateau_case(mat_t * J, char cote, int x, int y, char * nom_bateau, bateau_t bat) {
   int min, max;
   switch(cote) {
      case 'N':
         min = y - bat.taille;
         while (y > min) {
           	J->data[x][y].occuper = 1;
            J->data[x][y].nom_bat = nom_bateau;
            y--;
         } break;
      case 'S':
       	max = y + bat.taille;
         while (y < max) {
          	J->data[x][y].occuper = 1;
            J->data[x][y].nom_bat = nom_bateau;
            y++;
         } break;
      case 'O':
         min = x - bat.taille;
         while (x > min) {
            J->data[x][y].occuper = 1;
            J->data[x][y].nom_bat = nom_bateau;
            x--;
         } break;
      case 'E':
         max = x + bat.taille;
         while (x < max) {
           	J->data[x][y].occuper = 1;
            J->data[x][y].nom_bat = nom_bateau;
            x++;
         } break;
      default: printf("default");
    }
}

int direction_valide(mat_t J, char cote, int x, int y, bateau_t bat) {
   int min = 0, max = 0, cpt = 0;
   switch (cote) {
      case 'N':
         min = y - bat.taille;
         if (min >= 1) {
           	while (y > min) {
					if (J.data[x][y].occuper == 0)
                  cpt += est_valide(x, y, J);
               y--;
            }
         } else {
            return 0;
         }
         if (cpt == bat.taille)
            return 1;
         break;
      case 'S':
         max = y + bat.taille;
         if (max < 10) {
	         while (y < max) {
					if (J.data[x][y].occuper == 0)
	               cpt += est_valide(x, y, J);
	            y++;
	         }
         } else {
            return 0;
         }
			if (cpt == bat.taille)
            return 1;
         break;
      case 'O':
         min = x - bat.taille;
         if (min >= 1) {
         	while (x > min) {
					if (J.data[x][y].occuper == 0) {
                  cpt += est_valide(x,y,J);
					}
               x--;
            }
         } else {
            return 0;
         }
			if (cpt == bat.taille)
           	return 1;
         break;
      case 'E':
         max = x + bat.taille;
         if (max < J.nbc) {
            while (x < max) {
					if (J.data[x][y].occuper == 0)
                  cpt += est_valide(x, y, J);
               x++;
            }
         } else {
            return 0;
         }
			if (cpt == bat.taille)
            return 1;
         break;
      default:
		  	return 0;
			break;
   }
   return 0;
}

void demande_placement_bateau(mat_t J, bateau_t * s_J, char * T[5]) {
   int x = -1, y = -1, i = 0;
   char cote, c = '0';
   printf("Joueur:\n");
   while(i < 5) {
      cote = '0';
      do {
         printf("Où veux-tu placer le %s:%c? (donnez les coordonnées): ", T[i], s_J[i].immat);
         if (scanf("%i %i", &x, &y) == 0) {
				do {
					c = getchar();
				} while (!isdigit(c));
				ungetc(c,stdin);
			}
      } while((x < 0) || (x > J.nbl) || (y < 0) || (y > J.nbc) || (J.data[x][y].occuper == 1) || (!est_valide(x, y, J)));
     	do {
         printf("\nDe quel côté? (N pour Nord, O pour Ouest, E pour Est, S pour Sud): ");
         scanf("%c", &cote);
			if (isalpha(cote) == 0)
				scanf("%c", &cote);
            if (direction_valide(J, cote, x, y, s_J[i]) == 0)
               printf("\nErreur: changer de direction: direction %c impossible\n", cote);
      } while(direction_valide(J, cote, x, y, s_J[i]) == 0);
      printf("\n\n");
     	placement_bateau_case(&J, cote, x, y, T[i], s_J[i]);
      afficher_mat(J);
      i++;
   }
   printf("\n\n");
}

int main(void) {
   mat_t J1 = creer_mat(10, 10);
   mat_t J2 = creer_mat(10, 10);
 	bateau_t s_J1[6];
   bateau_t s_J2[6];
   char * T[5] = {"torpilleur", "contre-torpilleur:1", "contre-torpilleur:2", "croiseur", "porte-avions"};
 	remplissage_bateau_depart(s_J1);
   remplissage_bateau_depart(s_J2);
   printf("\n");
   afficher_mat(J1);
   printf("\n----------------------------------------\n\n");
   afficher_mat(J2);
   printf("\n");
 	demande_placement_bateau(J1, s_J1, T);
   printf("\nPassons à l'autre joueur\n");
   demande_placement_bateau(J2, s_J2, T);
 	afficher_mat(J1);
   printf("\n----------------------------------------\n\n");
   afficher_mat(J2);
}
