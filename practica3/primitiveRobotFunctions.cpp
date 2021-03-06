// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <string.h>

// Keep screen 16:10 aspect ratio
// 1440
// 1344
// 1280
//GLsizei winWidth = 1280, winHeight = (winWidth / 16) * 10;
GLsizei winWidth = 800, winHeight = 800;

// Same as window dimensions, centered origin
GLfloat xwcMin = winWidth / 2 * -1, xwcMax = winWidth / 2;
GLfloat ywcMin = winHeight / 2 * -1, ywcMax = winWidth / 2;

//Se define un objeto Punto (x, y) de tipo flotante
class wcPt2D {
public:
    GLfloat x, y;
};

// Used to scale
const GLint SCALE = 20;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //glPolygonMode(GL_FRONT, GL_LINE);
}

void setColor(char *color) {
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
    */
    if (strcmp(color, "metal") == 0) {
        glColor3f(0.7f, 0.7f, 0.7f);
    } else if (strcmp(color, "metal-shadow") == 0) {
        glColor3f(0.51f, 0.51f, 0.51f);
    } else if (strcmp(color, "metal-light") == 0) {
        glColor3f(0.76f, 0.79f, 0.78f);
    } else if (strcmp(color, "red") == 0) {
        glColor3f(0.91f, 0.0f, 0.22f);
    } else if (strcmp(color, "green") == 0) {
        glColor3f(0.28f, 0.96f, 0.65f);
    } else if (strcmp(color, "black") == 0) {
        glColor3f(0.0f, 0.0f, 0.0f);
    } else if (strcmp(color, "pink") == 0) {
        glColor3f(0.9f, 0.7f, 0.95f);
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
    setColor("red");
    glVertex2i(-6 * SCALE, 2.5 * SCALE);
    glVertex2i(-4.5 * SCALE, -2.5 * SCALE);
    glVertex2i(0 * SCALE, -1 * SCALE);
    glEnd();

    // Right Eye
    glBegin(GL_TRIANGLE_FAN);
    setColor("green");
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
    setColor("red");
    glVertex2i(-1.5 * SCALE, 2.5 * SCALE);
    glVertex2i(-1.5 * SCALE, -1.5 * SCALE);
    glVertex2i(0 * SCALE, -1.5 * SCALE);
    glVertex2i(0 * SCALE, 2.5 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("green");
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
    setColor("red");
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
    setColor("green");
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
    glLoadIdentity();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0 * SCALE, 7.5f * SCALE, 0);
    drawHead();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-0.5 * SCALE, -4.5 * SCALE, 0);
    drawBody();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-6.5 * SCALE, 4.5 * SCALE, 0);
    drawLeftArm();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(4 * SCALE, -4.5 * SCALE, 0);
    drawRightArm();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-2 * SCALE, -10.5 * SCALE, 0);
    drawFoot();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(1 * SCALE, -10.5 * SCALE, 0);
    drawFoot();
    glPopMatrix();

    glFlush();
}

void displayDeformedGir() {
    /*
        Deformed GIR
    */
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glLoadIdentity();
    glScalef(1.5, 1.5, 0);
    glTranslatef(-1.0 * SCALE, 7.5f * SCALE, 0);
    drawHead();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-0.5 * SCALE, -4.5 * SCALE, 0);
    drawBody();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-6.5 * SCALE, 4.5 * SCALE, 0);
    drawLeftArm();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(6 * SCALE, -3.5 * SCALE, 0);
    glRotatef(45, 0, 0, 1);
    drawRightArm();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glScalef(1, 0.5, 0);
    glTranslatef(-2 * SCALE, -18.5 * SCALE, 0);
    drawFoot();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glScalef(1.5, 0.8, 0);
    glTranslatef(1 * SCALE, -12.5 * SCALE, 0);
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
    setColor("red");
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

    GLint window_1, window_2;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 50);
    glutInitWindowSize(winWidth, winHeight);
    window_1 = glutCreateWindow("Primitive Garbage Information Recollector using functions(🤖)");
    glutDisplayFunc(displayGir);
    glutReshapeFunc(winReshapeFcn);
    init();

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(800, 50);
    glutInitWindowSize(winWidth, winHeight);
    window_2 = glutCreateWindow("Primitive Garbage Information Recollector Deformed 👾");
    glutDisplayFunc(displayDeformedGir);
    glutReshapeFunc(winReshapeFcn);
    init();
    glutMainLoop();

    return 0;
}