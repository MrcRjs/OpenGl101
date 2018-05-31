#define _USE_MATH_DEFINES
#include <GLUT/glut.h>
#include <math.h>
// VARIABLES GLOBALES -----------------------------------------------------------------------------------------------

// Tamaño inicial de la ventana de despliegue
GLsizei winWidth=900, winHeight=600;

// rango para las coordenadas de visión del mundo
// GLfloat xwcMin=0.0, xwcMax=1200.0;
// GLfloat ywcMin=0.0, ywcMax=900.0;

GLfloat xwcMin = 0.0, xwcMax = 900.0;
GLfloat ywcMin = 0.0, ywcMax = 600.0;

//se renombra a una matriz de tipo flotante de tamaño 3
typedef GLfloat Matrix3x3 [3][3];

//Se decalara un objeto del tipo "Matrix3x3"
Matrix3x3 matComposite;

//se define la constante Pi
const GLdouble pi=3.14159;

//Se define un objeto Punto (x, y) de tipo flotante
class wcPt2D
{
	public:
		GLfloat x,y;
};

// OPERACIONES CON LA MATRIZ DE TRANSFOMACIÓN _----------------------------------------------------------------------

// Construccion de la MATRIZ IDENTIDAD 3x3
void matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
	GLint row,col;

	for(row=0;row<3;row++)
		for (col=0;col<3;col++)
			matIdent3x3[row][col]= (row==col);
}

// preMULTIPLICA la matriz m1 por la matriz m2, almacena el resultado en m2
void matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	GLint row,col;
	Matrix3x3 matTemp;

	for(row=0;row<3;row++)
		for (col=0;col<3;col++)
			matTemp [row][col]= m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];

    for(row=0;row<3;row++)
		for (col=0;col<3;col++)
			m2 [row][col]= matTemp[row][col];
}

//TRASLACION
void translate2D(GLfloat tx, GLfloat ty)
{
	Matrix3x3 matTrans1;

	// inicializa la matriz de translacions a la matriz identidad
	matrix3x3SetIdentity(matTrans1);

	matTrans1[0][2]=tx;
    matTrans1[1][2]=ty;

	// concatena  matTrans1 con la matriz compuesta
	matrix3x3PreMultiply(matTrans1, matComposite);
}

//ROTACION
void rotate2D(wcPt2D pivotPt, GLfloat theta)
{
	Matrix3x3 matRot;

	// inicializa la matriz de rotacion a la matriz identidad
	matrix3x3SetIdentity(matRot);

	matRot [0][0]= cos(theta);
    matRot [0][1]= -sin(theta);
	matRot [0][2]= pivotPt.x*(1-cos(theta)) + pivotPt.y*sin(theta);
    matRot [1][0]= sin(theta);
	matRot [1][1]= cos(theta);
	matRot [1][2]= pivotPt.y*(1-cos(theta)) - pivotPt.x*sin(theta);

	// concatena matRot con la matriz compuesta
	matrix3x3PreMultiply(matRot, matComposite);
}

//ESCALAMIENTO
void scale2D(GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
	Matrix3x3 matScale;

	// inicialliza la matriz de escala a la matriz identidad
	matrix3x3SetIdentity(matScale);

	matScale [0][0] = sx;
    matScale [0][2] = (1-sx)*fixedPt.x;
	matScale [1][1] = sy;
	matScale [1][2] = (1-sy)*fixedPt.y;

	// concatena matScale con la matriz compuesta
	matrix3x3PreMultiply(matScale, matComposite);
}

// usando la matriz compuesta, calcula las coordenadas transformadas
void transformVerts2D(GLint nVerts, wcPt2D * verts)
{
	GLint k;
	GLfloat temp;

	for(k=0; k<nVerts; k++)
	{
		temp=matComposite[0][0]*verts[k].x+matComposite[0][1]*verts[k].y+matComposite[0][2];
		verts[k].y=matComposite[1][0]*verts[k].x+matComposite[1][1]*verts[k].y+matComposite[1][2];
		verts[k].x=temp;
	}
}

// DIBUJADO DE FIGURA(S) GEOMÉTRICA(S) ------------------------------------------------------------------------------

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
}

// CREACION DE LA FIGURA
void triangle(wcPt2D * verts)
{
	GLint k;

	glBegin(GL_TRIANGLES);
	  for(k=0;k<3;k++)
		  glVertex2f(verts[k].x,verts[k].y);
	glEnd();
}

