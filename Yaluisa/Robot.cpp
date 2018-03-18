#include <GL/freeglut.h>

class Color {
public:
	GLfloat r, g, b;
	Color() {
		r = 1;
		g = 1;
		b = 1;
	}
	Color(GLfloat r, GLfloat g, GLfloat b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

class ObjectBase {
public:
	Color * color = new Color();
	GLfloat x, y, z, size;
	ObjectBase() {
		color = new Color();
		x = y = z = size = 0;
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
public:
	int cubeAmount;
	CubeChain(int cubeAmount) : ObjectBase() {
		this->cubeAmount = cubeAmount;
	}
	GLfloat getFullSize() {
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
	Hand(int size) : ObjectBase() {
		palm->size = size;
		fingerArticulation1->x = size;
		fingerArticulation1->y = palm->size * 2 / 5.0;;
		fingerArticulation1->size = palm->size;

		fingerArticulation2->x = palm->size;
		fingerArticulation2->y = palm->size * 4 / 5.0;;
		fingerArticulation2->size = size;

		finger1->size = size;
		finger1->x = fingerArticulation1->size;
		//finger1->y = fingerArticulation1->y;

		finger2->size = size;
		finger2->x = fingerArticulation2->size;
		//finger2->y = fingerArticulation2->y;
	}
	void draw() {
		ObjectBase::predraw();
		palm->draw();
		fingerArticulation1->draw();
		finger1->draw();
		fingerArticulation2->draw();
		finger2->draw();
	}
};

class Arm : ObjectBase {
public:
	Sphere * shoulder = new Sphere();
	CubeChain* biceps = new CubeChain(2);
	Sphere* elbow = new Sphere();
	CubeChain* foreArm = new CubeChain(2);
	Sphere* wrist = new Sphere();
	Hand* hand;
	Arm(int size) : ObjectBase() {
		shoulder->size = size;
		biceps->size = size;
		elbow->size = size;
		foreArm->size = size;
		wrist->size = size;
		hand = new Hand(size);
	}
	void draw() {
		ObjectBase::predraw();
		shoulder->draw();
		biceps->draw();
		elbow->draw();
		foreArm->draw();
		wrist->draw();
		hand->draw();
	}
};

class Robot : ObjectBase {
public:
	Arm * leftArm;
	//Arm * rightArm = new Arm();
	Robot(int size) : ObjectBase() {
		leftArm = new Arm(size);
	}
	void draw() {
		ObjectBase::predraw();
		leftArm->draw();
		//rightArm->draw();
	}
};
