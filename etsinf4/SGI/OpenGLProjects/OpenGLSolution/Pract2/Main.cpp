/*
	\author Fabian Scherle Carboneres
*/

#define WINDOWNAME "Estrella de David"
#define _USE_MATH_DEFINES


// Cabeceras
#include <iostream>
#include <GL/freeglut.h>
#include <cmath>


GLuint estrella1;
GLuint estrella2;

void init() {
	std::cout << WINDOWNAME << std::endl;
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

	estrella1 = glGenLists(1); // Obtiene el identificador de la lista
	estrella2 = glGenLists(1); // Obtiene el identificador de la lista

	glColor3f(0.0, 0.0, 1.0);
	
	glNewList(estrella1, GL_COMPILE); // Abre la lista
	glBegin(GL_TRIANGLE_STRIP);
	float r1 = 1.0;
	float r2 = 0.7;
	for (int i = 0; i < 5; i++) {
		glVertex3f(r1 * sin(i * 2 * M_PI / 3), r1 * cos(i * 2 * M_PI / 3), 0.0); // vertices triangulo grande
		glVertex3f(r2 * sin(i * 2 * M_PI / 3), r2 * cos(i * 2 * M_PI / 3), 0.0); // vertices tirangulo pequeño
	}
	glEnd();
	glEndList();


	glNewList(estrella2, GL_COMPILE); // Abre la lista
	glBegin(GL_TRIANGLE_STRIP);
	float r3 = -1.0;
	float r4 = -0.7;
	for (int i = 0; i < 5; i++) {
		glVertex3f(r3 * sin(i * 2 * M_PI / 3), r3 * cos(i * 2 * M_PI / 3), 0.0); // vertices triangulo grande
		glVertex3f(r4 * sin(i * 2 * M_PI / 3), r4 * cos(i * 2 * M_PI / 3), 0.0); // vertices tirangulo pequeño
	}
	glEnd();
	glEndList();
}

void display() {
	// Fondo
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glCallList(estrella1);
	glCallList(estrella2);
	
	glFlush();
}


void reshape(int width, int height) {

}


int main(int argc, char** argv) {
	// Inicializar glut
	glutInit(&argc, argv);

	// Describir los buffers
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Definir y crear la ventana de dibujo
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(WINDOWNAME);

	init(); // Se ejecuta una vez

	// Registrar las callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}