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
      .pacman = {0, 0, 2, 'd', NULL},
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
        case SDLK_UP:
          game.pacman.dir = 'w';
          break;
        case SDLK_DOWN:
          game.pacman.dir = 's';
          break;
        case SDLK_LEFT:
          game.pacman.dir = 'd';
          break;
        case SDLK_RIGHT:
          game.pacman.dir = 'a';
          break;
        default:
          break;
        };
      default:
        break;
      };
    }

    clearRenderer(game.renderer);

    movePacman(&game.pacman, game.map); 

    RenderMap(&game);
    renderPacman(&game.pacman, game.renderer);
    SDL_RenderPresent(game.renderer);

    SDL_Delay(16);
  }

  game_clean(&game);
  return 0;
};
