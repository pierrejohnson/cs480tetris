#ifndef BLOCK_H_
#define BLOCK_H_
#include <iostream>		
#include <cstdlib>		
#include <ctime>			
//#include "GLUT/glut.h"
//#include <GLUT/glut.h>
#include <GL/glut.h>
#include "Matrix.h"

using namespace std;
/* Block Type
 * I-Long one
 * L-The L one
 * J-Backwards L
 * O-Block
 * S-Looks like an S
 * T-The one that looks like a T
 * Z-The backwards S
 */
enum blockType{I,L,J,O,S,T,Z};
/* Block Colors
 * E-Empty
 * C-Cyan
 * B-Blue
 * Or-Orange
 * Y-Yellow
 * G-Green
 * P-Purple
 * R-Red
 */
enum colorType{E,C,B,Or,Y,G,P,R};
class Block 
{

private:
	blockType myBlock;
	colorType myColor;
	Matrix blockMatrix;
	//Position is upper left of 4x4 matrix
	int currentX, currentY;
	
	
public:
	//Constructors
	Block();
	Block(blockType);
	//Rotate Block
	void rotateCW(){blockMatrix.rotateCW();};
	void rotateCCW(){blockMatrix.rotateCCW();};
	//Accessor Function
	blockType getBlockType(){return myBlock;};
	colorType getColorType(){return myColor;};
	int getCurrentX(){return currentX;};
	int getCurrentY(){return currentY;};
	Matrix getBlockMatrix(){return blockMatrix;};
	blockType getBlockType(int);
	//Mutator Function
	void changeColor(colorType);
	void setCurrentX(int x){currentX = x;};
	void setCurrentY(int y){currentY = y;};
	void updatePosition(int, int);
	
	

	
	
	

	
};

#endif /*BLOCK_H_*/
