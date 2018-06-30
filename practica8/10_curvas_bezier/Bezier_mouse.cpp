#include <GLUT/glut.h>
#define ANCHO 800
#define ALTO 600

GLint numPoints = 4, cnt = 0;
GLint pnt[4] = {0};
GLfloat ctrlPoints[4][3] = {0};

void DrawPoints(void)
{
	int i;
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	for (i = 0; i < numPoints; i++)
		if (pnt[i] == 1)
			glVertex2fv(ctrlPoints[i]);
	glEnd();
}

void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glMap1f(GL_MAP1_VERTEX_3,   // tipo de datos generados
			0.0f,				// rango inferior de u
			100.0f,				// rango superior de u
			3,					// distancia entre �los puntos en los datos
			numPoints,			// numero de puntos de control
			&ctrlPoints[0][0]); // arreglo de los puntos de control

	// activa el evaluador
	glEnable(GL_MAP1_VERTEX_3);
	if (cnt == 0)
	{
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 100; i++)
			glEvalCoord1f((GLfloat)i);
		glEnd();
	}
	DrawPoints();
	glutSwapBuffers();
}

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0.7, 0.7, 0.8, 0.0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 10.0f, 0.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ControlMouse(int boton, int edo, int x, int y)
{
	if ((boton == GLUT_LEFT_BUTTON) && (edo == GLUT_DOWN))
	{
		cnt++;
		switch (cnt)
		{
		case 1: //Punto inicial
			pnt[0] = pnt[1] = pnt[2] = pnt[3] = 0;
			ctrlPoints[0][0] = (float)x / (ANCHO / 10);
			ctrlPoints[0][1] = 10 - ((float)y / (ALTO / 10));
			pnt[0] = 1;
			break;
		case 2: //Punto final
			ctrlPoints[3][0] = (float)x / (ANCHO / 10);
			ctrlPoints[3][1] = 10 - ((float)y / (ALTO / 10));
			pnt[3] = 1;
			break;
		case 3: //Primer punto de control
			ctrlPoints[1][0] = (float)x / (ANCHO / 10);
			ctrlPoints[1][1] = 10 - ((float)y / (ALTO / 10));
			pnt[1] = 1;
			break;
		case 4: //Segundo punto de control
			ctrlPoints[2][0] = (float)x / (ANCHO / 10);
			ctrlPoints[2][1] = 10 - ((float)y / (ALTO / 10));
			pnt[2] = 1;
			cnt = 0;
			break;
		}
	}
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ANCHO, ALTO);
	glutCreateWindow("Curvas de Bezier con clicks");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(ControlMouse);
	init();
	glutMainLoop();

	return 0;
}
