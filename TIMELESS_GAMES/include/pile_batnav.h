/**
 * \file pile_batnav.h
 * \brief Fichier contenant les prototypes des primitives de la pile
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 28 mars 2022
 */

void init_pile(void);
int pile_vide(void);
void empiler(int coord_case);
void depiler(int * coord_case);
int lire_sommet(void);
