#include "Tetris.h"

//Test functionality
void Tetris::test() {
	clearPlayMatrix();
	getBlock();
	makePlayMatrix(*currentBlock);
}

//Default Constructor
Tetris::Tetris() {
	width = 10;
	height = 20;
	srand(time(0));
	//Initialize Matrices
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			playMatrix[i][j] = 0;
			fieldMatrix[i][j] = 0;
		}
	}
	getBlock();
}

//Initialize
void Tetris::Initialize() {
	width = 10;
	height = 20;
	srand(time(0));
	//Initialize Matrices
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			playMatrix[i][j] = 0;
			fieldMatrix[i][j] = 0;
		}
	}
	getBlock();
}

//Clear Matrix
void Tetris::clearPlayMatrix() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			playMatrix[i][j] = 0;
		}
	}
}
void Tetris::clearFieldMatrix() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			fieldMatrix[i][j] = 0;
		}
	}
}

//Make draw matrix
void Tetris::makePlayMatrix(Block block) {
	clearPlayMatrix();
	int x = block.getCurrentX();
	int y = block.getCurrentY();
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (block.getBlockMatrix().getCell(i, j)!=0 && i+y>-1 && j+x>-1) {
				playMatrix[i+y][j+x] = block.getBlockMatrix().getCell(i, j);
			}	
		}
	}
}

//Make play matrix
void Tetris::moveBlock() {
	cout<<endl<<"fieldmatrix"<<endl;
	for (int i = 0; i<20; i++) {
		for (int j = 0; j<10; j++) {
			
				fieldMatrix[i][j]+=getPlayCell(i, j);
				cout<<fieldMatrix[i][j];
				
		}
		cout<<endl;
	}
	currentBlock = NULL;
}

//Check if Block is in play area using a x and y offset
bool Tetris::isIn(Block block, int xoff, int yoff) {
	bool in = true;
	int x = block.getCurrentX()+xoff;
	int y = block.getCurrentY()+yoff;
	for (int i = 0; i<4; i++) {
		cout<<endl;
		cout<<"Compared :";
		for (int j = 0; j<4; j++) {
			int num = block.getBlockMatrix().getCell(i, j);
			cout<<num;
			if ((num!=0) && ((i+y>height-1) || (j+x>width-1) || (i+y<0) || (j+x<0))) {
				cout<<"!";
				in = false;
			}
		}
	}

	return in;
}

//Check if any blocks are interferring with offset
bool Tetris::isNoInter() {
	bool ok = true;
	makePlayMatrix(*currentBlock);
	for (int i = 0; i<10; i++) {
		for (int j = 0; j<20; j++) {
			if(playMatrix[i][j]!=0 && fieldMatrix[i][j]!=0) {
				ok = false;
			}
		}
	}
	return ok;
}

//Generate random blockType
blockType Tetris::randBlk() {
	int randomNum = rand()%7;
	blockType randBlk;
	switch (randomNum) {
	case (0):
		randBlk = I;
		break;
	case (1):
		randBlk = L;
		break;
	case (2):
		randBlk = J;
		break;
	case (3):
		randBlk = O;
		break;
	case (4):
		randBlk = S;
		break;
	case (5):
		randBlk = T;
		break;
	case (6):
		randBlk = Z;
		break;
	default:
		randBlk = S;
		break;
	}
	return randBlk;
}

//Generate new Block
void Tetris::getBlock() {

	//for the very first run
	if (currentBlock == NULL && nextBlock == NULL) {
		currentBlock = new Block(randBlk());
		nextBlock = new Block(randBlk());
		currentBlock->updatePosition(4, 0);
	//then it just keeps changing
	} else if (currentBlock == NULL) {
		currentBlock = nextBlock;
		nextBlock = new Block(randBlk());
		currentBlock->updatePosition(4, 0);
	}
}

//Move block left
bool Tetris::moveLeft() {
	bool success = false;
	if (isIn(*currentBlock, -1, 0)) {
		currentBlock->setCurrentX((currentBlock->getCurrentX())-1);
		cout<<"Move left"<<endl;
		success = true;
	}	
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}
//Move block right
bool Tetris::moveRight() {
	bool success = false;
	if (isIn(*currentBlock, 1, 0)) {
		cout<<"Move right"<<endl;
		currentBlock->setCurrentX((currentBlock->getCurrentX())+1);
		success = true;
	}
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}
//Move block up
bool Tetris::moveUp() {
	bool success = false;
	if (isIn(*currentBlock, 0, -1)) {
		currentBlock->setCurrentY((currentBlock->getCurrentY())-1);
		success = true;
	}
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}
//Move block down
bool Tetris::moveDown() {
	bool success = false;
	//if the current block is within an x offset of 0, and a y offset of 1
	if (isIn(*currentBlock, 0, 1)) {
		currentBlock->setCurrentY((currentBlock->getCurrentY())+1);
		success = true;
	}
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}

