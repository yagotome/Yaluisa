#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"
#define ROTATION_OFFSET 5.0

GLfloat angle = 45, fAspect;
GLdouble obsX = 0, obsY = 0, obsZ = 200;
GLfloat theta1 = 0.0;
GLfloat theta2 = 0.0;
GLfloat theta3 = 0.0;
GLfloat theta4 = 0.0;
GLfloat theta5 = 0.0;
GLfloat theta6 = 0.0;

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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	//M�o
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
	glPopMatrix();
	//Base
	glColor3f(0.66f, 0.66f, 0.66f);
	glTranslatef(6, 0, 0);
	glutSolidCube(3.0f);
	//Dedo2
	glColor3f(0.66f, 0.66f, 0.66f);
	glTranslatef(0, -3, 0);
	glRotatef(theta5, 0.0, 0.0, 1.0);
	//glutSolidCube(3.0f);
	glutSolidSphere(2, 20, 10);
	glTranslatef(3, 0, 0);
	glutSolidCube(3.0f);
	glTranslatef(3, 0, 0);
	glutSolidCube(3.0f);

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