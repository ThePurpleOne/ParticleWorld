/*
    * Author: Jonas S.
    * Date: 02/04/2021
    ! Basic test of SDL 2.0 graphics library in C
*/
// ! DOCS USED https://wiki.libsdl.org/APIByCategory
// ! IDEA BASED ON https://www.youtube.com/watch?v=Z_zmZ23grXE


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "global.h"
#include "gfx.h"
#include "particle.h"
#include "world.h"


// ! GLOBAL VARIABLES
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

int main()
{
    // ! VARIABLES
    particle t_particles[NB_BALL];
    SDL_Event event;

    //* FPS related
    unsigned int currentTime;
    unsigned int lastTime;

    // * INITs
    {
        // ?Try to initialise SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            printf("Unable to Initialize SDL: %s", SDL_GetError());
            return 1;
        }
        
        window = SDL_CreateWindow("OSEF", 
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT, 0);

        renderer = SDL_CreateRenderer( window, 
                                -1, 
                                SDL_RENDERER_TARGETTEXTURE);

        // ?Check if Window init was successful
        if (window == NULL)
        {
            printf("Unable to Initialize the Window: %s", SDL_GetError());
            return 1;
        }

        // ?Check if renderer init was successful
        if (renderer == NULL)
        {
            printf("Unable to Initialize the Window: %s", SDL_GetError());
            return 1;
        }
    }
    // * END INITs

    // ! SETTING UP RANDOM PARTICLES
    {
        time_t t;
        srand((unsigned) time(&t)); //set random seed

        for(int i = 0; i < NB_BALL - 1; i++)
        {
            double tabVect[4] = {
                        (rand() % WINDOW_WIDTH - 400) + 400, 	//X
                        (rand() % WINDOW_HEIGHT - 400) + 400,	//Y
                        0,//(rand() % 5) + 1,						//vX
                        0//(rand() % 5) + 1,						//vY
                        };
                        
            Particle_Set(   &t_particles[i], 
                            4,//(rand() % 11) + 10,                  //random Radius
                            tabVect,
                            1,
                            MAKE_COLOR(RANDOM_COLOR, RANDOM_COLOR, RANDOM_COLOR),
                            renderer
                            );
        }

        double tabSun[4] = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0};
        Particle_Set(&t_particles[NB_BALL - 1], 20, tabSun, 100, COLOR_BLACK, renderer);
    }
    // ! END SETTING UP RANDOM PARTICLES

    while(1)
    {
        // * Handle Quit event
        {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) 
            {
                printf("\n\nProgram has been terminated after %f seconds\n", (double)event.quit.timestamp / 1000 );
                break;
            }
        }
        // * END Handle Quit event

        // TODO Make an average and add delay to get capped FPS
        // * Show fps 
        {
            currentTime = SDL_GetTicks();  //number of ms since init
            //printf("\rFPS : %f", 1000.0 / (double)(currentTime - lastTime) );
            lastTime = currentTime;
            SDL_Delay(10);
        }
        // * END Limit and Show fps


        // ! UPDATE
        worldApplyForces(t_particles);
        for(int i = 0; i < NB_BALL; i++)
        {
            Particle_Update(&t_particles[i]);
        }
        // ! END UPDATE

        // ! DRAW
        GFX_ClearScreen(renderer, BACKGROUND_COLOR);
        for(int i = 0; i < NB_BALL; i++)
        {
            Particle_Draw(&t_particles[i]);
        }
        // ! END DRAW

        // ! Render renderer to the window
        SDL_RenderPresent(renderer);

        //break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
