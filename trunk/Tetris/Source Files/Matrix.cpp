#include "Matrix.h"

//Default Constructor
Matrix::Matrix(){
	//Clear matrix
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			matrix[i][j]=0;
		}
	}
}

//Constructor
Matrix::Matrix( int x00, int x01, int x02, int x03,
				int x10, int x11, int x12, int x13,
				int x20, int x21, int x22, int x23,
				int x30, int x31, int x32, int x33 ) {
matrix[0][0]=x00;	matrix[0][1]=x01;	matrix[0][2]=x02;	matrix[0][3]=x03;
matrix[1][0]=x10;	matrix[1][1]=x11;	matrix[1][2]=x12;	matrix[1][3]=x13;
matrix[2][0]=x20;	matrix[2][1]=x21;	matrix[2][2]=x22;	matrix[2][3]=x23;
matrix[3][0]=x30;	matrix[3][1]=x31;	matrix[3][2]=x32;	matrix[3][3]=x33;
}

//Set Matrix
void Matrix::setMatrix( int x00, int x01, int x02, int x03,
		int x10, int x11, int x12, int x13,
		int x20, int x21, int x22, int x23,
		int x30, int x31, int x32, int x33 ) {
matrix[0][0]=x00;	matrix[0][1]=x01;	matrix[0][2]=x02;	matrix[0][3]=x03;
matrix[1][0]=x10;	matrix[1][1]=x11;	matrix[1][2]=x12;	matrix[1][3]=x13;
matrix[2][0]=x20;	matrix[2][1]=x21;	matrix[2][2]=x22;	matrix[2][3]=x23;
matrix[3][0]=x30;	matrix[3][1]=x31;	matrix[3][2]=x32;	matrix[3][3]=x33;
}

//Clear Matrix
void Matrix::clearMatrix(){
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			matrix[i][j]=0;
		}
	}
}

//Rotate CW
void Matrix::rotateCW(){
	//Rotate matrix CW
	int newmatrix[4][4];
	newmatrix[0][0]=matrix[3][0];	newmatrix[0][1]=matrix[2][0];	newmatrix[0][2]=matrix[1][0];	newmatrix[0][3]=matrix[0][0];
	newmatrix[1][0]=matrix[3][1];	newmatrix[1][1]=matrix[2][1];	newmatrix[1][2]=matrix[1][1];	newmatrix[1][3]=matrix[0][1];
	newmatrix[2][0]=matrix[3][2];	newmatrix[2][1]=matrix[2][2];	newmatrix[2][2]=matrix[1][2];	newmatrix[2][3]=matrix[0][2];
	newmatrix[3][0]=matrix[3][3];	newmatrix[3][1]=matrix[2][3];	newmatrix[3][2]=matrix[1][3];	newmatrix[3][3]=matrix[0][3];
	//Copy newmatrix to matrix
	matrix[0][0]=newmatrix[0][0];	matrix[0][1]=newmatrix[0][1];	matrix[0][2]=newmatrix[0][2];	matrix[0][3]=newmatrix[0][3];
	matrix[1][0]=newmatrix[1][0];	matrix[1][1]=newmatrix[1][1];	matrix[1][2]=newmatrix[1][2];	matrix[1][3]=newmatrix[1][3];
	matrix[2][0]=newmatrix[2][0];	matrix[2][1]=newmatrix[2][1];	matrix[2][2]=newmatrix[2][2];	matrix[2][3]=newmatrix[2][3];
	matrix[3][0]=newmatrix[3][0];	matrix[3][1]=newmatrix[3][1];	matrix[3][2]=newmatrix[3][2];	matrix[3][3]=newmatrix[3][3];
}

//Rotate CCW
void Matrix::rotateCCW(){
	//Rotate matrix CCW
	int newmatrix[4][4];
	newmatrix[0][0]=matrix[0][3];	newmatrix[0][1]=matrix[1][3];	newmatrix[0][2]=matrix[2][3];	newmatrix[0][3]=matrix[3][3];
	newmatrix[1][0]=matrix[0][2];	newmatrix[1][1]=matrix[1][2];	newmatrix[1][2]=matrix[2][2];	newmatrix[1][3]=matrix[3][2];
	newmatrix[2][0]=matrix[0][1];	newmatrix[2][1]=matrix[1][1];	newmatrix[2][2]=matrix[2][1];	newmatrix[2][3]=matrix[3][1];
	newmatrix[3][0]=matrix[0][0];	newmatrix[3][1]=matrix[1][0];	newmatrix[3][2]=matrix[2][0];	newmatrix[3][3]=matrix[3][3];
	//Copy newmatrix to matrix
	matrix[0][0]=newmatrix[0][0];	matrix[0][1]=newmatrix[0][1];	matrix[0][2]=newmatrix[0][2];	matrix[0][3]=newmatrix[0][3];
	matrix[1][0]=newmatrix[1][0];	matrix[1][1]=newmatrix[1][1];	matrix[1][2]=newmatrix[1][2];	matrix[1][3]=newmatrix[1][3];
	matrix[2][0]=newmatrix[2][0];	matrix[2][1]=newmatrix[2][1];	matrix[2][2]=newmatrix[2][2];	matrix[2][3]=newmatrix[2][3];
	matrix[3][0]=newmatrix[3][0];	matrix[3][1]=newmatrix[3][1];	matrix[3][2]=newmatrix[3][2];	matrix[3][3]=newmatrix[3][3];
}

