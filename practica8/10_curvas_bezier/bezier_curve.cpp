// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <stdlib.h>
#include <math.h>

// Valores para el tamaño de la ventana de despliegue
GLsizei winWidth = 600, winHeight = 600;

// Fija el tamaño de las coordenadas del mundo de la ventana de recorte
GLfloat xwcMin = -50.0, xwcMax = 50.0;
GLfloat ywcMin = -50.0, ywcMax = 50.0;

class wcPt3D {
public:
    GLfloat x, y, z;
};

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void plotPoint(wcPt3D bezCurvePt) {
    glBegin(GL_POINTS);
    glVertex2f(bezCurvePt.x, bezCurvePt.y);
    glEnd();
}

// calcula los coeficientes binomiales C para un valor dado de n
void binomialCoeffs(GLint n, GLint *C) {
    GLint k, j;

    for (k = 0; k <= n; k++) {
        // calcula n!/k!(n-k)!
        C[k] = 1;
        for (j = n; j >= k + 1; j--)
            C[k] *= j;
        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *C) {
    GLint k, n = nCtrlPts - 1;
    GLfloat bezBlendFcn;

    bezPt->x = bezPt->y = bezPt->z = 0.0;

    // calcula las funciones de combinacion y combina los puntos de control
    for (k = 0; k < nCtrlPts; k++) {
        bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}

void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts) {
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint *C, k;

    // asigna el espacio para los coeficientes binomiales
    C = new GLint[nCtrlPts];

    binomialCoeffs(nCtrlPts - 1, C);
    for (k = 0; k <= nBezCurvePts; k++) {
        u = GLfloat(k) / GLfloat(nBezCurvePts);
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        plotPoint(bezCurvePt);
    }
    delete[] C;
}

void displayFcn(void) {
    // Fija el número de los puntos de control y el número de las posiciones
    // de la curva que se trazarán a lo largo de la curva de Bezier

    GLint nCtrlPts = 4, nBezCurvePts = 1000;

    wcPt3D ctrlPts[4] = {{-40.0, -40.0,  0.0},
                         {-10.0, 200.0,  0.0},
                         {10.0,  -200.0, 0.0},
                         {40.0,  40.0,   0.0}};

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    glColor3f(1.0, 0.0, 0.0); // punto color rojo

    bezier(ctrlPts, nCtrlPts, nBezCurvePts);

    glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glViewport(0, 0, newHeight, newHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Curva de Bezier");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();

    return 0;
}
