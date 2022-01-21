/*
	\author Fabian Scherle Carboneres
*/

#define WINDOWNAME "Estrella3D"
#define _USE_MATH_DEFINES


// Cabeceras
#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include <Utilidades.h>
#include <math.h>


GLuint estrella1;
GLuint estrella2;

float posCamX = 2.0;
float posCamY = 3.0;
float posCamZ = 4.0;


void init() {
	std::cout << WINDOWNAME << std::endl;
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

	estrella1 = glGenLists(1); // Obtiene el identificador de la lista
	estrella2 = glGenLists(1); // Obtiene el identificador de la lista

	glEnable(GL_DEPTH_TEST);

	//glColor3f(0.0, 0.0, 1.0);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(/* Posicion de la camara */ posCamX, posCamY, posCamZ,
		/* Punto de interes */ 0, 0, 0,
		/*vertical de la camara*/ 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Asi aseguramos que se cargue la matriz identidad

	for (int i = 1; i <= 6; i++) {
		// Dibujo de las 6 estrellas
		glPushMatrix();
		glRotatef(30*i, 0, 1, 0); // Rotacion en eje y
		glColor3f(1.0 - i / 10.0, i / 10.0, 0.0);
		glCallList(estrella1);
		glCallList(estrella2);
		glPopMatrix();
	}
	glColor3f(0.0, 0.0, 1.0);
	glutWireSphere(1.0, 20, 20);

	glFlush();
}

// Callback de redimensionamiento
void reshape(int width, int height) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Cambiamos el marco de dibujo al de la ventana
	glViewport(0, 0, width, height);
	// Relacion de aspecto:
	float ar = (float)width / height;

	// Seleccionar tipo de camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2, 2, -2, 2, -2, 2); Camara ortográfica
	// Camara perspectiva: Plano cercano es estrictamente positivo
	gluPerspective(2*asin(1.0 / sqrt(posCamX* posCamX 
		+ posCamY*posCamY  + posCamZ*posCamZ))*180.0 / M_PI, ar, 1, 100);
	// fovy es arcoseno del radio de la esfera dividido la distancia de
	// la camara al cengtro de cooredenadas (esta en radianes, se pasa a grados)
}


int main(int argc, char** argv) {
	// Inicializar glut
	glutInit(&argc, argv);

	// Describir los buffers, con GLUT_DEPTH se usa el z_buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

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