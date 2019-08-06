// Nota importante: Cuando realize el ligado, agregar la libreria glaux.lib
//  en Project --> Settings (Link)

// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include "../SOIL.h"
#include <math.h>

class COGLTexture {
public:
    unsigned char *Image;

    unsigned int GetID();

    void LoadFromFile(char *filename);

    void SetActive();

    int GetWidth();

    int GetHeight();

private:
    int Width, Height, Channels;
    unsigned int ID;
};

COGLTexture Tex1, Tex2, Tex3, Tex4, Tex5, Tex6;

GLfloat XRotated = 0.0;
GLfloat YRotated = 0.0;
GLfloat ZRotated = 0.0;

void COGLTexture::LoadFromFile(char *filename) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    Image = SOIL_load_image(filename, &this->Width, &this->Height, &this->Channels, 0);
    //Width = Image->sizeX;
    //Height = Image->sizeY;
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, this->Width, this->Height, GL_RGB, GL_UNSIGNED_BYTE, Image);
    delete Image;
}

void COGLTexture::SetActive() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

unsigned int COGLTexture::GetID() {
    return ID;
}

void InitTextures(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    Tex1.LoadFromFile("imagen1.bmp");
    Tex2.LoadFromFile("imagen2.bmp");
    Tex3.LoadFromFile("imagen3.bmp");
    Tex4.LoadFromFile("imagen4.bmp");
    Tex5.LoadFromFile("imagen5.bmp");
    Tex6.LoadFromFile("imagen6.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void DrawCube(void) {
    glEnable(GL_TEXTURE_2D);

    //left:
    Tex1.SetActive();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    //right:
    Tex2.SetActive();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    //front:
    Tex3.SetActive();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    //back:
    Tex4.SetActive();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    //top:
    Tex5.SetActive();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    //bottom:
    Tex6.SetActive();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void reshape(int x, int y) {
    if (y == 0 || x == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble) x / (GLdouble) y, 0.5, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -2.5);
    glRotatef(XRotated, 1.0, 0.0, 0.0);
    glRotatef(YRotated, 0.0, 1.0, 0.0);
    DrawCube();
    glFlush();
    glutSwapBuffers();
}


void KeyDown(unsigned char key, int x, int y) {
    switch (key) {
        case 27:   //ESC
            //exit(0);
            break;
    }
}

void Idle(void) {
    XRotated += 1.0;
    YRotated += 5.0;
    Display();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Multiples Texturas");
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    InitTextures();
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(KeyDown);
    glutIdleFunc(Idle);
    glutMainLoop();
    return 0;
}


