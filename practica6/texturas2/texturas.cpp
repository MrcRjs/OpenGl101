#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

static int year = 0, day = 0;
int posicionluz = 0;

int tx;

GLuint  texture_id[1];

int  LoadBMP(char *filename)
 {
    #define SAIR        {fclose(fp_arquivo); return -1;}
    #define CTOI(C)     (*(int*)&C)
 
    GLubyte     *image;
    GLubyte     Header[0x54]; 
    GLuint      DataPos, imageSize;
    GLsizei     Width,Height;

    int nb = 0;
    
    
    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE * fp_arquivo = fopen(filename,"rb");
    if (!fp_arquivo) 
        return -1;
    if (fread(Header,1,0x36,fp_arquivo)!=0x36) 
        SAIR;
    if (Header[0]!='B' || Header[1]!='M')   
        SAIR;
    if (CTOI(Header[0x1E])!=0)              
        SAIR;
    if (CTOI(Header[0x1C])!=24)             
        SAIR;
    
    // Recupera los atributos de la altura y ancho de la imagen 
    
    Width   = CTOI(Header[0x12]);
    Height  = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
 
    imageSize=Width*Height*3;
    
    // Llama a la imagen
    image = (GLubyte *) malloc ( imageSize );
    int retorno;
    retorno = fread(image,1,imageSize,fp_arquivo);
    
    if (retorno !=imageSize) 
     {
        free (image);
        SAIR;
     }

    // Invierte los valores de R y B
    int t, i;
    
    for ( i = 0; i < imageSize; i += 3 )
     {
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
     } 

    // Tratamiento de textura para OpenGL

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   
    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
                        
    fclose (fp_arquivo);
    free (image);
    return 1;
 }


void init(void)
{

   tx=0;
   
   GLfloat ambiente[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat difusa[] = { 0.7, 0.7, 0.7, 1.0 };
   GLfloat especular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat posicion[] = { 0.0, 3.0, 2.0, 0.0 };
   GLfloat lmodelo_ambiente[] = { 0.2, 0.2, 0.2, 1.0 };


   glClearColor(0.0, 0.0, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
   glLightfv(GL_LIGHT0, GL_POSITION, posicion);
   glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodelo_ambiente);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   
   
   /*
     Habilita el Texturizado.
     Creacion inicial de las texturas.     
   */
   
   glEnable ( GL_TEXTURE_2D );
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
   glGenTextures ( 1, texture_id );
   glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
   LoadBMP ("tenis.bmp");   
 

}


void esfera ( int radio,int longitud,int latitud  )
{   
   GLUquadricObj*  q = gluNewQuadric ( );
   gluQuadricDrawStyle ( q, GLU_FILL   );
   gluQuadricNormals   ( q, GLU_SMOOTH );
   gluQuadricTexture   ( q, GL_TRUE    );
   gluSphere ( q, radio, longitud, latitud );
   gluDeleteQuadric ( q );
}


void display(void)
{
  GLfloat semiespecular[4]={0.0,0.0,0.0,1.0};
  GLfloat especular[] = { 1.0, 1.0, 1.0, 1.0 };

  GLfloat posicion[] = { 0.0, 3.0, 2.0, 0.0 };

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f (1.0, 1.0, 1.0);

  glPushMatrix () ;

    glRotated ((GLdouble) posicionluz, 1.0, 0.0, 0.0);
    glLightfv (GL_LIGHT0, GL_POSITION, posicion);

  glPopMatrix(); 
 
 glPushMatrix (); 
     glRotatef (tx, 1.0, 0.0, 0.0);
     glTranslatef( 0.0, 0.0, 2.0);
 glPushMatrix ();
     glTranslatef (0.0, 0.0, -3.0);
 glPushMatrix ();
     glRotatef (9, 0.0, 0.0, 1.0);
    
    glPushMatrix();
      glRotatef ((GLfloat) year, 1.0, 0.0, 0.0);
      
      glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
      glColor3f (1.0, 1.0, 1.0);


      /* Define las propiedades del material */
      // reflectancia del material
      glMaterialfv(GL_FRONT,GL_SPECULAR, semiespecular);
        // Define el brillo
      glMateriali(GL_FRONT,GL_SHININESS,20);

      
      /* Habilita la textura y crea la esfera */
      glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 
      esfera ( 1.50, 20, 18); 

    glPopMatrix();
 glPopMatrix();
 glPopMatrix();
 glPopMatrix();

  glutSwapBuffers();

}


void reshape (int w, int h)
{

  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
      case 'd':
      case 'D':
           glDisable(GL_TEXTURE_2D);
           glutPostRedisplay();
           break;
      case 'A':
      case 'a':
           glEnable(GL_TEXTURE_2D);
           glutPostRedisplay();
           break;
  }
}

void spinDisplay(void)
{
  year = (year + 1) % 360;
  day  = (day + 2 ) % 360;
  tx = (tx + 1) % 360 ;
  
  glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
  switch (button) {
      case GLUT_LEFT_BUTTON:
           if (state == GLUT_DOWN)
              glutIdleFunc(spinDisplay);
           break;
      case GLUT_MIDDLE_BUTTON:
           if (state == GLUT_DOWN)
              glutIdleFunc(NULL);
           break;
      case GLUT_RIGHT_BUTTON:
           posicionluz = (posicionluz + 1) % 360;
           glutPostRedisplay();	  
           break;
      default:
           break;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (800, 600);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Texturas BMP");
  init ();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}		