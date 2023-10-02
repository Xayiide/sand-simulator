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
    SDL_Window *win = SDL_CreateWindow("Prueba", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (win == NULL) {
        fprintf(stderr, "[sdl]: Error en la creación de la ventana.\n");
        exit(EXIT_FAILURE);
    }

    /* Necesitamos un renderizador */
    SDL_Renderer *rnd = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (rnd == NULL) {
        fprintf(stderr, "[sdl]: Error creando el renderizador.\n");
        exit(EXIT_FAILURE);
    }

    /* Ahora necesitamos la imagen */
    SDL_Surface *lechuga = IMG_Load("../img/lettuce.png");
    if (lechuga == NULL) {
        fprintf(stderr, "[sdl] Error cargando la imagen.\n");
        exit(EXIT_FAILURE);
    }

    /* La Surface es un array de píxeles guardados en RAM. Se muestran
     * haciendo uso de un renderizador, que en este caso tiene la
     * instrucción de utilizar aceleración por HW.
     * Para que sea la GPU la que represente la imagen, tenemos que
     * crear una textura. Se asocia con el renderizador y con la
     * Surface que queremos convertir en textura */

    SDL_Texture *text_lechuga = SDL_CreateTextureFromSurface(rnd, lechuga);
    if (text_lechuga == NULL) {
        fprintf(stderr, "[sdl]: Error creando textura.\n");
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(lechuga);

    /* Para que el programa siga corriendo indefinidamente, hacemos un
     * bucle infinito */
    while (1) {
        SDL_Event e;
        if (SDL_WaitEvent(&e)) { /* SDL_PollEvent tb existe */
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        SDL_RenderClear(rnd);
        SDL_RenderCopy(rnd, text_lechuga, NULL, NULL);
        SDL_RenderPresent(rnd);
    }

    SDL_DestroyTexture(text_lechuga);
    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
