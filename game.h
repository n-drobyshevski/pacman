#ifndef GAME_H
#define GAME_H
#include "gestionGraphique.h"
#include "include/SDL2/SDL.h"
#include "pacman.h"
#include "settings.h"
#include <stdbool.h>
#include <stdlib.h>

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *sprite;

  SDL_Texture *wall;
  SDL_Texture *gum;
  int sprite_x;
  int sprite_y;
  int sprite_w;
  int sprite_h;
  int map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

  TPacman pacman;
};

struct Coords {
  int x;
  int y;
};
typedef struct Coords TCoords;
typedef struct Game TGame;

void game_init(TGame *game); // renvoie à la fonction game plus bas
void game_clean(TGame *game);

void media_init(TGame *game);
void map_init(TGame *game);

void RenderMap(TGame *game);

int getTileType(int map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int x, int y);
TCoords getTileCoords(int x, int y);
TCoords getCoords(int tileX, int tileY);
void start_menu(TGame *game);
#endif