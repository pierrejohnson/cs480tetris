#include <iostream>		
#include <cstdlib>		
#include <ctime>		
#include "GL/glut.h"
#include "GL/glu.h"
#include "Tetris.h"
//#include <GLUT/glut.h>
//#include <OpenGL/glu.h>
Tetris game;
bool pause = false;

//Timer function
//Calls the game update function
void update(int value) {
	if(!pause){
	//game.test();
	game.update();
	glutPostRedisplay();
	}
	//every 1000 ms (1s) the "update(1)" fn is called
	glutTimerFunc(1000, update, 1);
}

/*Initialization function
 * Initialize material property, light source, 
 * lighting model, and depth buffer.
 */
void init(void) {

	game.Initialize();
	//every 1 seconds calls the update function
	glutTimerFunc(1000, update, 1);

}

//Keyboard function
//When key is pressed, perform action here
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		game.moveLeft();
		glutPostRedisplay();
		break;
	case 'd':
		game.moveRight();
		glutPostRedisplay();
		break;
	case 'w':
		game.rotateCCW();
		glutPostRedisplay();
		break;
	case 's':
		game.moveDown();
		glutPostRedisplay();
		break;
	case 'o':
		game.moveBlock();
		game.getBlock();
		glutPostRedisplay();
		break;
	case 'p':
		if(pause)
			pause = false;
		else
			pause = true;
		break;
	case 'q':
		game.moveUp();
		glutPostRedisplay();
		break;
	default:
		break;

	}
}
void spkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		cout<<"Move Left"<<endl;
		game.moveLeft();
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		game.moveRight();
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		game.rotateCCW();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		game.moveDown();
		glutPostRedisplay();
		break;
	default:
		break;

	}
}

//Display function
//When screen is redrawn, redraw here
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(-0.7f, -1.2f, -6.0f);
	glVertex3f(-0.7f, 1.2f, -6.0f);
	glVertex3f(0.6f, 1.2f, -6.0f);
	glVertex3f(0.6f, -1.2f, -6.0f);
	glEnd();
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			int color = game.nextBlock->getBlockMatrix().getCell(i, j);
			glColor3f(color*0.4f, color*0.1f, color*0.6f);
			GLfloat x = j;
			GLfloat y = 18-i;
			if (color>0 && color<8) {
				glLoadIdentity();
				glPushMatrix();
				glTranslated(x*0.1+0.7, y*0.1-1, -5);
				glScalef(0.1f, 0.1f, 0.1f);
				glutSolidCube(1.0f);
				glColor3f(0, 0, 0);
				glutWireCube(1.0f);
				glPopMatrix();
			}
		}
	}
	for (int i = 19; i>=0; i--) {
		for (int j = 0; j<10; j++) {
			int color = game.getFieldCell(i, j);
			int color1 = game.getPlayCell(i, j);
			glColor3f(color*0.4f, color*0.1f, color*0.6f);
			GLfloat x = j;
			GLfloat y = 18-i;
			glColor3f(color1*0.4f, color1*0.1f, color1*0.6f);
			if (color1>0 && color1<8) {
				glLoadIdentity();
				glPushMatrix();
				glTranslated(x*0.1-.5, y*0.1-0.8, -5);
				glScalef(0.1f, 0.1f, 0.1f);
				glutSolidCube(1.0f);
				glColor3f(0, 0, 0);
				glutWireCube(1.0f);
				glPopMatrix();

			}
			glColor3f(color*0.4f, color*0.1f, color*0.6f);
			if (color>0 && color<8) {
				glLoadIdentity();
				glPushMatrix();
				glTranslated(x*0.1-.5, y*0.1-0.8, -5);
				glScalef(0.1f, 0.1f, 0.1f);
				glutSolidCube(1.0f);
				glColor3f(0, 0, 0);
				glutWireCube(1.0f);
				glPopMatrix();
			}

		}
	}
	glFlush();
	glutSwapBuffers();
}

//Reshape Function
void reshape(int x, int y) {
	if (y == 0 || x == 0)
		return; //Nothing is visible then, so return

	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(25.0, (GLdouble)x/(GLdouble)y, 1, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y); //Use the whole window for rendering
}

//Main function
//Sets up window and callback funcions
int main(int argc, char **argv) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(700, 700);
	glutInit(&argc, argv);
	init();
	glutCreateWindow("Tetris");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(spkeyboard);
	glutMainLoop();
	return 0;
}
