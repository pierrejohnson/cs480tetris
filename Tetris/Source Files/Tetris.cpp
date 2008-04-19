#include "Tetris.h"

//Default Constructor
Tetris::Tetris(){
	width = 10;
	height = 20;
	srand(time(0));
	//Initialize Matrices
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			playMatrix[i][j] = 0;
			fieldMatrix[i][j] = 0;
			drawMatrix[i][j] = 0;
		}
	}
}

//Clear Matrix
void Tetris::clearPlayMatrix(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			playMatrix[i][j] = 0;
		}
	}
}
void Tetris::clearFieldMatrix(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			fieldMatrix[i][j] = 0;
		}
	}
}
void Tetris::clearDrawMatrix(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			drawMatrix[i][j] = 0;
		}
	}
}

//Make draw matrix
void Tetris::makeDrawMatrix(){
	clearDrawMatrix();
	for(int i = 0; i<20;i++){
		for(int j = 0; j<10; j++){
			if(playMatrix[i][j]!=0){
				drawMatrix[i][j] = playMatrix[i][j]; 
			}
			if(fieldMatrix[i][j]!=0){
				drawMatrix[i][j] = fieldMatrix[i][j];
			}
		}
	}
}
//Check if Block is in play area
bool Tetris::isIn(Block block){
	bool in = true;
	int x = block.getCurrentX();
	int y = block.getCurrentY();
	for(int i = 0; i<4;i++){
		for(int j = 0; j<4;j++){
			if(block.getBlockMatrix().getCell(i,j)!=0 && (i+y>height) || (j+x>width)){
				in = false;
			}
		}
	}
	
	return in;
}

//Check if Block is in play area with offset
bool Tetris::isIn(Block block, int xoff, int yoff){
	bool in = true;
	int x = block.getCurrentX()+xoff;
	int y = block.getCurrentY()+yoff;
	for(int i = 0; i<4;i++){
		for(int j = 0; j<4;j++){
			if(block.getBlockMatrix().getCell(i,j)!=0 && (i+y>height) || (j+x>width)){
				in = false;
			}
		}
	}
	
	return in;
}

//Check if any blocks are interferring
bool Tetris::isNoInter(Block block){
	bool ok = true;
	int x = block.getCurrentX();
	int y = block.getCurrentY();
	for(int i = 0; i<4;i++){
		for(int j = 0; j<4;j++){
			if(block.getBlockMatrix().getCell(i,j)!=0 && fieldMatrix[i+y][j+x]!=0){
				ok = false;
			}
		}
	}
	return ok;
}

//Check if any blocks are interferring with offset
bool Tetris::isNoInter(Block block, int xoff, int yoff){
	bool ok = true;
	int x = block.getCurrentX()+xoff;
	int y = block.getCurrentY()+yoff;
	for(int i = 0; i<4;i++){
		for(int j = 0; j<4;j++){
			if(block.getBlockMatrix().getCell(i,j)!=0 && fieldMatrix[i+y][j+x]!=0){
				ok = false;
			}
		}
	}
	return ok;
}

//Generate new Block
void Tetris::getBlock(){
	int randomNum = rand()%7;
	blockType randBlk;
	switch(randomNum){
	case(0): randBlk = I;
			break;
	case(1): randBlk = L;
			break;
	case(2): randBlk = J;
			break;
	case(3): randBlk = O;
			break;
	case(4): randBlk = S;
			break;
	case(5): randBlk = T;
			break;
	case(6): randBlk = Z;
			break;
	default: randBlk = S;
		break;
	}
	if(currentBlock == NULL && nextBlock == NULL ){
		currentBlock = new Block(randBlk);
		nextBlock = new Block(randBlk);
	}else if(currentBlock == NULL){
		currentBlock = nextBlock;
		nextBlock = new Block(randBlk);
	}
}

