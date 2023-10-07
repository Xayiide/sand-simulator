#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

#include "inc/screen.hpp"

#define ANCHO 1280
#define ALTO  720

int main()
{
    int    i;
    Screen screen(ANCHO, ALTO);

    for (i = 0; i < 100; i++)
    {
        screen.pixel(rand()%ANCHO, rand()%ALTO);
    }

    while (true)
    {
        screen.show();
        screen.input();
    }

    return 0;
}
