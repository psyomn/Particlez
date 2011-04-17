/* @author Simon Symeonidis */
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>

// This is here to guard the random seed
int sw = 0;
int PRINTING = 1;

#include "macros.h"
#include "structs.h"
#include "func.h"
#include "glfunc.h"

void render(void);

// All the wanted particles
struct Particle part[PARTICLES];	
unsigned int stats_groups_before[GROUP+5];
unsigned int stats_groups_after[GROUP+5];
unsigned int special_groups;

int main(int argc, char** argv){
	int i;

	genSeed(); // Generate the seed

	printf("Begin Simluation\n");
	printf("Num of particles: %d\n", PARTICLES);
	printf("Sizeof struct   : %d\n", sizeof(part));
	printf("Room Sizes: \n");
	printf(" ::Max x %d\n", MAXX);
	printf(" ::Max y %d\n", MAXY);
	printf(" ::Max z %d\n", MAXZ);
	printf(" ::Min x %d\n", MINX);
	printf(" ::Min y %d\n", MINY);
	printf(" ::Min z %d\n", MINZ);

	// Random Generation
	printf("Gene");
	for(i=0; i<PARTICLES; ++i){
		part[i].x = rand()%MAXX;
		part[i].y = rand()%MAXY;
		part[i].z = rand()%MAXZ;
		part[i].group = rand()%GROUP;
		++stats_groups_before[part[i].group]; // count the groups
	}
	printf("rated!\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(40, 40);
	glutCreateWindow("Particlez");
	setup();	
	glutDisplayFunc(render);	
	//glutTimerFunc(33, timer, 1);
	glutMainLoop();

	return 0;
}

void render(){
	int i; // loop
	int j; // loop
	int k; // loop

	for(i=0; i<GROUP+5; ++i){
		stats_groups_before[i] = 0;
		stats_groups_after[i] = 0;
	}

	
	if (PRINTING == 1){
		// Show what we got
		printf("Particles before : \n");
		for(i=0; i<PARTICLES; ++i){
			printf("  :: [%p] [p#:%4d] [x : %3d] [y : %3d] [z : %3d] [g : %2d]\n", &part[i], i, part[i].x, part[i].y, part[i].z, part[i].group);
		}
	}

	// Simulation Cycles
	for(i=0; i<CYCLES; ++i){
		// Each particle
		for (j=0; j<PARTICLES; ++j){
			//Check with the rest of particles for collisions
			for (k=j+1; k<PARTICLES; ++k){
				// Reaction / Particle Collision
				if (ballsTouching(&part[j], &part[k])) { 
					particleReaction(&part[j], &part[k]);
					printf("Particle Collision!\n");
				}
			}
			
			// Wall Collision
			if(	part[j].x > MAXX || part[j].y > MAXY || part[j].z > MAXZ ||
				  part[j].x < MINX || part[j].y < MINY || part[j].z < MINZ ){
				oppositeGroup(&part[j].group);	
			}
			simulationStep(&part[j]);
			
		} 

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
			for (i=0; i<PARTICLES; ++i){
				switch(part[i].group){
					case 0:	 glColor3f(1.0f, 0.0f, 0.0f); break;
					case 1:  glColor3f(0.0f, 1.0f, 0.0f); break;
					case 2:  glColor3f(0.0f, 0.0f, 1.0f); break;
					case 3:  glColor3f(0.5f, 0.5f, 0.0f); break;
					case 4:  glColor3f(0.0f, 0.5f, 0.5f); break;
					case 5:  glColor3f(0.5f, 0.0f, 0.5f); break;
					default: glColor3f(1.0f, 1.0f, 1.0f); break; 
				}
				glVertex3f((float) part[i].x/MAXX - 0.5  ,(float) part[i].y/MAXY - 0.5, (float)part[i].z/MAXZ - 0.5);
			}
		glEnd();
		glutSwapBuffers();

	} // End simulation

	if (PRINTING == 1){
		printf("Particles After\n");
		for(i=0; i<PARTICLES; ++i){
			printf("  :: [%p] [p#:%4d] [x : %3d] [y : %3d] [z : %3d] [g : %2d]\n", &part[i], i, part[i].x, part[i].y, part[i].z, part[i].group);
			++stats_groups_after[part[i].group];
		}
		k=0;
		printf("Total num of particle groups before:\n");
		for(i=0; i<GROUP+5; ++i){
			printf("  :: Group [%d] = %d\n", i, stats_groups_before[i]);
			k += stats_groups_before[i];
		}
		printf("Total Particles : %d\n", k);
		k=0;
		printf("Total num of particle groups before:\n");
		for(i=0; i<GROUP+5; ++i){
			printf("  :: Group [%d] = %d\n", i, stats_groups_after[i]);
			k += stats_groups_after[i];
		}
		printf("Total Particles : %d\n", k);
	}

}

	
