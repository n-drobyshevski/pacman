#ifndef PACMAN_H
#define PACMAN_H

#include "include/SDL2/SDL.h"

struct Pacman{
  int x;
  int y;
  SDL_Texture *texture; 
} ;

typedef struct Pacman TPacman;

TPacman initPacman(int x, int y,
                const char *texturePath, SDL_Renderer *renderer);
void renderPacman(const TPacman *pacman, SDL_Renderer *renderer);
// int getPacmanX(const Pacman *pacman);
// int getPacmanY(const Pacman *pacman);

// void setPacmanX(Pacman *pacman, int x);
// void setPacmanY(Pacman *pacman, int y);

// void movePacman(Pacman *pacman, char direction);

#endif // PACMAN_H