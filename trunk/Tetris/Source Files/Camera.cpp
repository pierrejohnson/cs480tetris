#include "Camera.h"


Camera::Camera(){
	PositionVector = makeVector(0,0,0);
	ViewVector = makeVector(0,0,-1);
	UpVector = makeVector(0,1,0);
}

Camera::Camera(float eyex,  float eyey,  float eyez,
		  float centerx, float centery, float centerz,
		  float upx,   float upy,   float upz){
	PositionVector = makeVector(eyex,eyey,eyez);
	ViewVector = makeVector(centerx,centery,centerz);
	UpVector = makeVector(upx,upy,upz);
}

void Camera::setCamera(float eyex,  float eyey,  float eyez,
		  float centerx, float centery, float centerz,
		  float upx,   float upy,   float upz){
	PositionVector = makeVector(eyex,eyey,eyez);
	ViewVector = makeVector(centerx,centery,centerz);
	UpVector = makeVector(upx,upy,upz);
}

Vector Camera::makeVector(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

//Forward Movement
void Camera::moveCamera(float distance){
	Vector vec = makeVector(ViewVector.x-PositionVector.x,
			ViewVector.y-PositionVector.y,
			ViewVector.z-PositionVector.z);
	PositionVector.x = PositionVector.x + vec.x*distance;
	PositionVector.y = PositionVector.y + vec.y*distance;
	PositionVector.z = PositionVector.z + vec.z*distance;
	ViewVector.x = ViewVector.x + vec.x*distance;
	ViewVector.y = ViewVector.y + vec.y*distance;
	ViewVector.z = ViewVector.z + vec.z*distance;
}

//Left/Right Movement
void Camera::strafeCamera(float distance){
	Vector vec = makeVector(ViewVector.x-PositionVector.x,
			ViewVector.y-PositionVector.y,
			ViewVector.z-PositionVector.z);
	PositionVector.x = PositionVector.x - vec.z*distance;
	PositionVector.z = PositionVector.z + vec.x*distance;
	ViewVector.x = ViewVector.x - vec.z*distance;
	ViewVector.z = ViewVector.z + vec.x*distance;
}

//Up/Down Movement
void Camera::liftCamera(float distance){
	Vector vec = makeVector(ViewVector.x-PositionVector.x,
			ViewVector.y-PositionVector.y,
			ViewVector.z-PositionVector.z);
	PositionVector.y = PositionVector.y + distance;
	ViewVector.y = ViewVector.y + distance;
}

//Look around
void Camera::rotateCamera(float x, float y){
	float angleY = 0.0f;
	float angleZ = 0.0f;
	angleY = x/250;
	angleZ = y/250;
	ViewVector.y+=angleZ*2;
	//Rotate_View(-angle_y);
	Vector vec = makeVector(ViewVector.x-PositionVector.x,
			ViewVector.y-PositionVector.y,
			ViewVector.z-PositionVector.z);
	ViewVector.z = (float) (PositionVector.z + sin(-angleY)*vec.x + cos(-angleY)*vec.z);
	ViewVector.x = (float) (PositionVector.x + cos(-angleY)*vec.x - sin(-angleY)*vec.z);
}
