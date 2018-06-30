#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

// Valores para el tamaño de la ventana de despliegue
GLsizei winWidth = 600, winHeight = 600;

// Fija el tamaño de las coordenadas del mundo de la ventana de recorte
GLfloat xwcMin = -1.0, xwcMax = 11.0;
GLfloat ywcMin = -1.50, ywcMax = 13.5;

class wcPt3D
{
  public:
	GLfloat x, y, z;
};

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void plotPoint(wcPt3D bezCurvePt)
{
	glBegin(GL_POINTS);
	glVertex2f(bezCurvePt.x, bezCurvePt.y);
	glEnd();
}

// calcula los coeficientes binomiales C para un valor dado de n
void binomialCoeffs(GLint n, GLint *C)
{
	GLint k, j;

	for (k = 0; k <= n; k++)
	{
		// calcula n!/k!(n-k)!
		C[k] = 1;
		for (j = n; j >= k + 1; j--)
			C[k] *= j;
		for (j = n - k; j >= 2; j--)
			C[k] /= j;
	}
}

void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *C)
{
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;

	bezPt->x = bezPt->y = bezPt->z = 0.0;

	// calcula las funciones de combinacion y combina los puntos de control
	for (k = 0; k < nCtrlPts; k++)
	{
		bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
		bezPt->x += ctrlPts[k].x * bezBlendFcn;
		bezPt->y += ctrlPts[k].y * bezBlendFcn;
		bezPt->z += ctrlPts[k].z * bezBlendFcn;
	}
}

void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint *C, k;

	// asigna el espacio para los coeficientes binomiales
	C = new GLint[nCtrlPts];

	binomialCoeffs(nCtrlPts - 1, C);
	for (k = 0; k <= nBezCurvePts; k++)
	{
		u = GLfloat(k) / GLfloat(nBezCurvePts);
		computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
		plotPoint(bezCurvePt);
	}
	delete[] C;
}

