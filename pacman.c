#include "pacman.h"
#include "gestionGraphique.h"
#include "include/SDL2/SDL.h"
#include "settings.h"
#include <stdio.h>
TPacman initPacman(int x, int y, const char *texturePath,
                   SDL_Renderer *renderer) {
  TPacman pacman;
  pacman.x = x;
  pacman.y = y;
  pacman.texture = loadTexture(texturePath, renderer);
  return pacman;
}
void renderPacman(const TPacman *pacman, SDL_Renderer *renderer) {
  if (pacman->texture) {
    renderTexture(pacman->texture, renderer, pacman->x, pacman->y,
                  TILE_SIZE, TILE_SIZE);
    // printf("Rendering Pacman at position (%d, %d)\n", pacman->x, pacman->y);
  } else {
    printf("Pacman texture is NULL\n");
  }
}
// Implement other functions as needed