#include "inc/screen.hpp"

#include <SDL2/SDL.h>
#include <cstdlib>    /* exit */


Screen::Screen(int w, int h)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(w*2, h*2, 0, &win, &rnd);
    SDL_RenderSetScale(rnd, 2, 2);
}

void Screen::pixel(int x, int y)
{
    points.emplace_back(x, y);
}

void Screen::show()
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(rnd);

    SDL_SetRenderDrawColor(rnd, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (auto& point : points)
    {
        SDL_RenderDrawPoint(rnd, point.x, point.y);
    }

    SDL_RenderPresent(rnd);
}

void Screen::input()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            SDL_Quit();
            exit(EXIT_SUCCESS);
        }
    }
}

