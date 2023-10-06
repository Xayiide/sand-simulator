#include <iostream> /* cerr                  */
#include <cstdlib>  /* exit                  */
#include <chrono>   /* high_resolution_clock */

#include <SDL2/SDL.h>

#define ANCHO 1280
#define ALTO  720

SDL_Renderer *rnd      = nullptr;
SDL_Texture  *red_txt  = nullptr;
SDL_Texture  *blue_txt = nullptr;
int           color    = 0;

static void switch_color()
{
    if (color == 1) /* Azul. Cambiar a rojo */
    {
        SDL_RenderCopy(rnd, red_txt, nullptr, nullptr);
        SDL_RenderPresent(rnd);
        color = 0;
    }
    else if (color == 0) /* Rojo. Cambiar a azul */
    {
        SDL_RenderCopy(rnd, blue_txt, nullptr, nullptr);
        SDL_RenderPresent(rnd);
        color = 1;
    }
}


int main()
{
    std::chrono::duration<double> diff;
    std::chrono::duration<double> max = std::chrono::seconds(2);
    SDL_Event   e;
    SDL_Window *win = nullptr;
    bool        run = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        std::cerr << "Error en la inicialización de SDL.\n";
        exit(EXIT_FAILURE);
    }

    win = SDL_CreateWindow("Simulador de arena",
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           ANCHO, ALTO, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        std::cerr << "Error en la creación de la ventana.\n";
        exit(EXIT_FAILURE);
    }

    rnd = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (rnd == NULL)
    {
        std::cerr << "Error en la creación del render.\n";
        exit(EXIT_FAILURE);
    }

    SDL_RenderSetScale(rnd, 1, 1);

    red_txt  = SDL_CreateTexture(rnd, SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, ANCHO, ALTO);
    blue_txt = SDL_CreateTexture(rnd, SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, ANCHO, ALTO);

    SDL_SetRenderTarget(rnd, red_txt);
    SDL_SetRenderDrawColor(rnd, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(rnd);

    SDL_SetRenderTarget(rnd, blue_txt);
    SDL_SetRenderDrawColor(rnd, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(rnd);

    SDL_SetRenderTarget(rnd, nullptr);

    auto t1 = std::chrono::high_resolution_clock::now();

    while (run)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        run = false;
                        break;
                    case SDLK_SPACE:
                        switch_color();
                        break;
                }
            }

        }
        auto t2 = std::chrono::high_resolution_clock::now();
        diff = (t2 - t1);
        if (diff > max)
        {
            switch_color();
            t1 = t2; /* Hay desviación local pero bueno. TODO: delay until */
        }

    }

    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
