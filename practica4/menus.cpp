// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif
s
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>

using namespace std;

// Keep screen 16:10 aspect ratio
// 1440
// 1344
// 1280
//GLsizei winWidth = 1280, winHeight = (winWidth / 16) * 10;
GLsizei winWidth = 800, winHeight = 800;

// Same as window dimensions, centered origin
GLfloat xwcMin = winWidth / 2 * -1, xwcMax = winWidth / 2;
GLfloat ywcMin = winHeight / 2 * -1, ywcMax = winWidth / 2;

int nx, ny, alpha, beta, rz = 0;
float sx, sy = 0;
int tx, ty = 0;

typedef enum {
    bgBlack,
    bgWhite,
    leftGreen,
    leftRed,
    leftPurple,
    leftYellow,
    rightGreen,
    rightRed,
    rightPurple,
    rightYellow,
} menuOpt;

string leftLightGIRColor = "red";
string rightLightGIRColor = "green";
string bgColor = "white";

void
keypressed(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': {
            ty += 1;
            break;
        }
        case 'a': {
            tx -= 1;
            break;
        }
        case 's': {
            ty -= 1;
            break;
        }
        case 'd': {
            tx += 1;
            break;
        }
    }

    glutPostRedisplay();
};

void onMouse(int button, int state, int x, int y) {
    // MANEJO DE ROTACIÓN -> VINCULADO CON EL MOVIMIENTO DEL MOUSE i.e. onMotion()
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        nx = x;
        ny = y;
    }
    // MANEJO DE ESCALAMIENTO
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        sx += 0.5;
        sy += 0.5;
    }
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
        sx -= 0.5;
        sy -= 0.5;
    }
    glutPostRedisplay();
}

void onMotion(int x, int y) {
    // Calcular ángulo de rotación en base a la posición inicial y final del mouse
    alpha = (alpha + (y - ny));
    beta = (beta + (x - nx));
    // Actualizar valor de la última coordenada
    nx = x;
    ny = y;
    // Elegir el ángulo más grande para rotar
    if (abs((double) alpha) >= abs((double) beta))
        rz = alpha;
    else
        rz = beta;
    glutPostRedisplay();
}

// Used to scale robot from unit squares from draft to pixels 
const GLint SCALE = 20;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //glPolygonMode(GL_FRONT, GL_LINE);
}

void onMenu(int opt) {
    switch (opt) {
        case bgBlack:
            bgColor = "black";
            break;
        case bgWhite:
            bgColor = "white";
            break;
        case leftGreen:
            leftLightGIRColor = "green";
            break;
        case leftRed:
            leftLightGIRColor = "red";
            break;
        case leftPurple:
            leftLightGIRColor = "purple";
            break;
        case leftYellow:
            leftLightGIRColor = "yellow";
            break;
        case rightGreen:
            rightLightGIRColor = "green";
            break;
        case rightRed:
            rightLightGIRColor = "red";
            break;
        case rightPurple:
            rightLightGIRColor = "purple";
            break;
        case rightYellow:
            rightLightGIRColor = "yellow";
            break;
    }
    glutPostRedisplay();
}

