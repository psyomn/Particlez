/*
 Makes sure that the seed is only generated
 once.
*/
void genSeed(){
	if (sw==0){
		sw = 1;
		srand(time(NULL));
	}
}

/** @param og ref to other group */
void oppositeGroup(unsigned int* og){
	switch(*og){
		case 0:	*og = 3; break;
		case 1: *og = 4; break;
		case 2: *og = 5; break;
		case 3: *og = 0; break;
		case 4: *og = 1; break;
		case 5: *og = 2; break;
		default: break;
	}
}
/** @return true if collided
@return false if not...
*/
int ballsTouching(struct Particle *o, struct Particle *oo){
	return (
		o->x == oo->x &&
		o->y == oo->y &&
		o->z == oo->z 
	);
}

/** These are the reaction rules for the particles */
void particleReaction(struct Particle *one, struct Particle *two){
	printf(" :: Particle Collision !\n");		 
	printf("    [%p]--> Particle 1: x:%d y:%d z:%d g:%d\n", one, one->x, one->y, one->z, one->group);
	printf("    [%p]--> Particle 2: x:%d y:%d z:%d g:%d\n", two, two->x, two->y, two->z, two->group);
	switch((*one).group){
		case 0:
		case 1: // 0 + 1 = 2
			if ( (*two).group != (*one).group && (*two).group == 1 ){
				(*one).group = 2;
				(*two).group = 3;
				printf("     --> Reaction #1\n");
			}
			break;
		case 2:
		case 3: // 2 + 3 = 4
			if ( (*two).group != (*one).group && ((*two).group==2 || (*two).group==3 )){
				(*one).group = 4;
				(*two).group = 5;
				printf("     --> Reaction #2\n");
			}
			break;
		case 4: // 4 + 4 = 7
		case 5:
			if ( (*two).group == 4 || (*two).group == 5 ){
				(*one).group = 7;
				(*two).group = 7;
				printf("     --> Reaction #3\n");
			}
			break;
		default:
			printf("  :: No reaction possible!");
	}
}

/** Function that takes care of the simulation steps*/
void simulationStep(struct Particle *pp){
	switch((*pp).group){
		case 0: (*pp).x += 1; break;
		case 1: (*pp).y += 1; break;
		case 2: (*pp).z += 1; break;
		case 3: (*pp).x -= 1;	break;
		case 4:	(*pp).y -= 1;	break;
		case 5:	(*pp).z -= 1; break;
		default:
			switch(rand()%6){
				case 0: (*pp).x += 1; break;
				case 1: (*pp).y += 1; break;
				case 2: (*pp).z += 1; break;
				case 3: (*pp).x -= 1;	break;
				case 4:	(*pp).y -= 1;	break;
				case 5:	(*pp).z -= 1; break;
			}
	}
}

/** All the rendering functionality is taken care of here*/
void display(void){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSolidSphere (1.0, 20, 16);
  glFlush ();
}

