#include "gui.h"

display_t *display_new() {
    display_t *display = (display_t*)malloc(sizeof(display_t));
    SDL_Init(SDL_INIT_VIDEO);
    display->window = SDL_CreateWindow("RamenBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 144, SDL_WINDOW_OPENGL);
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    return display;
}

void display_draw_point(display_t *display, int row, int col, int r, int g, int b) {
    SDL_SetRenderDrawColor(display->renderer, r, g, b, 0xFF);
    SDL_RenderDrawPoint(display->renderer, col, row);
}

void display_render(display_t *display) {
    SDL_RenderPresent(display->renderer);
}

void display_destroy(display_t* display) {
    if (display != NULL) {
        SDL_DestroyWindow(display->window);
        SDL_DestroyRenderer(display->renderer);
        free(display);
        SDL_Quit();
    }
}

// int main() {
//     // display_t* display = (display_t*)malloc(sizeof(display_t));
//     display_t *display = display_new();
//     // if (display == NULL) {
//     //     printf("Failed to initialize window!");
//     //     return 1;
//     // }
//     // window_init(&display);

//     SDL_Delay(5000);
//     display_destroy(display);
//     // window_destroy(&display);
//     SDL_Quit();
// }