/**
* Programa inicial
*
* @author fabbo
*/

#define WINDOWNAME "Primer programa en OpenGL"

// Cabeceras
#include <iostream>
#include <GL/freeglut.h>

using namespace std;


void display() {
	glClearColor(0.0, 0.0, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush(); // He terminado de dibujar
}


void reshape(int width, int height) {

}


int main(int argc, char** argv) {
	// Inicializar glut
	glutInit(&argc, argv);

	// Describir los buffers
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Definir y crear la ventana de dibujo
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(600, 50);
	glutCreateWindow(WINDOWNAME);

	// Registrar las callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}