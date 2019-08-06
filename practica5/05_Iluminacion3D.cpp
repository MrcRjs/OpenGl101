// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

//Matriz de colores
float colores[9][3] =
        {
                {1.0, 1.0, 1.0}, //0 Blanco
                {1.0, 0.0, 0.0}, //1 Rojo
                {0.0, 1.0, 0.0}, //2 Verde
                {0.0, 0.0, 1.0}, //3 Azul
                {1.0, 1.0, 0.0}, //4 Amarillo
                {1.0, 0.0, 1.0}, //5 Magneta
                {0.0, 1.0, 1.0}, //6 Cian
                {0.8, 0.8, 0.8}, //7 Gris
                {0.0, 0.0, 0.0}, //8 Negro
        };

float *getColor(string color) {
    if (color.compare("white") == 0) {
        return colores[0];
    } else if (color.compare("red") == 0) {
        return colores[1];
    } else if (color.compare("green") == 0) {
        return colores[2];
    } else if (color.compare("blue") == 0) {
        return colores[3];
    } else if (color.compare("yellow") == 0) {
        return colores[4];
    } else if (color.compare("magenta") == 0) {
        return colores[5];
    } else if (color.compare("cyan") == 0) {
        return colores[6];
    } else if (color.compare("gray") == 0) {
        return colores[7];
    } else if (color.compare("black") == 0) {
        return colores[8];
    }
}

int window;

string color = "white";   // color de FIGURA
string colorf = "black"; // color de FONDO
int colorl = 3;    // color de LUZ
string coloresp = "gray";

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
    E3,
    D1,
    D2,
    D3,
    S1,
    S2
} opcionMenu;

