#include <GLUT/glut.h>

float aspect = 1.0f;

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 5.0f);
    gluPerspective(20.0f, aspect, 1.0f, 5.0f);
    //gluPerspective(20.0f, aspect, 1.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glutWireTeapot(0.5);

    glFlush();

    glutSwapBuffers();
    glFlush();
}

void onSize(int sx, int sy)
{
    glViewport(0, 0, sx, sy);
    aspect = (float)sx / (float)sy;
}

void winReshapeFcn(GLint w, GLint h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    if (w <= h)
        glOrtho(-1.0f, 1.0f, -1.0f * h / w, 1.0f * h / w, -5.0f, 5.0f);
    else
        glOrtho(-1.0f * w / h, 1.0f * w / h, -1.0f, 1.0f, -5.0f, 5.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(10, 50);
    glutCreateWindow("Objetos GLUT y Proyecciones");
    glutDisplayFunc(display);
    glutReshapeFunc(winReshapeFcn);

    init();

    glutMainLoop();

    return 0;
}