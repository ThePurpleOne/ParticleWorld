/*
    * Author: Jonas S.
    * Date: 02/04/2021
    ! Particle header
*/

/*
    RANDOM IDEAS
    ? https://www.youtube.com/watch?v=Z_zmZ23grXE
    ! Stats of cells
    ? speed
    ? Attraction radius
    ? Repulsion radius
*/

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <SDL2/SDL.h>

typedef struct
{
    unsigned int r;		//?radius
    double x, y;        //? Pos
    double vx, vy;		//? velocity
    double ax, ay;		//? acceleration
    double m;           //? mass
    unsigned int c;		//? color
    SDL_Renderer* ren;
} particle;

void Particle_Set(	particle* p, 
                    unsigned char r,
                    double* vect, 			//? initial pos, vel
                    double mass,
                    unsigned int c,
                    SDL_Renderer* ren);

void Particle_Draw(particle* p);

void Particle_Update(particle* p);
void Particle_AddForce(particle* pOrigin, particle* pTarget);









#endif