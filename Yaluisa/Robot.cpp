#include <GL/freeglut.h>

class Color {
public:
	GLfloat r, g, b;
	Color() {}
	Color(GLfloat r, GLfloat g, GLfloat b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

class ObjectBase {
public:
	Color * color;
	GLfloat x, y, z, size;
	ObjectBase() {
		color = new Color();
	}
	virtual void draw() = 0;
	void predraw() {
		glColor3f(color->r, color->g, color->b);
		glTranslatef(x, y, z);
	}
};

class Sphere : public ObjectBase {
public:
	GLfloat angleX, angleY, angleZ;
	void rotate(GLfloat angleX, GLfloat angleY, GLfloat angleZ) {
		this->angleX += angleX;
		this->angleY += angleY;
		this->angleZ += angleZ;
	}
	void draw() {
		ObjectBase::predraw();
		glRotatef(angleX, 1.0, 0.0, 0.0);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleZ, 0.0, 0.0, 1.0);
		glutSolidSphere(size, 20, 10);
	}
};

class CubeChain : public ObjectBase {
private:
	int cubeAmount;
	GLfloat size;
public:
	CubeChain(int cubeAmount) : ObjectBase() {
		this->cubeAmount = cubeAmount;
	}
	GLfloat getSize() {
		return size * cubeAmount;
	}
	void draw() {
		ObjectBase::predraw();
		glutSolidCube(size);
		for (int i = 0; i < cubeAmount - 1; i++) {
			glTranslatef(size, 0, 0);
			glutSolidCube(size);
		}
	}
};

class Hand : ObjectBase {
public:
	CubeChain * palm = new CubeChain(1);
	Sphere* fingerArticulation1 = new Sphere();
	Sphere* fingerArticulation2 = new Sphere();
	CubeChain* finger1 = new CubeChain(2);
	CubeChain* finger2 = new CubeChain(2);
	void draw() {
		ObjectBase::predraw();
		palm->draw();
		glTranslatef(palm->getSize(), 0, 0);

	}
};

class Arm {
public:
	Sphere * shoulder;
	CubeChain* biceps;
	Sphere* elbow;
	CubeChain* foreArm;
	Sphere* wrist;
};

class Robot {

};
