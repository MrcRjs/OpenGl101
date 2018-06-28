//JUAN CARLOS CONDE RAMÍREZ
//OBJETOS 3D - ILUMINACION
#include <GLUT/glut.h>
#include <stdio.h>

//Matriz de colores
float colores[9][3] =
	{
		{1.0, 1.0, 1.0}, //0 blanco
		{1.0, 0.0, 0.0}, //1 rojo
		{0.0, 1.0, 0.0}, //2 verde
		{0.0, 0.0, 1.0}, //3 azul
		{1.0, 1.0, 0.0}, //4 amarillo
		{1.0, 0.0, 1.0}, //5 magneta
		{0.0, 1.0, 1.0}, //6 cian
		{0.5, 0.5, 0.5}, //7 gris
		{0.0, 0.0, 0.0}, //8 negro
};
GLdouble vistas[6][9] = {
	//frontal
	{5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	//li
	{0.0f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	//ld
	{0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	//inferior
	{0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	//superior
	{0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	//trasera
	{-5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f}};
int color = 2;	// color de FIGURA
int colorf = 0;   // color de FONDO
int colorl = 3;   // color de LUZ
				  //int colordif= 2; //color difuso de ambiental (verde)
int coloresp = 3; //color especular ambiental
//variables globales para la rotacion
float alpha, beta;
int x0, y0;
int opc = 0;
GLenum modo = GL_FILL;

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
	F8
} opcionMenu;

void luzAmbiental(void)
{

	GLfloat l_difusa[] = {colores[color][0], colores[color][1], colores[color][2], 1.0f};
	GLfloat l_especular[] = {colores[coloresp][0], colores[coloresp][1], colores[coloresp][2], 1.0f};
	GLfloat l_posicion[] = {5.0, 5.0, 0.0, 1.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
	glEnable(GL_LIGHT0);
}

void luzUno(void)
{
	GLfloat l_difusa[] = {colores[3][0], colores[3][1], colores[3][2], 0.0f};
	GLfloat l_especular[] = {colores[1][0], colores[1][1], colores[1][2], 0.0f};
	GLfloat l_posicion[] = {5.0f, 5.0f,0.0f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_especular);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, l_especular);
	glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
	glEnable (GL_LIGHT1);
}

void init(void)
{
	//luzUno();
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void display(void)
{

	glClearColor(colores[colorf][0], colores[colorf][1], colores[colorf][2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	luzUno();
	//gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 5.0f);
	//gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);

	gluLookAt(vistas[opc][0], vistas[opc][1], vistas[opc][2], vistas[opc][3],
			  vistas[opc][4], vistas[opc][5], vistas[opc][6], vistas[opc][7], vistas[opc][8]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(xpos, ypos, 0);

	if (opc != 9)
		glScalef(inc, inc, inc);
	else
		glScalef(inc - 0.15, inc - 0.15, inc - 0.15);

	//glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	//glRotatef(beta, 0.0f, 1.0f, 0.0f);

	glColor3f(0.61, 0.66, 0.77);
	//glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, modo);
	glutSolidTeapot(1);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void perspectiva(void)
{

	glClearColor(colores[colorf][0], colores[colorf][1], colores[colorf][2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	luzAmbiental();

	//gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	//glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 5.0f);
	gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);

	gluLookAt(vistas[opc][0], vistas[opc][1], vistas[opc][2], vistas[opc][3],
			  vistas[opc][4], vistas[opc][5], vistas[opc][6], vistas[opc][7], vistas[opc][8]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(xpos, ypos, 0);

	if (opc != 9)
		glScalef(inc, inc, inc);
	else
		glScalef(inc - 0.15, inc - 0.15, inc - 0.15);

	//glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	//glRotatef(beta, 0.0f, 1.0f, 0.0f);

	glColor3f(0.61, 0.66, 0.77);
	//glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, modo);
	glutSolidTeapot(1);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

//Accion del mouse
void onMouse(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN))
	{
		x0 = x;
		y0 = y;
	}
}

//Incremento o decremente de los angulos de rotacion
void onMotion(int x, int y)
{
	alpha = (alpha + (y - y0));
	beta = (beta + (x - x0));
	x0 = x;
	y0 = y;
	glutPostRedisplay();
}

void menuFiguras(int opcion)
{
	switch (opcion)
	{
	case F1:
		opc = 0;
		break;
	case F2:
		opc = 1;
		break;
	case F3:
		opc = 2;
		break;
	case F4:
		opc = 3;
		break;
	case F5:
		opc = 4;
		break;
	case F6:
		opc = 5;
		break;
	case F7:
		modo = GL_LINE;
		break;
	case F8:
		modo = GL_FILL;
		break;
	}
	glutPostRedisplay();
}

//Creacion de menu y submenus
void creacionMenu(void)
{
	int menuPerspectiva, menuVista;
	int on, off;

	menuVista = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Vista Rejilla", F7);
	glutAddMenuEntry("Vista Relleno", F8);
	//----------------------------------------------------------

	// NIVEL 2 DE SUB-MENU PARA TIPO DE FIGURA
	menuPerspectiva = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Frontal", F1);
	glutAddMenuEntry("Trasera", F6);
	glutAddMenuEntry("Lateral Derecha", F2);
	glutAddMenuEntry("Lateral Izquierda", F3);
	glutAddMenuEntry("Superior", F4);
	glutAddMenuEntry("Inferior", F5);
	glutAddSubMenu("Tipo de vista", menuVista);


	/*
        AQUI VAN LAS OPCIONES
    */

	//---------------------------------------------------------
	// glutAddSubMenu("Desactivar Luces: ", off);
	/*
        AQUI VAN LOS SUB-MENUS DE NIVEL 2
    */

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Ortogonal 🍪");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	creacionMenu();

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Perspectiva 🥃");
	init();
	glutDisplayFunc(perspectiva);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	creacionMenu();
	glutMainLoop();

	return 0;
}
