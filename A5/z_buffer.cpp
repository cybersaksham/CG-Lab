#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define WIDTH 500
#define HEIGHT 500

float anglex = 0,
      angley = 0, anglez = 0;
float vertices[8][3] = {{-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {1, 1, 1}, {1, -1, 1}};
int faces[6][4] = {
    {0, 1, 2, 3}, {1, 5, 6, 2}, {4, 5, 6, 7}, {0, 4, 7, 3}, {0, 1, 5, 4}, {3, 2, 6, 7}};
float colors[6][3] = {
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {0, 1, 1}, {1, 0, 1}};
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
        glBegin(GL_POLYGON);
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        for (int j = 0; j < 4; j++)
        {
            glVertex3f(vertices[faces[i][j]][0],
                       vertices[faces[i][j]][1], vertices[faces[i][j]][2]);
        }
        glEnd();
    }
}

void update_depth_buffer(int x, int y, float z)
{
    if (x < 0 || x >= WIDTH)
        return;
    if (y < 0 || y >= HEIGHT)
        return;
    if (z_buffer[x][y] < z)
        return;
    z_buffer[x][y] = z;
}

void draw_pixel(int x, int y, float z)
{
    if (x < 0 || x >= WIDTH)
        return;
    if (y < 0 || y >= HEIGHT)
        return;
    if (z_buffer[x][y] < z)
        return;
    z_buffer[x][y] = z;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x1, int y1, float z1, int x2, int y2,
               float z2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    float dz = z2 - z1;
    if (abs(dx) > abs(dy))
    {
        if (x1 > x2)
        {
            swap(x1, x2);
            swap(y1, y2);
            swap(z1, z2);
        }
        for (int x = x1; x <= x2; x++)
        {
            float t = (x - x1) / (float)(x2 - x1);
            int y = y1 + t * dy;
            float z = z1 + t * dz;
            draw_pixel(x, y, z);
        }
    }
    else
    {
        if (y1 > y2)
        {
            swap(x1, x2);
            swap(y1, y2);
            swap(z1, z2);
        }
        for (int y = y1; y <= y2; y++)
        {
            float t = (y - y1) / (float)(y2 - y1);
            int x = x1 + t * dx;
            float z = z1 + t * dz;
            draw_pixel(x, y, z);
        }
    }
}

void draw_triangle(int x1, int y1, float z1, int x2, int y2, float z2, int x3, int y3, float z3)
{
    draw_line(x1, y1, z1, x2, y2, z2);
    draw_line(x2, y2, z2, x3, y3, z3);
    draw_line(x3, y3, z3, x1, y1, z1);
}
void draw_triangle(int x1, int y1, float z1, int x2, int y2, float z2, int x3, int y3, float z3, float r, float g,
                   float b)
{
    draw_line(x1, y1, z1, x2, y2, z2);
    draw_line(x2, y2, z2, x3, y3, z3);
    draw_line(x3, y3, z3, x1, y1, z1);
}
void draw_triangle(int x1, int y1, float z1, int x2, int y2, float z2, int x3, int y3, float z3, float r, float g,
                   float b, float a)
{
    draw_line(x1, y1, z1, x2, y2, z2);
    draw_line(x2, y2, z2, x3, y3, z3);
    draw_line(x3, y3, z3, x1, y1, z1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
    draw_cube();
    glutSwapBuffers();
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
                        GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Z-Buffer Algorithm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}