#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"
#include "Robot.h"
#define ROTATION_OFFSET 5.0

GLfloat angle = 45, fAspect;
GLdouble obsX = -10, obsY = 100, obsZ = 300;

Robot* robot;

void initRobot() {
	robot = new Robot();

	robot->leftArm->shoulder->size = 15;
	robot->leftArm->biceps->x = 20;
	robot->leftArm->biceps->size = 15;
	robot->leftArm->elbow->x = 13;
	robot->leftArm->elbow->size = 7;
	robot->leftArm->foreArm->x = 7;
	robot->leftArm->foreArm->size = 15;
	robot->leftArm->wrist->x = 12;
	robot->leftArm->wrist->size = 5;
	robot->leftArm->hand->palm->x = 5;
	robot->leftArm->hand->palm->size = 10;
	robot->leftArm->hand->fingerArticulation1->x = 6;
	robot->leftArm->hand->fingerArticulation1->y = 3;
	robot->leftArm->hand->fingerArticulation1->size = 2;
	robot->leftArm->hand->finger1->x = 3;
	robot->leftArm->hand->finger1->size = 3;
	robot->leftArm->hand->fingerArticulation2->x = 6;
	robot->leftArm->hand->fingerArticulation2->y = -3;
	robot->leftArm->hand->fingerArticulation2->size = 2;
	robot->leftArm->hand->finger2->x = 3;
	robot->leftArm->hand->finger2->size = 3;
	robot->leftArm->color = new Color("#c6af9b");

	robot->rightArm = new Arm(*robot->leftArm);
	robot->rightArm->x = 50;
	robot->rightArm->color = new Color("#c6af9b");
	// this code below makes right arm moviment independent from left arm
	/*robot->rightArm->shoulder = new Sphere(*robot->leftArm->shoulder);
	robot->rightArm->biceps = new CubeChain(*robot->leftArm->biceps);
	robot->rightArm->elbow = new Sphere(*robot->leftArm->elbow);
	robot->rightArm->foreArm = new CubeChain(*robot->leftArm->foreArm);
	robot->rightArm->wrist = new Sphere(*robot->leftArm->wrist);
	robot->rightArm->hand = new Hand(*robot->leftArm->hand);
	robot->rightArm->hand->palm = new CubeChain(*robot->leftArm->hand->palm);
	robot->rightArm->hand->fingerArticulation1 = new Sphere(*robot->leftArm->hand->fingerArticulation1);
	robot->rightArm->hand->finger1 = new CubeChain(*robot->leftArm->hand->finger1);
	robot->rightArm->hand->fingerArticulation2 = new Sphere(*robot->leftArm->hand->fingerArticulation2);
	robot->rightArm->hand->finger2 = new CubeChain(*robot->leftArm->hand->finger2);*/

	robot->body->x = 25;
	robot->body->size = 30;
	robot->body->color = new Color("#9b1577");
	
	robot->head->y = 42;
	robot->head->size = 20;
	robot->head->color = new Color("#f4e242");

	robot->dress->y = 145;
	robot->dress->base = 40;
	robot->dress->size = 120;
	robot->dress->color = new Color("#9b1577");
}

