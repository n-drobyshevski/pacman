#include "gestionGraphique.h"
#include "include/SDL2/SDL.h"
#include "pacman.h"
#include "settings.h"
#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

void game_init(TGame *game) {
  game->window = createWindow("Pacman", WINDOW_W, WINDOW_H);
  game->renderer = createRenderer(game->window);
  game->pacman = initPacman( 9*TILE_SIZE, 8*TILE_SIZE,"src/pakuman/pakuman_0.bmp" ,game->renderer);
  media_init(game);
  map_init(game);
};

void game_clean(TGame *game) {
  QuitSDL(game->window, game->renderer);
  exit(0);
};

void media_init(TGame *game) {
  game->sprite =
      loadTexture("src/pakuman/pakuman_0.bmp", game->renderer); //! change path
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

void start_menu(TGame *game) {
  bool start = false;
  SDL_Rect startButton = {WINDOW_W / 2 - 50, WINDOW_H / 2 + 90, 100, 50};

  TTF_Init();
  TTF_Font *font = createFont(FONT_SRC, 24);
  SDL_Color white = {255, 255, 255, 255};

  SDL_Texture *pacmanTextures[4];
  pacmanTextures[0] = loadTexture("src/pakuman/pakuman_3.bmp", game->renderer);
  pacmanTextures[1] = loadTexture("src/pakuman/pakuman_2.bmp", game->renderer);
  pacmanTextures[2] = loadTexture("src/pakuman/pakuman_1.bmp", game->renderer);
  pacmanTextures[3] = loadTexture("src/pakuman/pakuman_0.bmp", game->renderer);

  SDL_Texture *pacmanLogo = loadTexture("src/pacmanlogo.bmp", game->renderer);
  SDL_Rect logoRect = {WINDOW_W / 2 - 75, WINDOW_H / 2 - 150, 150,
                       50}; // Adjust dimensions as needed

  SDL_Rect pacmanRect = {WINDOW_W / 2 - 25, WINDOW_H / 2 - 70, 50, 50};

  int currentFrame = 0;
  Uint32 frameTime = 0;
  const Uint32 frameDelay = 500;

  while (!start) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        game_clean(game);
        exit(0);
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          game_clean(game);
          exit(0);
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          int x = event.button.x;
          int y = event.button.y;
          if (x >= startButton.x && x <= startButton.x + startButton.w &&
              y >= startButton.y && y <= startButton.y + startButton.h) {
            start = true; // Start the game when the button is clicked
          }
        }
        break;
      default:
        break;
      }
    }

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    clearRenderer(game->renderer);

    // Update animation frame
    if (SDL_GetTicks() - frameTime > frameDelay) {
      frameTime = SDL_GetTicks();
      currentFrame = (currentFrame + 1) % 4; // Cycle through frames
    }

    // Render Pacman image
    renderTexture(pacmanTextures[currentFrame], game->renderer, pacmanRect.x,
                  pacmanRect.y, pacmanRect.w, pacmanRect.h);

    // Render Pacman logo above the start button
    renderTexture(pacmanLogo, game->renderer, logoRect.x, logoRect.y,
                  logoRect.w, logoRect.h);

    // Render start button background
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255); // Blue color
    SDL_RenderFillRect(game->renderer, &startButton);

    // Render start button border
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255); // White color
    SDL_RenderDrawRect(game->renderer, &startButton);

    // Render start button text
    printText(startButton.x + 10, startButton.y + 10, "Start", font, white,
              game->renderer);
    SDL_RenderPresent(game->renderer);
  }

  // Clean up font and textures
  TTF_CloseFont(font);
  SDL_DestroyTexture(pacmanTextures[0]);
  SDL_DestroyTexture(pacmanTextures[1]);
  SDL_DestroyTexture(pacmanTextures[2]);
  SDL_DestroyTexture(pacmanTextures[3]);
  SDL_DestroyTexture(pacmanLogo);
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
}
