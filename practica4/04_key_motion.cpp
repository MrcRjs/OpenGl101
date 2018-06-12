#include <GLUT/glut.h>

// definici�n e inicializaci�n de variables globales
void init(void)
{
	glMatrixMode (GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glClearColor (0.0, 0.0, 0.0, 0.0);
}

void reshape(int w, int h)
{
    GLfloat nRange = 20.0f;

    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// partimos de la posici�n x= y z=o en el mundo
GLfloat xpos=0, zpos=0;

// rutinas de render
void dibujarMundo()
{
     glPushMatrix();
        glBegin(GL_POLYGON);            // dibuja 3 puntos
          glColor3f(1.0f, 0.0f, 0.0f);
          glVertex3f(-50.0f, -5.0f, -50.0f);
          glColor3f(1.0f, 0.5f, 0.0f);
          glVertex3f( 50.0f, -5.0f, -50.0f);
          glColor3f(0.0f, 1.0f, 0.0f);
          glVertex3f( 50.0f, 5.0f, 50.f);
          glColor3f(1.0f, 1.0f, 0.5f);
          glVertex3f(-50.0f, 5.0f, 50.0f);
        glEnd();
    glPopMatrix();
}

void Dibujar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    dibujarMundo(); // dibujo el mundo

    // el personaje se representa como una esfera amarilla
    glColor3f(1.0, 1.0, 0.0); // activo el color amarillo

    glPushMatrix();
        // se traslada a la posici�n concreta en el mundo
        glTranslatef(xpos, 0.0, zpos);
        // dibujo una esfera de radio 2 unidades y dividida en 16 trozos
        glutSolidSphere(3.0, 16, 16);
    glPopMatrix();

    glutSwapBuffers();
}
// rutina de control del teclado
void ControlTeclado(unsigned char key, int x, int y)
{
    // seg�n sea la tecla oprimida se incrementa una u otra variable de movimiento
    switch (key)
    {
        case 'o':
                xpos--;
                break;
        case 'p':
                xpos++;
                break;
        case 'q':
                zpos++;
                break;
        case 'a':
                zpos--;
                break;
    }
    // le digo a openGL que dibuje de nuevo cuando pueda
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    int id;

    glutInit(&argc, argv); // definici�n t�pica de una ventana
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0,0);

    id=glutCreateWindow("Ejemplo de control de movimiento");

    init();
    glutReshapeFunc(reshape);

    glutDisplayFunc(Dibujar);
    glutKeyboardFunc(ControlTeclado); // cuando el usuario oprima una tecla llamara�
    glutIdleFunc(Dibujar); // cuando no este haciendo nada tambi�n dibujar�

    glutMainLoop();

    return 0;
}
