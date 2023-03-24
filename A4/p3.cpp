#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846

// Define the unit cube vertices
GLfloat vertices[][3] = {
    {-0.5, -0.5, -0.5},
    {0.5, -0.5, -0.5},
    {0.5, 0.5, -0.5},
    {-0.5, 0.5, -0.5},
    {-0.5, -0.5, 0.5},
    {0.5, -0.5, 0.5},
    {0.5, 0.5, 0.5},
    {-0.5, 0.5, 0.5}};

// Define the indices of the unit cube faces
GLubyte indices[][4] = {
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {5, 4, 7, 6},
    {4, 0, 3, 7},
    {0, 4, 5, 1},
    {3, 2, 6, 7}};

// Define the projection matrices
GLfloat ortho_matrix[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 1};

GLfloat iso_matrix[] = {
    1 / sqrt(2), -1 / sqrt(2), 0, 0,
    1 / sqrt(6), 1 / sqrt(6), -2 / sqrt(6), 0,
    1 / sqrt(3), 1 / sqrt(3), 1 / sqrt(3), 0,
    0, 0, 0, 1};

GLfloat diametric_matrix[16] = {
    0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

GLfloat trimetric_matrix[16] = {
    0.866f, 0.5f, -0.5f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.707f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

GLfloat cavalier_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

GLfloat cabinet_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.5f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

// Perspective projection matrices
GLfloat perspective_matrix_1[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, -1.0f, -1.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

GLfloat perspective_matrix_2[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, -2.0f, -2.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

GLfloat perspective_matrix_3[16] = {
    1.0f, 0.0f, -1.0f, 0.0f,
    0.0f, 1.0f, -1.0f, 0.0f,
    0.0f, 0.0f, -1.0f, -1.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

// Define the current projection matrix
GLfloat *projection_matrix = ortho_matrix;

// Define the rotation angle
GLfloat angle = 0.0;

// Define the keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'o':
        projection_matrix = ortho_matrix;
        break;
    case 'i':
        projection_matrix = iso_matrix;
        break;
    case 'd':
        projection_matrix = diametric_matrix;
        break;
    case 't':
        projection_matrix = trimetric_matrix;
        break;
    case 'c':
        projection_matrix = cavalier_matrix;
        break;
    case 'b':
        projection_matrix = cabinet_matrix;
        break;
    case 'x':
        projection_matrix = perspective_matrix_1;
        break;
    case 'y':
        projection_matrix = perspective_matrix_2;
        break;
    case 'z':
        projection_matrix = perspective_matrix_3;
        break;
    case 27: // Escape key
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

const GLfloat AXIS_LENGTH = 5.0f;

void drawAxes()
{
    glLineWidth(2.0f);
    // X-axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(AXIS_LENGTH, 0.0f, 0.0f);
    glEnd();

    // Y-axis in green
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, AXIS_LENGTH, 0.0f);
    glEnd();

    // Z-axis in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, AXIS_LENGTH);
    glEnd();
}

// Define the display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the modelview matrix to rotate the cube
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(angle, 1.0, 1.0, 1.0);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection_matrix);

    drawAxes();

    // Draw the unit cube
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            glVertex3fv(vertices[indices[i][j]]);
        }
    }
    glEnd();

    // Swap the buffers and increment the rotation angle
    glutSwapBuffers();
    angle += 1.0;
}

// Define the main function
int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Planar Projections");

    // Enable depth testing and set the clear color
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set the viewport
    glViewport(0, 0, 500, 500);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(ortho_matrix);

    // Set the display function and keyboard callback function
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
