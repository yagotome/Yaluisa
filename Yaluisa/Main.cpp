#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"
#define ROBOT_NAME "Yaluisa"
#define INITIAL_WINDOW_WIDTH 1024
#define INITIAL_WINDOW_HEIGHT 768

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
	glutCreateWindow(ROBOT_NAME);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	init();
	glutMainLoop();

	return EXIT_SUCCESS;
}