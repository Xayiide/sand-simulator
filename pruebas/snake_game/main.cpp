#include <iostream>
#include <cstdlib>
#include <vector>     /* vector   */
#include <deque>      /* deque    */
#include <algorithm>  /* for_each */

#include <SDL2/SDL.h>

#define ANCHO 1080
#define ALTO  720

enum Direction
{
    DOWN,
    LEFT,
    RIGHT,
    UP
};

int main()
{
    SDL_Window   *win;
    SDL_Renderer *rnd;
    SDL_Event     e;
    bool          running = true;
    int           i, dir  = 0;
    int           size    = 1; /* Tamaño de la serpiente */
    SDL_Rect      head    = {500, 500, 10, 10};
    std::deque<SDL_Rect> body; /* El cuerpo de la serpiente */
    std::vector<SDL_Rect> apples; /* Las manzanas */

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error en la inicialización de SDL\n";
        exit(EXIT_FAILURE);
    }

    win = SDL_CreateWindow("Snake",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            ANCHO, ALTO, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        std::cerr << "Error creando la ventana.\n";
        exit(EXIT_FAILURE);
    }

    rnd = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (rnd == NULL)
    {
        std::cerr << "Error creando el renderizador.\n";
        exit(EXIT_FAILURE);
    }

    /* Crea 100 manzanas */
    for (i = 0; i < 100; i++)
    {
        int x = (int) rand() % 100 * 10;
        int y = (int) rand() % 100 * 10;
        SDL_Rect aux = {x, y, 10, 10};
        apples.emplace_back(aux);
    }

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_DOWN)
                    dir = DOWN;
                else if (e.key.keysym.sym == SDLK_UP)
                    dir = UP;
                else if (e.key.keysym.sym == SDLK_RIGHT)
                    dir = RIGHT;
                else if (e.key.keysym.sym == SDLK_LEFT)
                    dir = LEFT;
                else if (e.key.keysym.sym == SDLK_q)
                    running = false;
            }
        }

        switch (dir)
        {
            case DOWN:
                head.y += 10;
                break;
            case UP:
                head.y -= 10;
                break;
            case LEFT:
                head.x -= 10;
                break;
            case RIGHT:
                head.x += 10;
                break;
        }

        /* Detectar colisiones con las manzanas */
        std::for_each(apples.begin(), apples.end(), [&](auto &apple) {
            if (head.x == apple.x && head.y == apple.y)
            {
                size += 10;
                apple.x = -10;
                apple.y = -10;
            }
        });

        /* Detectar colisiones con la propia serpiente */
        std::for_each(body.begin(), body.end(), [&](auto &segment) {
            if (head.x == segment.x && head.y == segment.y)
            {
                size = 1;
            }
        });

        /* Añade nueva cabeza a la serpiente */
        body.push_front(head);

        while (body.size() > size)
            body.pop_back();

        /* Limpia la pantalla */
        SDL_SetRenderDrawColor(rnd, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rnd);

        /* Dibuja la serpiente */
        SDL_SetRenderDrawColor(rnd, 255, 255, 255, SDL_ALPHA_OPAQUE);
        std::for_each(body.begin(), body.end(), [&](auto &segment) {
            SDL_RenderFillRect(rnd, &segment);
        });

        /* Dibuja las manzanas */
        SDL_SetRenderDrawColor(rnd, 255, 0, 0, SDL_ALPHA_OPAQUE);
        std::for_each(apples.begin(), apples.end(), [&](auto &apple) {
            SDL_RenderFillRect(rnd, &apple);
        });


        SDL_RenderPresent(rnd);
        SDL_Delay(25);

    }
}
