// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif


// numero de puntos de control para esta curva
GLint nNumPoints = 4;

GLfloat ctrlPoints[4][3] = {
        {-4.0f, 0.0f,  0.0f}, // punto final
        // { -6.0f, 4.0f, 0.0f}, // punto de control
        {-2.0f, 2.0f,  0.0f},
        {2.0f,  -2.0f, 0.0f},
        // {  6.0f, -4.0f, 0.0f}, // punto de control
        {4.0f,  0.0f,  0.0f}}; // punto final

// dibuja los puntos de control sobre la curva
void DrawPoints(void) {
    int i;

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    for (i = 0; i < nNumPoints; i++)
        glVertex2fv(ctrlPoints[i]);
    glEnd();
}

void RenderScene(void) {
    int i;

    glClear(GL_COLOR_BUFFER_BIT);

    glMap1f(GL_MAP1_VERTEX_3,   // tipo de datos generados
            0.0f,                // rango inferior de u
            100.0f,                // rango superior de u
            3,                    // distancia entre los puntos en los datos
            nNumPoints,            // numero de puntos de control
            &ctrlPoints[0][0]); // arreglo de los puntos de control

    // activa el evaluador
    glEnable(GL_MAP1_VERTEX_3);

    // usa unaline strip para "connectar-los-puntos"
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= 100; i++) {
        // evalua curva en este punto
        glEvalCoord1f((GLfloat) i);
    }
    glEnd();

    // dibuja los puntos de control
    DrawPoints();

    glutSwapBuffers();
}

void SetupRC() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
}

void ChangeSize(int w, int h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Curva de Bezier 2D");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
