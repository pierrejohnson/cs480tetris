#include "Block.h"

//Constructor
Block::Block(){
	
}

Block::Block(blockType type){
	currentX = -1;
	currentY = -1;
	myBlock = type;
	int color;
	switch(type){
	case(I):myColor = C; 
		color = myColor;
		blockMatrix.setMatrix(	0,	0,	0,	0,
								color,	color,	color,	color,
								0,	0,	0,	0,
								0,	0,	0,	0 );
		break;
	case(L):myColor = Or;
	color = myColor;
		blockMatrix.setMatrix(	0,	0,	0,		0,
								0,	color,	0,		0,
								0,	color,	0,		0,
								0,	color,	color,0 );
		break;
	case(J):myColor = B;
	color = myColor;
		blockMatrix.setMatrix(	0,	0,		0,	0,
								0,	0,		color,	0,
								0,	0,		color,	0,
								0,	color,color,	0 );
		break;
	case(O):myColor = Y;
	color = myColor;
		blockMatrix.setMatrix(	0,0,		0,		0,
								0,color,	color,0,
								0,color,	color,0,
								0,0,		0,		0 );
		break;
	case(S):myColor = G;
	color = myColor;
		blockMatrix.setMatrix(	0,0,0,0,
								0,0,color,color,
								0,color,color,0,
								0,0,0,0 );
		break;
	case(T):myColor = P;
	color = myColor;
		blockMatrix.setMatrix(	0,0,0,0,
								0,0,color,0,
								0,color,color,color,
								0,0,0,0 );
		break;
	case(Z):myColor = R;
	color = myColor;
		blockMatrix.setMatrix(	0,0,0,0,
								0,color,color,0,
								0,0,color,color,
								0,0,0,0 );
		break;
	default:myColor = E;
	color = myColor;
		blockMatrix.setMatrix(	0,0,0,0,
								0,0,0,0,
								0,0,0,0,
								0,0,0,0 );
		break;
	}
}

//Change Color
void Block::changeColor(colorType color){
	myColor = color;
	//Update block Matrix
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(blockMatrix.getCell(i,j)!=0){
				blockMatrix.setCell(i,j,myColor);
			}
		}
	}
}

//Update position
void Block::updatePosition(int x, int y){
	currentX = x;
	currentY = y;
}

blockType Block::getBlockType(int num){
	switch(num){
	case 0:
		return I;
	case 1:
		return L;
	case 2:
		return J;
	case 3:
		return O;
	case 4:
		return S;
	case 5:
		return T;
	case 6:
		return Z;
	default:
		break;
	}
}
