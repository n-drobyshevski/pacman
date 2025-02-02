#ifndef PACMAN_H
#define PACMAN_H

#include "include/SDL2/SDL.h"
#include "settings.h"
struct Pacman{
  int x;
  int y;
  int vel;
  char dir;
  SDL_Texture *texture; 
} ;

typedef struct Pacman TPacman;

TPacman initPacman(int x, int y,int vel, char dir, SDL_Renderer *renderer);
void renderPacman(const TPacman *pacman, SDL_Renderer *renderer);
void movePacman(TPacman *pacman,char old_dir, int map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX]);

#endif // PACMAN_H