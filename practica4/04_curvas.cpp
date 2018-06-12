#define _USE_MATH_DEFINES
#include <GLUT/glut.h>
#include <iostream>

#include <stdlib.h>
#include <math.h>

using namespace std;


struct screenPt
{
	GLint x;
	GLint y;
};

typedef enum{limacon = 1, cardioid, threeLeaf, fourLeaf, spiral} curveName;

//-->
typedef enum {F1,F2,F3,F4,F5,C1,C2,C3,C4,C5,C6,C7,C8,CF1,CF2}
opcionesMenu;

GLint curveNum;

int color = 1;
int colorf = 7;

float colores[8][3]=
	{
		{0.0,0.0,0.0}, //negro
		{1.0,0.0,0.0}, //rojo
		{0.0,1.0,0.0}, //verde
		{1.0,1.0,0.0}, //amarillo
		{0.0,0.0,1.0}, //azul
		{1.0,0.0,1.0}, //magenta
		{0.0,1.0,1.0}, //cian
		{1.0,1.0,1.0}  //blanco
	};
//<--

// Tama�o inicial de la ventana
GLsizei winWidth = 600, winHeight = 600;

void init(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment(screenPt pt1, screenPt pt2)
{
	glBegin(GL_LINES);
	   glVertex2i(pt1.x, pt1.y);
       glVertex2i(pt2.x, pt2.y);
    glEnd();
}

void drawCurve(GLint curveNum)
{
	// El lima�on de Pascal es una modificaci�n de la ec. del c�rculo
	// con radio que varia como r=a * cos(theta) + b, donde a y b son constantes.
	// La cardioide es una lima�on con a=b.
	// Las curvas de tres y cuatro hojas son generadas cuando r=a*cos(n*theta),
	// con n=3 y n=4 respectivamente. Una espiral es dibujada cuando r es un
	// m�ltiplo de theta.

	const GLdouble twoPi = 6.283185;
	const GLint a = 175, b = 60;

	GLfloat r, theta, dtheta = 1.0/float(a);
	GLint x0 = 200, y0 = 250;
	screenPt curvePt[2];

	glColor3f(colores[color][0], colores[color][1], colores[color][2]);

	curvePt[0].x = x0;
    curvePt[0].y = y0;

	switch (curveNum)
	{
	    case limacon:   curvePt[0].x += a + b;
			break;
	    case cardioid:   curvePt[0].x += a + a;
			break;
        case threeLeaf: curvePt[0].x += a;
			break;
		case fourLeaf:  curvePt[0].x += a;
			break;
        case spiral:
			break;
        default:
			break;
    }

	theta = dtheta;

	while (theta < twoPi)
	{
		switch (curveNum)
		{
		    case limacon:
				r = a*cos(theta) + b;	break;
			case cardioid:
				r = a*(1 + cos(theta));	break;
			case threeLeaf:
				r = a*cos(3*theta);		break;
			case fourLeaf:
				r = a*cos(2*theta);		break;
			case spiral:
				r = (a/6.0)*theta;		break;
			default:
										break;
		}

		curvePt[1].x = x0 + r*cos(theta);
        curvePt[1].y = y0 + r*sin(theta);
        lineSegment(curvePt[0], curvePt[1]);

        curvePt[0].x = curvePt[1].x;
		curvePt[0].y = curvePt[1].y;
		theta +=dtheta;
	}
}

void winReshapeFcn(int newWidth, int newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble) newWidth, 0.0, (GLdouble) newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

void onMenu(int opcion) // posicion de matrzi de color
{
	switch(opcion) {
		case F1:
			curveNum = 1;
			break;
		case F2:
			curveNum = 2;
			break;
		case F3:
			curveNum = 3;
			break;
		case F4:
			curveNum = 4;
			break;
		case F5:
			curveNum = 5;
			break;
		case C1:
			color = 0;
			break;
		case C2:
			color = 1;
			break;
		case C3:
			color = 2;
			break;
		case C4:
			color = 3;
			break;
		case C5:
			color = 4;
			break;
		case C6:
			color = 5;
			break;
		case C7:
			color = 6;
			break;
		case C8:
			color = 7;
			break;
		case CF1:
			colorf = 0;
			break;
		case CF2:
			colorf = 7;
			break;
	}
	glutPostRedisplay();
}

void creacionMenu(void) // creacion de menu y submenus
{
	int menuColor, menuFondo, menuFigura, menuMain;

	menuColor = glutCreateMenu(onMenu);
	glutAddMenuEntry("Negro", C1);
	glutAddMenuEntry("Rojo", C2);
	glutAddMenuEntry("Verde", C3);
	glutAddMenuEntry("Amarillo", C4);
	glutAddMenuEntry("Azul", C5);
	glutAddMenuEntry("Magenta", C6);
	glutAddMenuEntry("Cyan", C7);
	glutAddMenuEntry("Blanco", C8);

	menuFondo = glutCreateMenu(onMenu);
	glutAddMenuEntry("Negro", CF1);
	glutAddMenuEntry("Blanco", CF2);

	menuFigura = glutCreateMenu(onMenu);
	glutAddMenuEntry("Limacon", F1);
	glutAddMenuEntry("Cardinoide", F2);
	glutAddMenuEntry("Tres Hojas", F3);
	glutAddMenuEntry("Cuatro Hojas", F4);
	glutAddMenuEntry("Espiral", F5);


	menuMain = glutCreateMenu(onMenu);
	glutAddSubMenu("Figura", menuFigura);
	glutAddSubMenu("Color Linea", menuColor);
	glutAddSubMenu("Color Fondo", menuFondo);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void displayFcn(void)
{
	glClearColor(colores[colorf][0], colores[colorf][1], colores[colorf][2], 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	drawCurve(curveNum);

	glFlush();

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Varias curvas");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);

    //CREACION EN UNA SOLA FUNCI�N DEL MEN�
	creacionMenu();

    glutMainLoop();

    return 0;
}
