#include "Camera.h"

Camera::Camera()
{
	u = new Vector3();
	v = new Vector3();
	n = new Vector3();
	set(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void Camera :: setModelViewMatrix(void)
{ 	// load modelview matrix with existing camera values
	float m[16];
	Vector3* eVec = new Vector3(eye.x, eye.y, eye.z); 	// a vector version of eye 
	m[0] =  u->x; m[4] =  u->y; m[8]  =  u->z;  m[12] = -eVec->dot(u);
	m[1] =  v->x; m[5] =  v->y; m[9]  =  v->z;  m[13] = -eVec->dot(v);
	m[2] =  n->x; m[6] =  n->y; m[10] =  n->z;  m[14] = -eVec->dot(n);
	m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m); 					// load OpenGL’s modelview matrix
}
void Camera :: set(float eyex, float eyey, float eyez,
		float lookx, float looky, float lookz,
		float upx, float upy, float upz)
{	// create a modelview matrix and send it to OpenGL
	Point3 Eye(eyex, eyey, eyez);
	Point3 look(lookx, looky, lookz);
	Vector3* up = new Vector3(upx, upy, upz);
	eye.set(Eye); 						// store the given eye position
	n->set(eye.x - look.x, eye.y - look.y, eye.z - look.z);	// make n
	u->set( up->cross(n) ); 				// make u = up X n
	n->normalize(); u->normalize(); 			// make them unit length
	v->set(n->cross(u));  					// make v =  n X u
	setModelViewMatrix(); 					// tell OpenGL
}

void Camera :: setShape(float vAng, float asp, float nearD, float farD)
{
	viewAngle = vAng;
	aspect = asp;
	nearDist = nearD;
	farDist = farD;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);
}

void Camera :: slide(float delU, float delV, float delN)
{
	eye.x += delU * u->x + delV * v->x + delN * n->x;
	eye.y += delU * u->y + delV * v->y + delN * n->y;
	eye.z += delU * u->z + delV * v->z + delN * n->z;
	setModelViewMatrix();
}

void Camera :: roll(float angle)
{ // roll the camera through angle degrees
	rotate(n, angle);
}

void Camera :: pitch(float angle)
{ // pitch the camera through angle degrees
	rotate(u, angle);
}

void Camera :: yaw(float angle)
{ // rotate the camera through angle degrees
	rotate(v, angle);
}

void Camera :: rotate(Vector3* axis, float angle)
{
	float cs = cos(3.14159265/180 * angle);
	float sn = sin(3.14159265/180 * angle);

	Vector3* t;
	Vector3* s;
	if(axis == v) {
		t = u;
		s = n;
	}
	else if(axis == u) {
		t = n;
		s = v;
	}
	else if(axis == n) {
		t = u;
		s = v;
	}

	Vector3* temp = new Vector3(t);

	t->set(cs*t->x + sn*s->x, cs*t->y + sn*s->y, cs*t->z + sn*s->z);
	s->set(cs*s->x - sn*temp->x, cs*s->y - sn*temp->y, cs*s->z - sn*temp->z);
	setModelViewMatrix();
}
