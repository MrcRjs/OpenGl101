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

// puntos de control de la superficie de Bezier
GLfloat ctrlpoints[5][5][3] = {
        /// 5a FILA DE PUNTOS
        {{-2.0, -2.0, 0.5},
                {-1.0, -2.0, -0.4},
                {0.0, -2.0, -0.5},
                {1.0, -2.0, -0.4},
                {2.0, -2.0, 0.5}},

        /// 4a FILA DE PUNTOS
        {{-2.0, -1.0, 0.5},
                {-1.0, -1.0, 0.5},
                {0.0, -1.0, 0.75},
                {1.0, -1.0, 0.5},
                {2.0, -1.0, 0.25}},

        /// 3a FILA DE PUNTOS
        {{-2.0, 0.0,  0.6},
                {-1.0, 0.0,  1.0},
                {0.0, 0.0,  1.5},
                {1.0, 0.0,  1.0},
                {2.0, 0.0,  0.26}},

        /// 2a FILA DE PUNTOS
        {{-2.0, 1.0,  0.5},
                {-1.0, 1.0,  1.0},
                {0.0, 1.0,  1.25},
                {1.0, 1.0,  1.0},
                {2.0, 1.0,  0.25}},

        /// 1a FILA DE PUNTOS
        {{-2.0, 2.0,  1.0},
                {-1.0, 2.0,  0.5},
                {0.0, 2.0,  0.25},
                {1.0, 2.0,  0.5},
                {2.0, 2.0,  1.0}}};

// propiedades del material
GLfloat mat_ambient[] = {0.0f, 0.05f, 0.06f, 1.0f};
GLfloat mat_diffuse[] = {0.0f, 0.50980392f, 0.50980392f, 1.0f};
GLfloat mat_specular[] = {0.90196078f, 0.90196078f, 0.90196078f, 1.0f};

// angulos de rotacion
GLfloat rotx = 0.0;
GLfloat roty = 0.0;
GLfloat rotz = 0.0;

// parametros de la fuente de luz
void initlights(void) {
    // propiedades de la fuente de luz
    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[] = {0.0f, 0.0f, 1.0f, 0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

// dibuja los puntos de control de la superficie
void DrawPoints(void) {
    int i, j;

    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);

    // cambia el tamaño del pexels para hacerlo mas visible
    glPointSize(4.0f);

    // dibuja todos los puntos de control de la superficie
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    for (j = 0; j < 5; j++)
        for (i = 0; i < 5; i++)
            glVertex3fv(ctrlpoints[j][i]);
    glEnd();

    glColor3f(0.0, 0.25, 0.5);
    glBegin(GL_LINES);
    for (j = 0; j < 4; j++)
        for (i = 0; i < 4; i++) {
            glVertex3fv(ctrlpoints[j][i]);
            glVertex3fv(ctrlpoints[j][i + 1]);
        }
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            glVertex3fv(ctrlpoints[j][i]);
            glVertex3fv(ctrlpoints[j + 1][i]);
        }
    glEnd();

    glPopAttrib();
}

// dibuja la superficie
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW_MATRIX);

    glLoadIdentity();

    glTranslated(0.0, 0.0, -12.0);
    glRotatef(rotx, 1.0, 0.0, 0.0);
    glRotatef(roty, 0.0, 1.0, 0.0);
    glRotatef(rotz, 0.0, 0.0, 1.0);

    // material para la superficie de Bezier
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glEvalMesh2(GL_FILL, 0, 20, 0, 20);

    DrawPoints();

    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMap2f(GL_MAP2_VERTEX_3,
            0, 1, 3, 5, 0, 1, 15, 5,
            &ctrlpoints[0][0][0]);
    // activa el evaluador
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    // crea una rejilla de 400 puntos (20x20)
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    initlights();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat) w / (GLfloat) h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            rotx = rotx + 10.0f;
            glutPostRedisplay();
            break;
        case '2':
            rotx = rotx - 10.0f;
            glutPostRedisplay();
            break;
        case '3':
            roty = roty + 10.0f;
            glutPostRedisplay();
            break;
        case '4':
            roty = roty - 10.0f;
            glutPostRedisplay();
            break;
        case '5':
            rotz = rotz + 10.0f;
            glutPostRedisplay();
            break;
        case '6':
            rotz = rotz - 10.0f;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

void teclado(int Key, int x, int y) {
    switch (Key) {
        case GLUT_KEY_RIGHT:
            roty = roty + 10.0f;
            break;
        case GLUT_KEY_LEFT:
            roty = roty - 10.0f;
            break;
        case GLUT_KEY_UP:
            rotx = rotx - 10.0f;
            break;
        case GLUT_KEY_DOWN:
            rotx = rotx + 10.0f;
            break;
        case GLUT_KEY_PAGE_UP:
            rotz = rotz + 10.0f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            rotz = rotz - 10.0f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Superficie de Bezier");
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclado);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
