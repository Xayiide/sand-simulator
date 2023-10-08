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

        std::vector<SDL_FPoint> points;

    public:
        Screen(int w, int h);
        void pixel(float x, float y);
        void line(float x1, float y1, float x2, float y2);
        void show(void);
        void clear(void);
        void input(void);
};



#endif
