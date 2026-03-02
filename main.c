#include <SDL3/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 800

#define WHITE 0xffffffff
#define BLACK 0x00000000
#define BRANCH_COLOR 0xff6bf8ff

#define GREEN 0x2deb2dff

#define COLORS_NUM 13

#define OR1 0xe0983aff
#define OR2 0xe0ae3aff
#define YE1 0xe0cd3aff
#define YE2 0xd8e03aff
#define LI1 0xabe03aff
#define LI2 0x8de03aff
#define GR1 0x69e03fff
#define GR2 0x3ae042ff

#define BRANCH_ANGLE 30
#define INITIAL_LENGTH 220

#define RGBA(c)             \
    ((c >> 24) & 0xFF),     \
        ((c >> 16) & 0xFF), \
        ((c >> 8) & 0xFF),  \
        (c & 0xFF)


int colorID = 0;

void DrawBranch(SDL_Renderer *renderer, float x, float y, float angle, float length) {

    if (length <= 1) {
        return;
    }
    float rad = angle * (M_PI / 180.0f);
    float end_x = x + sinf(rad) * length;
    float end_y = y - cosf(rad) * length;
    SDL_RenderLine(renderer, x, y, end_x, end_y);
    
    float new_x = end_x;
    float new_y = end_y;
    float new_length = length * 0.7;
    float left_angle = angle - BRANCH_ANGLE;
    float right_angle = angle + BRANCH_ANGLE;

    DrawBranch(renderer, new_x, new_y, left_angle, new_length);
    DrawBranch(renderer, new_x, new_y, right_angle, new_length);
}


int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Fractal Tree", WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    Uint32 colors[COLORS_NUM] = {
        OR1,
        OR2,
        YE1,
        YE2,
        LI1,
        LI2,
        GR1,
        GR2,
        GR1,
        LI2,
        LI1,
        YE2,
        YE1,
    };

    int running = 1;  // 1 = yes, 0 = no
    while (running) {

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_EVENT_QUIT:
                    running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, RGBA(0x00000000));
        SDL_FRect rect = {0, 0, WIDTH, HEIGHT};
        SDL_RenderFillRect(renderer, &rect);
        
        SDL_SetRenderDrawColor(renderer, RGBA(colors[colorID % COLORS_NUM]));
        colorID++;
        DrawBranch(renderer, WIDTH/2, HEIGHT - 50, 0, INITIAL_LENGTH);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
}
    return 0;
}
