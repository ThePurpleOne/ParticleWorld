/*
    * Author: Jonas S.
    * Date: 02/04/2021
    ! World code
*/

#include "global.h"
#include "particle.h"
#include "world.h"
#include "gfx.h"
#include <math.h>

void worldApplyForces(particle * tabOfP)
{
    // ! F(a/b) = G * (ma * mb) / distance Squared
    // ! We need to add all the forces applied from every other cells.
    
    //TODO Optimize
    for (int i = 0; i < NB_BALL; i++) //For Every Particle 
    {
        for (int j = 0; j < NB_BALL; j++)
        {
            if(j != i) //does not compute its own force
            {
                // ! Add force applied from jth particle to ith particle
                Particle_AddForce(&tabOfP[i], &tabOfP[j]);
            }
        }
    }
    for (int i = 0; i < NB_BALL; i++) //For Every Particle 
    {
        tabOfP[i].ax = tabOfP[i].ax / tabOfP[i].m;
        tabOfP[i].ay = tabOfP[i].ax / tabOfP[i].m;
        printf("Ball n%i   : Acceleration X :  %f   | Acceleration Y  %f   \n", i, tabOfP[i].ax, tabOfP[i].ay);
    }
    printf("\n\n\n");
}



