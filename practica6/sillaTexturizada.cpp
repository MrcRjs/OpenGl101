// Marco Antonio Rojas Arriaga

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif


#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "../utils/normalizer.h"

Normalizer NZ;

GLuint texture_id[4];

//Matriz de colores
float colores[4][3] =
        {
                {1.0, 1.0, 1.0}, //0 blanco
                {1.0, 0.0, 0.0}, //1 rojo
                {0.0, 1.0, 0.0}, //2 verde
                {0.0, 0.0, 1.0}, //3 azul
        };

int color = 2;  // color de FIGURA
int colorf = 0; // color de FONDO
int colorl = 3; // color de LUZ

//variables globales para la rotacion
float alpha, beta;
int x0, y0;
int opc;

//Variables globales para las transformaciones
float xpos = 0, ypos = 0, inc = 0.5;

void luzAmbiental(void) {
    GLfloat l_difusa[] = {0.22f, 0.17f, 0.12f, 0.0f};
    GLfloat l_especular[] = {0.22f, 0.17f, 0.12f, 0.0f};
    GLfloat l_posicion[] = {0.0, 0.0, 5.0, 1.0};
    GLfloat l_a_color[] = {0.22f, 0.17f, 0.12f, 0.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
    // glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
    glEnable(GL_LIGHT0);
    glutPostRedisplay();
}

int LoadBMP(char *filename, int tex_name) {
#define SAIR                \
    {                       \
        fclose(fp_archivo); \
        return -1;          \
    }
#define CTOI(C) (*(int *)&C)

    GLubyte *image;
    GLubyte Header[0x54];
    GLuint DataPos, imageSize;
    GLsizei Width, Height;

    int nb = 0;

    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE *fp_archivo = fopen(filename, "rb");
    if (!fp_archivo)
        return -1;
    if (fread(Header, 1, 0x36, fp_archivo) != 0x36) SAIR;
    if (Header[0] != 'B' || Header[1] != 'M') SAIR;
    if (CTOI(Header[0x1E]) != 0) SAIR;
    if (CTOI(Header[0x1C]) != 24) SAIR;

    // Recupera los atributos de la altura y ancho de la imagen

    Width = CTOI(Header[0x12]);
    Height = CTOI(Header[0x16]);
    (CTOI(Header[0x0A]) == 0) ? (DataPos = 0x36) : (DataPos = CTOI(Header[0x0A]));

    imageSize = Width * Height * 3;

    // Llama a la imagen
    image = (GLubyte *) malloc(imageSize);
    int retorno;
    retorno = fread(image, 1, imageSize, fp_archivo);

    if (retorno != imageSize) {
        free(image);
        SAIR;
    }

    // Invierte los valores de R y B
    int t, i;

    for (i = 0; i < imageSize; i += 3) {
        t = image[i];
        image[i] = image[i + 2];
        image[i + 2] = t;
    }

    // Tratamiento de textura para OpenGL

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MODULATE);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    fclose(fp_archivo);
    free(image);
    return 1;
}

