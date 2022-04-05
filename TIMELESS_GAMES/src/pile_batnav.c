/**
 * \file pile_batnav.c
 * \brief Fichier contenant les primitives d'une pile pour le jeu de la bataille navale
 * \author Duclos Christal
 * \version 1.0
 * \date 05 avril 2022
 */

#include <pile_batnav.h>

#define TAILLE_MAX 100
coord_ordi_t pile[TAILLE_MAX];
int sommet_pile;

/**
 * \brief Primitive qui initialise une pile
 */
void init_pile(void) {
   sommet_pile = -1;
}

/**
 * \brief Primitive qui regarde si la pile est vide ou non
 * \return Renvoie 1 si la pile est vide, 0 sinon
 */
int pile_vide(void) {
   return (sommet_pile == -1);
}

/**
 * \brief Primitive qui empile des coordonnéesdans la pile et met à jour le sommet de la pile
 * \param coord_case Structure contenant les coordonnées de la case du plateau que l'on veut empiler
 */
void empiler(coord_ordi_t coord_case) {
   if (sommet_pile < TAILLE_MAX - 1) {
      sommet_pile++;
      pile[sommet_pile] = coord_case;
   }
}

/**
 * \brief Primitive qui dépile des coordonnées dans la pile et met à jour le sommet de la pile
 * \param coord_case Récupère la valeur des coordonnées dépilées
 */
void depiler(coord_ordi_t * coord_case) {
   if (sommet_pile > -1) {
      *coord_case = pile[sommet_pile];
      sommet_pile--;
   }
}

/**
 * \brief Primitive qui lit les coordonnées au sommet de la pile
 * \return coord_case Renvoie les coordonnées
 */
coord_ordi_t lire_sommet(void) {
   return (pile[sommet_pile]);
}