void luzAmbiental(void) {
    GLfloat l_difusa[] = {getColor(color)[0], getColor(color)[1], getColor(color)[2], 1.0f};
    GLfloat l_especular[] = {getColor(coloresp)[0], getColor(coloresp)[1], getColor(coloresp)[2], 1.0f};
    GLfloat l_a_color[] = {getColor(coloresp)[0], getColor(coloresp)[1], getColor(coloresp)[2], 1.0f};
    GLfloat l_posicion[] = {0.0, 0.0, 5.0, 1.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
    //glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
    glEnable(GL_LIGHT0);
}

void luzUno(void) {
    GLfloat l_difusa[] = {getColor("green")[0], getColor("green")[1], getColor("green")[2], 0.0f};
    GLfloat l_especular[] = {getColor("gray")[0], getColor("gray")[1], getColor("gray")[2], 0.0f};
    GLfloat l_posicion[] = {0.0f, 5.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
    //glEnable (GL_LIGHT1);
}

void luzDos(void) {
    GLfloat l_difusa[] = {getColor("blue")[0], getColor("blue")[1], getColor("blue")[2], 0.0f};
    GLfloat l_especular[] = {getColor("cyan")[0], getColor("cyan")[1], getColor("cyan")[2], 0.0f};
    GLfloat l_posicion[] = {0.0f, -5.0f, 0.0f, 0.0f};

    glLightfv(GL_LIGHT2, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT2, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT2, GL_POSITION, l_posicion);
}

void luzTres(void) {
    GLfloat l_difusa[] = {getColor("yellow")[0], getColor("yellow")[1], getColor("yellow")[2], 1.0f};
    GLfloat l_especular[] = {getColor("red")[0], getColor("red")[1], getColor("red")[2], 1.0f};

    GLfloat l_position[] = {0.0f, 0.0f, 6.0f, 1.0f};
    GLfloat spot_direction[] = {0.0f, 0.0f, -1.0f, 1.0f};

    glLightfv(GL_LIGHT3, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT3, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT3, GL_POSITION, l_position);

    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
}

void init(void) {
    luzAmbiental();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    glClearColor(getColor(colorf)[0], getColor(colorf)[1], getColor(colorf)[2], 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
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

    glColor3f(1.0f, 0.0f, 0.0f);

    switch (opc) {
        case 1:
            glutSolidCube(0.8);
            break;
        case 2:
            glutSolidCone(1, 2, 20, 20);
            break;
        case 3:
            glutSolidSphere(1, 20, 20);
            break;
        case 4:
            glutSolidTeapot(0.8);
            break;
        case 5:
            glutSolidTorus(0.4, 0.8, 10, 40);
            break;
        case 6:
            glutSolidIcosahedron();
            break;
        case 7:
            glutSolidDodecahedron();
            break;
        case 8:
            glutSolidOctahedron();
            break;
        case 9:
            glutSolidTetrahedron();
            break;
    }

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

        case F2:
            opc = 2;
            break;
        case F3:
            opc = 3;
            break;
        case F4:
            opc = 4;
            break;
        case F5:
            opc = 5;
            break;
        case F6:
            opc = 6;
            break;
        case F7:
            opc = 7;
            break;
        case F8:
            opc = 8;
            break;
        case F9:
            opc = 9;
            break;

        case C1:
            colorf = "white";
            break;
        case C2:
            colorf = "black";
            break;

        case C3:
            color = "red";
            break;

        case C4:
            color = "green";
            break;

        case C5:
            color = "blue";
            break;

        case C6:
            color = "yellow";
            break;

        case C7:
            color = "magenta";
            break;

        case C8:
            color = "cyan";
            break;

        case C9:
            color = "gray";
            break;

        case E1:
            glEnable(GL_LIGHT1);
            glutChangeToMenuEntry(1, "Desactivar luz 1", D1);
            break;
        case E2:
            glEnable(GL_LIGHT2);
            glutChangeToMenuEntry(2, "Desactivar luz 2", D2);
            break;
        case E3:
            glEnable(GL_LIGHT3);
            glutChangeToMenuEntry(3, "Desactivar luz 3", D3);
            break;

        case D1:
            glDisable(GL_LIGHT1);
            glutChangeToMenuEntry(1, "Activar luz 1", E1);
            break;
        case D2:
            glDisable(GL_LIGHT2);
            glutChangeToMenuEntry(2, "Activar luz 2", E2);
            break;
        case D3:
            glDisable(GL_LIGHT3);
            glutChangeToMenuEntry(3, "Activar luz 3", E3);
            break;
    }

    luzAmbiental();
    luzUno();
    luzDos();
    luzTres();

    glutPostRedisplay();
}

//Creacion de menu y submenus
void creacionMenu(void) {
    int menuFigura, menuBG, menuColor, menuMain;
    int lightControl;

    menuFigura = glutCreateMenu(menuFiguras);
    glutAddMenuEntry("Cubo", F1);
    glutAddMenuEntry("Cono", F2);
    glutAddMenuEntry("Esfera", F3);
    glutAddMenuEntry("Tetera", F4);
    glutAddMenuEntry("Toroide", F5);
    glutAddMenuEntry("Icosaedro", F6);
    glutAddMenuEntry("Dodecaedro", F7);
    glutAddMenuEntry("Octaedro", F8);
    glutAddMenuEntry("Tetraedro", F9);

    menuBG = glutCreateMenu(menuFiguras);
    glutAddMenuEntry("Blanco", C1);
    glutAddMenuEntry("Negro", C2);

    menuColor = glutCreateMenu(menuFiguras);
    glutAddMenuEntry("Rojo", C3);
    glutAddMenuEntry("Verde", C4);
    glutAddMenuEntry("Azul", C5);
    glutAddMenuEntry("Amarillo", C6);
    glutAddMenuEntry("Magenta", C7);
    glutAddMenuEntry("Cian", C8);
    glutAddMenuEntry("Gris", C9);

    lightControl = glutCreateMenu(menuFiguras);
    glutAddMenuEntry("Activar luz 1", E1);
    glutAddMenuEntry("Activar luz 2", E2);
    glutAddMenuEntry("Activar luz 3", E3);

    // MENU PRINCIPAL (NIVEL 1)
    menuMain = glutCreateMenu(menuFiguras);
    glutAddSubMenu("Figura 3D", menuFigura);
    glutAddSubMenu("Color de Fondo", menuBG);
    glutAddSubMenu("Color de Figura", menuColor);
    glutAddSubMenu("Activar/Desactivar Luces", lightControl);

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

void hitkey(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Escape key
            glutDestroyWindow(window);
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("Iluminación de Figuras 3D 🍤");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(ControlTeclado);
    glutKeyboardFunc(hitkey);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    creacionMenu();
    //system("afplay sound.wav &");
    glutMainLoop();
    return 0;
}
