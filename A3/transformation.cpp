#include <iostream>
#include <GL/glut.h>

using namespace std;

int winWidth = 800, winHeight = 600;
int mouseX, mouseY;
float angle = 0.0f, scale = 1.0f, translateX = 0.0f, translateY = 0.0f;
float centerX = 150.0f, centerY = 150.0f;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, winWidth, 0, winHeight);
}

void drawPolygon() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(centerX + translateX, centerY + translateY, 0.0f);
	glRotatef(angle, 0, 0, 1);
	glScalef(scale, scale, 0);
	glTranslatef(-centerX - translateX, -centerY - translateY, 0.0f);
	glTranslatef(translateX, translateY, 0.0f);

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(200, 100);
	glVertex2f(200, 200);
	glVertex2f(100, 200);
	glEnd();

	glFlush();
}

void createMenu() {
	int menu = glutCreateMenu([](int value) {
		switch(value) {
			case 1: // rotate polygon
				angle += 5.0f;
				break;
			case 2: // scale polygon
				scale += 0.1f;
				break;
			case 3: // translate up
				translateY += 10.0f;
				break;
			case 4: // translate down
				translateY -= 10.0f;
				break;
			case 5: // translate right
				translateX += 10.0f;
				break;
			case 6: // translate left
				translateX -= 10.0f;
				break;
		}
		glutPostRedisplay();
	});
	glutAddMenuEntry("Rotate", 1);
	glutAddMenuEntry("Scale", 2);
	glutAddMenuEntry("Translate Up", 3);
	glutAddMenuEntry("Translate Down", 4);
	glutAddMenuEntry("Translate Right", 5);
	glutAddMenuEntry("Translate Left", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch(key) {
		case 'r': // rotate polygon
			angle += 5.0f;
			break;
		case 's': // scale polygon
			scale += 0.1f;
			break;
	}
	glutPostRedisplay();
}

void arrowFunc(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP: // Up Arrow Key
			translateY += 10.0f;
			break;
		case GLUT_KEY_DOWN: // Down Arrow Key
			translateY -= 10.0f;
			break;
		case GLUT_KEY_RIGHT: // Right Arrow Key
			translateX += 10.0f;
			break;
		case GLUT_KEY_LEFT: // Left Arrow Key
			translateX -= 10.0f;
			break;
	}
	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseX = x;
		mouseY = y;
	}
}

void mouseMotionFunc(int x, int y) {
	translateX += x - mouseX;
	translateY += mouseY - y;
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transform Polygon");
	init();
	createMenu();
	glutDisplayFunc(drawPolygon);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(arrowFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	glutMainLoop();
	return 0;
}

