#include <GLUT/glut.h>
#include <iostream>

using namespace std;

GLsizei winWidth = 600, winHeight = 600;

void ControlVertices();
void ControlNormales();
void ControlAristas();
void ControlLuces();
void ControlColisiones();
void ControlSonido();

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

// Funciones de control del menú seleccionado, se ejecutan cuando el usuario utilice el menú
void menu_nivel2(int identificador1)
{
    // Según la opción del 2do nivel activada, ejecutar una rutina u otra
    switch (identificador1)
    {
    case 0:
        ControlVertices();
        break;
    case 1:
        ControlNormales();
        break;
    case 2:
        ControlAristas();
        break;
    }

    glutPostRedisplay();
}

void menu_nivel1(int identificador2)
{
    // Seún la opción de 1er nivel activada, se ejecutar una rutina u otra
    switch (identificador2)
    {
    case 0:
        ControlLuces();
        break;
    case 1:
        ControlColisiones();
        break;
    case 2:
        ControlSonido();
        break;
    case 3:
        exit(0);
    }

    glutPostRedisplay();
}

void displayFcn(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glutSwapBuffers();
}

void creacionMenu(void)
{
    int submenu, menu;

    /// Creación del Submenú
    submenu = glutCreateMenu(menu_nivel2);
    glutAddMenuEntry("Vertices", 0);
    glutAddMenuEntry("Normales", 1);
    glutAddMenuEntry("Aristas", 2);

    /// Creación del Menú principal
    menu = glutCreateMenu(menu_nivel1);
    glutAddSubMenu("Ver", submenu);
    glutAddMenuEntry("Luces on/off", 0);
    glutAddMenuEntry("Colisiones on/off", 1);
    glutAddMenuEntry("Sonido on/off", 2);
    glutAddMenuEntry("Salir", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Ventana con menu contextual");

    init();
    creacionMenu();
    glutDisplayFunc(displayFcn);
    glutMainLoop();

    return 0;
}

void ControlVertices()
{
    cout << "Control de Vertices" << endl;
}

void ControlNormales()
{
    cout << "Control de Normales" << endl;
}

void ControlAristas()
{
    cout << "Control de Aristas" << endl;
}

void ControlLuces()
{
    cout << "Control de Luces" << endl;
}

void ControlColisiones()
{
    cout << "Control de Colisiones" << endl;
}

void ControlSonido()
{
    cout << "Control de Sonido" << endl;
}
