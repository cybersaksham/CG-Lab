#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857

void myInit (void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);

	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780, 780, -420, 420);
}

void display (void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	int x0=0,y0=0 , x1 = 100 , y1 = 100;
	int a = y1-y0 , b = -(x1-x0);
	int d = 2*(y1-y0)+x1-x0;
	int x=x0 , y = y0;
	glVertex2i(x, y);

	for (x = x0; x <=x1; x+=1) {
		if(d>0) {
			y+=1;
		    d+= a+b;
		} else d+=a;
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

int main (int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Scan conversion of line");
	myInit();

	glutDisplayFunc(display);
	glutMainLoop();
}
