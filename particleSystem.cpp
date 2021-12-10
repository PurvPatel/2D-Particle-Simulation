#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits>
#include "mathLib2D.h"
#include "particle2D.h"


// intialize number of particles
int N = 200;

//Initial window size
int windowHeight = 600;
int windowWidth = 600;

//active coords of mouse
int curX = 0;
int curY = 0;

//passive mouse coords for particle insertion
int passiveCurX = 0;
int passiveCurY = 0;

//params for particles
std::vector<particle2D> particles;

// attract and repel flags and force
bool attract = false;
bool repel = false;
float attractAndRepelForce = 5.0f;

//gravity flag and acceleration
bool gravity = false;
Vec2D gravityForce(0.0f, -0.1f);

//velocity decay for particles: velocity = velocity - decay * velocity
float decay = 0.01f;

// globals for global increase to speed and range and its bounds
float baseRange = 2500.0f;
float baseRangeMin = 100.0f;
float baseRangeMax = 100000.0f;
float baseRangeInc = 625.0f;

float baseSpeed = 2.5f;
float baseSpeedMin = 0.1f;
float baseSpeedMax = 5.0f;
float baseSpeedInc = 0.5f;

//globals for random selections (speed selection not needed since speed is determined by acceleration and size/mass of particle)
//size choices
float pointSize[5] = {3.0f, 5.0f, 7.0f, 9.0f, 11.0f};

// ranges in pixels ^ 2
float ranges[5] = {225.0f, 400.0f, 625.0f, 900.0f, 1225.0f};

//pause play state flag
bool pause = false;

void updateParticleMovements(particle2D *particle){
	if (attract)
		particle->setAcceleration(curX, curY, baseRange, true, attractAndRepelForce);
	else if (repel)
		particle->setAcceleration(curX, curY, baseRange, false, attractAndRepelForce);
	if (gravity)
		particle->updateAcceleration(gravityForce);
	particle->move(windowWidth, windowHeight, baseSpeed);
}


void display(void)
{

	if (!pause){
		glClear(GL_COLOR_BUFFER_BIT);
	
		for(auto &particle : particles){

			
			glPointSize(particle.size);

			//update particle movements
			updateParticleMovements(&particle);

			glBegin(GL_POINTS);
				glColor4fv(particle.colour.data());
				glVertex2f(particle.position.mX, particle.position.mY);
			glEnd();
		}	
		
		glutSwapBuffers();
		glFlush();
	}
	
	
}


void mouse(int btn, int state, int x, int y) {
	
	// attracting particles
	if (btn == GLUT_LEFT_BUTTON) {
		//update curY and curX
		curY = windowHeight - y;
		curX = x;

		//set attract flag
		if (state == GLUT_UP) {
			attract = false;
		}
		if (state == GLUT_DOWN) {
			attract = true;
		}
	}
	else if (btn == GLUT_RIGHT_BUTTON){
		//update curY and curX
		curY = windowHeight - y;
		curX = x;

		//set repel flag
		if (state == GLUT_UP) {
			repel = false;
		}
		if (state == GLUT_DOWN) {
			repel = true;
		}
	}

}
void addParticle(float x, float y){
	
	Point2D position(x, y);
	Vec2D direction(0, 0);

	std::vector<float> colour = {float(rand()) / RAND_MAX, float(rand()) / RAND_MAX, float(rand()) / RAND_MAX, 1.0f};

	float size = pointSize[rand() % 5];
	float range = ranges[rand() % 5];

	Vec2D acceleration(0, 0);
	Vec2D velocity(0, 0);

	particles.push_back(particle2D(position, direction, colour, size, range, acceleration, velocity, decay));
}

void resetParticles(){

	// wipe all particles
	particles.clear();

	//initialize new particles
	for(int i = 0; i < N; i++){
		addParticle(float(rand() % windowWidth), float(rand() % windowHeight));
	}
}

void deleteParticle(){
	float minDist = std::numeric_limits<float>::max();
	float dist;
	int indexSmallest = -1;

	//get current mouse coords to avoid errors caused by read/write errors due to multiple threads
	float x = float(passiveCurX);
	float y = float(passiveCurY);
	Point2D cursorPos(x, y);

	for(std::vector<particle2D>::size_type i = 0; i < particles.size(); i++)
    {
        dist = particles[i].position.fastDistanceTo(cursorPos);

		if (minDist > dist){
			minDist = dist;
			indexSmallest = i;
		}
    }

	if (indexSmallest >= 0)
		particles.erase(particles.begin() + indexSmallest);
}
void kbd(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'd': {
			deleteParticle();
			break;
		}
		case 'r': {
			resetParticles();
			break;
		}
		case 'a': {
			addParticle(float(passiveCurX), float(passiveCurY));
			break;
		}
		case ' ': {
			pause = !pause;
			break;
		}
		case 'q': case 27:{
			exit(0);
			break;
		}
		case '+': {
			baseRange = std::min(baseRangeMax, baseRange + baseRangeInc);
			break;
		}
		case '-': {
			baseRange = std::max(baseRangeMin, baseRange - baseRangeInc);
			break;
		}
		case 'g': {
			gravity = !gravity;
			break;
		}
	}

}

