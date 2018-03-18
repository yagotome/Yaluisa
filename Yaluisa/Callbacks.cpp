#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"
#include "Robot.cpp"
#include "Utils.cpp"
#define ROTATION_OFFSET 5.0

GLfloat angle = 45, fAspect;
GLdouble obsX = -10, obsY = 100, obsZ = 300;
GLfloat theta1 = 0.0;
GLfloat theta2 = 0.0;
GLfloat theta3 = 0.0;
GLfloat theta4 = 0.0;
GLfloat theta5 = 0.0;
GLfloat theta6 = 0.0;

Robot* robot = new Robot(3);

void initRobot() {
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
}

void init() {
	GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };	   // "cor" 
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };// "brilho" 
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 60;

	// Especifica que a cor de fundo da janela sera preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorizacao de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletancia do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentracao do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parametros da luz de numero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Habilita a definicao da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminacao
	glEnable(GL_LIGHTING);
	// Habilita a luz de numero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	initRobot();
}

void special(int key, int, int) {

	switch (key) {
	case GLUT_KEY_LEFT:
		obsX -= 10;
		break;
	case GLUT_KEY_RIGHT:
		obsX += 10;
		break;
	case GLUT_KEY_UP:
		obsY += 10;
		break;
	case GLUT_KEY_DOWN:
		obsY -= 10;
		break;

	case GLUT_KEY_HOME:
		obsZ += 10;
		break;
	case GLUT_KEY_END:
		obsZ -= 10;
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
		theta1 += ROTATION_OFFSET;
		break;
	case 'A':
	case 'a':
		theta1 -= ROTATION_OFFSET;
		break;
	case 'W':
	case 'w':
		theta2 += ROTATION_OFFSET;
		break;
	case 'S':
	case 's':
		theta2 -= ROTATION_OFFSET;
		break;
	case 'T':
	case 't':
		theta3 += ROTATION_OFFSET;
		break;
	case 'G':
	case 'g':
		theta3 -= ROTATION_OFFSET;
		break;
	case 'E':
	case 'e':
		theta4 += ROTATION_OFFSET;
		theta5 -= ROTATION_OFFSET;
		break;
	case 'Q':
	case 'q':
		theta4 -= ROTATION_OFFSET;
		theta5 += ROTATION_OFFSET;
		break;
	case 'Z':
	case 'z':
		if (angle >= 10) angle -= 5;
		break;
	case 'X':
	case 'x':
		if (angle <= 130) angle += 5;
		break;
	case 'R':
	case 'r':
		theta6 += ROTATION_OFFSET;
		break;
	case 'F':
	case 'f':
		theta6 -= ROTATION_OFFSET;
		break;
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	default:
		return;
	}
	glutPostRedisplay();
}

// Funcao usada para especificar o volume de visualizacao
void AdjustCamera(void)
{
	// Especifica sistema de coordenadas de projecao
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projecao
	glLoadIdentity();

	// Especifica a projecao perspectiva
	gluPerspective(angle, fAspect, 0.5, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posicao do observador e do alvo
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
}

void drawArm() {
	glPushMatrix();
		//Ombro
		glColor3f(0.66f, 0.66f, 0.66f);
		glRotatef(theta1, 0.0, 1.0, 0.0);
		glRotatef(theta6, 0.0, 0.0, 1.0);
		glutSolidSphere(15, 20, 10);
		//Biceps
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(20, 0, 0);
		glutSolidCube(15.0f);
		glTranslatef(15, 0, 0);
		glutSolidCube(15.0f);
		//Cotovelo
		glColor3f(0.66f, 0.66f, 0.66f);
		glTranslatef(13, 0, 0);
		glRotatef(theta2, 0.0, 0.0, 1.0);
		glutSolidSphere(7, 20, 10);
		//Antebraco 
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(7, 0, 0);
		glutSolidCube(15.0f);
		glTranslatef(15, 0, 0);
		glutSolidCube(15.0f);
		//Pulso
		glColor3f(0.66f, 0.66f, 0.66f);
		glTranslatef(12, 0, 0);
		glRotatef(theta3, 0.0, 0.0, 1.0);
		glutSolidSphere(5, 20, 10);
		//Mao
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(5, 0, 0);
		glutSolidCube(10.0f);
		//Dedo1
		glPushMatrix();
			glColor3f(0.66f, 0.66f, 0.66f);
			glTranslatef(6, 3, 0);
			//glutSolidCube(3.0f);
			glRotatef(theta4, 0.0, 0.0, 1.0);
			glutSolidSphere(2, 20, 10);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);

			glutSolidSphere(2, 20, 10);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);
		glPopMatrix();
		//Base
		glColor3f(0.66f, 0.66f, 0.66f);
		glTranslatef(6, 0, 0);
		glutSolidCube(3.0f);
		//Dedo2
		glPushMatrix();
			glColor3f(0.66f, 0.66f, 0.66f);
			glTranslatef(0, -3, 0);
			glRotatef(theta5, 0.0, 0.0, 1.0);
			//glutSolidCube(3.0f);
			glutSolidSphere(2, 20, 10);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);

			glutSolidSphere(2, 20, 10);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);
			glTranslatef(3, 0, 0);
			glutSolidCube(3.0f);
		glPopMatrix();
	glPopMatrix();
}

void drawRobot() {
	drawArm();
	glRotatef(180, 0.0, 1.0, 0.0);
	glTranslatef(25, 0, 0);
	glPushMatrix();
		//glutSolidCube(40);
		//glColor3f(0.97f, 0.32f, 0.78f);
		glColor3fv(Utils::ParseColor("#f74fc7"));
		glutSolidSphere(30, 20, 10);
		glTranslatef(0, 42, 0);
		glRotatef(180, 1.0, 0, 0.0);
		glColor3f(1.0f, 1.0f, 0.0f);
		glutSolidSphere(20, 20, 10);
		glColor3f(0.97f, 0.32f, 0.78f);
		//glutSolidCube(40.0f);
		glTranslatef(0, 100, 0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glutSolidCone(40, 120, 20, 10);
	glPopMatrix();
	glTranslatef(25, 0, 0);
	drawArm();
}

void updateAngles() {
	robot->leftArm->shoulder->angleY = theta1;
	robot->leftArm->shoulder->angleZ = theta6;
	robot->leftArm->elbow->angleZ = theta2;
	robot->leftArm->wrist->angleZ = theta3;
	robot->leftArm->hand->fingerArticulation1->angleZ = theta4;
	robot->leftArm->hand->fingerArticulation2->angleZ = theta5;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	updateAngles();
	robot->draw();
	//drawRobot();

	AdjustCamera();
	// Executa os comandos OpenGL
	glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
	// Para previnir uma divisao por zero
	if (h == 0) h = 1;
	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	// Calcula a correcao de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;
	AdjustCamera();
}