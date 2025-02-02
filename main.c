#include "gestionGraphique.h"
#include "include/SDL2/SDL.h"
#include <stdbool.h>
#include <stdlib.h>
#include "pacman.h"
#include "settings.h"
#include "game.h"


int main(int argc, char *argv[]) {
  TGame game = {
      // initialise l'objet game
      .window = NULL,
      .renderer = NULL,
      .wall = NULL,
      .gum = NULL,
      .pacman = {0, 0, NULL},
      .map = {0},
  };
  game_init(&game);

  if (PRODUCTION_MODE){
    start_menu(&game);
  }

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


    RenderMap(&game);

    renderPacman(&game.pacman, game.renderer);
    renderTexture(game.sprite, game.renderer, game.sprite_x, game.sprite_y,
                  game.sprite_w, game.sprite_h);
    SDL_RenderPresent(game.renderer);

    SDL_Delay(16);
  }

  game_clean(&game);
  return 0;
};
