/*
    * Author: Jonas S.
    * Date: 02/04/2021
    * Description: Cell declaration and behaviour
    ! Particle code
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "gfx.h"
#include "global.h"

void Particle_Set(	particle* p, 
                    unsigned char r,
                    double* vect, 			//? initial pos, vel
                    double mass,
                    unsigned int c,
                    SDL_Renderer* ren)
{
    p->r = r;
    p->x = vect[0];
    p->y = vect[1];
    p->vx = vect[2];
    p->vy = vect[3];
    p->ax = p->ay = 0;
    p->m = mass;
    p->c = c;
    p->ren = ren;
}

void Particle_Draw(particle* p)
{
    GFX_DrawFillCircle(p->ren, p->x, p->y, p->r, p->c, 255);
    //GFX_DrawPixel(p->ren, p->x, p->y, p->c, 255);
}


// ? Move according to vel
void Particle_Update(particle* p)
{
    //Add acceleration to the velocity
    p->vx += p->ax;
    p->vy += p->ay;

    p->x += p->vx;
    p->y += p->vy;

   // printf("\rVel X =  %i   || Vel Y =  %i  ", p->vx, p->vy);
    // // ! WALLS COLLISIONS
    // {
    //     if(p->x + p->vx + p->r > WINDOW_WIDTH ) // ! X AXIS RIGHT
    //     {
    //         p->x = WINDOW_WIDTH - p->r;
    //         p->vx *= -1;
    //     }
    //     else if(p->x + p->vx < p->r ) // ! X AXIS LEFT
    //     {
    //         p->x = p->r + 1;
    //         p->vx *= -1;
    //     }
    //     else
    //     {
    //         p->x += p->vx;
    //     }

    //     if(p->y + p->vy + p->r> WINDOW_HEIGHT ) // ! Y AXIS BOT
    //     {
    //         p->y = WINDOW_HEIGHT - p->r;
    //         p->vy *= -1;
    //     } 
    //     else if(p->y + p->vy < p->r ) // ! Y AXIS TOP
    //     {
    //         p->y = p->r + 1;
    //         p->vy *= -1;
    //     }
    //     else
    //     {
    //         p->y += p->vy;
    //     }
    // }

    //reset acceleretion
    p->ax = p->ay = 0;
}

// ? Apply force from the origin to the target
// ! F = m * a
// ! lets say mass = 1 so F = a
// TODO - Use vectors
void Particle_AddForce(particle * pOrigin, particle * pTarget)
{
    double G = 6.27;
    //double mass = 1;
    double distance, ResultantMagnitude, factor,  forceX, forceY;
    
    // ? Get the scaling factor to varry according to distance and mass
    distance = sqrt( fabs(pOrigin->x - pTarget->x) * fabs(pOrigin->y - pTarget->y) );
    factor = G * (pOrigin->m * pTarget->m) / (distance * distance * distance);

    printf("Origin X :   %f\n", pOrigin->x );
    printf("Origin Y :   %f\n", pOrigin->y);
    printf("target X :   %f\n", pTarget->x );
    printf("target Y :   %f\n", pTarget->y);
    printf("Distance :   %f\n", distance);
    printf("factor :   %f\n", factor);

    // ? Get the Direction of the force to apply
    forceX = ( ( pOrigin->x ) - ( pTarget->x ) );
    forceY = ( ( pOrigin->y ) - ( pTarget->y ) );

    printf("ForceX before mag :   %f\n", forceX);
    printf("ForceY before mag :   %f\n", forceY);

    // ? Set the Magnitude of the force as factor
    ResultantMagnitude = sqrt( (forceX * forceX) + (forceY * forceY ) ); // ! Used to set magnitude
    forceX = forceX / ResultantMagnitude * factor;
    forceY = forceY / ResultantMagnitude * factor;

    printf("ResultantMagnitude :   %f\n", ResultantMagnitude);
    printf("ForceX :   %f\n", forceX);
    printf("ForceY :   %f\n\n", forceY);


    // ! Add the force / acceleration to the target
    pTarget->ax += forceX;
    pTarget->ay += forceY;
}