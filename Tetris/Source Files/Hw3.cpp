#include <iostream>		
#include <cstdlib>		
#include <ctime>		
#include "GL/glut.h"
#include "GL/glu.h"
#include "Tetris.h"
//#include <GLUT/glut.h>
//#include <OpenGL/glu.h>
#include "Camera.h"
#include "AL/al.h"
#include "AL/alut.h"


//Global Variables
Tetris game;
bool pause1 = false;
GLfloat eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz;
Camera camera;
GLuint texture1;

//Timer function
//Calls the game update function
void update(int value) {
	if (!pause1) {
		//game.test();
		if (!game.update())
			pause1 = true;
		glutPostRedisplay();
	}
	//every 1000 ms (1s) the "update(1)" fn is called
	glutTimerFunc(1000, update, 1);
}

//Keyboard function
//When key is pressed, perform action here
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		camera.strafeCamera(-0.03);
		glutPostRedisplay();
		break;
	case 'd':
		camera.strafeCamera(0.03);
		glutPostRedisplay();
		break;
	case 'w':
		camera.moveCamera(0.03);
		glutPostRedisplay();
		break;
	case 's':
		camera.moveCamera(-0.03);
		glutPostRedisplay();
		break;
	case 'r':
		camera.liftCamera(0.1);
		glutPostRedisplay();
		break;
	case 'f':
		camera.liftCamera(-0.1);
		glutPostRedisplay();
		break;
	case 'g':
		camera.rotateCamera(10, 0);
		glutPostRedisplay();
		break;
	case 'j':
		camera.rotateCamera(-10, 0);
		glutPostRedisplay();
		break;
	case 'y':
		camera.rotateCamera(0, 50);
		glutPostRedisplay();
		break;
	case 'h':
		camera.rotateCamera(0, -50);
		glutPostRedisplay();
		break;
	case 'o':
		game.moveBlock();
		game.getBlock();
		glutPostRedisplay();
		break;
	case 'p':
		if (pause1)
			pause1 = false;
		else
			pause1 = true;
		break;
	case 'v':
		if (pause1) {
			game.moveUp();
			glutPostRedisplay();
		}
		break;
	case 'm':
		//Camera
		eyex = eyey = eyez = centerx = centery = centerz = upx = upy = upz = 0.0f;
		upy = 1.0f;
		centery = 10.0f;
		eyey = 10.0f;
		eyez = 35.0f;
		camera.setCamera(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glutPostRedisplay();
		break;
	case ' ':
		game.dropDown();
		glutPostRedisplay();
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

//Draw Cube function
void drawCube() {
	glBegin(GL_QUADS);
	glVertex3f( 0.5f, 0.5f, 0.5f);
	glVertex3f( 0.5f, -0.5f, 0.5f); 
	glVertex3f( 0.5f, -0.5f, -0.5f); 
	glVertex3f( 0.5f, 0.5f, -0.5f); 
	
	glVertex3f( 0.5f, 0.5f, -0.5f); 
	glVertex3f( 0.5f, -0.5f, -0.5f); 
	glVertex3f(-0.5f, -0.5f, -0.5f); 
	glVertex3f(-0.5f, 0.5f, -0.5f); 
	
	glVertex3f(-0.5f, 0.5f, -0.5f); 
	glVertex3f(-0.5f, -0.5f, -0.5f); 
	glVertex3f(-0.5f, -0.5f, 0.5f); 
	glVertex3f(-0.5f, 0.5f, 0.5f); 
	
	glVertex3f(-0.5f, 0.5f, 0.5f); 
	glVertex3f(-0.5f, -0.5f, 0.5f); 
	glVertex3f( 0.5f, -0.5f, 0.5f); 
	glVertex3f( 0.5f, 0.5f, 0.5f); 
	
	glVertex3f(-0.5f, 0.5f, -0.5f); 
	glVertex3f(-0.5f, 0.5f, 0.5f); 
	glVertex3f( 0.5f, 0.5f, 0.5f); 
	glVertex3f( 0.5f, 0.5f, -0.5f); 
	
	glVertex3f(-0.5f, -0.5f, 0.5f); 
	glVertex3f(-0.5f, -0.5f, -0.5f); 
	glVertex3f( 0.5f, -0.5f, -0.5f); 
	glVertex3f( 0.5f, -0.5f, 0.5f); 
	glEnd();
	glColor3f(0, 0, 0);
	glutWireCube(1.0f);
}

//Draw Game Frame Function
void drawFrame() {
	for (int i = -6; i<6; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glTranslated(i, 21, 0);
	//	glutSolidCube(1.0f);
	//	glColor3f(0, 0, 0);
	//	glutWireCube(1.0f);
		drawCube();
		glPopMatrix();
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslated(i, 0, 0);
	//	glutSolidCube(1.0f);
	//	glColor3f(0, 0, 0);
	//	glutWireCube(1.0f);
		drawCube();
		glPopMatrix();
	}
	for (int i = -10; i<11; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glTranslated(-6, i+10, 0);
	//	glutSolidCube(1.0f);
	//	glColor3f(0, 0, 0);
	//	glutWireCube(1.0f);
		drawCube();
		glPopMatrix();
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslated(5, i+10, 0);
	//	glutSolidCube(1.0f);
	//	glColor3f(0, 0, 0);
	//	glutWireCube(1.0f);
		drawCube();
		glPopMatrix();
	}
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	for (int i = 6; i<13; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(i, 12, 0);
	//	glutSolidCube(1.0f);
	//	glColor3f(0, 0, 0);
	//	glutWireCube(1.0f);
		drawCube();
		glPopMatrix();

		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(i, 17, 0);
	//	glutSolidCube(1.0f);
	//	glColor3f(0, 0, 0);
	//	glutWireCube(1.0f);
		drawCube();
		glPopMatrix();
	}

	for (int i = 13; i<17; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(12, i, 0);
	//	glutSolidCube(1.0f);
	//	glColor3f(0, 0, 0);
	//	glutWireCube(1.0f);
		drawCube();
		glPopMatrix();
	}

}
//Display function
//When screen is redrawn, redraw here
void display(void) {
	eyex = camera.PositionVector.x;
	eyey = camera.PositionVector.y;
	eyez = camera.PositionVector.z;
	centerx = camera.ViewVector.x;
	centery = camera.ViewVector.y;
	centerz = camera.ViewVector.z;

	glEnable(GL_LINE_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	//Draw grid
	glBegin(GL_QUADS);
		glColor3f(0.6, 0.4, 0.5);
		glVertex3f(25, -0.5, -25);
		glVertex3f(-25, -0.5, -25);
		glVertex3f(-25, -0.5, 25);
		glVertex3f(25, -0.5, 25);
	glEnd();
	glBegin(GL_LINES);
	for (float i = -250; i <= 250; i += 10) {
		glColor3f(1.0, 1.0, 0.5);
		glVertex3f(-25, -0.5, i/10);
		glVertex3f(25, -0.5, i/10);
		glVertex3f(i/10, -0.5, -25);
		glVertex3f(i/10, -0.5, 25);
	}
	glEnd();
	//Draw Game Frame
	drawFrame();
	//Draw Next Block
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			int color = game.nextBlock->getBlockMatrix().getCell(i, j);
			glColor3f(color*0.4f, color*0.1f, color*0.6f);
			GLfloat x = j+7;
			GLfloat y = 16-i;
			if (color>0 && color<8) {
				glLoadIdentity();
				gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx,
						upy, upz);
				glPushMatrix();
				glTranslated(x, y, 0);
				drawCube();
				glPopMatrix();
			}
		}
	}
	//Draw Game Area
	for (int i = 19; i>=0; i--) {
		for (int j = 0; j<10; j++) {
			int color = game.getFieldCell(i, j);
			int color1 = game.getPlayCell(i, j);
			glColor3f(color*0.4f, color*0.1f, color*0.6f);
			GLfloat x = j-5;
			GLfloat y = 20-i;
			glColor3f(color1*0.4f, color1*0.1f, color1*0.6f);
			if (color1>0 && color1<8) {
				glLoadIdentity();
				gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx,
						upy, upz);
				glPushMatrix();
				glTranslated(x, y, 0);
			//	glutSolidCube(1.0f);
			//	glColor3f(0, 0, 0);
			//	glutWireCube(1.0f);
				drawCube();
				glPopMatrix();

			}
			glColor3f(color*0.4f, color*0.1f, color*0.6f);
			if (color>0 && color<8) {
				glLoadIdentity();
				gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx,
						upy, upz);
				glPushMatrix();
				glTranslated(x, y, 0);
			//	glutSolidCube(1.0f);
			//	glColor3f(0, 0, 0);
			//	glutWireCube(1.0f);
				drawCube();
				glPopMatrix();
			}

		}
	}

	glFlush();
	glutSwapBuffers();
}

//Load Textures
void loadTextures() {

}

/*Initialization function
 * Initialize material property, light source, 
 * lighting model, and depth buffer.
 */
void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0, (GLdouble)700/(GLdouble)700, 5, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 700, 700); //Use the whole window for rendering
	//Texture Map
	glGenTextures( 1, &texture1);
	//Camera
	eyex = eyey = eyez = centerx = centery = centerz = upx = upy = upz = 0.0f;
	upy = 1.0f;
	centery = 10.0f;
	eyey = 10.0f;
	eyez = 35.0f;
	camera.setCamera(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
/*	glEnable(GL_LINE_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_NICEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
*/	
	game.Initialize();
	//every 1 seconds calls the update function
	glutTimerFunc(1000, update, 1);

}

//Reshape Function
void reshape(int x, int y) {
	if (y == 0 || x == 0)
		return; //Nothing is visible then, so return

	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)x/(GLdouble)y, 5, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y); //Use the whole window for rendering
}

//Main function
//Sets up window and callback funcions
int main(int argc, char **argv) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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


