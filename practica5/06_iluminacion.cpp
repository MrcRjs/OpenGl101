#include <GLUT/glut.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>

using namespace std;

GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
GLfloat mat_shininess[] = {50};

GLfloat kc = 1.0, cutoff = 45.0;

/// LUZ AZUL ---------------------------------------------
void luzAzulOn(void)
{
    GLfloat light_blue_position[] = {2.0, 2.0, 2.0, 1.0};
    GLfloat light_blue_difusse[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat light_blue_specular[] = {0.8, 0.8, 1.0, 1.0};

    glLightfv(GL_LIGHT1, GL_POSITION, light_blue_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_blue_difusse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_blue_specular);
    glEnable(GL_LIGHT1);
}

void luzAzulOff(void)
{
    glDisable(GL_LIGHT1);
}

/// LUZ TIPO REFLECTOR ------------------------------------

void luzSpotOn(void)
{
    GLfloat light_red_position[] = {-2.0, 2.0, 2.0, 1.0};
    GLfloat light_red_difusse[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light_red_specular[] = {1.0, 0.80, 0.80, 1.0};
    GLfloat light_red_spot_direction[] = {1.0, -1.0, -1.0};

    glLightfv(GL_LIGHT2, GL_POSITION, light_red_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_red_difusse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_red_specular);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_red_spot_direction);

    glEnable(GL_LIGHT2);
}

void luzSpotOff(void)
{
    glDisable(GL_LIGHT2);
}

/// LUZ: AUMENTAR - ATENUAR -------------------------------

void atenuaLuz(void)
{
    if (kc < 10.0)
    {
        kc = kc + 1.0;
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, kc);
        cout << "Atenuar: " << kc << endl;
    }
}

void aumentaLuz(void)
{
    if (kc > 1.0)
    {
        kc = kc - 1.0;
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, kc);
        cout << "Aumentar: " << kc << endl;
    }
}

/// SPOT: AUMENTAR - ATENUAR -----------------------------

void reducirSpot(void)
{
    if (cutoff > 0.0)
    {
        cutoff = cutoff - 15.0;
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
        cout << "Reducir SPOT: " << cutoff << endl;
    }
}

void ampliarSpot(void)
{
    if (cutoff < 180.0)
    {
        cutoff = cutoff + 15.0;
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
        cout << "Ampliar SPOT: " << cutoff << endl;
    }
}

/// FUNCIONES COMUNES ----------------------------------

void init(void)
{

    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void display(void)
{
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            glPushMatrix();
            glTranslatef((float)i * 3.0, (float)j * 3.0, 0.0);
            glutSolidSphere(1.0, 16, 16);
            glPopMatrix();
        }
    }
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (h == 0)
        gluPerspective(60, (float)w, 1.0, 20.0);
    else
        gluPerspective(60, (float)w / (float)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: /* tecla de Escape */
        exit(0);
        break;
    case 'f':
        glutFullScreen();
        break;
    case 'w':
        glutReshapeWindow(250, 250);
        break;
    case 'l':
        luzAzulOn();
        break;
    case 'L':
        luzAzulOff();
        break;
    case 's':
        luzSpotOn();
        break;
    case 'S':
        luzSpotOff();
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void especial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        atenuaLuz();
        break;
    case GLUT_KEY_UP:
        aumentaLuz();
        break;
    case GLUT_KEY_LEFT:
        reducirSpot();
        break;
    case GLUT_KEY_RIGHT:
        ampliarSpot();
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(450, 450);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejemplo de luz");

    init();

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(especial);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
