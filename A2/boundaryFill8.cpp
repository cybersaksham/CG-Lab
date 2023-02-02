#include <GL/glut.h>
#include <iostream>
#include <stack>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 800;
GLfloat fillColor[] = {1.0f, 0.0f, 0.0f};
GLfloat boundaryColor[] = {0.0f, 0.0f, 0.0f};

void checkPixel(int x, int y, stack<pair<int, int>> &st, GLfloat* fillColor) {
   GLfloat color[3];
   glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
   if(color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2]) {
      st.push({x, y});
   }
}

void boundaryFill8(int x, int y, GLfloat* fillColor, GLfloat* boundaryColor) {
   stack<pair<int, int>> pixels;
   pixels.push(make_pair(x, y));

   while (!pixels.empty()) {
      pair<int, int> point = pixels.top();
      pixels.pop();

      int x = point.first;
      int y = point.second;

      GLfloat color[3];
      glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
      if (color[0] != boundaryColor[0] || color[1] != boundaryColor[1] || color[2] != boundaryColor[2]) {
         glColor3f(fillColor[0], fillColor[1], fillColor[2]);
         glBegin(GL_POINTS);
         glVertex2i(x, y);
         glEnd();
         glFlush();

         checkPixel(x + 1, y, pixels, fillColor);
         checkPixel(x, y + 1, pixels, fillColor);
         checkPixel(x - 1, y, pixels, fillColor);
         checkPixel(x, y - 1, pixels, fillColor);
         checkPixel(x + 1, y + 1, pixels, fillColor);
         checkPixel(x - 1, y + 1, pixels, fillColor);
         checkPixel(x + 1, y - 1, pixels, fillColor);
         checkPixel(x - 1, y - 1, pixels, fillColor);
      }
   }
}

void drawPolygon(GLfloat* boundaryColor) {
   glColor3f(boundaryColor[0], boundaryColor[1], boundaryColor[2]);
   glBegin(GL_LINE_LOOP);
   int n;
   cout << "Enter number of sides: ";
   cin >> n;

   for(int i=0; i<n; i++) {
      int x, y;
      cout << "Enter point " << i + 1 << ": ";
      cin >> x >> y;
      glVertex2f(x, y);
   }

   glEnd();
   glFlush();
}

void display() {
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   drawPolygon(boundaryColor);
}

void mouseClick(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      boundaryFill8(x, HEIGHT - y, fillColor, boundaryColor);
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(WIDTH, HEIGHT);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Boundary Fill 4 Point Algorithm");
   gluOrtho2D(0, WIDTH, 0, HEIGHT);
   glutMouseFunc(mouseClick);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
