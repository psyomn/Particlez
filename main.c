/* @author Simon Symeonidis
Particle Simulator for COMP 426
*/
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>

// This is here to guard the random seed
int sw = 0;
int PRINTING = 0;

#include "macros.h"
#include "structs.h"
#include "func.h"

int main(){
	struct Particle part[PARTICLES];	
	int i; // loop
	int j; // loop
	int k; // loop

	genSeed(); // Generate the seed

	printf("Begin Simluation\n");
	printf("Num of particles: %d\n", PARTICLES);
	printf("Room Sizes: \n");
	printf(" ::Max x %d\n", MAXX);
	printf(" ::Max y %d\n", MAXY);
	printf(" ::Max z %d\n", MAXZ);
	printf(" ::Min x %d\n", MINX);
	printf(" ::Min y %d\n", MINY);
	printf(" ::Min z %d\n", MINZ);

	// Random Generation
	for(i=0; i<PARTICLES; ++i){
		part[i].x = rand()%MAXX;
		part[i].y = rand()%MAXY;
		part[i].z = rand()%MAXZ;
		part[i].group = rand()%GROUP;
	}

	if (PRINTING == 1){
		// Show what we got
		printf("Particles before : \n");
		for(i=0; i<PARTICLES; ++i){
			printf("  :: %d x : %d y : %d z : %d g : %d\n", i, part[i].x, part[i].y, part[i].z, part[i].group);
		}
	}

	// Simulation Cycles
	for(i=0; i<CYCLES; ++i){
		// Each particle
		for (j=0; j<PARTICLES; ++j){
			//Check with the rest of particles for collisions
			for (k=j+1; k<PARTICLES; ++k){
				// Check for collision
				//  yes -> switch group
				//	no  -> proceed with needed path
				if ( part[j].x == part[k].x && part[j].y == part[k].y && part[j].z == part[k].z) { 
					printf("Collision !\n");		 
					particleReaction(&part[j], &part[k]);
				}
				if(	part[j].x > MAXX || part[j].y > MAXY || part[j].z > MAXZ ||
					  part[j].x < MINX || part[j].y < MINY || part[j].z < MINZ ){
					oppositeGroup(&part[j].group);	
				}

				simulationStep(&part[j]);

			}
		} 
	} // End simulation

	if (PRINTING == 1){
		printf("Particles After\n");
		for(i=0; i<PARTICLES; ++i){
			printf("  :: %d x : %d y : %d z : %d g : %d\n", i, part[i].x, part[i].y, part[i].z, part[i].group);
		}
	}
}


