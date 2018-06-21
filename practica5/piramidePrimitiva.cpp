//JUAN CARLOS CONDE RAMÍREZ
//OBJETOS 3D - ILUMINACION
#define _USE_MATH_DEFINES
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>

//Matriz de colores
float colores[9][3] =
    {
        {1.0, 1.0, 1.0}, //0 Blanco
        {1.0, 0.0, 0.0}, //1 Rojo
        {0.0, 1.0, 0.0}, //2 Verde
        {0.0, 0.0, 1.0}, //3 Azul
        {0.0, 0.0, 0.0}, //4 Negro
        {1.0, 1.0, 0.0}, //5 Amarillo
        {1.0, 0.0, 1.0}, //6 Magenta
        {0.0, 1.0, 1.0}, //7 Cian
        {0.8, 0.8, 0.8}  //8 Gris
};

int w = 500;
int h = 500;

int color = 2;  // color de FIGURA
int colorf = 0; // color de FONDO
int colorl = 3; // color de LUZ

//variables globales para la rotacion
float alpha, beta;
int rX, rY;
int opc;

//Variables globales para las transformaciones
float xpos = 0, ypos = 0, inc = 0.5;

//Menu de figuras a elegir
typedef enum
{
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    C1,
    C2,
    C3,
    C4,
    C5,
    C6,
    C7,
    C8,
    C9,
    E1,
    E2,
    D1,
    D2,
    S1,
    S2
} opcionMenu;

void normalize(float *v)
{
    float N = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    for (int i = 0; i < 3; i++)
    {
        v[i] = v[i] / N;
    }
}

float *crossProduct(float *a, float *b)
{
    float result[] = {
        a[1] * b[2] - a[2] * b[1],
        a[0] * b[2] - a[2] * b[0],
        a[0] * b[1] - a[1] * b[0]};

    normalize(result);

    return result;
}

float *calculateNormal(float *a, float *b, float *c)
{
    float X[] = {
        b[0] - a[0],
        b[1] - a[1],
        b[2] - a[2]};

    float Y[] = {
        c[0] - a[0],
        c[1] - a[1],
        c[2] - a[2]};

    float *result = crossProduct(X, Y);

    return result;
}

void luzAmbiental(void)
{
    GLfloat l_difusa[] = {0.22f, 0.17f, 0.12f, 0.0f};
    GLfloat l_especular[] = {0.22f, 0.17f, 0.12f, 0.0f};
    //GLfloat l_posicion[] = {0.0, 0.0, 5.0, 1.0};
    GLfloat l_a_color[] = {0.93f, 0.89f, 0.78f, 0.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l_especular);
    //glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
    glEnable(GL_LIGHT0);
}

void luzUno(void)
{
    GLfloat l_difusa[] = {colores[2][0], colores[2][1], colores[2][2], 0.0f};
    GLfloat l_especular[] = {colores[2][0], colores[2][1], colores[2][2], 0.0f};
    GLfloat l_posicion[] = {0.0f, 5.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
    //glEnable (GL_LIGHT1);
}

void luzTres(void)
{
    GLfloat l_difusa[] = {colores[0][0], colores[0][1], colores[0][2], 0.0f};
    GLfloat l_especular[] = {colores[0][0], colores[0][1], colores[0][2], 0.0f};

    GLfloat l_posicion[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat spot_direccion[] = {0.0, 0.0, 0.0, 0.0};

    glLightfv(GL_LIGHT3, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT3, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT3, GL_POSITION, l_posicion);

    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direccion);
    //glEnable (GL_LIGHT3);
}

void init(void)
{
    luzUno();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluPerspective(45.0f, w/h, 5.0f, -5.0f);
    gluPerspective(20.0f, 1.0f, 2.0f, 10.0f);
    gluLookAt(0.0f, 0.0f, 5.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glTranslatef(xpos, ypos, 0);

    if (opc != 9)
        glScalef(inc, inc, inc);
    else
        glScalef(inc - 0.15, inc - 0.15, inc - 0.15);

    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);

    glEnable(GL_CULL_FACE);
    luzAmbiental();
    //glColor3f(0.22f, 0.17f, 0.12f);

    // frente
    glBegin(GL_TRIANGLES);
    float vf[3][3] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
    glNormal3fv(calculateNormal(vf[0], vf[1], vf[2]));
    glVertex3fv(vf[1]);
    glVertex3fv(vf[2]);
    glVertex3fv(vf[0]);
    glEnd();

    // Posterior
    glBegin(GL_TRIANGLES);
    float vb[3][3] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f};
    glNormal3fv(calculateNormal(vb[0], vb[1], vb[2]));
    glVertex3fv(vb[1]);
    glVertex3fv(vb[2]);
    glVertex3fv(vb[0]);
    glEnd();

    // Derecha
    glBegin(GL_TRIANGLES);
    float vd[3][3] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f};
    glNormal3fv(calculateNormal(vd[0], vd[1], vd[2]));
    glVertex3fv(vd[1]);
    glVertex3fv(vd[2]);
    glVertex3fv(vd[0]);
    glEnd();

    // Izquierda
    glBegin(GL_TRIANGLES);
    float vi[3][3] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f};
    glNormal3fv(calculateNormal(vi[0], vi[1], vi[2]));
    glVertex3fv(vi[1]);
    glVertex3fv(vi[2]);
    glVertex3fv(vi[0]);
    glEnd();

    // Inferior
    glBegin(GL_QUADS);
    float vbase[3][3] = {-0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f};
    glNormal3fv(calculateNormal(vbase[0], vbase[1], vbase[2]));
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3fv(vbase[2]);
    glVertex3fv(vbase[1]);
    glVertex3fv(vbase[0]);
    glEnd();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//Accion del mouse
