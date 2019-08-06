// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif


// Tamaño inicial de la ventana de despliegue
GLsizei winWidth = 900, winHeight = 600;

// rango para las coordenadas de visión del mundo
//GLfloat xwcMin=0.0, xwcMax=1200.0;
//GLfloat ywcMin=0.0, ywcMax=900.0;

GLfloat xwcMin = -200.0, xwcMax = 900.0;
GLfloat ywcMin = 0.0, ywcMax = 600.0;

//Se define un objeto Punto (x, y) de tipo flotante
class wcPt2D {
public:
    GLfloat x, y;
};

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// CREACION DE LA FIGURA
void triangle(wcPt2D *verts) {
    GLint k;

    glBegin(GL_TRIANGLES);
    for (k = 0; k < 3; k++)
        glVertex2f(verts[k].x, verts[k].y);
    glEnd();
}

// FUNCIÓN QUE CONFIGURA Y DIBUJA TODO LO QUE SE MUESTRA EN LA VENTANA
//      Aquí se aplican las transformaciones programadas anteriormente
void displayFcn(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    wcPt2D verts[3] = {{0.0,   25.0},
                       {100.0, 150.0},
                       {200.0, 25.0}};

    // Original Green Triangle
    glColor3f(0.0, 0.78, 0.39); // Green
    triangle(verts);
    glPopMatrix();

    glLoadIdentity();
    glPushMatrix();
    glColor3f(0.9, 0.04, 0.5); // Magenta
    glTranslatef(0.0, 200.0, 0.0f);
    glRotatef(90.0f, 0, 0, 1.0);
    glScalef(0.5, 0.5, 0.0f);
    triangle(verts);
    glPopMatrix();

    glLoadIdentity();
    glPushMatrix();
    glColor3f(0.08, 0.39, 0.5);
    glTranslatef(300.0, 300.0, 0.0f);
    glRotatef(90.0f, 0, 0, 1.0);
    glScalef(1.25, 1.25, 0.0f);
    triangle(verts);
    glPopMatrix();

    glLoadIdentity();
    glPushMatrix();
    glColor3f(0.78, 0.78, 0.39);
    glTranslatef(400.0, 100.0, 0.0f);
    glRotatef(-36.0f, 0, 0, 1.0);
    glScalef(2.0, 1.0, 0.0f);
    triangle(verts);
    glPopMatrix();

    glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("OpenGL Matrix Transformations 🔥");

    init();

    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);

    glutMainLoop();
}