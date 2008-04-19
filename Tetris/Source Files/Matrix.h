/* Matrix Class for a 4x4 Matrix
 * Will be used to hold shapes
 */
#ifndef MATRIX_H_
#define MATRIX_H_
#include <iostream>	

using namespace std;
class Matrix 
{
private:
	int matrix[4][4];
public:
	//Default Constructor
	Matrix();
	//Constructor
	Matrix( int,int,int,int,
			int,int,int,int,
			int,int,int,int,
			int,int,int,int );
	//Set Matrix
	void setMatrix( int,int,int,int,
					int,int,int,int,
					int,int,int,int,
					int,int,int,int );
	//Clear Matrix
	void clearMatrix();
	//Rotate CW
	void rotateCW();
	//Rotate CCW
	void rotateCCW();
	//Get cell
	int getCell(int i, int j){return matrix[i][j];};
	//Set cell
	void setCell(int i, int j, int k){matrix[i][j] = k;};
	
};

#endif /*MATRIX_H_*/
