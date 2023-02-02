#include <iostream>
#include <GL/glut.h>

using namespace std;

float xmin = 50, ymin = 50, xmax = 100, ymax = 100;

void clip(float x1, float y1, float x2, float y2) {
	float t1 = 0, t2 = 1, dx = x2 - x1, dy;
	float p[4], q[4];

	for (int edge = 0; edge < 4; edge++) {
		if (edge == 0) {
			dy = y2 - y1;
			p[0] = -dx;
			q[0] = x1 - xmin;
		}
		if (edge == 1) {
			dy = y2 - y1;
			p[1] = dx;
			q[1] = xmax - x1;
		}
		if (edge == 2) {
			dx = x2 - x1;
			dy = -(y2 - y1);
			p[2] = dy;
			q[2] = y1 - ymin;
		}
		if (edge == 3) {
			dx = x2 - x1;
			dy = -(y2 - y1);
			p[3] = -dy;
			q[3] = ymax - y1;
		}

		if (p[edge] == 0 && q[edge] < 0) return;

		float t = q[edge] / p[edge];

		if (p[edge] < 0) {
			if (t > t2) return;
			else if (t > t1) t1 = t;
		} else {
			if (t < t1) return;
			else if (t < t2) t2	 = t;
		}
	}

	float finalx1 = x1 + t1 * dx;
	float finaly1 = y1 + t1 * dy;
	float finalx2 = x1 + t2 * dx;
	float finaly2 = y1 + t2 * dy;

	cout << finalx1 << " " << finaly1 << endl;
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(finalx1, finaly1);
	glVertex2f(finalx2, finaly2);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.0, 0.0, 1.0);
	glRectf(xmin, ymin, xmax, ymax);
	

	float x1 = 60, y1 = 20, x2 = 80, y2 = 120;

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	clip(x1, y1, x2, y2);

	glFlush();
}
 
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Liang Barsky Line Clipping Algorithm");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 400, 0, 300);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

