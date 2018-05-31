#define _USE_MATH_DEFINES
#include <GLUT/glut.h>
#include <math.h>

GLint window_1, window_2;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // DEFINE COLOR DE FONDO
	glColor3f(0.0f, 1.0f, 0.0f);            // DEFINE COLOR DE PUNTOS
	glPointSize(8.0);                       // DEFINE TAMAÑO DE PUNTO
	gluOrtho2D(0.0, 640.0, 0.0, 480.0); 
	    // DEFINE VISTA (ORTOGONAL 2D)
	glPolygonMode(GL_FRONT, GL_LINE);		// GL_POINT, GL_LINE, GL_FILL
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   // LIMPIA PANTALLA

	glBegin(GL_POINTS);             // DIBUJA 3 PUNTOS
		glVertex2i(100, 50);
		glVertex2i(100, 130);
		glVertex2i(150, 130);
    glEnd();

	glBegin(GL_LINES);
		glLineWidth(10.0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2i(100, 50);
		glVertex2i(100, 130);

		glVertex2i(100, 130);
		glVertex2i(150, 130);

		glVertex2i(150, 130);
		glVertex2i(100, 50);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(400, 50);
		glVertex2i(400, 130);
		glVertex2i(300, 130);
		glVertex2i(300, 50);
		glVertex2i(400, 50);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.7f, 0.7f);
		for (float i = 0.f; i < 2 * M_PI; i += M_PI / 20.f)
		{
			glVertex2f(350 + 40 * cos(i), 300 + 40 * sin(i));
		}
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0.9f, 0.5f, 0.0f);
		glVertex2i(100, 150);
		glVertex2i(100, 230);
		glVertex2i(150, 150);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.8f, 0.8f, 0.8f);
		glVertex2i(400, 150);
		glVertex2i(400, 230);
		glVertex2i(450, 230);
		glVertex2i(450, 150);
	glEnd();

	glFlush(); // ENVIA TODA LA SALIDA A LA PANTALLA
}

void displayTriangles(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);

	// Treats each group of four vertices as an independent quadrilateral.
	// Vertices 4 ⁢ n - 3 , 4 ⁢ n - 2 , 4 ⁢ n - 1 , and 4 ⁢ n define quadrilateral n.
	// N 4 quadrilaterals are drawn.
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.6f, 0.9f);
	glVertex2i(100, 200);
	glVertex2i(100, 150);
	glVertex2i(150, 150);
	glVertex2i(150, 200);
	glEnd();

	// Draws a connected group of triangles.
	// One triangle is defined for each vertex presented after the first two vertices.
	// For odd n, vertices n, n + 1 , and n + 2 define triangle n.
	// For even n, vertices n + 1 , n, and n + 2 define triangle n.
	// N - 2 triangles are drawn.
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.7f, 0.0f, 0.5f);
	glVertex2i(200, 150);
	glVertex2i(200, 280);
	glVertex2i(250, 150);
	glEnd();

	// Draws a connected group of triangles.
	// One triangle is defined for each vertex presented after the first two vertices.
	// Vertices 1 , n + 1 , and n + 2 define triangle n.
	// N - 2 triangles are drawn.
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9f, 0.9f, 0.0f);
	glVertex2i(300, 150);
	glVertex2i(350, 150);
	glVertex2i(350, 230);
	glVertex2i(325, 250);
	glEnd();

	// Draws a connected group of quadrilaterals.
	// One quadrilateral is defined for each pair of vertices presented after the first pair.
	// Vertices 2 ⁢ n - 1 , 2 ⁢ n , 2 ⁢ n + 2 , and 2 ⁢ n + 1 define quadrilateral n.
	// N 2 - 1 quadrilaterals are drawn.
	// Note that the order in which vertices are used to construct a quadrilateral from strip data
	// is different from that used with independent data.
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.2f, 0.8f, 0.3f);
	glVertex2i(450, 150);
	glVertex2i(400, 150);
	glVertex2i(450, 200);
	glVertex2i(400, 200);
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 100);
	glutDisplayFunc(display);

	window_1 = glutCreateWindow(argv[0]);
	glutSetWindowTitle("Primer ejemplo 💀");
	init();
	glutDisplayFunc(display);

	window_2 = glutCreateWindow(argv[0]);
	init();
	glutSetWindowTitle("Segundo ejemplo 🍷");
	glutDisplayFunc(displayTriangles);

    glutMainLoop();

	return 0;
}