#include <iostream>
#include <GL/glut.h>

using namespace std;

struct Point {
    int x;
    int y;
};

Point p1, p2;
const int WIDTH = 500;
const int HEIGHT = 500;

GLfloat red[] = {1.0, 0.0, 0.0};
GLfloat blue[] = {0.0, 0.0, 1.0};

bool clip_line(Point &p1, Point &p2, int x_min, int x_max, int y_min, int y_max) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int p[4];
    int q[4];
    p[0] = -dx;
    q[0] = p1.x - x_min;
    p[1] = dx;
    q[1] = x_max - p1.x;
    p[2] = -dy;
    q[2] = p1.y - y_min;
    p[3] = dy;
    q[3] = y_max - p1.y;

    float u1 = 0.0, u2 = 1.0;
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0)
                return false;
        } else {
            float u = (float)q[i] / p[i];
            if (p[i] < 0) {
                u1 = max(u1, u);
                if (u1 > u2)
                    return false;
            } else {
                u2 = min(u2, u);
                if (u1 > u2)
                    return false;
            }
        }
    }

    if (u1 < 0)
        u1 = 0;
    if (u2 > 1)
        u2 = 1;

    p2.x = p1.x + u2 * dx;
    p2.y = p1.y + u2 * dy;
    p1.x = p1.x + u1 * dx;
    p1.y = p1.y + u1 * dy;

    return true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(red);
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(100, 300);
    glEnd();

    glColor3fv(blue);
    glBegin(GL_LINES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'c') {
		if (!clip_line(p1, p2, 100, 100, 300, 300)) {
            p1.x = p2.x = 0;
            p1.y = p2.y = 0;
        }
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[]) {
    cout << "Enter the end points of the line: " << endl;
    cout << "x1: ";
    cin >> p1.x;
    cout << "y1: ";
    cin >> p1.y;
    cout << "x2: ";
    cin >> p2.x;
    cout << "y2: ";
    cin >> p2.y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Liang Barsky Line Clipping Algorithm");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}