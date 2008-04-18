#include <iostream>		
#include <cstdlib>		//for rand
#include <ctime>		//for random
#include <strstream>	
#include <stdio.h>
#include "GL/glut.h"

//Keyboard function
//When key is pressed, perform action here
void keyboard(unsigned char key, int x, int y) {

}

//Display function
//When screen is redrawn, redraw here
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

//Main function
//Sets up window and callback funcions
int main(int argc, char **argv) {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(700, 700);
	glutInit(&argc, argv);

	glutCreateWindow("Tetris");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
