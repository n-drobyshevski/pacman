#include "pacman.h"
#include "game.h"
#include "gestionGraphique.h"
#include "include/SDL2/SDL.h"
#include "settings.h"
#include <stdio.h>
#include <stdlib.h>

TPacman initPacman(int x, int y, int vel, char dir, SDL_Renderer *renderer) {
  TPacman pacman;
  const char *texturePath = "src/pakuman/pakuman_0.bmp";
  pacman.x = x;
  pacman.y = y;
  pacman.vel = vel;
  pacman.dir = dir;
  pacman.texture = loadTexture(texturePath, renderer);
  return pacman;
}

void renderPacman(const TPacman *pacman, SDL_Renderer *renderer) {
  if (pacman->texture) {
    renderTexture(pacman->texture, renderer, pacman->x, pacman->y, TILE_SIZE,
                  TILE_SIZE);
  } else {
    printf("Pacman texture is NULL\n");
  }
}

void movePacman(TPacman *pacman, char old_dir, int map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX]) {
  // Initialize newX and newY with current position
  int newX = pacman->x;
  int newY = pacman->y;

  switch (pacman->dir) {
  case 'w': // Up
    newY = newY - pacman->vel;
    break;
  case 's': // Down
    newY = newY + pacman->vel;
    break;
  case 'a': // Left
    newX = newX - pacman->vel;
    break;
  case 'd': // Right
    newX = newX + pacman->vel;
    break;
  default:
    break;
  }

  // Sprite size is 16x16
  // Check collision for all 4 corners
  int tileTopLeft = getTileType(map, newX, newY);
  int tileTopRight = getTileType(map, newX + 15, newY);
  int tileBottomLeft = getTileType(map, newX, newY + 15);
  int tileBottomRight = getTileType(map, newX + 15, newY + 15);

  // Debug logs
  // printf("TileTopLeft = %d at (%d, %d)\n", tileTopLeft, newX, newY);
  // printf("TileTopRight = %d at (%d, %d)\n", tileTopRight, newX + 15, newY);
  // printf("TileBottomLeft = %d at (%d, %d)\n", tileBottomLeft, newX, newY + 15);
  // printf("TileBottomRight = %d at (%d, %d)\n", tileBottomRight, newX + 15,newY + 15);

  if (tileTopLeft != 1 && tileTopRight != 1 && tileBottomLeft != 1 &&
      tileBottomRight != 1) {
    pacman->x = newX;
    pacman->y = newY;
  } else {
    if (AUTO_MODE) {
      // Collision detected, change direction randomly
      char directions[] = {'w', 'a', 's', 'd'};
      int idx = rand() % 4;
      pacman->dir = directions[idx];
      // printf("Collision detected. Changing direction randomly to %c\n", pacman->dir);
    }else{
      pacman->dir = old_dir;
      }
  }
  // printf("New Pacman position: (%d, %d)\n", newX, newY);
}

void updatePacmanTexture(TPacman *pacman,SDL_Renderer *renderer) {
  switch (pacman->dir) {
  case 'w': // Up
    pacman->texture = loadTexture("src/pakuman/pakuman_1.bmp", renderer);
    break;
  case 's': // Down
    pacman->texture = loadTexture("src/pakuman/pakuman_3.bmp", renderer);
    break;
  case 'a': // Left
    pacman->texture = loadTexture("src/pakuman/pakuman_2.bmp", renderer);
    break;
  case 'd': // Right
    pacman->texture = loadTexture("src/pakuman/pakuman_0.bmp", renderer);
    break;
  default:
    break;
  }
}