/**
* HolaMundo.cpp
*
* Programa inicial
*
* @author yuuri, 2021
*/

#define PROYECTO "Hola OpenGL"

// Cabeceras
#include <iostream>
#include <GL/freeglut.h>

using namespace std;

void display()
{
	glClearColor(0.0, 0.2, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush(); // He terminado de dibujar
}

void reshape(int width, int height)
{

}

int main(int argc, char** argv)
{
	// Inicializar glut
	glutInit(&argc, argv);

	// Describir los buffers
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Definir y crear la ventana de dibujo
	glutInitWindowsSize(600, 400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(PROYECTO);

	// Registrar las callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atención a eventos
	glutMainLoop();
}