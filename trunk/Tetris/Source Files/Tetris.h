#ifndef TETRIS_H_
#define TETRIS_H_
#include "Block.h"

using namespace std;
class Tetris{
private:
	int width;
	int height;
	int playMatrix[20][10];//Contains the active block
	int fieldMatrix[20][10];//Contains the block on the field

public:
	Block *currentBlock;
	Block *nextBlock;
	//Test
	void test();
	//Constructor
	Tetris();
	//Initialize
	void Initialize();
	//Check if block is in play area after offset
	bool isIn(Block, int, int);
	//Check if any blocks are interferring after offset
	bool isNoInter();
	//Check if block is stuck
	bool isStuck();
	//Move stuck block to fieldMatrix
	void moveBlock();
	//Get new block
	void getBlock();
	//Move block left
	bool moveLeft();
	//Move block right
	bool moveRight();
	//Move block up
	bool moveUp();
	//Move block down
	bool moveDown();
	//Drop block down
	bool dropDown();
	//Rotate block CW
	bool rotateCW();
	//Rotate block CCW
	bool rotateCCW();
	//Clear Matrices
	void clearPlayMatrix();
	void clearFieldMatrix();
	//Get cell for play matrix
	int getPlayCell(int i, int j){return playMatrix[i][j];};
	//Get cell for field matrix
	int getFieldCell(int i, int j){return fieldMatrix[i][j];};
	//Set cell for play matrix
	void setPlayCell(int i, int j, int k){playMatrix[i][j] = k;};
	//Set cell for field matrix
	void setFieldCell(int i, int j, int k){fieldMatrix[i][j] = k;};
	//Make play matrix
	void makePlayMatrix(Block);
	//Check for lines
	int checkForLines();
	//Remove lines
	void removeLines();
	void shiftDown(int);
	//Update 
	bool update();
	blockType Tetris::randBlk();
	
};
#endif /*TETRIS_H_*/
