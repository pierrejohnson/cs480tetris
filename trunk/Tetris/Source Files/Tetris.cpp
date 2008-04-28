#include "Tetris.h"

bool LINECOMPLETED= false;
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

bool Tetris::linecompleted() {
	return LINECOMPLETED;
}

void Tetris::resetlinecompleted() {
		LINECOMPLETED= false;
}


//create a copy of an empty matrix with our block into it
//Make draw matrix
void Tetris::makePlayMatrix(Block block) {
//	cout<<endl<<"call to makePlayMatrix()"<<endl;
	clearPlayMatrix();	
	
	int x = block.getCurrentX();	//ex: 14
//	cout<<endl<<"block current X: " << x;
	
	int y = block.getCurrentY();
//	cout<<endl<<"block current Y: " << y;
	
	
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			//for some reason the x value can be = to -1 on the left side... this seems to fix it.
			if ((block.getBlockMatrix().getCell(i, j)!=0) && (i+y>0) && (j+x>-2)) {
				playMatrix[i+y][j+x] = block.getBlockMatrix().getCell(i, j);
			}	
		}
	}
	//printing the playmatrix
	for (int i = 0; i<20; i++) {
	//	cout<<endl<<"playmatrix: ";
		for (int j = 0; j<10; j++) {
		//	cout<<playMatrix[i][j];
		}
	}
	
	

	
	
}

//Make play matrix
void Tetris::moveBlock() {
//	cout<<endl<<"call to game.moveBlock()"<<endl;
	for (int i = 0; i<20; i++) {
	//	cout<<endl<<"FM: "; 
		for (int j = 0; j<10; j++) {
			
				fieldMatrix[i][j]+=getPlayCell(i, j);
		//		cout<<fieldMatrix[i][j];
				
		}
		
	}
	currentBlock = NULL;
}

//Check if Block is within the boundaries of the play area
bool Tetris::isIn(Block block, int xoff, int yoff) {
	bool in = true;
	int x = block.getCurrentX()+xoff;
	int y = block.getCurrentY()+yoff;
	for (int i = 0; i<4; i++) {
	//	cout<<endl;
	//	cout<<"Compared :";
		for (int j = 0; j<4; j++) {
			int num = block.getBlockMatrix().getCell(i, j);
	//		cout<<num;
			if ((num!=0) && ((i+y>height-1) || (j+x>width-1) || (i+y<0) || (j+x<0))) {
	//			cout<<"!";
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
	
	for (int i = 0; i<20; i++) {
	//	cout<<endl<<"fieldmatrix: "; 
		for (int j = 0; j<10; j++) {
			//if we have a conflict
			if((playMatrix[i][j]>0) && (fieldMatrix[i][j]>0)) {
			//	cout<<"!"<<endl;
				ok = false;
			}else 
			//	cout <<fieldMatrix[i][j];
				ok = ok;
			
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
bool Tetris::getBlock() {
	
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
	return isNoInter();
}

//Move block left
bool Tetris::moveLeft() {
	bool success = false;
	
	
	
	//might have a bug here with the checking "isNoInter()
//	cout<<endl<<"Call to game.moveLeft()"<<endl;
	currentBlock->setCurrentX((currentBlock->getCurrentX())-1);
	if (isIn(*currentBlock, 0, 0)&&isNoInter()) {
		cout<<"Moving left"<<endl;
		success = true;
	}else
		currentBlock->setCurrentX((currentBlock->getCurrentX())+1);
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}
//Move block right
bool Tetris::moveRight() {
	bool success = false;
//	cout<<endl<<"Call to game.moveRight()"<<endl;
	currentBlock->setCurrentX((currentBlock->getCurrentX())+1);
	if (isIn(*currentBlock, 0, 0)&&isNoInter()) {
		cout<<"Moving right"<<endl;
		success = true;
	}else
		currentBlock->setCurrentX((currentBlock->getCurrentX())-1);
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}
//Move block up ..... might be out of date
bool Tetris::moveUp() {
	bool success = false;
//	cout<<endl<<"Call to game.moveUp()"<<endl;
	currentBlock->setCurrentY((currentBlock->getCurrentY())-1);
	if (isIn(*currentBlock, 0, 0) && isNoInter()) {
		success = true;
	}else
		currentBlock->setCurrentY((currentBlock->getCurrentY())+1);
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}
//Move block down
bool Tetris::moveDown() {
	bool success = false;
//	cout<<endl<<"Call to game.moveDown()"<<endl;
	//if the current block is within an x offset of 0, and a y offset of 1
	currentBlock->setCurrentY((currentBlock->getCurrentY())+1);
	if (isIn(*currentBlock, 0, 0) && isNoInter()) {
//		cout<<endl<<"Moving Down from moveDown()"<<endl;
		success = true;
	}else{
		currentBlock->setCurrentY((currentBlock->getCurrentY())-1);
//	cout<<endl<<"trying to move it back up from moveDown()"<<endl;
	}
	clearPlayMatrix();
	makePlayMatrix(*currentBlock);
	return success;
}

bool Tetris::dropDown(){
	while(moveDown()){
		
	}
	update();
	return true;
}

//Rotate block CW
bool Tetris::rotateCW() {
	bool success = true;
//	cout<<endl<<"Call to game.rotateCW()"<<endl;
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
//	cout<<endl<<"Call to game.rotateCCW()"<<endl;
	currentBlock->rotateCCW();
	//Check if it is still in playing field
	if (!isIn(*currentBlock,0,0)) {
	//	cout<<"Rotating"<<endl;
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
//Doesn't work yet
bool Tetris::isStuck() {
	return (!(rotateCW()||rotateCCW()||moveUp()||moveDown()||moveRight()
			||moveLeft()));
}

//Move stuck block to fieldMatrix
//Update
bool Tetris::update() {
	bool success = true;
	clearPlayMatrix();
	//If no current block, make a new block
	if (currentBlock == NULL) {
	//	cout<<"Get new block"<<endl;
		getBlock();
		//Draw new updated state
		return success;
	}
	//If it can move down
	makePlayMatrix(*currentBlock);
	bool flag = moveDown();
	if (flag) {
		makePlayMatrix(*currentBlock);
		//Draw new updated state
		return success;
	}
	//If it can't move down
	else if (!flag) {
	//	cout<<"Stuck"<<endl;
		//Merge Tetris matrix
		moveBlock();
		clearPlayMatrix();
		//Check for line here
		checkForLines();
		//updateScore(lines);
		removeLines();
		success = getBlock();
	}
	
	return success;
}

int Tetris::checkForLines() {
//	cout<<endl<<"call to game.checkForLines()"<<endl;
	int count = 0;
	bool line = true;
	for (int i = 0; i<20; i++) {
		
		line = true;
		for (int j = 0; j<10; j++) {
			if (fieldMatrix[i][j] == 0){
				line = false;
			}
		}
		if (line){
			count++;
			cout<<endl<<"LINE detected"<<endl;
			LINECOMPLETED = true;
		//	cout<<"count:"<<count<<endl;
		}
	}
	return count;
}

void Tetris::removeLines() {
	
		cout<<"removing a line";
	bool line = true;
	for (int i = 19; i>=0; i--) {
		line = true;
		for (int j = 0; j<10; j++) {
			if (fieldMatrix[i][j] == 0)
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
		if (j==0)
			for (int k = 0; k<10; k++) 
				fieldMatrix[j][k] = 0;
			
		else
			for (int k = 0; k<10; k++) {
				fieldMatrix[j][k] = fieldMatrix[j-1][k];
			}
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
