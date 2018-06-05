#include <GLUT/glut.h>
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
class wcPt2D
{
  public:
    GLfloat x, y;
};

// Used to scale 
const GLint SCALE = 20;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT, GL_LINE);
}

void setColor(char *color)
{
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
    if(strcmp(color, "metal") == 0)
    {
        glColor3f(0.7f, 0.7f, 0.7f);
    }
    else if (strcmp(color, "metal-shadow") == 0)
    {
        glColor3f(0.51f, 0.51f, 0.51f);
    }
    else if (strcmp(color, "metal-light") == 0)
    {
        glColor3f(0.76f, 0.79f, 0.78f);
    }
    else if (strcmp(color, "red") == 0)
    {
        glColor3f(0.91f, 0.0f, 0.22f);
    }
    else if (strcmp(color, "green") == 0)
    {
        glColor3f(0.28f, 0.96f, 0.65f);
    }
    else if (strcmp(color, "black") == 0)
    {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    else if (strcmp(color, "pink") == 0)
    {
        glColor3f(0.9f, 0.7f, 0.95f);
    }
}

// Main display function, to draw and apply transformations to polygons
void displayGir(void)
{
    /*
        Robot Head
    */

    // Robot neck
    glBegin(GL_QUADS);
    setColor("metal");
    glVertex2i(0 * SCALE, 1 * SCALE);
    glVertex2i(0 * SCALE, -1 * SCALE);
    glVertex2i(1 * SCALE, -1 * SCALE);
    glVertex2i(1 * SCALE, 1 * SCALE);
    glEnd();
    glBegin(GL_QUADS);
    setColor("metal-shadow");
    glVertex2i(0 * SCALE, 1 * SCALE);
    glVertex2i(0 * SCALE, -1 * SCALE);
    glVertex2i(0.3 * SCALE, -1 * SCALE);
    glVertex2i(0.3 * SCALE, 1 * SCALE);
    glEnd();

    // Robot Head Center
    glBegin(GL_QUADS);
    setColor("metal");
    glVertex2i(-2 * SCALE, 12 * SCALE);
    glVertex2i(-2 * SCALE, 1 * SCALE);
    glVertex2i(3 * SCALE, 1 * SCALE);
    glVertex2i(3 * SCALE, 12 * SCALE);
    glEnd();

    // Head Left
    glBegin(GL_QUADS);
    setColor("metal");
    glVertex2i(-4 * SCALE, 11 * SCALE);
    glVertex2i(-4 * SCALE, 2 * SCALE);
    glVertex2i(-2 * SCALE, 1 * SCALE);
    glVertex2i(-2 * SCALE, 12 * SCALE);
    glEnd();

    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-5 * SCALE, 10 * SCALE);
    glVertex2i(-4 * SCALE, 2 * SCALE);
    glVertex2i(-4 * SCALE, 11 * SCALE);
    glEnd();

    // Head Right
    glBegin(GL_QUADS);
    setColor("metal");
    glVertex2i(3 * SCALE, 12 * SCALE);
    glVertex2i(3 * SCALE, 1 * SCALE);
    glVertex2i(5 * SCALE, 2 * SCALE);
    glVertex2i(5 * SCALE, 11 * SCALE);
    glEnd();

    glBegin(GL_TRIANGLES);
    setColor("metal-light");
    glVertex2i(5 * SCALE, 11 * SCALE);
    glVertex2i(5 * SCALE, 2 * SCALE);
    glVertex2i(6 * SCALE, 10 * SCALE);
    glEnd();

    // Antenna
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(0 * SCALE, 12 * SCALE);
    glVertex2i(1 * SCALE, 12 * SCALE);
    glVertex2i(2 * SCALE, 15 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(0 * SCALE, 12 * SCALE);
    glVertex2i(0.5 * SCALE, 12 * SCALE);
    glVertex2i(2 * SCALE, 15 * SCALE);
    glEnd();
    glBegin(GL_QUADS);
    setColor("metal-shadow");
    glVertex2i(2 * SCALE, 15.5 * SCALE);
    glVertex2i(2 * SCALE, 15 * SCALE);
    glVertex2i(2.5 * SCALE, 15 * SCALE);
    glVertex2i(2.5 * SCALE, 15.5 * SCALE);
    glEnd();
    
    /*
    Face
    */
    // Left Eye
    glBegin(GL_TRIANGLES);
    setColor("red");
    glVertex2i(-6 * SCALE, 9 * SCALE);
    glVertex2i(-4.5 * SCALE, 5 * SCALE);
    glVertex2i(0 * SCALE, 6.5 * SCALE);
    glEnd();

    // Right Eye
    glBegin(GL_TRIANGLE_FAN);
    setColor("green");
    glVertex2i(4 * SCALE, 7 * SCALE);
    glVertex2i(3 * SCALE, 9 * SCALE);
    glVertex2i(2 * SCALE, 8 * SCALE);
    glVertex2i(2 * SCALE, 6 * SCALE);
    glVertex2i(3 * SCALE, 5 * SCALE);
    glVertex2i(5 * SCALE, 5 * SCALE);
    glVertex2i(6 * SCALE, 6 * SCALE);
    glVertex2i(6 * SCALE, 8 * SCALE);
    glVertex2i(5 * SCALE, 9 * SCALE);
    glVertex2i(3 * SCALE, 9 * SCALE);
    glEnd();

    /*
        Mouth
    */
    glLineWidth(2.0);
    glBegin(GL_LINES);
    setColor("black");
    glVertex2i(-1 * SCALE, 3 * SCALE);
    glVertex2i(3 * SCALE, 4 * SCALE);
    glEnd();
    glBegin(GL_QUADS);
    setColor("pink");
    glVertex2i(2 * SCALE, 3.666 * SCALE);
    glVertex2i(2 * SCALE, 3 * SCALE);
    glVertex2i(3 * SCALE, 3 * SCALE);
    glVertex2i(3 * SCALE, 4 * SCALE);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINES);
    setColor("black");
    glVertex2i(2.5 * SCALE, 3.8 * SCALE);
    glVertex2i(2.5 * SCALE, 3.2 * SCALE);
    glEnd();

    /*
        GIR Body
    */

    // Torso
    glBegin(GL_QUADS);
    setColor("metal");
    glVertex2i(-3 * SCALE, -1 * SCALE);
    glVertex2i(-2 * SCALE, -8 * SCALE);
    glVertex2i(3 * SCALE, -8 * SCALE);
    glVertex2i(4 * SCALE, -1 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-3 * SCALE, -1 * SCALE);
    glVertex2i(-2 * SCALE, -8 * SCALE);
    glVertex2i(-1 * SCALE, -8 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-light");
    glVertex2i(4 * SCALE, -1 * SCALE);
    glVertex2i(2.5 * SCALE, -8 * SCALE);
    glVertex2i(3 * SCALE, -8 * SCALE);
    glEnd();
    glBegin(GL_QUADS);
    setColor("red");
    glVertex2i(-1 * SCALE, -2 * SCALE);
    glVertex2i(-1 * SCALE, -6 * SCALE);
    glVertex2i(0.5 * SCALE, -6 * SCALE);
    glVertex2i(0.5 * SCALE, -2 * SCALE);
    glEnd();
    glBegin(GL_QUADS);
    setColor("green");
    glVertex2i(0.5 * SCALE, -2 * SCALE);
    glVertex2i(0.5 * SCALE, -6 * SCALE);
    glVertex2i(2 * SCALE, -6 * SCALE);
    glVertex2i(2 * SCALE, -2 * SCALE);
    glEnd();

    /*
        Left Arm
    */

    // Shoulder Left
    glBegin(GL_QUADS);
    setColor("red");
    glVertex2i(-4 * SCALE, -1 * SCALE);
    glVertex2i(-4 * SCALE, -2 * SCALE);
    glVertex2i(-3 * SCALE, -2 * SCALE);
    glVertex2i(-3 * SCALE, -1 * SCALE);
    glEnd();

    // Arm
    glBegin(GL_QUADS);
    setColor("metal-shadow");
    glVertex2i(-8 * SCALE, 7 * SCALE);
    glVertex2i(-4 * SCALE, -2 * SCALE);
    glVertex2i(-4 * SCALE, -1 * SCALE);
    glVertex2i(-7 * SCALE, 7 * SCALE);
    glEnd();
    glBegin(GL_QUADS);
    setColor("metal-shadow");
    glVertex2i(-7 * SCALE, 10 * SCALE);
    glVertex2i(-8 * SCALE, 7 * SCALE);
    glVertex2i(-7 * SCALE, 7 * SCALE);
    glVertex2i(-6 * SCALE, 10 * SCALE);
    glEnd();

    // Hand
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(-7 * SCALE, 10 * SCALE);
    glVertex2i(-4 * SCALE, 10 * SCALE);
    glVertex2i(-6 * SCALE, 11 * SCALE);
    glEnd();

    /*
        Right Arm
    */

    // Shoulder Right
    glBegin(GL_QUADS);
    setColor("green");
    glVertex2i(4 * SCALE, -1 * SCALE);
    glVertex2i(4 * SCALE, -2 * SCALE);
    glVertex2i(5 * SCALE, -2 * SCALE);
    glVertex2i(5 * SCALE, -1 * SCALE);
    glEnd();

    // Arm
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(4 * SCALE, -2 * SCALE);
    glVertex2i(4 * SCALE, -8 * SCALE);
    glVertex2i(5 * SCALE, -2 * SCALE);
    glEnd();

    // Hand
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(4 * SCALE, -8 * SCALE);
    glVertex2i(5 * SCALE, -8 * SCALE);
    glVertex2i(5 * SCALE, -7 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(4 * SCALE, -8 * SCALE);
    glVertex2i(6 * SCALE, -8 * SCALE);
    glVertex2i(6 * SCALE, -7 * SCALE);
    glEnd();

    /*
    Legs
    */
    // Left
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(-1 * SCALE, -8 * SCALE);
    glVertex2i(-2 * SCALE, -13 * SCALE);
    glVertex2i(0 * SCALE, -13 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-1 * SCALE, -8 * SCALE);
    glVertex2i(-2 * SCALE, -13 * SCALE);
    glVertex2i(-1.5 * SCALE, -13 * SCALE);
    glEnd();

    // Right
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(2 * SCALE, -8 * SCALE);
    glVertex2i(1 * SCALE, -13 * SCALE);
    glVertex2i(3 * SCALE, -13 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(2 * SCALE, -8 * SCALE);
    glVertex2i(1 * SCALE, -13 * SCALE);
    glVertex2i(1.5 * SCALE, -13 * SCALE);
    glEnd();

    glFlush();
}

void displayGirWTriangle()
{
    /*
        Robot Head
    */

    // Robot neck
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(0 * SCALE, 1 * SCALE);
    glVertex2i(0 * SCALE, -1 * SCALE);
    glVertex2i(1 * SCALE, -1 * SCALE);
    glVertex2i(1 * SCALE, 1 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(0 * SCALE, 1 * SCALE);
    glVertex2i(0 * SCALE, -1 * SCALE);
    glVertex2i(0.3 * SCALE, -1 * SCALE);
    glVertex2i(0.3 * SCALE, 1 * SCALE);
    glEnd();

    // Robot Head Center
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(-2 * SCALE, 12 * SCALE);
    glVertex2i(-2 * SCALE, 1 * SCALE);
    glVertex2i(3 * SCALE, 1 * SCALE);
    glVertex2i(3 * SCALE, 12 * SCALE);
    glEnd();

    // Head Left
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(-4 * SCALE, 11 * SCALE);
    glVertex2i(-4 * SCALE, 2 * SCALE);
    glVertex2i(-2 * SCALE, 1 * SCALE);
    glVertex2i(-2 * SCALE, 12 * SCALE);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(-5 * SCALE, 10 * SCALE);
    glVertex2i(-4 * SCALE, 2 * SCALE);
    glVertex2i(-4 * SCALE, 11 * SCALE);
    glEnd();

    // Head Right
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(3 * SCALE, 12 * SCALE);
    glVertex2i(3 * SCALE, 1 * SCALE);
    glVertex2i(5 * SCALE, 2 * SCALE);
    glVertex2i(5 * SCALE, 11 * SCALE);
    glEnd();

    glBegin(GL_TRIANGLES);
    setColor("metal-light");
    glVertex2i(5 * SCALE, 11 * SCALE);
    glVertex2i(5 * SCALE, 2 * SCALE);
    glVertex2i(6 * SCALE, 10 * SCALE);
    glEnd();

    // Antenna
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(0 * SCALE, 12 * SCALE);
    glVertex2i(1 * SCALE, 12 * SCALE);
    glVertex2i(2 * SCALE, 15 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(0 * SCALE, 12 * SCALE);
    glVertex2i(0.5 * SCALE, 12 * SCALE);
    glVertex2i(2 * SCALE, 15 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(2 * SCALE, 15.5 * SCALE);
    glVertex2i(2 * SCALE, 15 * SCALE);
    glVertex2i(2.5 * SCALE, 15 * SCALE);
    glVertex2i(2.5 * SCALE, 15.5 * SCALE);
    glEnd();

    /*
    Face
    */
    // Left Eye
    glBegin(GL_TRIANGLES);
    setColor("red");
    glVertex2i(-6 * SCALE, 9 * SCALE);
    glVertex2i(-4.5 * SCALE, 5 * SCALE);
    glVertex2i(0 * SCALE, 6.5 * SCALE);
    glEnd();

    // Right Eye
    glBegin(GL_TRIANGLE_FAN);
    setColor("green");
    glVertex2i(4 * SCALE, 7 * SCALE);
    glVertex2i(3 * SCALE, 9 * SCALE);
    glVertex2i(2 * SCALE, 8 * SCALE);
    glVertex2i(2 * SCALE, 6 * SCALE);
    glVertex2i(3 * SCALE, 5 * SCALE);
    glVertex2i(5 * SCALE, 5 * SCALE);
    glVertex2i(6 * SCALE, 6 * SCALE);
    glVertex2i(6 * SCALE, 8 * SCALE);
    glVertex2i(5 * SCALE, 9 * SCALE);
    glVertex2i(3 * SCALE, 9 * SCALE);
    glEnd();

    /*
        Mouth
    */
    glLineWidth(2.0);
    glBegin(GL_LINES);
    setColor("black");
    glVertex2i(-1 * SCALE, 3 * SCALE);
    glVertex2i(3 * SCALE, 4 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("pink");
    glVertex2i(2 * SCALE, 3.666 * SCALE);
    glVertex2i(2 * SCALE, 3 * SCALE);
    glVertex2i(3 * SCALE, 3 * SCALE);
    glVertex2i(3 * SCALE, 4 * SCALE);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINES);
    setColor("black");
    glVertex2i(2.5 * SCALE, 3.8 * SCALE);
    glVertex2i(2.5 * SCALE, 3.2 * SCALE);
    glEnd();

    /*
        GIR Body
    */

    // Torso
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal");
    glVertex2i(-3 * SCALE, -1 * SCALE);
    glVertex2i(-2 * SCALE, -8 * SCALE);
    glVertex2i(3 * SCALE, -8 * SCALE);
    glVertex2i(4 * SCALE, -1 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-3 * SCALE, -1 * SCALE);
    glVertex2i(-2 * SCALE, -8 * SCALE);
    glVertex2i(-1 * SCALE, -8 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-light");
    glVertex2i(4 * SCALE, -1 * SCALE);
    glVertex2i(2.5 * SCALE, -8 * SCALE);
    glVertex2i(3 * SCALE, -8 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("red");
    glVertex2i(-1 * SCALE, -2 * SCALE);
    glVertex2i(-1 * SCALE, -6 * SCALE);
    glVertex2i(0.5 * SCALE, -6 * SCALE);
    glVertex2i(0.5 * SCALE, -2 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("green");
    glVertex2i(0.5 * SCALE, -2 * SCALE);
    glVertex2i(0.5 * SCALE, -6 * SCALE);
    glVertex2i(2 * SCALE, -6 * SCALE);
    glVertex2i(2 * SCALE, -2 * SCALE);
    glEnd();

    /*
        Left Arm
    */

    // Shoulder Left
    glBegin(GL_TRIANGLE_FAN);
    setColor("red");
    glVertex2i(-4 * SCALE, -1 * SCALE);
    glVertex2i(-4 * SCALE, -2 * SCALE);
    glVertex2i(-3 * SCALE, -2 * SCALE);
    glVertex2i(-3 * SCALE, -1 * SCALE);
    glEnd();

    // Arm
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(-8 * SCALE, 7 * SCALE);
    glVertex2i(-4 * SCALE, -2 * SCALE);
    glVertex2i(-4 * SCALE, -1 * SCALE);
    glVertex2i(-7 * SCALE, 7 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    setColor("metal-shadow");
    glVertex2i(-7 * SCALE, 10 * SCALE);
    glVertex2i(-8 * SCALE, 7 * SCALE);
    glVertex2i(-7 * SCALE, 7 * SCALE);
    glVertex2i(-6 * SCALE, 10 * SCALE);
    glEnd();

    // Hand
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(-7 * SCALE, 10 * SCALE);
    glVertex2i(-4 * SCALE, 10 * SCALE);
    glVertex2i(-6 * SCALE, 11 * SCALE);
    glEnd();

    /*
        Right Arm
    */

    // Shoulder Right
    glBegin(GL_TRIANGLE_FAN);
    setColor("green");
    glVertex2i(4 * SCALE, -1 * SCALE);
    glVertex2i(4 * SCALE, -2 * SCALE);
    glVertex2i(5 * SCALE, -2 * SCALE);
    glVertex2i(5 * SCALE, -1 * SCALE);
    glEnd();

    // Arm
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(4 * SCALE, -2 * SCALE);
    glVertex2i(4 * SCALE, -8 * SCALE);
    glVertex2i(5 * SCALE, -2 * SCALE);
    glEnd();

    // Hand
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(4 * SCALE, -8 * SCALE);
    glVertex2i(5 * SCALE, -8 * SCALE);
    glVertex2i(5 * SCALE, -7 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(4 * SCALE, -8 * SCALE);
    glVertex2i(6 * SCALE, -8 * SCALE);
    glVertex2i(6 * SCALE, -7 * SCALE);
    glEnd();

    /*
    Legs
    */
    // Left
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(-1 * SCALE, -8 * SCALE);
    glVertex2i(-2 * SCALE, -13 * SCALE);
    glVertex2i(0 * SCALE, -13 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(-1 * SCALE, -8 * SCALE);
    glVertex2i(-2 * SCALE, -13 * SCALE);
    glVertex2i(-1.5 * SCALE, -13 * SCALE);
    glEnd();

    // Right
    glBegin(GL_TRIANGLES);
    setColor("metal");
    glVertex2i(2 * SCALE, -8 * SCALE);
    glVertex2i(1 * SCALE, -13 * SCALE);
    glVertex2i(3 * SCALE, -13 * SCALE);
    glEnd();
    glBegin(GL_TRIANGLES);
    setColor("metal-shadow");
    glVertex2i(2 * SCALE, -8 * SCALE);
    glVertex2i(1 * SCALE, -13 * SCALE);
    glVertex2i(1.5 * SCALE, -13 * SCALE);
    glEnd();

    glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    GLint window_1, window_2;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 50);
    glutInitWindowSize(winWidth, winHeight);
    window_1 = glutCreateWindow("Primitive Garbage Information Recollector 🤖");
    glutDisplayFunc(displayGir);
    glutReshapeFunc(winReshapeFcn);
    init();

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(800, 50);
    glutInitWindowSize(winWidth, winHeight);
    window_2 = glutCreateWindow("Primitive Garbage Information Recollector w/Triangles 👾");
    glutDisplayFunc(displayGirWTriangle);
    glutReshapeFunc(winReshapeFcn);
    init();

    glutMainLoop();

    return 0;
}