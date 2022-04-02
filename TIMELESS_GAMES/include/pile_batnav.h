/**
 * \file pile_batnav.h
 * \brief Fichier contenant les prototypes des primitives de la pile
 * \author Duclos Christal Brochelard Hugo Thibaut Duchesne
 * \version 1.0
 * \date 02 avril 2022
 */

/**
 * \struct coord_ordi_t Structure qui contient les coordonnées d'une case
 */
typedef struct s_coord_ordi {
    int x;
    int y;
} coord_ordi_t;

void init_pile(void);
int pile_vide(void);
void empiler(coord_ordi_t coord_case);
void depiler(coord_ordi_t * coord_case);
coord_ordi_t lire_sommet(void);