void displayFcn(void)
{
	// Fija el n�mero de los puntos de control y el n�mero de las posiciones
	// de la curva que se trazar�n a lo largo de la curva de Bezier

	GLint nCtrlPts = 4, nBezCurvePts = 1000;

	wcPt3D c01[4] = {{2.8, 0.7}, {3.05, 0}, {4.675, 0}, {5.3, 0.7}}; //BOCA
	wcPt3D c02[4] = {{5.3, 0.7}, {6, 1.35}, {6, 2.65}, {5.3, 3.3}};
	wcPt3D c03[4] = {{5.3, 3.3}, {4.55, 4.25}, {3.05, 4}, {2.3, 4}};
	wcPt3D c04[4] = {{2.3, 4}, {1.2, 3.7}, {0.8, 3}, {1.2, 2.2}};
	wcPt3D c05[4] = {{1.2, 2.2}, {0.9, 2.1}, {0.8, 1.4}, {1.3, 1.3}};
	wcPt3D c06[4] = {{1.3, 1.3}, {1.5, 1.27}, {1.9, 1.23}, {2.1, 1.2}};
	wcPt3D c07[4] = {{2.1, 1.2}, {1.8, 0.8}, {2.4, 0.4}, {2.8, 0.7}}; //BOCA

	wcPt3D c08[4] = {{1.62, 3.7}, {1.62, 4.2}, {1.65, 4.6}, {1.7, 5}};
	wcPt3D c09[4] = {{1.7, 5}, {1, 5.3}, {1, 6.6}, {1.4, 7}}; //OJO
	wcPt3D c10[4] = {{1.4, 7}, {1, 7.2}, {1.2, 7.8}, {1.7, 7.8}};
	wcPt3D c11[4] = {{1.7, 7.8}, {2.3, 13}, {7.65, 13}, {7.9, 7.8}}; //CABEZA

	wcPt3D c12[4] = {{7.9, 7.8}, {7.7, 6.2}, {7.45, 5.5}, {7.3, 4.5}}; //OREJA
	wcPt3D c13[4] = {{6.9, 2.9}, {6.9, 2.2}, {7.0, 1.3}, {7, 0.6}};

	wcPt3D c14[4] = {{1.4, 7}, {2, 7.8}, {3.3, 7.6}, {3.5, 6.6}}; //OJOS
	wcPt3D c15[4] = {{4.7, 4.65}, {2.9, 4.5}, {2.9, 7.40}, {4.7, 7.25}};
	wcPt3D c16[4] = {{4.4, 4.65}, {6.2, 4.5}, {6.2, 7.40}, {4.4, 7.25}};
	wcPt3D c17[4] = {{2.7, 5.2}, {3.1, 5.2}, {3.3, 5.2}, {3.47, 5.35}}; //NARIZ
	wcPt3D c18[4] = {{2.7, 5.2}, {2, 5.2}, {2, 4}, {2.7, 4}};
	wcPt3D c19[4] = {{1.7, 5}, {1.85, 4.9}, {2.05, 4.9}, {2.3, 5}};

	wcPt3D c20[4] = {{6.9, 4.3}, {7.1, 4.55}, {7.5, 4.55}, {7.7, 4.3}}; //OREJA
	wcPt3D c21[4] = {{6.7, 3.1}, {6.8, 2.8}, {7.2, 2.8}, {7.3, 2.9}};
	wcPt3D c22[4] = {{7.7, 4.3}, {8, 3.9}, {7.7, 3}, {7.3, 2.9}};
	wcPt3D c23[4] = {{6.9, 3.4}, {6.9, 3.8}, {7.25, 4.2}, {7.4, 3.9}}; //OREJA

	wcPt3D c24[4] = {{4.3, 11.6}, {4.8, 12.5}, {6.4, 13}, {6.3, 10.5}}; //PELO
	wcPt3D c25[4] = {{5.3, 11.7}, {5.8, 12.5}, {7.5, 13}, {7.1, 10}};   //ARRIBA

	wcPt3D c26[4] = {{6.4, 4.3}, {7.2, 7}, {7.2, 7}, {7.35, 4.65}};	//PELO
	wcPt3D c27[4] = {{7.35, 4.65}, {8.1, 6.8}, {8.1, 6.8}, {8, 4.85}}; //COSTADO

	//wcPt3D c2 [4] = {{},{},{},{}};
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glColor3f(0.0, 0.0, 0.0); // punto color rojo

	bezier(c01, nCtrlPts, nBezCurvePts);
	bezier(c02, nCtrlPts, nBezCurvePts);
	bezier(c03, nCtrlPts, nBezCurvePts);
	bezier(c04, nCtrlPts, nBezCurvePts);
	bezier(c05, nCtrlPts, nBezCurvePts);
	bezier(c06, nCtrlPts, nBezCurvePts);
	bezier(c07, nCtrlPts, nBezCurvePts);
	bezier(c08, nCtrlPts, nBezCurvePts);
	bezier(c09, nCtrlPts, nBezCurvePts);
	bezier(c10, nCtrlPts, nBezCurvePts);
	bezier(c11, nCtrlPts, nBezCurvePts);
	bezier(c12, nCtrlPts, nBezCurvePts);
	bezier(c13, nCtrlPts, nBezCurvePts);
	bezier(c14, nCtrlPts, nBezCurvePts);
	bezier(c15, nCtrlPts, nBezCurvePts);
	bezier(c16, nCtrlPts, nBezCurvePts);
	bezier(c17, nCtrlPts, nBezCurvePts);
	bezier(c18, nCtrlPts, nBezCurvePts);
	bezier(c19, nCtrlPts, nBezCurvePts);
	bezier(c20, nCtrlPts, nBezCurvePts);
	bezier(c21, nCtrlPts, nBezCurvePts);
	bezier(c22, nCtrlPts, nBezCurvePts);
	bezier(c23, nCtrlPts, nBezCurvePts);
	bezier(c24, nCtrlPts, nBezCurvePts);
	bezier(c25, nCtrlPts, nBezCurvePts);
	bezier(c26, nCtrlPts, nBezCurvePts);
	bezier(c27, nCtrlPts, nBezCurvePts);

	glPushMatrix(); ///BOCA
	glTranslatef(2.45, 1, 0.0);
	glScalef(1, 1.2, 1);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.15, 30, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 6.8, 0.0);
	glScalef(1, 1.10, 1);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.15, 30, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.8, 6.7, 0.0);
	glScalef(1, 1.15, 1);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.15, 30, 20);
	glPopMatrix();

	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newHeight, newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Homero Bezier");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();

	return 0;
}
