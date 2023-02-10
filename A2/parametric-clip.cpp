#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

using namespace std;

const int X_MIN = 50, X_MAX = 150;
const int Y_MIN = 50, Y_MAX = 150;
const int Z_MIN = 50, Z_MAX = 150;

const float R = 0.0f, G = 1.0f, B = 0.0f;

struct Point3D
{
    float x, y, z;
};

bool isClipped(Point3D p)
{
    if(p.x < X_MIN || p.x > X_MAX ||
       p.y < Y_MIN || p.y > Y_MAX ||
       p.z < Z_MIN || p.z > Z_MAX)
        return true;
    return false;
}

Point3D getIntersection(Point3D a, Point3D b, float t)
{
    Point3D p;
    p.x = a.x + t * (b.x - a.x);
    p.y = a.y + t * (b.y - a.y);
    p.z = a.z + t * (b.z - a.z);
    return p;
}

float getTForX(Point3D a, Point3D b)
{
    float t = (X_MIN - a.x) / (b.x - a.x);
    return t;
}

float getTForXMax(Point3D a, Point3D b)
{
    float t = (X_MAX - a.x) / (b.x - a.x);
    return t;
}

float getTForY(Point3D a, Point3D b)
{
    float t = (Y_MIN - a.y) / (b.y - a.y);
    return t;
}

float getTForYMax(Point3D a, Point3D b)
{
    float t = (Y_MAX - a.y) / (b.y - a.y);
    return t;
}

float getTForZ(Point3D a, Point3D b)
{
    float t = (Z_MIN - a.z) / (b.z - a.z);
    return t;
}

float getTForZMax(Point3D a, Point3D b)
{
    float t = (Z_MAX - a.z) / (b.z - a.z);
    return t;
}

void clipLine(Point3D a, Point3D b)
{
    if(!isClipped(a) && !isClipped(b))
    {
        glColor3f(R, G, B);
        glBegin(GL_LINES);
            glVertex3f(a.x, a.y, a.z);
            glVertex3f(b.x, b.y, b.z);
        glEnd();
    }
    else
    {
        float t0 = 0.0f, t1 = 1.0f;
        Point3D p0 = a, p1 = b;
        if(isClipped(a))
        {
            if(a.x < X_MIN)
            {
                t0 = max(t0, getTForX(a, b));
                p0 = getIntersection(a, b, t0);
            }
            if(a.x > X_MAX)
            {
                t0 = max(t0, getTForXMax(a, b));
                p0 = getIntersection(a, b, t0);
            }
            if(a.y < Y_MIN)
            {
                t0 = max(t0, getTForY(a, b));
                p0 = getIntersection(a, b, t0);
            }
            if(a.y > Y_MAX)
            {
                t0 = max(t0, getTForYMax(a, b));
                p0 = getIntersection(a, b, t0);
            }
            if(a.z < Z_MIN)
            {
                t0 = max(t0, getTForZ(a, b));
                p0 = getIntersection(a, b, t0);
            }
            if(a.z > Z_MAX)
            {
                t0 = max(t0, getTForZMax(a, b));
                p0 = getIntersection(a, b, t0);
            }
        }
        if(isClipped(b))
        {
            if(b.x < X_MIN)
            {
                t1 = min(t1, getTForX(a, b));
                p1 = getIntersection(a, b, t1);
            }
            if(b.x > X_MAX)
            {
                t1 = min(t1, getTForXMax(a, b));
                p1 = getIntersection(a, b, t1);
            }
            if(b.y < Y_MIN)
            {
                t1 = min(t1, getTForY(a, b));
                p1 = getIntersection(a, b, t1);
            }
            if(b.y > Y_MAX)
            {
                t1 = min(t1, getTForYMax(a, b));
                p1 = getIntersection(a, b, t1);
            }
            if(b.z < Z_MIN)
            {
                t1 = min(t1, getTForZ(a, b));
                p1 = getIntersection(a, b, t1);
            }
            if(b.z > Z_MAX)
            {
                t1 = min(t1, getTForZMax(a, b));
                p1 = getIntersection(a, b, t1);
            }
        }

        if(t0 < t1)
        {
            glColor3f(R, G, B);
            glBegin(GL_LINES);
                glVertex3f(p0.x, p0.y, p0.z);
                glVertex3f(p1.x, p1.y, p1.z);
            glEnd();
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    vector<pair<Point3D, Point3D>> lines;

    GLfloat R = 0.0f, G = 0.0f, B = 0.0f;

    for(int i = 0; i < lines.size(); i++)
    {
        clipLine(lines[i].first, lines[i].second);
        R = (R + 0.1f) > 1.0f ? 0.0f : (R + 0.1f);
        G = (G + 0.2f) > 1.0f ? 0.0f : (G + 0.2f);
        B = (B + 0.3f) > 1.0f ? 0.0f : (B + 0.3f);
    }

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 300, 0, 300);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Line Clipping using Parametric Clipping Algorithm");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    init();
    glutMainLoop();
    return 0;
}
