/*!
	\file		HolaMundo.cpp
	\brief		Plantilla basica para OpenGL

	Programa para generar una ventana OpenGL usando *freeglut*

	\author		Roberto Vivo' <rvivo@upv.es>
	\date		2016-2021
 */


#define PROYECTO "ISGI::S1E01::Hola OpenGL"

#include <iostream>			
#include <gl/freeglut.h>

using namespace std;

//! Inicializaciones
void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
}

//! Callback de dibujo
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
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
	glutInitWindowSize(600, 400);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}