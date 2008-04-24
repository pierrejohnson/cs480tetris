#ifndef CAMERA_H_
#define CAMERA_H_

#include <gl\glut.h>
#include "math.h"
#define PI PI 3.1415265359

using namespace std;

//Make Camera Vectors
struct Vector{
	GLfloat x,y,z;
};

class Camera{
public:
	Vector PositionVector;
	Vector ViewVector;
	Vector UpVector;
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

};



#endif /*CAMERA_H_*/
