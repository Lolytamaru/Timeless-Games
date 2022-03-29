typedef struct s_bateau {
   char immat;
   int taille;
   int engager;
} bateau_t;

typedef struct s_case {
   int etat;
   int occuper;
   char * nom_bat;
} case_t;

typedef struct s_mat {
   case_t **data;
   int nbc, nbl;
} mat_t;

mat_t creer_mat(int l, int c);
void remplissage_bateau_depart(bateau_t * J);
void afficher_mat(mat_t mat);
int est_valide(int i,int j,mat_t mat);
void placement_bateau_case(mat_t * J, char cote, int x, int y, char * nom_bateau, bateau_t bat);
int direction_valide(mat_t J, char cote, int x, int y, bateau_t bat);