void init() {
	GLfloat luzAmbiente[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat luzDifusa[4] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 60;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	initRobot();
}

void special(int key, int, int) {

	switch (key) {
	case GLUT_KEY_LEFT:
		if (obsX > -100 && obsX <= 100) {
			obsX -= 5;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (obsX >= -100 && obsX < 100) {
			obsX += 5;
		}
		break;
	case GLUT_KEY_UP:
		if (obsY >= -90 && obsY < 160) {
			obsY += 5;
		}
		break;
	case GLUT_KEY_DOWN:
		if (obsY > -90 && obsY <= 160) {
			obsY -= 5;
		}
		break;
	case GLUT_KEY_HOME:
		if (obsZ >= -320 && obsZ < 330) {
			obsZ += 5;
		}
		break;
	case GLUT_KEY_END:
		if (obsZ > -320 && obsZ <= 330) {
			obsZ -= 5;
		}
		break;
	}
	glLoadIdentity();
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'D':
	case 'd':
		if (robot->leftArm->shoulder->angleY >= -60 && robot->leftArm->shoulder->angleY < 60) {
			robot->leftArm->shoulder->angleY += ROTATION_OFFSET;
		}
		break;
	case 'A':
	case 'a':
		if (robot->leftArm->shoulder->angleY > -60 && robot->leftArm->shoulder->angleY <= 60) {
			robot->leftArm->shoulder->angleY -= ROTATION_OFFSET;
		}
		break;
	case 'R':
	case 'r':
		if (robot->leftArm->shoulder->angleZ >= -60 && robot->leftArm->shoulder->angleZ < 85) {
			robot->leftArm->shoulder->angleZ += ROTATION_OFFSET;
		}
		break;
	case 'F':
	case 'f':
		if (robot->leftArm->shoulder->angleZ > -60 && robot->leftArm->shoulder->angleZ <= 85) {
			robot->leftArm->shoulder->angleZ -= ROTATION_OFFSET;
		}
		break;
	case 'W':
	case 'w':
		if (robot->leftArm->elbow->angleZ >= -40 && robot->leftArm->elbow->angleZ < 40) {
			robot->leftArm->elbow->angleZ += ROTATION_OFFSET;
		}
		break;
	case 'S':
	case 's':
		if (robot->leftArm->elbow->angleZ > -40 && robot->leftArm->elbow->angleZ <= 40) {
			robot->leftArm->elbow->angleZ -= ROTATION_OFFSET;
		}
		break;
	case 'T':
	case 't':
		if (robot->leftArm->wrist->angleZ >= -70 && robot->leftArm->wrist->angleZ < 70) {
			robot->leftArm->wrist->angleZ += ROTATION_OFFSET;
		}
		break;
	case 'G':
	case 'g':
		if (robot->leftArm->wrist->angleZ > -70 && robot->leftArm->wrist->angleZ <= 70) {
			robot->leftArm->wrist->angleZ -= ROTATION_OFFSET;
		}
		break;
	case 'E':
	case 'e':
		if (robot->leftArm->hand->fingerArticulation1->angleZ >= -15 && robot->leftArm->hand->fingerArticulation1->angleZ < 60) {
			robot->leftArm->hand->fingerArticulation1->angleZ += ROTATION_OFFSET;
			robot->leftArm->hand->fingerArticulation2->angleZ -= ROTATION_OFFSET;
		}
		break;
	case 'Q':
	case 'q':
		if (robot->leftArm->hand->fingerArticulation1->angleZ > -15 && robot->leftArm->hand->fingerArticulation1->angleZ <= 60) {
			robot->leftArm->hand->fingerArticulation1->angleZ -= ROTATION_OFFSET;
			robot->leftArm->hand->fingerArticulation2->angleZ += ROTATION_OFFSET;
		}
		break;
	case 'Z':
	case 'z':
		if (angle >= 10) angle -= 5;
		break;
	case 'X':
	case 'x':
		if (angle <= 130) angle += 5;
		break;
	case 'l':
		if (robot->x >= -100 && robot->x < 155) {
			robot->x += 5;
		}
		break;
	case 'j':
		if (robot->x > -100 && robot->x <= 155) {
			robot->x -= 5;
		}
		break;
	case 'k':
		if (robot->z >= -145 && robot->z < 60) {
			robot->z += 5;
		}
		break;
	case 'i':
		if (robot->z > -145 && robot->z <= 60) {
			robot->z -= 5;
		}
		break;
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	default:
		return;
	}
	glutPostRedisplay();
}

void drawPlatform()
{
	glTranslated(-180, -120, -150);
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 8; j++) {
			glTranslated(40, 0, 0);
			glutSolidCube(40);
		}
		glTranslated(-320, 0, 10);
	}
}

void adjustCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
}

void adjustProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect, 0.5, 500);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	robot->draw();
	glPopMatrix();

	drawPlatform();

	adjustProjection();
	adjustCamera();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	adjustProjection();
	adjustCamera();
}