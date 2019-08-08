// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <stdio.h>

//Matriz de colores
float colores[4][3] =
        {
                {1.0, 1.0, 1.0}, //0 blanco
                {1.0, 0.0, 0.0}, //1 rojo
                {0.0, 1.0, 0.0}, //2 verde
                {0.0, 0.0, 1.0}, //3 azul
        };

int color = 2;  // color de FIGURA
int colorf = 0; // color de FONDO
int colorl = 3; // color de LUZ

//variables globales para la rotacion
float alpha, beta;
int x0, y0;
int opc;

//Variables globales para las transformaciones
float xpos = 0, ypos = 0, inc = 0.5;

//Menu de figuras a elegir
typedef enum {
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

void redPlastic() {
    GLfloat l_ambiente[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat l_difusa[] = {0.5f, 0.0f, 0.0f, 1.0f};
    GLfloat l_especular[] = {0.7f, 0.6f, 0.6f, 1.0f};
    GLfloat brillo[] = {32.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, l_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, l_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, l_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brillo);
}

void esmeralda() {
    GLfloat l_ambiente[] = {0.0215f, 0.1745f, 0.0215f, 0.55f};
    GLfloat l_difusa[] = {0.07568f, 0.61424f, 0.07568f, 0.55f};
    GLfloat l_especular[] = {0.633f, 0.727811f, 0.633f, 0.55f};
    GLfloat brillo[] = {76.8};
    glMaterialfv(GL_FRONT, GL_AMBIENT, l_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, l_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, l_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brillo);
}

void pewter() {
    GLfloat l_ambiente[] = {0.105882f, 0.058824f, 0.113725f, 1.0f};
    GLfloat l_difusa[] = {0.427451f, 0.470588f, 0.541176f, 1.0f};
    GLfloat l_especular[] = {0.333333f, 0.333333f, 0.521569f, 1.0f};
    GLfloat brillo[] = {9.84615};
    glMaterialfv(GL_FRONT, GL_AMBIENT, l_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, l_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, l_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brillo);
}

void chrome() {
    GLfloat l_ambiente[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat l_difusa[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat l_especular[] = {0.774597f, 0.774597f, 0.774597f, 1.0f};
    GLfloat brillo[] = {76.8};
    glMaterialfv(GL_FRONT, GL_AMBIENT, l_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, l_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, l_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brillo);
}

void blackPlastic() {
    GLfloat l_ambiente[] = {0.02f, 0.02f, 0.02f, 1.0f};
    GLfloat l_difusa[] = {0.01f, 0.01f, 0.01f, 1.0f};
    GLfloat l_especular[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat brillo[] = {10.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, l_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, l_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, l_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brillo);
}

void luzAmbiental(void) {
    GLfloat l_difusa[] = {0.5f, 0.5f, 0.5f, 0.0f};
    GLfloat l_especular[] = {0.5f, 0.5f, 0.5f, 0.0f};
    GLfloat l_posicion[] = {0.0, 0.0, 5.0, 1.0};
    GLfloat l_ambiente[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, l_ambiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
    glEnable(GL_LIGHT0);
}

void luzUno(void) {
    GLfloat l_difusa[] = {colores[2][0], colores[2][1], colores[2][2], 0.0f};
    GLfloat l_especular[] = {colores[2][0], colores[2][1], colores[2][2], 0.0f};
    GLfloat l_posicion[] = {0.0f, 5.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
    //glEnable (GL_LIGHT1);
}

void luzTres(void) {
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

void init(void) {
    luzAmbiental();
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void display(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
    gluLookAt(0.0f, 0.0f, 5.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    luzAmbiental();
    // Material define
    //redPlastic();
    //blackPlastic();
    //esmeralda();
    pewter();
    //chrome();
    glPushMatrix();

    glTranslatef(xpos, ypos, 0);

    if (opc != 9)
        glScalef(inc, inc, inc);
    else
        glScalef(inc - 0.15, inc - 0.15, inc - 0.15);

    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    glutSolidTeapot(1);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//Accion del mouse
void onMouse(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {
        x0 = x;
        y0 = y;
    }
}

//Incremento o decremente de los angulos de rotacion
void onMotion(int x, int y) {
    alpha = (alpha + (y - y0));
    beta = (beta + (x - x0));
    x0 = x;
    y0 = y;
    glutPostRedisplay();
}

void menuFiguras(int opcion) {
    switch (opcion) {
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
void creacionMenu(void) {
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

void ControlTeclado(int Key, int x, int y) {
    switch (Key) {
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

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Materials GL 🍿");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(ControlTeclado);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    creacionMenu();
    glutMainLoop();

    return 0;
}