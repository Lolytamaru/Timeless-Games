#ifndef ALLINCLUDES_H
#define ALLINCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> // Bibliothèque utile pour la fonction sleep()
#include <time.h> // Bibliothèque utile pour la fonction rand()
#include <SDL2/SDL.h> // Bibliothèque principale de SDL
#include <SDL2/SDL_ttf.h> // Bibliothèque de SDL utile pour l'affichage texte
#include <SDL2/SDL_image.h> // Bibliothèque de SDL utile pour utiliser tout les formats d'image
#include <SDL2/SDL_keycode.h> // Bibliothèque de SDL utile pour l'entrée de lettres au clavier
#include <SDL_projet.h> // Bibliothèque personnelle de SDL condensée

#define N 26
// Definition de valeur pour chaque statut du programme selon la fenêtre
#define J1 37
#define J2 38
enum {JVSJ =39,JVSO};
enum{PENDU_JCJ_INIT =70,PENDUJEU,PENDUFINI};
typedef enum {ACCUEIL=30, MENU, PENDU, MASTERMIND, BATNAV, PARAM, PSEUDO } t_statut;


#endif // ALLINCLUDES_H