//Move block left
bool Tetris::moveLeft(){
	if(isIn(*currentBlock,-1,0) && isNoInter(*currentBlock,-1,0)){
		currentBlock->setCurrentX((currentBlock->getCurrentX())-1);
		return true;
	}
	return false;
}
//Move block right
bool Tetris::moveRight(){
	if(isIn(*currentBlock,1,0) && isNoInter(*currentBlock,1,0)){
			currentBlock->setCurrentX((currentBlock->getCurrentX())+1);
			return true;
		}
	return false;
}
//Move block up
bool Tetris::moveUp(){
	if(isIn(*currentBlock,0,-1) && isNoInter(*currentBlock,0,-1)){
			currentBlock->setCurrentX((currentBlock->getCurrentY())-1);
			return true;
		}
	return false;
}
//Move block down
bool Tetris::moveDown(){
	if(isIn(*currentBlock,0,1) && isNoInter(*currentBlock,0,1)){
				currentBlock->setCurrentX((currentBlock->getCurrentY())+1);
				return true;
			}	
	return false;
	}
	
//Rotate block CW
bool Tetris::rotateCW(){
	bool success = true;
	//Rotate
	currentBlock->rotateCW();
	//Check if it is still in playing field
	if(!isIn(*currentBlock)){
		//If not, try to move it
		if(currentBlock->getCurrentX()<0){
			success = moveRight();
			if(!isIn(*currentBlock)){
				if(currentBlock->getCurrentX()<0)
					success = moveRight();
			}
		}else if(currentBlock->getCurrentX()>6){
			success = moveLeft();
			if(!isIn(*currentBlock)){
				if(currentBlock->getCurrentX()>6)
					success = moveLeft();
			}
		}else if(currentBlock->getCurrentY()==17){
			success = moveUp();
		}else{ //still outside, so can't rotate
			currentBlock->rotateCCW();
			success = false;
		}
	}else if(!isNoInter(*currentBlock)){//In playfield, but has interference
		currentBlock->rotateCCW(); //Interference, can't rotate
		success = false;
	}
	return success;
}

//Rotate block CCW
bool Tetris::rotateCCW(){
	bool success = true;
	//Rotate
	currentBlock->rotateCCW();
	//Check if it is still in playing field
	if(!isIn(*currentBlock)){
		//If not, try to move it
		if(currentBlock->getCurrentX()<0){
			success = moveRight();
			if(!isIn(*currentBlock)){
				if(currentBlock->getCurrentX()<0)
					success = moveRight();
			}
		}else if(currentBlock->getCurrentX()>6){
			success = moveLeft();
			if(!isIn(*currentBlock)){
				if(currentBlock->getCurrentX()>6)
					success = moveLeft();
			}
		}else if(currentBlock->getCurrentY()==17){
			success = moveUp();
		}else{//still outside, so can't rotate
			currentBlock->rotateCW();
			success = false;
		}
	}else if(!isNoInter(*currentBlock)){//In playfield, but has interference
		currentBlock->rotateCW();//Interference, can't rotate
		success = false;
	}
	return success;
}

//Check if block is stuck
bool Tetris::isStuck(){
	return(!(rotateCW()||rotateCCW()||moveUp()||moveDown()||moveRight()||moveLeft()));
}

//Move stuck block to fieldMatrix
void Tetris::moveBlock(){
	for(int i = 0; i<20;i++){
		for(int j = 0; j<10;j++){
			if(playMatrix[i][j]!=0 && fieldMatrix[i][j]==0)
				setFieldCell(i,j, getPlayCell(i,j));
		}
	}
}

//Update
bool Tetris::update(){
	bool success = true;
	if(moveDown()){
		//clear play matrix
		//make play matrix
		
		return true;
	}else{
		//Can't move down anymore
		//Check for full line
		//If full line, delete line, increment score
		success = false;
	}
	
	
	return success;
}

/* ToDo
 * Update
 * Check for current
 * if not current, make new block
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
