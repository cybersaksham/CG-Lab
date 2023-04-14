#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define WIDTH 500
#define HEIGHT 500

float vertices[8][3] = {{-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {1, 1, 1}, {1, -1, 1}};
int faces[6][4] = {{0, 1, 2, 3}, {1, 5, 6, 2}, {4, 5, 6, 7}, {0, 4, 7, 3}, {0, 1, 5, 4}, {3, 2, 6, 7}};
float colors[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {0, 1, 1}, {1, 0, 1}};
float anglex = 0, angley = 0, anglez = 0;
float z_buffer[WIDTH][HEIGHT];

void init()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)WIDTH / HEIGHT, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw_cube()
{
    glRotatef(anglex, 1, 0, 0);
    glRotatef(angley, 0, 1, 0);
    glRotatef(anglez, 0, 0, 1);
    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glColor3fv(colors[i]);
        for (int j = 0; j < 4; j++)
        {
            glVertex3fv(vertices[faces[i][j]]);
        }
        glEnd();
    }
}

void update_depth_buffer(int x, int y, float z)
{
    if (z_buffer[x][y] > z)
    {
        z_buffer[x][y] = z;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5, 2, 3, 0, 0, 0, 0, 1, 0);
    draw_cube();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        anglex += 5;
        break;
    case 'y':
        angley += 5;
        break;
    case 'z':
        anglez += 5;
        break;
    case 'X':
        anglex -= 5;
        break;
    case 'Y':
        angley -= 5;
        break;
    case 'Z':
        anglez -= 5;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / h, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB |
                        GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Painter's Algorithm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}