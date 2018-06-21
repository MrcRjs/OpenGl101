//JUAN CARLOS CONDE RAMÍREZ
//OBJETOS 3D - ILUMINACION
#include <stdio.h>
#include <GLUT/glut.h>

using namespace std;

#include "../utils/normalizer.h"

Normalizer NZ;

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

void luzAmbiental(void)
{
	GLfloat l_difusa[] = {0.22f, 0.17f, 0.12f, 0.0f};
	GLfloat l_especular[] = {0.22f, 0.17f, 0.12f, 0.0f};
	GLfloat l_posicion[] = {0.0, 0.0, 5.0, 1.0};
	GLfloat l_a_color[] = {0.22f, 0.17f, 0.12f, 0.0f};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	// glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
	glEnable(GL_LIGHT0);
	glutPostRedisplay();
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

void drawCube()
{
	// Frente
	glBegin(GL_QUADS);
	//glNormal3d(0.0f, 0.0f, 1.0f);
	float vf[3][3] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f};

	glNormal3fv(NZ.calculateNormal(vf[0], vf[1], vf[2]));
	glVertex3d(-0.5f, -0.5f, 0.5f);
	glVertex3d(0.5f, -0.5f, 0.5f);
	glVertex3d(0.5f, 0.5f, 0.5f);
	glVertex3d(-0.5f, 0.5f, 0.5f);
	glEnd();
	// Posterior
	glBegin(GL_QUADS);
	glNormal3d(0.0f, 0.0f, -1.0f);
	glVertex3d(-0.5f, 0.5f, -0.5f);
	glVertex3d(0.5f, 0.5f, -0.5f);
	glVertex3d(0.5f, -0.5f, -0.5f);
	glVertex3d(-0.5f, -0.5f, -0.5f);
	glEnd();

	// Derecha
	glBegin(GL_QUADS);
	glNormal3d(1.0f, 0.0f, 0.0f);
	glVertex3d(0.5f, -0.5f, 0.5f);
	glVertex3d(0.5f, -0.5f, -0.5f);
	glVertex3d(0.5f, 0.5f, -0.5f);
	glVertex3d(0.5f, 0.5f, 0.5f);
	glEnd();
	// Izquierda
	glBegin(GL_QUADS);
	glNormal3d(-1.0f, 0.0f, 0.0f);
	glVertex3d(-0.5f, 0.5f, 0.5f);
	glVertex3d(-0.5f, 0.5f, -0.5f);
	glVertex3d(-0.5f, -0.5f, -0.5f);
	glVertex3d(-0.5f, -0.5f, 0.5f);
	glEnd();

	// Superior
	glBegin(GL_QUADS);
	glNormal3d(0.0f, 1.0f, 0.0f);
	glVertex3d(-0.5f, 0.5f, 0.5f);
	glVertex3d(0.5f, 0.5f, 0.5f);
	glVertex3d(0.5f, 0.5f, -0.5f);
	glVertex3d(-0.5f, 0.5f, -0.5f);
	glEnd();
	// Inferior
	glBegin(GL_QUADS);
	glNormal3d(0.0f, -1.0f, 0.0f);
	glVertex3d(-0.5f, -0.5f, -0.5f);
	glVertex3d(0.5f, -0.5f, -0.5f);
	glVertex3d(0.5f, -0.5f, 0.5f);
	glVertex3d(-0.5f, -0.5f, 0.5f);
	glEnd();
}

void drawChair()
{
	//pata trasera izquierda
	glPushMatrix();
	glTranslatef(-0.5, -0.5, -0.5);
	glScalef(0.2, 1.0, 0.2);
	drawCube();
	glPopMatrix();
	//pata trasera derecha
	glPushMatrix();
	glTranslatef(0.5, -0.5, -0.5);
	glScalef(0.2, 1.0, 0.2);
	drawCube();
	glPopMatrix();

	//pata delantera izquierda
	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0.5);
	glScalef(0.2, 1.0, 0.2);
	drawCube();
	glPopMatrix();

	//pata delantera derecha
	glPushMatrix();
	glTranslatef(0.5, -0.5, 0.5);
	glScalef(0.2, 1.0, 0.2);
	drawCube();
	glPopMatrix();

	// Asiento
	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.0);
	glScalef(1.2, 0.2, 1.2);
	drawCube();
	glPopMatrix();

	// Respaldo
	glPushMatrix();
	glTranslatef(0.0, 0.7, -0.5);
	glScalef(1.2, 1.0, 0.2);
	drawCube();
	glPopMatrix();
}

void init(void)
{
	luzAmbiental();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 1.0f, 5.0f, 20.0f);
	gluLookAt(0.0f, 0.0f, 10.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);

	luzAmbiental();

	glEnable(GL_CULL_FACE);

	glLoadIdentity();
	glPushMatrix();

	glTranslatef(xpos, ypos, 0);
	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
	drawChair();

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
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Silla Primitiva 🥨");
	glutDisplayFunc(display);
	glutSpecialFunc(ControlTeclado);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	init();
	glutMainLoop();

	return 0;
}