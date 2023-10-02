#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "[sdl]: Error en la inicialización de SDL.\n");
        exit(EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "[sdl]: Error en la inicialización de IMG.\n");
        exit(EXIT_FAILURE);
    }

    /* Creamos la ventana */
    SDL_Window *win = SDL_CreateWindow("Barra de salud",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            800, 600,
            SDL_WINDOW_SHOWN);
    if (win == NULL) {
        fprintf(stderr, "[sdl]: Error en la creación de la ventana.\n");
        exit(EXIT_FAILURE);
    }

    /* Necesitamos un renderizador */
    SDL_Renderer *rnd = SDL_CreateRenderer(win,
            -1,
            SDL_RENDERER_ACCELERATED);
    if (rnd == NULL) {
        fprintf(stderr, "[sdl]: Error creando el renderizador.\n");
        exit(EXIT_FAILURE);
    }

    /* Ahora necesitamos la imagen */
    SDL_Surface *barra = IMG_Load("../img/barrasalud.png");
    if (barra == NULL) {
        fprintf(stderr, "[sdl] Error cargando la imagen.\n");
        exit(EXIT_FAILURE);
    }

    /* La Surface es un array de píxeles guardados en RAM. Se muestran
     * haciendo uso de un renderizador, que en este caso tiene la
     * instrucción de utilizar aceleración por HW.
     * Para que sea la GPU la que represente la imagen, tenemos que
     * crear una textura. Se asocia con el renderizador y con la
     * Surface que queremos convertir en textura */

    SDL_Texture *text_barra = SDL_CreateTextureFromSurface(rnd, barra);
    if (text_barra == NULL) {
        fprintf(stderr, "[sdl]: Error creando textura.\n");
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(barra);

    /* Rectángulo de la barra de vida */
    SDL_Rect rect{100, 100, 200, 22}; /* x, y, ancho, alto */

    int x = 0; /* posición del ratón */

    /* Para que el programa siga corriendo indefinidamente, hacemos un
     * bucle infinito */
    while (1) {
        SDL_Event e;
        if (SDL_WaitEvent(&e)) { /* SDL_PollEvent tb existe */
            if (e.type == SDL_QUIT) {
                break;
            }
            if (e.type == SDL_MOUSEMOTION) {
                x = e.motion.x;

                if (x < 102)
                    x = 102;

                if (x > 298)
                    x = 298;
            }
        }
        SDL_Rect rect2{102, 102, (x - 102), 18};

        SDL_SetRenderDrawColor(rnd, 255, 255, 255, 255);
        SDL_RenderClear(rnd);

        SDL_RenderCopy(rnd, text_barra, NULL, &rect);

        SDL_SetRenderDrawColor(rnd, 255, 0, 0, 255);
        SDL_RenderFillRect(rnd, &rect2);

        SDL_RenderPresent(rnd);
    }

    SDL_DestroyTexture(text_barra);
    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
