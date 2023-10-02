#include <iostream>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "[sdl]: Error en la inicialización de SDL.\n");
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "[sdl]: Error en la inicialización de TTF.\n");
        exit(EXIT_FAILURE);
    }

    SDL_Window   *win = NULL;
    SDL_Renderer *rnd = NULL;

    if (SDL_CreateWindowAndRenderer(400, 300, 0, &win, &rnd) < 0) {
        fprintf(stderr, "[sdl]: Error creando ventana y render.\n");
        exit(EXIT_FAILURE);
    }

    std::wstring txt = L"申し訳ございませんがたくさんあります。\n忘れている世界によって忘れている世界。\n汚れのない心の永遠の日差し！\nそれぞれの祈りが受け入れられ、それぞれが辞任を望む";

    /* Cargamos la fuente */
    TTF_Font *kosugi = TTF_OpenFont("KosugiMaru-Regular.ttf", 16);
    if (kosugi == NULL) {
        fprintf(stderr, "[sdl]: Error abriendo fuente.\n");
        exit(EXIT_FAILURE);
    }
    /* Para poder renderizar los fin de línea \n */
    /* Blended queda mejor con los Kanji. También están Shaded o Solid,
     * que dan mejor velocidad de renderizado */
    SDL_Surface *sur = TTF_RenderUNICODE_Blended_Wrapped(kosugi, 
            (const Uint16*) txt.c_str(),
            SDL_Color{ 255, 255, 255, 255 },
            300);
    SDL_Rect     rect{50, 100, sur->w, sur->h};
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rnd, sur);
    SDL_FreeSurface(sur);

    SDL_Event ev;
    bool done = false;

    while (!done) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_KEYDOWN) {
                if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    done = 1;
                }
            }
        }
        SDL_RenderClear(rnd);
        SDL_RenderCopy(rnd, tex, NULL, &rect);
        SDL_RenderPresent(rnd);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(win);
    TTF_CloseFont(kosugi);

    SDL_Quit();

    return 0;
}
