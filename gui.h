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

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

display_t *display_new();
void display_destroy(display_t* display);

#endif