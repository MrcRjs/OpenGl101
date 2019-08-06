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
GLfloat xwcMin = -1.0, xwcMax = 11.0;
GLfloat ywcMin = -1.50, ywcMax = 13.5;

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

    wcPt3D c15[4] = {{4.7, 5.5},
                     {3.4, 5.35},
                     {3.4, 8.15},
                     {4.7, 8.0}}; //Ojo Completo
    wcPt3D c16[4] = {{4.6, 5.5},
                     {6.1, 5.35},
                     {6.1, 8.15},
                     {4.7, 8.0}};

    wcPt3D c17[4] = {{5.5, 5.9},
                     {6.0, 5.9},
                     {6.5, 5.8},
                     {6.5, 5.5}}; //Nariz
    wcPt3D c18[4] = {{5.4, 5.0},
                     {6.0, 4.8},
                     {6.5, 4.9},
                     {6.5, 5.5}}; //Nariz

    wcPt3D c19[4] = {{5.7, 7.2},
                     {6.0, 8},
                     {7.3, 8},
                     {7.5, 6.9}};   //ojo derecho
    wcPt3D c20[4] = {{6.5, 5.5},
                     {7,   5.5},
                     {7.6, 5.8},
                     {7.5, 6.9}}; //ojo derecho

    wcPt3D c29[4] = {{6.9, 5.55},
                     {6.9, 5.55},
                     {7.5, 4.8},
                     {7.5, 4.8}}; //Boca
    wcPt3D c30[4] = {{3.7, 4.3},
                     {5,   3.5},
                     {7,   3.65},
                     {7.5, 4.83}};        //
    wcPt3D c32[4] = {{3.6, 4.1},
                     {3.6, 4.1},
                     {3.8, 4.5},
                     {3.8, 4.5}};   //

    wcPt3D c31[4] = {{3.3, 4.4},
                     {2.4, 3.95},
                     {2.4, 5.65},
                     {3.3, 5.2}}; //Oreja
    wcPt3D c28[4] = {{2.9, 4.6},
                     {2.6, 4.8},
                     {2.9, 5.1},
                     {3.1, 4.9}};   //Oreja

    wcPt3D c33[4] = {{3.0,  4.3},
                     {3.1,  3.7},
                     {3.05, 3.5},
                     {3.0,  3.}};   //Cuello
    wcPt3D c34[4] = {{2.4, 4.3},
                     {2.4, 4.3},
                     {2.4, 3.6},
                     {2.4, 3.6}};   //Cabello
    wcPt3D c35[4] = {{2.4,  3.6},
                     {2.4,  3.6},
                     {3.05, 3.6},
                     {3.05, 3.6}}; //Cabello
    wcPt3D c36[4] = {{5.7, 3.8},
                     {5.5, 3.5},
                     {5.2, 3.6},
                     {5.2, 3.4}};   //Menton
    wcPt3D c37[4] = {{5.2, 3.4},
                     {5.0, 3.},
                     {5.0, 2.8},
                     {4.9, 2.5}};    //cuello

    //Ojo 2 (Completo)
    wcPt3D c38[4] = {{3.4, 7.2},
                     {3.4, 7.2},
                     {3.7, 7.0},
                     {3.7, 7.0}}; //Pestañas
    wcPt3D c39[4] = {{3.8, 8.0},
                     {3.8, 8.0},
                     {4.0, 7.7},
                     {4.0, 7.7}}; //Pestañas
    wcPt3D c40[4] = {{4.5, 8.3},
                     {4.5, 8.3},
                     {4.6, 8.0},
                     {4.6, 8.0}}; //Pestañas
    wcPt3D c41[4] = {{5.2, 7.9},
                     {5.2, 7.9},
                     {5.3, 8.2},
                     {5.3, 8.2}}; //Pestañas
    //Ojo 2
    wcPt3D c42[4] = {{6.5, 7.75},
                     {6.5, 7.75},
                     {6.6, 8.05},
                     {6.6, 8.05}}; //Pestañas
    wcPt3D c43[4] = {{7.0, 7.6},
                     {7.0, 7.6},
                     {7.2, 7.9},
                     {7.2, 7.9}};     //Pestañas
    wcPt3D c44[4] = {{7.4, 7.2},
                     {7.4, 7.2},
                     {7.7, 7.5},
                     {7.7, 7.5}};     //Pestañas
    wcPt3D c45[4] = {{7.53, 6.7},
                     {7.53, 6.7},
                     {7.87, 6.9},
                     {7.87, 6.9}}; //Pestañas

    wcPt3D c26[4] = {{2.4, 4.3},
                     {1,   4.3},
                     {1,   4.3},
                     {2,   6}};          //PELO
    wcPt3D c27[4] = {{2,   6},
                     {0.7, 7},
                     {0.7, 7},
                     {2,   8}};              //PELO
    wcPt3D c25[4] = {{2,   8},
                     {1.8, 9.5},
                     {1.3, 9.5},
                     {3,   9.8}};          //ARRIBA
    wcPt3D c24[4] = {{3,   9.8},
                     {4,   11.5},
                     {3.5, 11.5},
                     {4.8, 10.5}};  //PELO
    wcPt3D c23[4] = {{4.8, 10.5},
                     {6,   11.5},
                     {5.5, 11.5},
                     {6.6, 10}}; //OREJA
    wcPt3D c22[4] = {{6.6, 10},
                     {8,   9.8},
                     {7.5, 9.8},
                     {7.5, 8.5}};
    wcPt3D c21[4] = {{7.5, 8.5},
                     {8.3, 7.8},
                     {8.3, 7.8},
                     {7.5, 6.9}};

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);
    glColor3f(0.0, 0.0, 0.0); // punto color rojo

    bezier(c20, nCtrlPts, nBezCurvePts);
    bezier(c19, nCtrlPts, nBezCurvePts);
    bezier(c18, nCtrlPts, nBezCurvePts);
    bezier(c17, nCtrlPts, nBezCurvePts);
    bezier(c15, nCtrlPts, nBezCurvePts);
    bezier(c16, nCtrlPts, nBezCurvePts);
    bezier(c21, nCtrlPts, nBezCurvePts);
    bezier(c22, nCtrlPts, nBezCurvePts);
    bezier(c23, nCtrlPts, nBezCurvePts);
    bezier(c24, nCtrlPts, nBezCurvePts);
    bezier(c25, nCtrlPts, nBezCurvePts);
    bezier(c26, nCtrlPts, nBezCurvePts);
    bezier(c27, nCtrlPts, nBezCurvePts);
    bezier(c28, nCtrlPts, nBezCurvePts);
    bezier(c29, nCtrlPts, nBezCurvePts);
    bezier(c30, nCtrlPts, nBezCurvePts);
    bezier(c31, nCtrlPts, nBezCurvePts);
    bezier(c32, nCtrlPts, nBezCurvePts);
    bezier(c33, nCtrlPts, nBezCurvePts);
    bezier(c34, nCtrlPts, nBezCurvePts);
    bezier(c35, nCtrlPts, nBezCurvePts);
    bezier(c36, nCtrlPts, nBezCurvePts);
    bezier(c37, nCtrlPts, nBezCurvePts);
    bezier(c38, nCtrlPts, nBezCurvePts);
    bezier(c39, nCtrlPts, nBezCurvePts);
    bezier(c40, nCtrlPts, nBezCurvePts);
    bezier(c41, nCtrlPts, nBezCurvePts);
    bezier(c42, nCtrlPts, nBezCurvePts);
    bezier(c43, nCtrlPts, nBezCurvePts);
    bezier(c44, nCtrlPts, nBezCurvePts);
    bezier(c45, nCtrlPts, nBezCurvePts);

    glPushMatrix(); ///Ojos
    glTranslatef(4.6, 6.7, 0.0);
    glScalef(1, 1.2, 1);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

    glPushMatrix(); ///Ojos
    glTranslatef(6.5, 6.5, 0.0);
    glScalef(1, 1.2, 1);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

    glPushMatrix(); ///Collar
    glTranslatef(2.8, 2.8, 0.0);
    glScalef(2.0, 2.3, 1.0);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

    glPushMatrix(); ///Collar
    glTranslatef(3.2, 2.4, 0.0);
    glScalef(2.1, 2.3, 1.0);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

    glPushMatrix(); ///Collar
    glTranslatef(3.7, 2.2, 0.0);
    glScalef(2.1, 2.3, 1.0);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

    glPushMatrix(); ///Collar
    glTranslatef(4.2, 2.1, 0.0);
    glScalef(2.1, 2.3, 1.0);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

    glPushMatrix(); ///Collar
    glTranslatef(4.7, 2.1, 0.0);
    glScalef(2.1, 2.3, 1.0);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

    glPushMatrix(); ///Collar
    glTranslatef(5.1, 2.3, 0.0);
    glScalef(2.1, 2.3, 1.0);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.15, 30, 20);
    glPopMatrix();

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
    glutCreateWindow("Lisa Bezier");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();

    return 0;
}