void colorMenu(void) {
    int GIRLeftMenu, GIRRightMenu, BgMenu, GIRMenu, MainMenu;

    GIRLeftMenu = glutCreateMenu(onMenu);
    glutAddMenuEntry("Green", leftGreen);
    glutAddMenuEntry("Red", leftRed);
    glutAddMenuEntry("Purple", leftPurple);
    glutAddMenuEntry("Yellow", leftYellow);

    GIRRightMenu = glutCreateMenu(onMenu);
    glutAddMenuEntry("Green", rightGreen);
    glutAddMenuEntry("Red", rightRed);
    glutAddMenuEntry("Purple", rightPurple);
    glutAddMenuEntry("Yellow", rightYellow);

    GIRMenu = glutCreateMenu(onMenu);
    glutAddSubMenu("Left", GIRLeftMenu);
    glutAddSubMenu("Right", GIRRightMenu);

    BgMenu = glutCreateMenu(onMenu);
    glutAddMenuEntry("Blanco", bgWhite);
    glutAddMenuEntry("Negro", bgBlack);

    MainMenu = glutCreateMenu(onMenu);
    glutAddSubMenu("Background Color", BgMenu);
    glutAddSubMenu("GIR color theme", GIRMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void setColor(string color) {
    /*
    GIR colors
    metal
    #B2B2B2
    metal-shadow
    #838383
    metal-light
    #C2C9C6
    green
    #47F4A7
    red
    #E70039
    pink
    #E6B2F1
    yellow
    #ccff00
    purple
    #ba0be0
    */
    if (color.compare("metal") == 0) {
        glColor3f(0.7f, 0.7f, 0.7f);
    } else if (color.compare("metal-shadow") == 0) {
        glColor3f(0.51f, 0.51f, 0.51f);
    } else if (color.compare("metal-light") == 0) {
        glColor3f(0.76f, 0.79f, 0.78f);
    } else if (color.compare("red") == 0) {
        glColor3f(0.91f, 0.0f, 0.22f);
    } else if (color.compare("green") == 0) {
        glColor3f(0.28f, 0.96f, 0.65f);
    } else if (color.compare("black") == 0) {
        glColor3f(0.0f, 0.0f, 0.0f);
    } else if (color.compare("pink") == 0) {
        glColor3f(0.9f, 0.7f, 0.95f);
    } else if (color.compare("white") == 0) {
        glColor3f(1.0f, 1.0f, 1.0f);
    } else if (color.compare("purple") == 0) {
        glColor3f(0.73f, 0.04f, 0.88f);
    } else if (color.compare("yellow") == 0) {
        glColor3f(0.8f, 1.0f, 0.0f);
    }
}

void drawHead() {
    /*
        Robot Head
    */

    // Robot neck
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(0 * SCALE, -6.5 * SCALE);
    glVertex2i(0 * SCALE, -8.5 * SCALE);
    glVertex2i(1 * SCALE, -8.5 * SCALE);
    glVertex2i(1 * SCALE, -6.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(0 * SCALE, -6.5 * SCALE);
    glVertex2i(0 * SCALE, -8.5 * SCALE);
    glVertex2i(0.3 * SCALE, -8.5 * SCALE);
    glVertex2i(0.3 * SCALE, -6.5 * SCALE);
    glEnd();

    // Robot Head Center
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(-2 * SCALE, 4.5 * SCALE);
    glVertex2i(-2 * SCALE, -6.5 * SCALE);
    glVertex2i(3 * SCALE, -6.5 * SCALE);
    glVertex2i(3 * SCALE, 4.5 * SCALE);
    glEnd();

    // Head Left
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(-4 * SCALE, 3.5 * SCALE);
    glVertex2i(-4 * SCALE, -5.5 * SCALE);
    glVertex2i(-2 * SCALE, -6.5 * SCALE);
    glVertex2i(-2 * SCALE, 4.5 * SCALE);
    glEnd();

    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-5 * SCALE, 2.5 * SCALE);
    glVertex2i(-4 * SCALE, -5.5 * SCALE);
    glVertex2i(-4 * SCALE, 3.5 * SCALE);
    glEnd();

    // Head Right
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(3 * SCALE, 4.5 * SCALE);
    glVertex2i(3 * SCALE, -6.5 * SCALE);
    glVertex2i(5 * SCALE, -5.5 * SCALE);
    glVertex2i(5 * SCALE, 3.5 * SCALE);
    glEnd();

    glBegin(GL_TRIANGLES);
    setColor("metal-light");
    glVertex2i(5 * SCALE, 3.5 * SCALE);
    glVertex2i(5 * SCALE, -5.5 * SCALE);
    glVertex2i(6 * SCALE, 2.5 * SCALE);
    glEnd();

    // Antenna
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(0 * SCALE, 4.5 * SCALE);
    glVertex2i(1 * SCALE, 4.5 * SCALE);
    glVertex2i(2 * SCALE, 7.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(0 * SCALE, 4.5 * SCALE);
    glVertex2i(0.5 * SCALE, 4.5 * SCALE);
    glVertex2i(2 * SCALE, 7.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(2 * SCALE, 8 * SCALE);
    glVertex2i(2 * SCALE, 7.5 * SCALE);
    glVertex2i(2.5 * SCALE, 7.5 * SCALE);
    glVertex2i(2.5 * SCALE, 8 * SCALE);
    glEnd();

    /*
    Face
    */
    // Left Eye
    glBegin(GL_TRIANGLES);
    setColor(leftLightGIRColor);
    glVertex2i(-6 * SCALE, 2.5 * SCALE);
    glVertex2i(-4.5 * SCALE, -2.5 * SCALE);
    glVertex2i(0 * SCALE, -1 * SCALE);
    glEnd();

    // Right Eye
    glBegin(GL_TRIANGLE_FAN);
    setColor(rightLightGIRColor);
    glVertex2i(4 * SCALE, -0.5 * SCALE);
    glVertex2i(3 * SCALE, 1.5 * SCALE);
    glVertex2i(2 * SCALE, 0.5 * SCALE);
    glVertex2i(2 * SCALE, -1.5 * SCALE);
    glVertex2i(3 * SCALE, -2.5 * SCALE);
    glVertex2i(5 * SCALE, -2.5 * SCALE);
    glVertex2i(6 * SCALE, -1.5 * SCALE);
    glVertex2i(6 * SCALE, 0.5 * SCALE);
    glVertex2i(5 * SCALE, 1.5 * SCALE);
    glVertex2i(3 * SCALE, 1.5 * SCALE);
    glEnd();

    /*
        Mouth
    */
    glLineWidth(2.0);
    glBegin(GL_LINES);
    setColor("black");
    glVertex2i(-1 * SCALE, -4.5 * SCALE);
    glVertex2i(3 * SCALE, -3.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("pink");
    glVertex2i(2 * SCALE, -3.834 * SCALE);
    glVertex2i(2 * SCALE, -4.5 * SCALE);
    glVertex2i(3 * SCALE, -4.5 * SCALE);
    glVertex2i(3 * SCALE, -3.5 * SCALE);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINES);
    setColor("black");
    glVertex2i(2.5 * SCALE, -3.7 * SCALE);
    glVertex2i(2.5 * SCALE, -4.3 * SCALE);
    glEnd();
}

void drawBody() {
    /*
        GIR Body
    */

    // Torso
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(-3.5 * SCALE, 3.5 * SCALE);
    glVertex2i(-2.5 * SCALE, -3.5 * SCALE);
    glVertex2i(2.5 * SCALE, -3.5 * SCALE);
    glVertex2i(3.5 * SCALE, 3.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-3.5 * SCALE, 3.5 * SCALE);
    glVertex2i(-2.5 * SCALE, -3.5 * SCALE);
    glVertex2i(-1.5 * SCALE, -3.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-light");
    glVertex2i(3.5 * SCALE, 3.5 * SCALE);
    glVertex2i(2 * SCALE, -3.5 * SCALE);
    glVertex2i(2.5 * SCALE, -3.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor(leftLightGIRColor);
    glVertex2i(-1.5 * SCALE, 2.5 * SCALE);
    glVertex2i(-1.5 * SCALE, -1.5 * SCALE);
    glVertex2i(0 * SCALE, -1.5 * SCALE);
    glVertex2i(0 * SCALE, 2.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor(rightLightGIRColor);
    glVertex2i(0 * SCALE, 2.5 * SCALE);
    glVertex2i(0 * SCALE, -1.5 * SCALE);
    glVertex2i(1.5 * SCALE, -1.5 * SCALE);
    glVertex2i(1.5 * SCALE, 2.5 * SCALE);
    glEnd();
}

void drawLeftArm() {
    /*
        Left Arm
    */

    // Shoulder Left
    glBegin(GL_TRIANGLE_FAN);
    setColor(leftLightGIRColor);
    glVertex2i(1.5 * SCALE, -5.5 * SCALE);
    glVertex2i(1.5 * SCALE, -6.5 * SCALE);
    glVertex2i(2.5 * SCALE, -6.5 * SCALE);
    glVertex2i(2.5 * SCALE, -5.5 * SCALE);
    glEnd();

    // Arm
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(-2.5 * SCALE, 2.5 * SCALE);
    glVertex2i(1.5 * SCALE, -6.5 * SCALE);
    glVertex2i(1.5 * SCALE, -5.5 * SCALE);
    glVertex2i(-1.5 * SCALE, 2.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(-1.5 * SCALE, 5.5 * SCALE);
    glVertex2i(-2.5 * SCALE, 2.5 * SCALE);
    glVertex2i(-1.5 * SCALE, 2.5 * SCALE);
    glVertex2i(-0.5 * SCALE, 5.5 * SCALE);
    glEnd();

    // Hand
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(-1.5 * SCALE, 5.5 * SCALE);
    glVertex2i(1.5 * SCALE, 5.5 * SCALE);
    glVertex2i(-0.5 * SCALE, 6.5 * SCALE);
    glEnd();
}

void drawRightArm() {
    /*
        Right Arm
    */

    // Shoulder Right
    glBegin(GL_TRIANGLE_FAN);
    setColor(rightLightGIRColor);
    glVertex2i(-1 * SCALE, 3.5 * SCALE);
    glVertex2i(-1 * SCALE, 2.5 * SCALE);
    glVertex2i(0 * SCALE, 2.5 * SCALE);
    glVertex2i(0 * SCALE, 3.5 * SCALE);
    glEnd();

    // Arm
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(-1 * SCALE, 2.5 * SCALE);
    glVertex2i(-1 * SCALE, -3.5 * SCALE);
    glVertex2i(0 * SCALE, 2.5 * SCALE);
    glEnd();

    // Hand
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-1 * SCALE, -3.5 * SCALE);
    glVertex2i(0 * SCALE, -3.5 * SCALE);
    glVertex2i(0 * SCALE, -2.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(-1 * SCALE, -3.5 * SCALE);
    glVertex2i(1 * SCALE, -3.5 * SCALE);
    glVertex2i(1 * SCALE, -2.5 * SCALE);
    glEnd();
}

void drawFoot() {
    // Foot
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(0 * SCALE, 2.5 * SCALE);
    glVertex2i(-1 * SCALE, -2.5 * SCALE);
    glVertex2i(1 * SCALE, -2.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(0 * SCALE, 2.5 * SCALE);
    glVertex2i(-1 * SCALE, -2.5 * SCALE);
    glVertex2i(-0.5 * SCALE, -2.5 * SCALE);
    glEnd();
}

// Main display function, to draw and apply transformations to polygons
void displayGir(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    if (bgColor.compare("white") == 0) {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glutPostRedisplay();
    } else if (bgColor.compare("black") == 0) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glutPostRedisplay();
    }

    glPushMatrix();
    glLoadIdentity();
    glScalef(1 + sx, 1 + sy, 0);
    glTranslatef((tx - 1.0) * SCALE, (ty + 7.5f) * SCALE, 0);
    glRotatef(rz, 0, 0, 1);
    drawHead();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef((tx - 0.5) * SCALE, (ty - 4.5) * SCALE, 0);
    drawBody();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef((tx - 6.5) * SCALE, (ty + 4.5) * SCALE, 0);
    drawLeftArm();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef((tx + 4) * SCALE, (ty - 4.5) * SCALE, 0);
    drawRightArm();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef((tx - 2) * SCALE, (ty - 10.5) * SCALE, 0);
    drawFoot();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef((tx + 1) * SCALE, (ty - 10.5) * SCALE, 0);
    drawFoot();
    glPopMatrix();

    glFlush();
}


void testDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    /*
        Draw axes
    */
    glLineWidth(1.0);
    setColor(leftLightGIRColor);
    glBegin(GL_LINES);
    glVertex2i(-1000, 0);
    glVertex2i(1000, 0);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2i(0, -1000);
    glVertex2i(0, 1000);
    glEnd();

    // Test draw functions
    glLoadIdentity();
    glPushMatrix();
    //glTranslatef(0.0, 100, 0);
    //glRotatef(180,0,0,1);
    drawFoot();
    glPopMatrix();

    glFlush();
}

void winReshapeFcn(GLint w, GLint h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    if (w <= h)
        gluOrtho2D(xwcMin, xwcMax, ywcMin * h / w, ywcMax * h / w);
    else
        gluOrtho2D(xwcMin * w / h, xwcMax * w / h, ywcMin, ywcMax);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    GLint window_1;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 50);
    glutInitWindowSize(winWidth, winHeight);
    window_1 = glutCreateWindow("Primitive Garbage Information Recollector using functions(🤖)");
    glutKeyboardFunc(keypressed);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    colorMenu();
    glutDisplayFunc(displayGir);
    glutReshapeFunc(winReshapeFcn);
    init();
    glutMainLoop();

    return 0;
}