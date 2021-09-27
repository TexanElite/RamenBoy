#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>

typedef struct display_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *surface;
    unsigned int frames;
} display_t;

display_t *display_new();
void display_destroy(display_t* display);
void display_draw_point(display_t *display, int row, int col, int r, int g, int b);
void display_render(display_t *display);

#endif