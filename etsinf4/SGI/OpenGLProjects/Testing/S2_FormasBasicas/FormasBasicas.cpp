/*!
	\file		FormasBasicas.cpp
	\brief		Primitivas en Opengl

	Programa para dibujar primitivas basicas usando *freeglut*,
	OpenGl y listas de dibujo

	\author		Roberto Vivo' <rvivo@upv.es>
	\date		2016-2021
 */


#define PROYECTO "ISGI::S2E01::Formas Basicas"

#include <iostream>			
#include <gl/freeglut.h>

using namespace std;

GLuint cuadradito, esfera;

//! Inicializaciones
void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

	// Display List
	cuadradito = glGenLists(1);

	glNewList(cuadradito, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);

	glPointSize(10);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0.5, -0.5, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0.5, 0.5, 0);
	glColor3f(1, 1, 1);
	glVertex3f(-0.5, 0.5, 0);
	glEnd();

	glPopAttrib();
	glEndList();

	esfera = glGenLists(1);
	glNewList(esfera, GL_COMPILE);
	glutWireSphere(1, 20, 20);
	glCallList(cuadradito);
	glEndList();


}

//! Callback de dibujo
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 1, 0);
	glCallList(esfera);
	glutWireTeapot(0.5);

	glFlush();
}

//! Callback de redimensionamiento
void reshape(GLint w, GLint h)
{
}

//! Programa principal
int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);

	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}