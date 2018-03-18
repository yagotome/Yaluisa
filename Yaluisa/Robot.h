#include <GL/freeglut.h>
#include "Utils.h"

class Color {
public:
	GLfloat r, g, b;
	Color() {
		r = 1;
		g = 1;
		b = 1;
	}
	Color(string hexColor) {
		float* color = Utils::ParseColor(hexColor);
		r = color[0];
		g = color[1];
		b = color[2];
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

class Cone : public ObjectBase {
public:
	int base;
	void draw() {
		ObjectBase::predraw();
		glRotatef(90, 1, 0, 0);
		glutSolidCone(base, size, 20, 10);
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

class Hand : public ObjectBase {
public:
	CubeChain * palm = new CubeChain(1);
	Sphere* fingerArticulation1 = new Sphere();
	Sphere* fingerArticulation2 = new Sphere();
	CubeChain* finger1 = new CubeChain(2);
	CubeChain* finger2 = new CubeChain(2);
	void draw() {
		ObjectBase::predraw();
		palm->draw();

		glPushMatrix();
			fingerArticulation1->draw();
			finger1->draw();
		glPopMatrix();

		fingerArticulation2->draw();
		finger2->draw();
	}
};

class Arm : public ObjectBase {
public:
	Sphere * shoulder = new Sphere();
	CubeChain* biceps = new CubeChain(2);
	Sphere* elbow = new Sphere();
	CubeChain* foreArm = new CubeChain(2);
	Sphere* wrist = new Sphere();
	Hand* hand = new Hand();
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

class Robot : public ObjectBase {
public:
	Arm * leftArm = new Arm();
	Arm * rightArm = new Arm();
	Sphere* body = new Sphere();
	Sphere* head = new Sphere();
	Cone* dress = new Cone();
	void draw() {
		ObjectBase::predraw();
		glPushMatrix();
			leftArm->draw();
		glPopMatrix();

		glRotatef(180, 0, 1, 0);

		glPushMatrix();
			body->draw();
			head->draw();
			glRotatef(180, 1, 0, 0);
			dress->draw();
		glPopMatrix();

		rightArm->draw();
	}
};