//Rotate block CW
bool Tetris::rotateCW() {
	bool success = true;
	//Rotate
	currentBlock->rotateCW();
	//Check if it is still in playing field
	if (!isIn(*currentBlock,0,0)) {
		//If not, try to move it
		if (currentBlock->getCurrentX()<0) {
			success = moveRight();
			if (!isIn(*currentBlock,0,0)) {
				if (currentBlock->getCurrentX()<0)
					success = moveRight();
			}
		} else if (currentBlock->getCurrentX()>6) {
			success = moveLeft();
			if (!isIn(*currentBlock,0,0)) {
				if (currentBlock->getCurrentX()>6)
					success = moveLeft();
			}
		} else if (currentBlock->getCurrentY()==17) {
			success = moveUp();
		} else { //still outside, so can't rotate
			currentBlock->rotateCCW();
			success = false;
		}
	} else if (!isNoInter()) {//In playfield, but has interference
		currentBlock->rotateCCW(); //Interference, can't rotate
		success = false;
	}
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}

//Rotate block CCW
bool Tetris::rotateCCW() {
	bool success = true;
	//Rotate
	currentBlock->rotateCCW();
	//Check if it is still in playing field
	if (!isIn(*currentBlock,0,0)) {
		cout<<"Rotating"<<endl;
		//If not, try to move it
		if (currentBlock->getCurrentX()<0) {
			success = moveRight();
			if (!isIn(*currentBlock,0,0)) {
				success = moveRight();
			}
		} else if (currentBlock->getCurrentX()>6) {
			success = moveLeft();
			if (!isIn(*currentBlock,0,0)) {
					success = moveLeft();
			}
		} else if (currentBlock->getCurrentY()==17) {
			success = moveUp();
		} else {//still outside, so can't rotate
			currentBlock->rotateCW();
			success = false;
		}
	} else if (!isNoInter()) {//In playfield, but has interference
		currentBlock->rotateCW();//Interference, can't rotate
		success = false;
	}
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}

//Check if block is stuck
bool Tetris::isStuck() {
	return (!(rotateCW()||rotateCCW()||moveUp()||moveDown()||moveRight()
			||moveLeft()));
}

//Move stuck block to fieldMatrix
//Update
bool Tetris::update() {
	bool success = true;
	//If no current block, make a new block
	if (currentBlock == NULL) {
		cout<<"Get new block"<<endl;
		getBlock();
		makePlayMatrix(*currentBlock);
		//Draw new updated state
		return success;
	}
	//If it can move down
	bool flag = moveDown();
	if (flag) {
		makePlayMatrix(*currentBlock);
		//Draw new updated state
		return success;
	}
	//If it can't move down
	else if (!flag) {
		cout<<"Stuck"<<endl;
		//Merge Tetris matrix
		moveBlock();
		//Check for line here
		checkForLines();
		//updateScore(lines);
		removeLines();
		
		success = false;
	}
	return success;
}

int Tetris::checkForLines() {
	int count = 0;
	bool line = true;
	for (int i = 0; i<20; i++) {
		line = true;
		for (int j = 0; j<10; j++) {
			if (fieldMatrix[i][j] == 0)
				line = false;
		}
		if (line)
			count++;
	}
	return count;
}

void Tetris::removeLines() {
	bool line = true;
	for (int i = 19; i>=0; i--) {
		line = true;
		for (int j = 0; j<10; j++) {
//			if (drawMatrix[i][j] == 0)
				line = false;
		}
		if (line) {
			shiftDown(i);
			i++;
		}
	}
}

void Tetris::shiftDown(int i) {
	for (int j = i; j>=0; j--) {
	//	if (j==0)
//			for (int k = 0; k<10; k++) 
//				drawMatrix[j][k] = 0;
			
	//	else
//			for (int k = 0; k<10; k++) {
//				setDrawCell(j, k, getDrawCell(j-1, k));
//			}
	}
}
/* ToDo
 * Update
 * Check for current
 * if not current, make new block, add to play area
 * Check if can move down
 * if can move down, update play and draw
 * if can't move down, move to field
 * 		check for line
 * 		if line, delete line and add point
 * 		if no line, end
 * 
 * For every successful movement
 * Delete play matrix
 * Make new play matrix
 * Make new draw matrix
 * 
 * Setup clock function to call update
 * need line counter
 * need level counter
 * 
 */
