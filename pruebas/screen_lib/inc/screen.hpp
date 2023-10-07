#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <SDL2/SDL.h>
#include <vector>


class Screen
{
    private:
        SDL_Event     e;
        SDL_Window   *win;
        SDL_Renderer *rnd;

        std::vector<SDL_Point> points;

    public:
        Screen(int w, int h);
        void pixel(int x, int y);
        void show(void);
        void input(void);
};



#endif
