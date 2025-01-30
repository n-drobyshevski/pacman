#include "gestionGraphique.h"
#include "include/SDL2/SDL.h"
#include <stdbool.h>
#include <stdlib.h>

#define WINDOW_H 500
#define WINDOW_W 600

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *sprite;
  int sprite_x;
  int sprite_y; 
  int sprite_w;
  int sprite_h;
};

typedef struct Game TGame;

void game_init(TGame *game);
void game_clean(TGame *game);
void media_init(TGame *game);


int main(int argc, char *argv[]) {
  TGame game = {
      .window = NULL,
      .renderer = NULL,
      .sprite = NULL,
      .sprite_x = 0,
      .sprite_y = 0, 
      .sprite_w = 16,
      .sprite_h = 16,
  };
  game_init(&game);
  media_init(&game);

  bool quit = true;
  while (quit) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = false;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
          quit = false;
          break;
        default:
          break;
        };
      default:
        break;
      };
    }

    clearRenderer(game.renderer);

    renderTexture(game.sprite, game.renderer, game.sprite_x, game.sprite_y,game.sprite_w, game.sprite_h);
    
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

void media_init(TGame *game){
  game->sprite = loadTexture("src/pakuman_0.bmp", game->renderer);
}