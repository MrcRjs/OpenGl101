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

float alpha, beta;
int x0, y0;
GLuint texture_id[4];

int LoadBMP(char *filename, int tex_name) {
#define SAIR        {fclose(fp_archivo); return -1;}
#define CTOI(C)     (*(int*)&C)

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


void onMouse(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {
        x0 = x;
        y0 = y;
    }
}

void onMotion(int x, int y) {
    alpha = (alpha + (y - y0));
    beta = (beta + (x - x0));
    x0 = x;
    y0 = y;
    glutPostRedisplay();
}


void myinit(void) {

    // Propiedades del material
    GLfloat mat_especular[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    GLfloat mat_ambiente[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat mat_difuso[] = {0.5f, 0.5f, 0.5f, 1.0f};

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

    // Parametros de las luces

    // Habilitando la luz
    glEnable(GL_LIGHTING);

    // Especifica una luz de direccion simple
    GLfloat ambiente1[] = {0.5f, 0.5f, 0.5f};
    GLfloat difusa1[] = {0.5f, 0.5f, 0.5f};
    GLfloat especular1[] = {1.0f, 0.0f, 0.0f};
    GLfloat posicion1[] = {0.0f, 0.0f, 5.0f, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, especular1);
    glLightfv(GL_LIGHT0, GL_POSITION, posicion1);

    glEnable(GL_LIGHT0);

    // Especifica un solo proyector posicional
    GLfloat ambiente2[] = {1.0f, 1.0f, 0.0f};
    GLfloat difuso2[] = {1.0f, 0.0f, 0.0f};
    GLfloat posicion2[] = {1.0f, 0.0f, 5.0f, 1.0};
    GLfloat direccion2[] = {0.0f, 0.0f, -5.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, difuso2);
    glLightfv(GL_LIGHT1, GL_POSITION, posicion2);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direccion2);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);

    glEnable(GL_LIGHT1);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glEnable(GL_TEXTURE_2D);//
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(2, texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    LoadBMP("madera.bmp", 0);
    //glGenTextures(2,&texture_id2);
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    LoadBMP("textura_lava.bmp", 1);
    glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    LoadBMP("diamantemaincra.bmp", 2);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);
    //glutSolidCube(0.5);
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);

    //Front Face
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(-0.3f, -0.3f, 0.3f);
    glTexCoord2f(1, 0);
    glVertex3f(0.3f, -0.3f, 0.3f);
    glTexCoord2f(1, 1);
    glVertex3f(0.3f, 0.3f, 0.3f);
    glTexCoord2f(0, 1);
    glVertex3f(-0.3f, 0.3f, 0.3f);
    glEnd();

    //Back Face
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 0);
    glVertex3f(-0.3f, -0.3f, -0.3f);
    glTexCoord2f(1, 1);
    glVertex3f(-0.3f, 0.3f, -0.3f);
    glTexCoord2f(0, 1);
    glVertex3f(0.3f, 0.3f, -0.3f);
    glTexCoord2f(0, 0);
    glVertex3f(0.3f, -0.3f, -0.3f);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    //Left Face
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 0);
    glVertex3f(-0.3f, -0.3f, 0.3f);
    glTexCoord2f(1, 1);
    glVertex3f(-0.3f, 0.3f, 0.3f);
    glTexCoord2f(0, 1);
    glVertex3f(-0.3f, 0.3f, -0.3f);
    glTexCoord2f(0, 0);
    glVertex3f(-0.3f, -0.3f, -0.3f);
    glEnd();

    //Right Face
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(0.3f, -0.3f, 0.3f);
    glTexCoord2f(1, 0);
    glVertex3f(0.3f, -0.3f, -0.3f);
    glTexCoord2f(1, 1);
    glVertex3f(0.3f, 0.3f, -0.3f);
    glTexCoord2f(0, 1);
    glVertex3f(0.3f, 0.3f, 0.3f);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, texture_id[2]);

    //Top Face
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(-0.3f, 0.3f, 0.3f);
    glTexCoord2f(0, 1);
    glVertex3f(0.3f, 0.3f, 0.3f);
    glTexCoord2f(1, 1);
    glVertex3f(0.3f, 0.3f, -0.3f);
    glTexCoord2f(1, 0);
    glVertex3f(-0.3f, 0.3f, -0.3f);
    glEnd();

    //Botton Face
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex3f(-0.3f, -0.3f, 0.3f);
    glTexCoord2f(0, 0);
    glVertex3f(-0.3f, -0.3f, -0.3f);
    glTexCoord2f(1, 0);
    glVertex3f(0.3f, -0.3f, -0.3f);
    glTexCoord2f(1, 1);
    glVertex3f(0.3f, -0.3f, 0.3f);
    glEnd();


    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0f, (GLdouble) w / (GLdouble) h, 1.0f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Texturas");
    myinit();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutMainLoop();
    return 0;
}






