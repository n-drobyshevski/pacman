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
    char old_dir = game.pacman.dir;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true; //!change
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          quit = true;
          break;
        case SDLK_UP:
        case SDLK_w:
          game.pacman.dir = 'w';
          break;
        case SDLK_DOWN:
        case SDLK_s:
          game.pacman.dir = 's';
          break;
        case SDLK_LEFT:
        case SDLK_a:
          game.pacman.dir = 'a';
          break;
        case SDLK_RIGHT:
        case SDLK_d:
          game.pacman.dir = 'd';
          break;
        default:
          break;
        };
      default:
        break;
      };
    }

    clearRenderer(game.renderer);

    movePacman(&game.pacman,old_dir, game.map); 

    RenderMap(&game);
    renderPacman(&game.pacman, game.renderer);
    SDL_RenderPresent(game.renderer);

    SDL_Delay(16);
  }

  game_clean(&game);
  return 0;
};
