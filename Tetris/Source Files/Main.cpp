#include <iostream>		
#include <cstdlib>		
#include <ctime>		
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

/*Initialization function
 * Initialize material property, light source, 
 * lighting model, and depth buffer.
*/
void init(void) {
	
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
	init();
	glutMainLoop();
	return 0;
}
