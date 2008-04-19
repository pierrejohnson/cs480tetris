#include "Block.h"

//Constructor
Block::Block(){
	
}

Block::Block(blockType type){
	myBlock = type;
	switch(type){
	case(I):myColor = C; 
		blockMatrix.setMatrix(	E,	E,	myColor,	E,
								E,	E,	myColor,	E,
								E,	E,	myColor,	E,
								E,	E,	myColor,	E );
		break;
	case(L):myColor = Or;
		blockMatrix.setMatrix(	E,	myColor,	E,		E,
								E,	myColor,	E,		E,
								E,	myColor,	E,		E,
								E,	myColor,	myColor,E );
		break;
	case(J):myColor = B;
		blockMatrix.setMatrix(	E,	E,		myColor,	E,
								E,	E,		myColor,	E,
								E,	E,		myColor,	E,
								E,	myColor,myColor,	E );
		break;
	case(O):myColor = Y;
		blockMatrix.setMatrix(	E,E,		E,		E,
								E,myColor,	myColor,E,
								E,myColor,	myColor,E,
								E,E,		E,		E );
		break;
	case(S):myColor = G;
		blockMatrix.setMatrix(	E,E,E,E,
								E,E,myColor,myColor,
								E,myColor,myColor,E,
								E,E,E,E );
		break;
	case(T):myColor = P;
		blockMatrix.setMatrix(	E,E,E,E,
								E,E,myColor,E,
								E,myColor,myColor,myColor,
								E,E,E,E );
		break;
	case(Z):myColor = R;
		blockMatrix.setMatrix(	E,E,E,E,
								E,myColor,myColor,E,
								E,E,myColor,myColor,
								E,E,E,E );
		break;
	default:myColor = E;
		blockMatrix.setMatrix(	E,E,E,E,
								E,E,E,E,
								E,E,E,E,
								E,E,E,E );
		break;
	}
}

//Change Color
void Block::changeColor(colorType color){
	myColor = color;
	//Update block Matrix
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(blockMatrix.getCell(i,j)!=E){
				blockMatrix.setCell(i,j,myColor);
			}
		}
	}
}



