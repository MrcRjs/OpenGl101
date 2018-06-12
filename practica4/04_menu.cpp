/*
    PROGRAMA:       "Manejo de Men�s y Sub-men�s GLUT"

    AUTOR:          Juan Carlos Conde Ram�rez

    DESCRIPCI�N:    Programa que dibuja 3 cuadrados a partir de uno principal, cada uno de diferente color.
                    Hace uso de las funciones de GLUT para definir la acci�n de los eventos de un MEN�
                    principal que tiene 2 opciones: "Color de Fondo" y "Color de Figuras". De estas dos
                    opciones se desprenden dos SUBMEN�S con 2 y 6 opciones, respectivamente, para cambiar
                    el color.
*/

#include <GLUT/glut.h>

int sky=0;
int fig1=2;
int fig2=4;
int fig3=6;

typedef enum {FONDO0,FONDO1,COLOR2,COLOR3,COLOR4,COLOR5,COLOR6,COLOR7}opcionesMenu;

float colores[8][3] =
{
    { 1.00f, 1.00f, 1.00f}, // 0 - blanco
    { 0.00f, 0.00f, 0.00f}, // 1 - negro
    { 1.00f, 0.00f, 0.00f}, // 2 - rojo
    { 0.50f, 0.26f, 0.12f}, // 3 - rojo claro
    { 0.00f, 1.00f, 0.00f}, // 4 - verde
    { 0.06f, 0.25f, 0.13f}, // 5 - verde oscuro
    { 0.00f, 0.00f, 1.00f}, // 6 - azul
    { 0.85f, 0.95f, 1.00f}, // 7 - azul claro
};

void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void miCuadrado();

void display(void)
{
    glClearColor(colores[sky][0], colores[sky][1], colores[sky][2], 0.0);

	glClear(GL_COLOR_BUFFER_BIT);   // limpia la pantalla

    glPushMatrix();
        glTranslatef(100.0f, 100.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        miCuadrado();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(100.0f, 400.0f, 0.0f);
        glColor3f(colores[fig1][0], colores[fig1][1], colores[fig1][2]);
        miCuadrado();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(400.0f, 400.0f, 0.0f);
        glScalef(1.5f, 1.5f, 1.0f);
        glColor3f(colores[fig2][0], colores[fig2][1], colores[fig2][2]);
        miCuadrado();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(400.0f, 100.0f, 0.0f);
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glColor3f(colores[fig3][0], colores[fig3][1], colores[fig3][2]);
        miCuadrado();
    glPopMatrix();

	glFlush();   // envia toda la salida a la pantalla
}

void miCuadrado()
{
    glBegin(GL_POLYGON);
      glVertex2f(-50.0f, -50.0f);
      glVertex2f( 50.0f, -50.0f);
      glVertex2f( 50.0f, 50.f);
      glVertex2f(-50.0f, 50.0f);
    glEnd();
}

// posicion de matrzi de color
void onMenu(int opcion)
{
	switch(opcion) {
		case FONDO0:
			sky = 0;
			break;
		case FONDO1:
			sky = 1;
			break;
		case COLOR2:
			fig1 = 2;
			break;
		case COLOR3:
			fig1 = 3;
			break;
        case COLOR4:
			fig2 = 4;
			break;
		case COLOR5:
			fig2 = 5;
			break;
        case COLOR6:
			fig3 = 7;
			break;
		case COLOR7:
			fig3 = 6;
			break;
		break;
	}
	glutPostRedisplay();
}

// creacion de menu y submenus
void creacionMenu(void)
{
	int menuSky, menuFig, menuMain;

	menuFig = glutCreateMenu(onMenu);
	glutAddMenuEntry("ROJO -> claro", COLOR2);
	glutAddMenuEntry("ROJO -> oscuro", COLOR3);
    glutAddMenuEntry("VERDE -> claro", COLOR4);
	glutAddMenuEntry("VERDE -> oscuro", COLOR5);
	glutAddMenuEntry("AZUL -> claro", COLOR6);
	glutAddMenuEntry("AZUL -> oscuro", COLOR7);

	menuSky = glutCreateMenu(onMenu);
	glutAddMenuEntry("Blanco", FONDO0);
	glutAddMenuEntry("Negro", FONDO1);

	menuMain = glutCreateMenu(onMenu);
	glutAddSubMenu("Color de Fondo", menuSky);
	glutAddSubMenu("Color de Figuras", menuFig);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Manejo de Menús y Sub-menús GLUT");

    init();
    creacionMenu();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
}

