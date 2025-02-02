#include "gestionGraphique.h"
#include "include/SDL2/SDL.h"
#include <stdbool.h>
#include <stdlib.h>

#define WINDOW_W 305
#define WINDOW_H 330
#define MAP_HEIGHT_MAX 21
#define MAP_WIDTH_MAX 19
#define WALL_SIZE_W 16
#define WALL_SIZE_H 16
#define GUM_SIZE_H 16
#define GUM_SIZE_W 16
#define TILE_SIZE 16
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
};

typedef struct Game TGame;

void game_init(TGame *game); // renvoie à la fonction game plus bas
void game_clean(TGame *game);
void media_init(TGame *game);
void map_init(TGame *game);
void RenderMap(TGame *game);

int main(int argc, char *argv[]) {
  TGame game = {
      // initialise l'objet game
      .window = NULL, 
      .renderer = NULL,
      .wall = NULL,
      .gum = NULL, 
      .map = 0,
  };
  game_init(&game);
  media_init(&game);

  map_init(&game);
  bool quit = false; // !CHANGE
  while (!quit) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true; //!change
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE: //!CHANGE sdlk
          quit = true; //!change
          break;
        default:
          break;
        };
      default:
        break;
      };
    }

    clearRenderer(game.renderer);

    renderTexture(game.sprite, game.renderer, game.sprite_x, game.sprite_y,
                  game.sprite_w, game.sprite_h);

    RenderMap(&game);
    SDL_RenderPresent(game.renderer);

    SDL_Delay(16);
  }

  game_clean(&game);
  return 0;
};
void game_init(TGame *game) {
  game->window = createWindow("Pacman", WINDOW_W, WINDOW_H);
  game->renderer = createRenderer(game->window);
};

void game_clean(TGame *game) {
  QuitSDL(game->window, game->renderer);
  exit(0);
};

void media_init(TGame *game) {
  game->sprite = loadTexture("src/pakuman_0.bmp", game->renderer);

  game->wall = loadTexture("src/wall.bmp", game->renderer);
    game->gum = loadTexture("src/gum.bmp", game->renderer);
}

void map_init(TGame *game) {
  int temp_map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
      {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
      {1, 3, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 3, 1},
      {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
      {1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
      {1, 2, 2, 2, 2, 1, 3, 2, 2, 1, 2, 2, 3, 1, 2, 2, 2, 2, 1},
      {1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1},
      {1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1},
      {1, 1, 1, 1, 2, 1, 0, 1, 1, 0, 1, 1, 0, 1, 2, 1, 1, 1, 1},
      {1, 1, 1, 1, 2, 2, 0, 1, 0, 0, 0, 1, 0, 2, 2, 1, 1, 1, 1},
      {1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1},
      {1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1},
      {1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1},
      {1, 2, 2, 2, 2, 1, 3, 2, 2, 1, 2, 2, 3, 1, 2, 2, 2, 2, 1},
      {1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
      {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
      {1, 3, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 3, 1},
      {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
      {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  for (int i = 0; i < MAP_HEIGHT_MAX; i++) {
    for (int j = 0; j < MAP_WIDTH_MAX; j++) {
      game->map[i][j] = temp_map[i][j]; // Copie ligne par ligne
    }
  }
};


void RenderMap(TGame *game) {
  int i, j;
  int tile_x, tile_y;
  for (i = 0; i < MAP_HEIGHT_MAX; i++) {
    tile_y = i * TILE_SIZE;
    for (j = 0; j < MAP_WIDTH_MAX; j++) {
      tile_x = j * TILE_SIZE; // prend tous les multiples de la lageur du mur
      switch (game->map[i][j]) {
      case 1:
        renderTexture(game->wall, game->renderer, tile_x, tile_y, TILE_SIZE,
                      TILE_SIZE);
        break;
      case 2:
        renderTexture(game->gum, game->renderer, tile_x, tile_y, TILE_SIZE,
                      TILE_SIZE);
        break;
      default:
        break;
      }
    };
  };
}
