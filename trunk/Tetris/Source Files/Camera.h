#ifndef CAMERA_H_
#define CAMERA_H_

//#include <gl\glut.h>
#include <GLUT/glut.h>
#include "math.h"
#include <iostream>
#define PI PI 3.1415265359

using namespace std;

//Make Camera Vectors
struct Vector{
	GLfloat x,y,z;
};

class Camera{
public:
	GLfloat startX,startY,currentX,currentY,endX,endY;
	GLfloat changeX,changeY;
	Vector PositionVector;
	Vector ViewVector;
	Vector UpVector;
	Vector savedPositionVector;
	Vector savedViewVector;
	Vector savedUpVector;
	//Vector Operations
	Vector  makeVector(GLfloat,GLfloat,GLfloat);
	//Constructor
	Camera();
	Camera(float,float,float,float,float,float,float,float,float);
	void setCamera(float,float,float,float,float,float,float,float,float);
	//Forward Movement
	void moveCamera(float distance);
	//Left/Right Movement
	void strafeCamera(float distance);
	//Up/Down Movement
	void liftCamera(float distance);
	//Look around
	void rotateCamera(float x, float y);
	//Mouse Camera
	void mouse(int button, int state, int x, int y);
	void mouseMovement(int x, int y);

};



#endif /*CAMERA_H_*/
