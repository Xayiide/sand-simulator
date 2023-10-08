#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

#include "inc/screen.hpp"
#include "inc/vec3.hpp"

#define ANCHO 640
#define ALTO  480

struct arista
{
    int a, b;
};

int main()
{
    Screen screen(ANCHO, ALTO);
    Vec3   c = {0, 0, 0}; /* centroide */
    
    std::vector<Vec3> puntos = {
        Vec3(100, 100, 100),
        Vec3(200, 100, 100),
        Vec3(200, 200, 100),
        Vec3(100, 200, 100),

        Vec3(100, 100, 200),
        Vec3(200, 100, 200),
        Vec3(200, 200, 200),
        Vec3(100, 200, 200)
    };

    std::vector<arista> aristas
    {
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},

        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},

        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4}
    };

    /* Calcular centroide */
    for (auto &p : puntos)
    {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }
    c.x /= puntos.size();
    c.y /= puntos.size();
    c.z /= puntos.size();


    while (true)
    {
        for (auto &p : puntos)
        {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;
            p.rotate(0.002, 0.001, 0.004);
            p.x += c.x;
            p.y += c.y;
            p.z += c.z;
            screen.pixel(p.x, p.y);
        }

        for (auto &ar : aristas)
        {
            screen.line(puntos[ar.a].x,
                        puntos[ar.a].y,
                        puntos[ar.b].x,
                        puntos[ar.b].y);
        }

        screen.show();
        screen.clear();

        screen.input();
        SDL_Delay(30);
    }

    return 0;
}
