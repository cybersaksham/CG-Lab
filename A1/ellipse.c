#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define DEG2RAD 0.0174533

float xRadius = 50.0;
float yRadius = 100.0;
float centerX = 350.0;
float centerY = 250.0;

void drawEllipse(float xRadius, float yRadius) {
    glBegin(GL_POINTS);
    for(int i = 0; i < 360; i++) {
        float degInRad = i*DEG2RAD;
        glVertex2f(cos(degInRad)*xRadius + centerX, sin(degInRad)*yRadius + centerY);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 1.0);
	glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(-780, 780, -420, 420);

    drawEllipse(xRadius, yRadius);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(683, 384);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ellipse Example");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
