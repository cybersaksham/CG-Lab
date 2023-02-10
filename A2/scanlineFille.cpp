#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glut.h>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
GLfloat fillColor[] = {1.0f, 0.0f, 0.0f};
GLfloat boundaryColor[] = {0.0f, 0.0f, 0.0f};

struct Point
{
    int x, y;
};

struct Edge
{
    int yMax;
    float x;
    float m;
};

vector<Point> polygon;
vector<Edge> ET;
vector<Edge> AET;
vector<int> yMinMax;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glShadeModel(GL_FLAT);
}

void drawPolygon()
{
    glColor3f(boundaryColor[0], boundaryColor[2], boundaryColor[2]);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < polygon.size(); i++)
        glVertex2i(polygon[i].x, polygon[i].y);
    glEnd();
}

bool compEdges(Edge a, Edge b)
{
    if (a.x != b.x)
        return a.x < b.x;
    return a.m < b.m;
}

void createEdgeTable()
{
    int yMin, yMax;
    for (int i = 0; i < polygon.size(); i++)
    {
        int j = (i + 1) % polygon.size();
        if (polygon[i].y > polygon[j].y)
        {
            yMin = polygon[j].y;
            yMax = polygon[i].y;
        }
        else
        {
            yMin = polygon[i].y;
            yMax = polygon[j].y;
        }

        if (yMin != yMax)
        {
            Edge edge;
            edge.yMax = yMax;
            edge.x = polygon[i].x;
            edge.m = (float)(polygon[j].x - polygon[i].x) / (polygon[j].y - polygon[i].y);
            ET.push_back(edge);
        }
    }
    sort(ET.begin(), ET.end(), compEdges);
}

void fillScanLine()
{
    int y = yMinMax[0];
    while (y < yMinMax[1])
    {
        vector<Edge>::iterator i = ET.begin();
        while (i != ET.end())
        {
            Edge edge = *i;
            if (edge.yMax == y)
            {
                ET.erase(i);
                i = ET.begin();
                continue;
            }

            if (edge.x > WIDTH || edge.x < 0)
            {
                i = ET.erase(i);
                continue;
            }

            int flag = 0;
                       for (int j = 0; j < AET.size(); j++)
            {
                if (AET[j].x == edge.x && AET[j].m == edge.m)
                {
                    flag = 1;
                    break;
                }
            }

            if (!flag)
                AET.push_back(edge);
            i++;
        }

        sort(AET.begin(), AET.end(), compEdges);
        for (int j = 0; j < AET.size(); j += 2)
        {
            int x1 = (int)AET[j].x;
            int x2 = (int)AET[j + 1].x;
            glColor3f(fillColor[0], fillColor[1], fillColor[2]);
            glBegin(GL_POLYGON);
            glVertex2i(x1, y);
            glVertex2i(x2, y);
            glVertex2i(x2, y + 1);
            glVertex2i(x1, y + 1);
            glEnd();
        }

        for (int j = 0; j < AET.size(); j++)
            AET[j].x += AET[j].m;

        y++;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();

    yMinMax.clear();
    yMinMax.push_back(HEIGHT);
    yMinMax.push_back(0);

    for (int i = 0; i < polygon.size(); i++)
    {
        if (polygon[i].y < yMinMax[0])
            yMinMax[0] = polygon[i].y;
        if (polygon[i].y > yMinMax[1])
            yMinMax[1] = polygon[i].y;
    }

    createEdgeTable();
    fillScanLine();

    glFlush();
}

int main(int argc, char** argv)
{
    int n;
    cout << "Enter number of sides: ";
    cin >> n;

    for(int i=0; i<n; i++) {
        int x, y;
        cout << "Enter point " << i + 1 << ": ";
        cin >> x >> y;
        polygon.push_back({x, y});
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Scan Line Polygon Filling Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}