void luzUno(void) {
    GLfloat l_difusa[] = {colores[2][0], colores[2][1], colores[2][2], 0.0f};
    GLfloat l_especular[] = {colores[2][0], colores[2][1], colores[2][2], 0.0f};
    GLfloat l_posicion[] = {0.0f, 5.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
    //glEnable (GL_LIGHT1);
}

void luzTres(void) {
    GLfloat l_difusa[] = {colores[0][0], colores[0][1], colores[0][2], 0.0f};
    GLfloat l_especular[] = {colores[0][0], colores[0][1], colores[0][2], 0.0f};

    GLfloat l_posicion[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat spot_direccion[] = {0.0, 0.0, 0.0, 0.0};

    glLightfv(GL_LIGHT3, GL_DIFFUSE, l_difusa);
    glLightfv(GL_LIGHT3, GL_SPECULAR, l_difusa);
    glLightfv(GL_LIGHT3, GL_POSITION, l_posicion);

    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direccion);
    //glEnable (GL_LIGHT3);
}

void drawCube() {
    glEnable(GL_NORMALIZE);
    // Frente
    glBegin(GL_QUADS);
    float vf[3][3] = {
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f};
    //glNormal3fv(NZ.calculateNormal(vf[0], vf[1], vf[2]));
    glTexCoord2f(0, 0);
    glVertex3d(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0);
    glVertex3d(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1);
    glVertex3d(0.5f, 0.5f, 0.5f);
    glTexCoord2f(-1, 1);
    glVertex3d(-0.5f, 0.5f, 0.5f);
    glEnd();
    // Posterior
    glBegin(GL_QUADS);
    float vp[3][3] = {
            0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f};
    //glNormal3fv(NZ.calculateNormal(vp[0], vp[1], vp[2]));
    glTexCoord2f(-1, 1);
    glVertex3d(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1, 1);
    glVertex3d(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1, -1);
    glVertex3d(0.5f, -0.5f, -0.5f);
    glTexCoord2f(-1, -1);
    glVertex3d(-0.5f, -0.5f, -0.5f);
    glEnd();

    // Derecha
    glBegin(GL_QUADS);
    float vd[3][3] = {
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f};
    //glNormal3fv(NZ.calculateNormal(vd[0], vd[1], vd[2]));
    glTexCoord3d(1, -1, 1);
    glVertex3d(0.5f, -0.5f, 0.5f);
    glTexCoord3d(1, -1, -1);
    glVertex3d(0.5f, -0.5f, -0.5f);
    glTexCoord3d(1, 1, -1);
    glVertex3d(0.5f, 0.5f, -0.5f);
    glTexCoord3d(1, 1, 1);
    glVertex3d(0.5f, 0.5f, 0.5f);
    glEnd();
    // Izquierda
    glBegin(GL_QUADS);
    float vi[3][3] = {
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f};
    //glNormal3fv(NZ.calculateNormal(vi[0], vi[1], vi[2]));
    glTexCoord2f(-1, 1);
    glVertex3d(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(-1, 1);
    glVertex3d(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(-1, -1);
    glVertex3d(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(-1, -1);
    glVertex3d(-0.5f, -0.5f, 0.5f);
    glEnd();

    // Superior
    glBegin(GL_QUADS);
    float vu[3][3] = {
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f};
    //glNormal3fv(NZ.calculateNormal(vu[0], vu[1], vu[2]));
    glTexCoord3f(-1, 1, 1);
    glVertex3d(-0.5f, 0.5f, 0.5f);
    glTexCoord3f(1, 1, 1);
    glVertex3d(0.5f, 0.5f, 0.5f);
    glTexCoord3f(1, 1, -1);
    glVertex3d(0.5f, 0.5f, -0.5f);
    glTexCoord3f(-1, 1, -1);
    glVertex3d(-0.5f, 0.5f, -0.5f);
    glEnd();
    // Inferior
    glBegin(GL_QUADS);
    float va[3][3] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f};
    //glNormal3fv(NZ.calculateNormal(va[0], va[1], va[2]));
    glVertex3d(-0.5f, -0.5f, -0.5f);
    glVertex3d(0.5f, -0.5f, -0.5f);
    glVertex3d(0.5f, -0.5f, 0.5f);
    glVertex3d(-0.5f, -0.5f, 0.5f);
    glEnd();

    glEnable(GL_TEXTURE_2D); //
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(2, texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    LoadBMP("madera.bmp", 0);
}

void drawChair() {
    // Pata trasera izquierda
    glPushMatrix();
    glTranslatef(-0.5f, -0.5f, -0.5);
    glScalef(0.2f, 1.0f, 0.2);
    drawCube();
    glPopMatrix();

    // Pata trasera derecha
    glPushMatrix();
    glTranslatef(0.5f, -0.5f, -0.5);
    glScalef(0.2f, 1.0f, 0.2);
    drawCube();
    glPopMatrix();

    // Pata delantera izquierda
    glPushMatrix();
    glTranslatef(-0.5f, -0.5f, 0.5);
    glScalef(0.2f, 1.0f, 0.2);
    drawCube();
    glPopMatrix();

    // Pata delantera derecha
    glPushMatrix();
    glTranslatef(0.5f, -0.5f, 0.5);
    glScalef(0.2f, 1.0f, 0.2);
    drawCube();
    glPopMatrix();

    // Asiento
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0);
    glScalef(1.2f, 0.2f, 1.2);
    drawCube();
    glPopMatrix();

    // Respaldo
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, -0.5);
    glScalef(1.2f, 1.0f, 0.2);
    drawCube();
    glPopMatrix();
}

void init(void) {
    luzAmbiental();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, 1.0f, 5.0f, 20.0f);
    gluLookAt(0.0f, 0.0f, 10.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);

    luzAmbiental();

    glEnable(GL_CULL_FACE);

    glPushMatrix();
    glLoadIdentity();

    glTranslatef(xpos, ypos, 0);
    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);
    drawChair();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//Accion del mouse
void onMouse(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {
        x0 = x;
        y0 = y;
    }
}

//Incremento o decremente de los angulos de rotacion
void onMotion(int x, int y) {
    alpha = (alpha + (y - y0));
    beta = (beta + (x - x0));
    x0 = x;
    y0 = y;
    glutPostRedisplay();
}

void ControlTeclado(int Key, int x, int y) {
    switch (Key) {
        //TRASLACION
        case GLUT_KEY_RIGHT:
            xpos += 0.05;
            break;
        case GLUT_KEY_LEFT:
            xpos -= 0.05;
            break;
        case GLUT_KEY_UP:
            ypos += 0.05;
            break;
        case GLUT_KEY_DOWN:
            ypos -= 0.05;
            break;
            //ESCALAMIENTO
        case GLUT_KEY_HOME:
            inc += 0.05;
            break;
        case GLUT_KEY_END:
            if (inc > 0.0)
                inc -= 0.05;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Silla Primitiva🥨");
    glutDisplayFunc(display);
    glutSpecialFunc(ControlTeclado);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    init();
    glutMainLoop();

    return 0;
}