void directional_keys(int key, int x, int y){
	switch(key)
	{
		case GLUT_KEY_UP: {
			baseSpeed = std::min(baseSpeedMax, baseSpeed + baseSpeedInc);
			break;
		}
		case GLUT_KEY_DOWN: {
			baseSpeed = std::max(baseSpeedMin, baseSpeed - baseSpeedInc);
			break;
		}
	}
}
void motion(int x, int y) {
	//update coords for mouse
	curX = x;
	curY = windowHeight - y;
}

void passiveMotion(int x, int y){
	//get passive mouse coords, used for inserting particle
	passiveCurX = x;
	passiveCurY = windowHeight - y;
}

// Set FPS
void FPS(int val) {
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 0);
	// Rendering every 17ms
	// 1 sec = 1000, 60 FPS = 1000/60 =~17
}

void init() {

	printf("Welcome to Particle Simulation\n");
	printf("\n------------------------------------------------------------\n\n");
	printf("Adding a particle:\n");
	printf("Press \'a\' and a particle will be added at the cursor location, make sure to place the cursor inside the window.\n\n");

	printf("Deleting a particle:\n");
	printf("Press \'d\' and the particle closest to your cursor position will be deleted.\n\n");

	printf("Reset simulation:\n");
	printf("Press \'r\' to reset the entire simulation.\n\n");

	printf("Pause/Play simulation:\n");
	printf("Press space to pause/play the simulation.\n\n");

	printf("Generate an attractive force:\n");
	printf("Press/hold the left mouse button to generate an attractive force around the cursor position.\n\n");

	printf("Generate a repelling force:\n");
	printf("Press/hold the right mouse button to generate a repelling force around the cursor position.\n\n");

	printf("Increase/Decrease the attracting/repelling range: \n");
	printf("Use \'+\' to increase, or \'-\' to decrease the range of the forces.\n\n");

	printf("Increase/Decrease the speeds of particles: \n");
	printf("Use \'UP_ARROW_KEY\' to increase, or \'DOWN_ARROW_KEY\' to decrease the speeds of particles.\n\n");

	printf("Simulate Gravity:\n");
	printf("Press \'g\' to toggle gravity on and off.\n\n");
	printf("\n------------------------------------------------------------\n\n");

	printf("Extra Features: \n");
	printf("1. Improved physics: Particles have acceleration and velocity to provide more realistic movements when acted upon by forces.\n");
	printf("2. Bounded Particles: Particles will bounce off of the window borders instead of going off of them.\n");
	printf("3. Gravity Mode: Gravity can be toggled on and off.\n");
	printf("\n------------------------------------------------------------\n\n");

	printf("Helpful Tips and Notes\n");
	printf(" - Attraction and repulsion are forces so you will be able to see particles orbit around attracting forces and be bounced away from repelling forces.\n");
	printf(" - Since these are forces, their affects on particle speeds will be present a bit after the forces fade away.\n");
	printf(" - There is a artifical decay programmed into the particles to stimulate air friction to eventually slow down and stop the particles.\n");
	printf(" - You can still interact through attracting and repelling forces even when gravity is enabled.\n");
	printf(" - Particles are bounded by the window and will bounce off the edges to provide a better simulation.\n");

	// set random seed
	srand(time(0));

	//initialize particles
	for(int i = 0; i < N; i++){
		addParticle(float(rand() % windowWidth), float(rand() % windowHeight));
	}

}


//reshape function from lecture slides week 2
void reshape(int w, int h) 
{ 
	windowWidth  = w; //set global width 
	windowHeight = h; //set global height 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0, w, 0, h); 
	glMatrixMode(GL_MODELVIEW); 
	glViewport(0, 0, w, h); 
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Particles");	//creates the window

	glutKeyboardFunc(kbd);             //keyboard callbacks
	glutSpecialFunc(directional_keys);

	glutTimerFunc(17, FPS, 0);        //timer function

	glutMotionFunc(motion);               //mouse callbacks
	glutPassiveMotionFunc(passiveMotion);
	glutMouseFunc(mouse);

	glutDisplayFunc(display);	//registers "display" as the display callback function
	
	glutReshapeFunc(reshape);  //resizing window size callback

	init();                     //initialze particles
	glutMainLoop();				//starts the event loop

	return(0);					
}