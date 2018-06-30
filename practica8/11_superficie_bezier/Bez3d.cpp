#include <GLUT/glut.h>

// numero de puntos de control para esta curva
GLint nNumPoints = 3;

GLfloat ctrlPoints[3][3][3] = {{{-4.0f, 0.0f, 4.0f},
                                {-2.0f, 4.0f, 4.0f},
                                {4.0f, 0.0f, 4.0f}},

                               {{-4.0f, 0.0f, 0.0f},
                                {-2.0f, 4.0f, 0.0f},
                                {4.0f, 0.0f, 0.0f}},

                               {{-4.0f, 0.0f, -4.0f},
                                {-2.0f, 4.0f, -4.0f},
                                {4.0f, 0.0f, -4.0f}}};

// esta  funcion se usa para dibujar los puntos de control sobre la curva
void DrawPoints(void)
{
    int i, j;

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    for (i = 0; i < nNumPoints; i++)
        for (j = 0; j < 3; j++)
            glVertex3fv(ctrlPoints[i][j]);
    glEnd();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);

    glMap2f(GL_MAP2_VERTEX_3,      // tipo de dato generado
            0.0f,                  // rango inferior de u
            10.0f,                 // rango superior de u
            3,                     // distancia entre los puntos en los datos
            3,                     // dimension en la direccion de u (orden)
            0.0f,                  // rango inferior de v
            10.0f,                 // rango superior de v
            9,                     // distancia entre los puntos en los datos
            3,                     // dimension en la direccion de v (orden)
            &ctrlPoints[0][0][0]); // arreglo de los puntos de control

    glEnable(GL_MAP2_VERTEX_3);

    // usa funciones de alto nivel para mapear a una rejilla, entonces evalua todo

    // mapea una rejilla de 10 puntos desde 0 hasta 10
    glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);

    // evalua la rejilla, usando lineas
    glEvalMesh2(GL_LINE, 0, 10, 0, 10);

    // dibuja los puntos de control
    DrawPoints();

    // restaura la matriz modelview
    glPopMatrix();

    // despliega la imagen
    glutSwapBuffers();
}

void SetupRC()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // dibuja en azul
    glColor3f(0.0f, 0.0f, 1.0f);
}

void ChangeSize(int w, int h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Superficie de Bezier 3D");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