void onMouse(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN))
    {
        rX = x;
        rY = y;
    }
}

//Incremento o decremente de los angulos de rotacion
void onMotion(int x, int y)
{
    alpha = (alpha + (y - rY));
    beta = (beta + (x - rX));
    rX = x;
    rY = y;
    glutPostRedisplay();
}

void menuFiguras(int opcion)
{
    switch (opcion)
    {
    case F1:
        opc = 1;
        break;
    case C1:
        colorf = 0;
        break;
    case E1:
        glEnable(GL_LIGHT1);
        break;
    }

    luzAmbiental();
    luzUno();
    luzTres();

    glutPostRedisplay();
}

//Creacion de menu y submenus
void creacionMenu(void)
{
    int menuFIGURA, menuFONDO, menuCOLOR, menuLUCES, menuMain;
    int on, off;

    //----------------------------------------------------------

    // NIVEL 2 DE SUB-MENU PARA TIPO DE FIGURA
    menuFIGURA = glutCreateMenu(menuFiguras);
    glutAddMenuEntry("Cube", F1);
    /*
        AQUI VAN LAS OPCIONES
    */

    //----------------------------------------------------------

    // NUVEL 2 DE SUB-MENU PARA COLOR DE FONDO
    menuFONDO = glutCreateMenu(menuFiguras);
    /*
        AQUI VAN LAS OPCIONES
    */

    //----------------------------------------------------------

    // NIVEL 3 DE SUB-MENUS PARA ACTIVAR LUCES
    on = glutCreateMenu(menuFiguras);
    /*
            AQUI VAN LAS OPCIONES
        */

    // NIVEL 3 DE SUB-MENUS PARA DESACTIVAR LUCES
    off = glutCreateMenu(menuFiguras);
    /*
            AQUI VAN LAS OPCIONES
        */

    // NIVEL 2 DE SU-MENUS
    menuLUCES = glutCreateMenu(menuFiguras);
    /*
        AQUI VAN LOS SUB-MENUS DE NIVEL 3
    */

    //----------------------------------------------------------

    // NIVEL 2 DE SUB-MENUS
    menuCOLOR = glutCreateMenu(menuFiguras);
    /*
        AQUI VAN LAS OPCIONES
    */

    // MENU PRINCIPAL (NIVEL 1)
    menuMain = glutCreateMenu(menuFiguras);
    glutAddSubMenu("Figura 3D", menuFIGURA);
    /*
        AQUI VAN LOS SUB-MENUS DE NIVEL 2
    */

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ControlTeclado(int Key, int x, int y)
{
    switch (Key)
    {
    //TRASLACION
    case GLUT_KEY_RIGHT:
        xpos += 0.05;
        break;
    case GLUT_KEY_LEFT:
        xpos -= 0.05;
        break;
    case GLUT_KEY_UP:
        ypos += 0.05;
        break;
    case GLUT_KEY_DOWN:
        ypos -= 0.05;
        break;
    //ESCALAMIENTO
    case GLUT_KEY_HOME:
        inc += 0.05;
        break;
    case GLUT_KEY_END:
        if (inc > 0.0)
            inc -= 0.05;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Piramide Primitiva 🤘🏼");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(ControlTeclado);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    creacionMenu();
    glutMainLoop();

    return 0;
}
