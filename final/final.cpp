//JUAN CARLOS CONDE RAMÍREZ
//OBJETOS 3D - ILUMINACION
#include <GLUT/glut.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include "../utils/OBJ-Loader/Source/OBJ_Loader.h"

using namespace std;
//Matriz de colores
float colores[9][3] =
	{
		{1.0, 1.0, 1.0},	//0 blanco
		{1.0, 0.0, 0.0},	//1 rojo
		{0.0, 1.0, 0.0},	//2 verde
		{0.0, 0.0, 1.0},	//3 azul
		{0.99, 0.72, 0.07}, //4 amarillo
		{1.0, 0.0, 1.0},	//5 magneta
		{0.0, 1.0, 1.0},	//6 cian
		{0.5, 0.5, 0.5},	//7 gris
		{0.0, 0.0, 0.0},	//8 negro
};

GLdouble vistas[7][9] = {
	//frontal
	{5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	//li
	{0.0f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	//ld
	{0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	//inferior
	{0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	//superior
	{0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	//superior far
	{0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	//trasera
	{-5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f}};

// Initialize Loader
objl::Loader Loader;

int color = 4;	// color de FIGURA
int colorf = 0;   // color de FONDO
int colorl = 3;   // color de LUZ
				  //int colordif= 2; //color difuso de ambiental (verde)
int coloresp = 3; //color especular ambiental
//variables globales para la rotacion
float alpha, beta;
int x0, yy0;
int opc = 5;
GLenum modo = GL_FILL;

GLuint texture_id[7];

//Variables globales para las transformaciones
float xpos = 0, ypos = 0, inc = 0.5;

//Menu de figuras a elegir
typedef enum
{
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8
} opcionMenu;

int LoadBMP(char *filename, int tex_name)
{
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
	if (fread(Header, 1, 0x36, fp_archivo) != 0x36)
		SAIR;
	if (Header[0] != 'B' || Header[1] != 'M')
		SAIR;
	if (CTOI(Header[0x1E]) != 0)
		SAIR;
	if (CTOI(Header[0x1C]) != 24)
		SAIR;

	// Recupera los atributos de la altura y ancho de la imagen

	Width = CTOI(Header[0x12]);
	Height = CTOI(Header[0x16]);
	(CTOI(Header[0x0A]) == 0) ? (DataPos = 0x36) : (DataPos = CTOI(Header[0x0A]));

	imageSize = Width * Height * 3;

	// Llama a la imagen
	image = (GLubyte *)malloc(imageSize);
	int retorno;
	retorno = fread(image, 1, imageSize, fp_archivo);

	if (retorno != imageSize)
	{
		free(image);
		SAIR;
	}

	// Invierte los valores de R y B
	int t, i;

	for (i = 0; i < imageSize; i += 3)
	{
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

void setTexture(string textName)
{

	if (textName.compare("0.002") == 0)
	{
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.000000, 0.000000, 0.000000, 1.0f};
		GLfloat mat_especular[] = {0.009961, 0.009961, 0.009961, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.000000 0.000000 0.000000
		//Ks 0.009961 0.009961 0.009961
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
	}

	else if (textName.compare("500000.001") == 0)
	{
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.313726, 0.000000, 0.000000, 1.0f};
		GLfloat mat_especular[] = {0.009961, 0.009961, 0.009961, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.313726 0.000000 0.000000
		//Ks 0.009961 0.009961 0.009961
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
	}
	else if (textName.compare("AlternatingBrick_ColorMapMaterial") == 0)
	{
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.690196, 0.690196, 0.690196, 1.0f};
		GLfloat mat_especular[] = {0.001176, 0.001176, 0.001176, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		glBindTexture(GL_TEXTURE_2D, texture_id[0]);
		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.690196 0.690196 0.690196
		//Ks 0.001176 0.001176 0.001176
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
		//map_Kd "AlternatingBrick-ColorMap.bmp"
	}

	else if (textName.compare("Material_001") == 0)
	{
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.000000, 0.439216, 0.015686, 1.0f};
		GLfloat mat_especular[] = {0.017647, 0.048627, 0.002745, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.000000 0.439216 0.015686
		//Ks 0.017647 0.048627 0.002745
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
	}

	else if (textName.compare("WebGL_Brick_2") == 0)
	{
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.690196, 0.690196, 0.690196, 1.0f};
		GLfloat mat_especular[] = {0.004706, 0.004706, 0.004706, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		glBindTexture(GL_TEXTURE_2D, texture_id[1]);
		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.690196 0.690196 0.690196
		//Ks 0.004706 0.004706 0.004706
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
		//map_Kd "rocks.bmp"
	}

	else if (textName.compare("floorMaterial") == 0)
	{
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.690196, 0.690196, 0.690196, 1.0f};
		GLfloat mat_especular[] = {0.001176, 0.001176, 0.001176, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		glBindTexture(GL_TEXTURE_2D, texture_id[2]);
		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.690196 0.690196 0.690196
		//Ks 0.001176 0.001176 0.001176
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
		//map_Kd "floor.bmp"
	}

	else if (textName.compare("grass_texture_015Material") == 0)
	{
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.690196, 0.690196, 0.690196, 1.0f};
		GLfloat mat_especular[] = {0.001176, 0.001176, 0.001176, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		glBindTexture(GL_TEXTURE_2D, texture_id[3]);

		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.690196 0.690196 0.690196
		//Ks 0.001176 0.001176 0.001176
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
		//map_Kd "grass-texture-015.bmp"
	}

	else if (textName.compare("roofMaterial") == 0)
	{
		// Propiedades del material
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.690196, 0.690196, 0.690196, 1.0f};
		GLfloat mat_especular[] = {0.001176, 0.001176, 0.001176, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		glBindTexture(GL_TEXTURE_2D, texture_id[4]);
		// Ns 96.078431
		// Ka 1.000000 1.000000 1.000000
		// Kd 0.690196 0.690196 0.690196
		// Ks 0.001176 0.001176 0.001176
		// Ke 0.000000 0.000000 0.000000
		// Ni 1.000000
		// d 1.000000
		//illum 2
		//map_Kd "roof.bmp"
	}

	else if (textName.compare("trunkMaterial") == 0)
	{
		// Propiedades del material
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.690196, 0.690196, 0.690196, 1.0f};
		GLfloat mat_especular[] = {0.001176, 0.001176, 0.001176, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		glBindTexture(GL_TEXTURE_2D, texture_id[5]);

		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.690196 0.690196 0.690196
		//Ks 0.001176 0.001176 0.001176
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
		//map_Kd "trunk.bmp"
	}

	else if (textName.compare("woodplanks2Material") == 0)
	{
		// Propiedades del material
		GLfloat mat_shininess[] = {96.078431};
		GLfloat mat_ambiente[] = {1.000000, 1.000000, 1.000000, 1.0f};
		GLfloat mat_difuso[] = {0.690196, 0.690196, 0.690196, 1.0f};
		GLfloat mat_especular[] = {0.001176, 0.001176, 0.001176, 1.0f};

		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

		glBindTexture(GL_TEXTURE_2D, texture_id[6]);
		//Ns 96.078431
		//Ka 1.000000 1.000000 1.000000
		//Kd 0.690196 0.690196 0.690196
		//Ks 0.001176 0.001176 0.001176
		//Ke 0.000000 0.000000 0.000000
		//Ni 1.000000
		//d 1.000000
		//illum 2
		//map_Kd "woodplanks2.bmp"
	}
}

void luzAlt(void)
{
	GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};	// "cor"
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
	GLfloat posicaoLuz[4] = {0.0, 400.0, 0.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4] = {0.7, 0.5, 0.5, 0.0};
	GLint especMaterial = 60;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
}

void init(void)
{
	//luzUno();
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D); //
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(6, texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	//LoadBMP("../tree/textures/AlternatingBrick-ColorMap.bmp", 0);
	LoadBMP("../tree/textures/afuera.bmp", 0);
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);
	LoadBMP("../tree/textures/woodplanks2.bmp", 1);
	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	LoadBMP("../tree/textures/floor.bmp", 2);
	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	LoadBMP("../tree/textures/grass-texture-015.bmp", 3);
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	LoadBMP("../tree/textures/te.bmp", 4);
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	LoadBMP("../tree/textures/trunk.bmp", 5);
	glBindTexture(GL_TEXTURE_2D, texture_id[6]);
	LoadBMP("../tree/textures/door.bmp", 6);
}

void scenario(void)
{
	//glPolygonMode(GL_FRONT_AND_BACK, modo);
	//glutSolidSphere(1, 50, 50);
	//glPushMatrix();
	//glLoadIdentity();
	//glScalef(0.5,0.5,0.5);
	//glTranslatef(0, 1, -1);
	//piramide();
	for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		for (int j = 0; j < curMesh.Indices.size(); j += 3)
		{

			setTexture(curMesh.MeshMaterial.name);
			// Triangle Vertices
			int v1idx = curMesh.Indices[j];
			int v2idx = curMesh.Indices[j + 1];
			int v3idx = curMesh.Indices[j + 2];

			glBegin(GL_TRIANGLES);
			glTexCoord2d(
				curMesh.Vertices[v1idx].TextureCoordinate.X,
				curMesh.Vertices[v1idx].TextureCoordinate.Y);
			glNormal3f(
				curMesh.Vertices[v1idx].Normal.X,
				curMesh.Vertices[v1idx].Normal.Y,
				curMesh.Vertices[v1idx].Normal.Z);
			glVertex3f(
				curMesh.Vertices[v1idx].Position.X,
				curMesh.Vertices[v1idx].Position.Y,
				curMesh.Vertices[v1idx].Position.Z);

			glTexCoord2d(
				curMesh.Vertices[v2idx].TextureCoordinate.X,
				curMesh.Vertices[v2idx].TextureCoordinate.Y);
			glNormal3f(
				curMesh.Vertices[v2idx].Normal.X,
				curMesh.Vertices[v2idx].Normal.Y,
				curMesh.Vertices[v2idx].Normal.Z);
			glVertex3f(
				curMesh.Vertices[v2idx].Position.X,
				curMesh.Vertices[v2idx].Position.Y,
				curMesh.Vertices[v2idx].Position.Z);

			glTexCoord2d(
				curMesh.Vertices[v3idx].TextureCoordinate.X,
				curMesh.Vertices[v3idx].TextureCoordinate.Y);
			glNormal3f(
				curMesh.Vertices[v3idx].Normal.X,
				curMesh.Vertices[v3idx].Normal.Y,
				curMesh.Vertices[v3idx].Normal.Z);
			glVertex3f(
				curMesh.Vertices[v3idx].Position.X,
				curMesh.Vertices[v3idx].Position.Y,
				curMesh.Vertices[v3idx].Position.Z);
			glEnd();
		}
	}
}

void perspectiva(void)
{

	glClearColor(colores[colorf][0], colores[colorf][1], colores[colorf][2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//luzAmbiental();
	luzAlt();

	//gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	//glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 5.0f);
	gluPerspective(20.0f, 1.0f, 1.0f, 100.0f);

	gluLookAt(vistas[opc][0], vistas[opc][1], vistas[opc][2], vistas[opc][3],
			  vistas[opc][4], vistas[opc][5], vistas[opc][6], vistas[opc][7], vistas[opc][8]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(xpos, ypos, 0);

	if (opc != 9)
		glScalef(inc, inc, inc);
	else
		glScalef(inc - 0.15, inc - 0.15, inc - 0.15);

	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
	glEnable(GL_CULL_FACE);
	//glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	//glRotatef(beta, 0.0f, 1.0f, 0.0f);

	//glColor3f(0.61, 0.66, 0.77);
	//glPolygonMode(GL_FRONT,GL_FILL);
	scenario();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

//Accion del mouse
void onMouse(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN))
	{
		x0 = x;
		yy0 = y;
	}
}

//Incremento o decremente de los angulos de rotacion
void onMotion(int x, int y)
{
	alpha = (alpha + (y - yy0));
	beta = (beta + (x - x0));
	x0 = x;
	yy0 = y;
	glutPostRedisplay();
}

void menuFiguras(int opcion)
{
	switch (opcion)
	{
	case F1:
		opc = 0;
		break;
	case F2:
		opc = 1;
		break;
	case F3:
		opc = 2;
		break;
	case F4:
		opc = 3;
		break;
	case F5:
		opc = 4;
		break;
	case F6:
		opc = 5;
		break;
	case F7:
		modo = GL_LINE;
		break;
	case F8:
		modo = GL_FILL;
		break;
	}
	glutPostRedisplay();
}

//Creacion de menu y submenus
void creacionMenu(void)
{
	int menuPerspectiva, menuVista;
	int on, off;

	menuVista = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Vista Rejilla", F7);
	glutAddMenuEntry("Vista Relleno", F8);
	//----------------------------------------------------------

	// NIVEL 2 DE SUB-MENU PARA TIPO DE FIGURA
	menuPerspectiva = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Frontal", F1);
	glutAddMenuEntry("Trasera", F6);
	glutAddMenuEntry("Lateral Derecha", F2);
	glutAddMenuEntry("Lateral Izquierda", F3);
	glutAddMenuEntry("Superior", F4);
	glutAddMenuEntry("Inferior", F5);
	glutAddSubMenu("Tipo de vista", menuVista);

	/*
        AQUI VAN LAS OPCIONES
    */

	//---------------------------------------------------------
	// glutAddSubMenu("Desactivar Luces: ", off);
	/*
        AQUI VAN LOS SUB-MENUS DE NIVEL 2
    */

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
	bool loadout;
	// Load .obj File
	loadout = Loader.LoadFile("../tree/tree-toonB.obj");
	if (loadout)
	{
		glutInit(&argc, argv);

		glutInitWindowSize(1000, 1000);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Final 🥂");
		init();
		glutDisplayFunc(perspectiva);
		glutMouseFunc(onMouse);
		glutMotionFunc(onMotion);
		//creacionMenu();
		glutMainLoop();
	}
	return 0;
}
