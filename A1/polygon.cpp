#include <iostream>
#include <vector>
#include <GL/glut.h>

using namespace std;

struct Vertex {
    float x, y, z;
};

struct Surface {
    vector<Vertex> vertices;
    float r, g, b;
};

struct Polygon {
    vector<Surface> surfaces;
};

void initPolygon(Polygon &polygon) {
    // Surface 1
    Surface surface1;
    surface1.vertices.push_back({-1, -1, 0});
    surface1.vertices.push_back({1, -1, 0});
    surface1.vertices.push_back({1, 1, 0});
    surface1.vertices.push_back({-1, 1, 0});
    surface1.r = 1.0;
    surface1.g = 0.0;
    surface1.b = 0.0;

    // Surface 2
    Surface surface2;
    surface2.vertices.push_back({-1, -1, 0});
    surface2.vertices.push_back({-1, 1, 0});
    surface2.vertices.push_back({-1.5, 0.8, 2});
    surface2.vertices.push_back({-1.5, -0.8, 2});
    surface2.r = 0.0;
    surface2.g = 1.0;
    surface2.b = 0.0;

    // Surface 3
    Surface surface3;
    surface3.vertices.push_back({1, -1, 0});
    surface3.vertices.push_back({1, 1, 0});
    surface3.vertices.push_back({1.5, 0.7, 2});
    surface3.vertices.push_back({1.5, -0.7, 2});
    surface3.r = 0.0;
    surface3.g = 0.0;
    surface3.b = 1.0;

    // Add surfaces to the polygon
    polygon.surfaces.push_back(surface1);
    polygon.surfaces.push_back(surface2);
    polygon.surfaces.push_back(surface3);
}

void drawPolygon(Polygon &polygon) {
    for (Surface surface : polygon.surfaces) {
        glColor3f(surface.r, surface.g, surface.b);
        glBegin(GL_POLYGON);
        for (Vertex vertex : surface.vertices) {
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Polygon polygon;
    initPolygon(polygon);
    drawPolygon(polygon);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polygon Example");
    glutDisplayFunc(display);
    glutReshapeFunc([](int w, int h) {
        reshape(w, h);
    });
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}