// FUNCIÓN QUE CONFIGURA Y DIBUJA TODO LO QUE SE MUESTRA EN LA VENTANA
//      Aquí se aplican las transformaciones programadas anteriormente
void displayFcn(void)
{
	// define la posicion inicial para el triangulo
	GLint nVerts=3;
	wcPt2D verts[3]={{0.0, 25.0},{200.0, 25.0},{100.0, 150.0}};

	// calcula la posicion del centroide del triangulo
	wcPt2D centroidPt;

	GLint k,xSum=0, ySum=0;

	for(k=0;k<nVerts;k++)
    {
		xSum+=verts[k].x;
        ySum+=verts[k].y;
	}
	centroidPt.x=GLfloat(xSum)/(GLfloat) (nVerts);
    centroidPt.y=GLfloat(ySum)/(GLfloat) (nVerts);

	// parámetros geométricos determinados de la transformación
	wcPt2D pivPt,fixedPt;
	pivPt=centroidPt;
	fixedPt=centroidPt;

	GLfloat tx=0.0, ty=200.0;
	GLfloat sx=0.5, sy=0.5;
	GLdouble theta=pi/2.0;

    // SE COMIENZA CON LA LIMPIEZA DEL BUFFER DE COLOR Y LAS TRANSFORMACIONES
	glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(0.0, 0.0, 1.0);
    glColor3f(0.0, 0.78, 0.39);
    triangle(verts);

	// inicializa la matriz compuesta a la matriz identidad
	matrix3x3SetIdentity(matComposite);

	// construye la matriz compuesta para la secuencia de transformacion
	scale2D(sx,sy,fixedPt);			// primera transformacion: Escala
	rotate2D(pivPt, theta);			// segunda transformacion: Rotacion
	translate2D(tx,ty);				// transformacion final: Translacion

	// construye la matriz compuesta para los vertices del triangulo
	transformVerts2D(nVerts, verts);

    //glColor3f(1.0, 0.0, 0.0);		// toma el color para el triangulo transformado
    glColor3f(0.9, 0.04, 0.5);
    triangle(verts);				// despliega el triangulo rojo transformado

    // Tercer triangulo
    matrix3x3SetIdentity(matComposite);

    // coordenadas originales
    wcPt2D ov[3] = {{0.0, 25.0}, {200.0, 25.0}, {100.0, 150.0}};

    wcPt2D pivT3, fixedPT3;
    pivT3 = centroidPt;
    fixedPT3 = centroidPt;

    GLfloat Sx3 = 1.25, Sy3 = 1.25; // Escalamos 25% mas al original
    GLfloat Tx3 = 300.0, Ty3 = 300.0; // Trasladamos 300 unidades tanto en x como en y
    GLdouble angle = (M_PI / 2); // Rotamos 90

    rotate2D(pivT3, angle);
    translate2D(Tx3, Ty3);
    scale2D(Sx3, Sy3, fixedPT3);

    transformVerts2D(nVerts, ov);

    glColor3f(0.08, 0.39, 0.5); // Color azul aqua personalizado
    triangle(ov);

    // Cuarto triangulo
    matrix3x3SetIdentity(matComposite);

    // coordenadas originales
    wcPt2D ov2[3] = {{0.0, 25.0}, {200.0, 25.0}, {100.0, 150.0}};

    pivT3 = centroidPt;
    fixedPT3 = centroidPt;

    Sx3 = 2.0; // Escalamos al doble en X
    Sy3 = 1.0;   // Mantenemos misma dimension en Y
    Tx3 = 400.0; // Trasladamos 400 en X
    Ty3 = 100.0; // Trasladamos 100 en Y
    angle = -(M_PI/5); // Rotamos -36º 

    scale2D(Sx3, Sy3, fixedPT3);
    rotate2D(pivT3, angle);
    translate2D(Tx3, Ty3);

    transformVerts2D(nVerts, ov2);

    glColor3f(0.78, 0.78, 0.39);
    triangle(ov2);

    glFlush();
}

// FUNCIÓN QUE REAJUSTA EL TAMAÑO DE LA VENTANA
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

// MAIN: ADMINISTRACIÓN DE FUNCIONES PRINCIPALES --------------------------------------------------------------------

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("Secuencia de transformaciones geometricas 2D");
	init();

	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();
}