#include "inc/screen.hpp"

#include <SDL2/SDL.h>
#include <cstdlib>    /* exit     */
#include <cmath>      /* cos, sin */


Screen::Screen(int w, int h)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(w*2, h*2, 0, &win, &rnd);
    SDL_RenderSetScale(rnd, 2, 2);
}

void Screen::pixel(float x, float y)
{
    SDL_FPoint aux = {x, y};
    points.push_back(aux);
}

void Screen::line(float x1, float y1, float x2, float y2)
{
    float i;
    float dx, dy;
    float length, angle;

    dx = x2 - x1;
    dy = y2 - y1;



    length = std::sqrt(dx * dx + dy * dy);
    angle  = std::atan2(dy, dx);

    for (i = 0; i < length; i++)
    {
        pixel(x1 + std::cos(angle) * i,
              y1 + std::sin(angle) * i);
    }
    
}

void Screen::show()
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(rnd);

    SDL_SetRenderDrawColor(rnd, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (auto& point : points)
    {
        SDL_RenderDrawPointF(rnd, point.x, point.y);
    }

    SDL_RenderPresent(rnd);
}

void Screen::clear()
{
    points.clear();
}

void Screen::input()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            /* TODO: Eliminar todo lo demás */
            SDL_Quit();
            exit(EXIT_SUCCESS);
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_q:
                    SDL_Quit();
                    exit(EXIT_SUCCESS);
                    break;
            }
        }
    }
}

