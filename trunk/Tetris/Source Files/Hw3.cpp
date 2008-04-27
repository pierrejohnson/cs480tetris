#include <iostream>       
#include <cstdlib>       
#include <ctime>       
#include "GL/glut.h"
#include "GL/glu.h"
#include "Tetris.h"
//#include <GLUT/glut.h>
//#include <OpenGL/glu.h>
#include "Camera.h"
//#include "AL/al.h"
//#include "AL/alut.h"

//Global Variables
GLuint texture[3];
struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};
typedef struct Image Image;
Tetris game;
bool pause1 = false;
GLfloat eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz;
Camera camera;
bool pressed = false;

void update(int value) {
	if (!(pause1)) {
		//game.test();
		if (!game.update())
			pause1 = true;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, update, 1);
}

int ImageLoad(char *filename, Image *image) {
	FILE *file;
	unsigned long size;
	unsigned long i;
	unsigned short int planes;
	unsigned short int bpp;
	char temp;

	if ((file = fopen(filename, "rb"))==NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}

	fseek(file, 18, SEEK_CUR);

	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	printf("Width of %s: %lu\n", filename, image->sizeX);

	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	printf("Height of %s: %lu\n", filename, image->sizeY);

	size = image->sizeX * image->sizeY * 3;

	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}
	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	fseek(file, 24, SEEK_CUR);

	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i=0; i<size; i+=3) {
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	}

	return 1;
}

void LoadGLTextures() {
	Image *image1;

	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("Resource Files/texture1.bmp", image1)) {
		exit(1);
	}

	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
	
	Image *image2;

	image2 = (Image *) malloc(sizeof(Image));
	if (image2 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("Resource Files/texture2.bmp", image2)) {
		exit(1);
	}

	glGenTextures(2, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);
	
	Image *image3;

		image3 = (Image *) malloc(sizeof(Image));
		if (image3 == NULL) {
			printf("Error allocating space for image");
			exit(0);
		}

		if (!ImageLoad("Resource Files/grass.bmp", image3)) {
			exit(1);
		}

		glGenTextures(3, &texture[2]);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data);
	
}
;

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		camera.strafeCamera(-0.01);

		break;
	case 'd':
		camera.strafeCamera(0.01);

		break;
	case 'w':
		camera.moveCamera(0.01);

		break;
	case 's':
		camera.moveCamera(-0.01);
		break;
	case 'r':
		camera.liftCamera(0.1);

		break;
	case 'f':
		camera.liftCamera(-0.1);

		break;
	case 'g':
		camera.rotateCamera(10, 0);

		break;
	case 'j':
		camera.rotateCamera(-10, 0);

		break;
	case 'y':
		camera.rotateCamera(0, 50);

		break;
	case 'h':
		camera.rotateCamera(0, -50);

		break;
	case 'o':
		game.moveBlock();
		game.getBlock();

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

		}
		break;
	case 'm':
		eyex = eyey = eyez = centerx = centery = centerz = upx = upy = upz
				= 0.0f;
		upy = 1.0f;
		centery = 10.0f;
		eyey = 10.0f;
		eyez = 35.0f;
		camera.setCamera(eyex, eyey, eyez, centerx, centery, centerz, upx, upy,
				upz);

		break;
	case ' ':
		game.dropDown();

	default:
		break;

	}
	//if(!pressed)
	glutPostRedisplay();
}
void spkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		game.moveLeft();

		break;
	case GLUT_KEY_RIGHT:
		game.moveRight();

		break;
	case GLUT_KEY_UP:
		game.rotateCCW();

		break;
	case GLUT_KEY_DOWN:
		game.moveDown();

		break;
	default:
		break;

	}
	glutPostRedisplay();
}

void drawCube() {

//	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( 0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( 0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( 0.5f, 0.5f, -0.5f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( 0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( 0.5f, 0.5f, 0.5f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( 0.5f, 0.5f, -0.5f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( 0.5f, -0.5f, 0.5f);
	glEnd();
	//glColor3f(0, 0, 0);
	//glutWireCube(1.0f);
}

void drawFrame() {
	for (int i = -6; i<6; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glTranslated(i, 20, 0);
		drawCube();
		glColor3f(0, 0, 0);
		glutWireCube(1.0f);
		glPopMatrix();
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslated(i, 0, 0);
		drawCube();
		glColor3f(0, 0, 0);
		glutWireCube(1.0f);
		glPopMatrix();
	}
	for (int i = -10; i<10; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glTranslated(-6, i+10, 0);
		drawCube();
		glColor3f(0, 0, 0);
		glutWireCube(1.0f);
		glPopMatrix();
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslated(5, i+10, 0);
		drawCube();
		glColor3f(0, 0, 0);
		glutWireCube(1.0f);
		glPopMatrix();
	}
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	for (int i = 6; i<13; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(i, 12, 0);
		drawCube();
		glColor3f(0, 0, 0);
		glutWireCube(1.0f);
		glPopMatrix();

		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(i, 17, 0);
		drawCube();
		glColor3f(0, 0, 0);
		glutWireCube(1.0f);
		glPopMatrix();
	}

	for (int i = 13; i<17; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(12, i, 0);
		drawCube();
		glColor3f(0, 0, 0);
		glutWireCube(1.0f);
		glPopMatrix();
	}

}

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
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for(int i = -250;i<250;i+=10){//x
		for(int j = -250;j<250;j+=10){//y
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(i, -0.5, j+10);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(i+10, -0.5, j+10);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(i+10, -0.5, j);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(i, -0.5, j);
		}
	}
	glEnd();
	//Draw Game Frame
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	drawFrame();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
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
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				drawCube();
				glBindTexture(GL_TEXTURE_2D, texture[0]);
				glColor3f(0, 0, 0);
				glutWireCube(1.0f);
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
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				drawCube();
				glColor3f(0, 0, 0);
				glutWireCube(1.0f);

				glPopMatrix();

			}
			glColor3f(color*0.4f, color*0.1f, color*0.6f);
			if (color>0 && color<8) {
				glLoadIdentity();
				gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx,
						upy, upz);
				glPushMatrix();
				glTranslated(x, y, 0);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				drawCube();
				glColor3f(0, 0, 0);
				glutWireCube(1.0f);

				glPopMatrix();
			}

		}
	}

	glFlush();
	glutSwapBuffers();
}

void init() 
{
	LoadGLTextures(); 
	glEnable(GL_TEXTURE_2D); 
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f); 
	glClearDepth(1.0); 
	glDepthFunc(GL_LEQUAL); 
	glEnable(GL_DEPTH_TEST); 
	glShadeModel(GL_SMOOTH); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 

	gluPerspective(40.0, (GLdouble)700/(GLdouble)700, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 700, 700); 
	eyex = eyey = eyez = centerx = centery = centerz = upx = upy = upz = 0.0f;
	upy = 1.0f;
	centery = 10.0f;
	eyey = 10.0f;
	eyez = 35.0f;
	camera.setCamera(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
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
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	cout<<state<<endl;
	if (state == GLUT_DOWN)
		pressed = true;
	else
		pressed = false;
	camera.mouse(button, state, x, y);
	glutPostRedisplay();
}

void mouseMovement(int x, int y) {
	camera.mouseMovement(x, y);
	glutPostRedisplay();
}

//Main function
//Sets up window and callback funcions
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tetris");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(spkeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMovement);
	init();
	glutMainLoop();
	return 0;
}
