/*!
	\file		Texturas.cpp
	\brief		Uso de texturas en OpenGL con Freeimage

	Dibujar un plano con una textura de superposicion y un toro
	con una textura de mapa esferico. Texturar el fondo con una
	imagen fija usando una funcion de Utilidades.h.

	\author		Roberto Vivo' <rvivo@upv.es>
	\version	1.0
	\date		2016 - 2021
	\copyright(c) upv.es LGPL
*/

#define PROYECTO "ISGI::S8E01::Texturas"

#include <iostream>			
#include <Utilidades.h>

using namespace std;

static float girox = 0, giroy = 0;
static int xanterior, yanterior;

GLuint erre, nubes;


void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;
	cout << endl <<
		"Pulse 0 para encender/apagar LIGHT0" << endl <<
		"Pulse 1 para encender/apagar LIGHT1" << endl;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Luces (caracteristicas cromaticas)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, GRISCLARO);
	glLightfv(GL_LIGHT0, GL_SPECULAR, BLANCO);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, GRISOSCURO);
	glLightfv(GL_LIGHT1, GL_SPECULAR, GRISCLARO);

	// Carga de texturas
	glGenTextures(1, &erre);
	glBindTexture(GL_TEXTURE_2D, erre);
	loadImageFile((char *)"erre.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &nubes);
	glBindTexture(GL_TEXTURE_2D, nubes);
	loadImageFile((char*)"nubes.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Configurar el motor de render
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Fondo fijo
	glBindTexture(GL_TEXTURE_2D, nubes);
	texturarFondo();

	// Seleccion de la matriz modelo-vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Si situo las luces aqui son solidarias a la camara
	// (luz de minero)

	static GLfloat P1[] = { 0,0,-1,1 }; // puntual a 1 delante de la camara
	glLightfv(GL_LIGHT1, GL_POSITION, P1);

	// Situamos y orientamos la camara
	gluLookAt(2, 2, 3, 0, 0, 0, 0, 1, 0);

	// Si situo las luces aqui son fijas en la escena
	static GLfloat P0[] = { -5,5,0,0 }; // direccional
	glLightfv(GL_LIGHT0, GL_POSITION, P0);


	ejes();


	// Geometria
	glRotatef(girox, 1, 0, 0);
	glRotatef(giroy, 0, 1, 0);

	// Material difuso
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ORO);
	glMaterialfv(GL_FRONT, GL_SPECULAR, GRISOSCURO);
	glMaterialf(GL_FRONT, GL_SHININESS, 2);
	glShadeModel(GL_SMOOTH);

	// Textura a aplicar
	glBindTexture(GL_TEXTURE_2D, erre);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


	// Un cuadrado
	glPushMatrix();
	glTranslatef(0, 0, -1);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2f(2, 2);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(0, 2);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, 0);
	glTexCoord2f(2, 0);
	glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix();

	// Mapa esferico aplicado a un toro
	// Material brillante
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ORO);
	glMaterialfv(GL_FRONT, GL_SPECULAR, BLANCO);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glShadeModel(GL_SMOOTH);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBindTexture(GL_TEXTURE_2D, nubes);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glutSolidTorus(0.3, 0.7, 40, 40);
	glPopAttrib();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	float ra = (float)w / h;

	// Fijamos el marco dentro de la ventana de dibujo
	glViewport(0, 0, w, h);

	// Seleccionar la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Camara perspectiva
	gluPerspective(40, ra, 0.1, 100);
}

void onClick(int boton, int estado, int x, int y)
{
	// Callback de atencion al pulsado de un boton del raton

	// Almacenar la posicion cuando click
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
	}
}

void onDrag(int x, int y)
{
	// Calbback de arrastre del raton pulsado

	const float pixel2grados = 1;
	// Al mover el raton hacia la derecha la x aumenta
	// y el giro es alrededor del eje y positivo 
	giroy += (x - xanterior) * pixel2grados;
	// Al mover el raton hacia abajo la y aumenta 
	// y el giro es alrededor del eje x positivo
	girox += (y - yanterior) * pixel2grados;

	xanterior = x;
	yanterior = y;
	// Encolar un evento de redibujo
	glutPostRedisplay();
}

//! Apaga y enciende luces
void onKey(unsigned char tecla, int x, int y)
{
	static bool L0 = true;
	static bool L1 = true;
	switch (tecla) {
	case '0':
		L0 ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
		L0 = !L0;
		break;
	case '1':
		L1 ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
		L1 = !L1;
		break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);
	glutKeyboardFunc(onKey);

	// Bucle de atencion a eventos
	glutMainLoop();
	FreeImage_DeInitialise();
}