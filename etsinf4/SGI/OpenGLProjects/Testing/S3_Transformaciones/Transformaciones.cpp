/*!
	\file		Transformaciones.cpp
	\brief		Ejemplo de transformaciones para OpenGL

	Programa para dibujar una flor con listas y transformaciones

	\author		Roberto Vivo' <rvivo@upv.es>
	\date		2016-2021
 */


#define PROYECTO "ISGI::S3E01::FLOR"

#include <iostream>			
#include <gl/freeglut.h>

GLuint petalo, corola, flor;

using namespace std;

//! Inicializaciones
void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

	// Modelado de objetos -----------------------------

	// Petalo
	petalo = glGenLists(1);
	glNewList(petalo, GL_COMPILE);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glScalef(0.15, 0.5, 0.1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glEndList();

	// Corola
	corola = glGenLists(1);
	glNewList(corola, GL_COMPILE);

	for (auto i = 0; i < 12; i++) {
		glPushMatrix();
		glRotatef(30*i, 0, 0, 1);
		glTranslatef(0, 0.25, 0);
		glScalef(0.5, 0.5, 0.5);
		glCallList(petalo);
		glPopMatrix();
	}

	glPushMatrix();
	glColor3f(1, 1, 0);
	glScalef(0.25, 0.25, 0.25);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glEndList();

	// Flor
	flor = glGenLists(1);
	glNewList(flor, GL_COMPILE);

	glColor3f(0, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.125, 0);
	glScalef(0.05, 0.75, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.25, 0);
	glRotatef(7, 0, 0, 1);
	glScalef(0.5, 0.5, 0.5);
	glCallList(corola);
	glPopMatrix();

	glEndList();
}

//! Callback de dibujo
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i = 0; i < 100; i++) {
		glPushMatrix();
		glTranslatef((rand() % 200 - 100) / 100.0,
			(rand() % 100 - 50) / 100.0,
			0);
		glScalef(0.3, 0.3, 0.1);
		glCallList(flor);
		glPopMatrix();
	}
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