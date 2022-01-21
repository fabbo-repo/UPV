/**
*	@author: Fabian Scherle
*/

#define WINDOWNAME "Reloj 3D"
#define _USE_MATH_DEFINES


// Librerias
#include <iostream>
#include <sstream>
#include <GL/freeglut.h>
#include <cmath>
#include <Utilidades.h>
#include <math.h>
#include <ctime>
#include <string>
using namespace std;

GLuint stargateInt;
GLuint stargateExt;

float posCamX = 0.0;
float posCamY = 0.0;
float posCamZ = 12.0;
float dx = 0.5;
float anguloForE = 0;
float anguloSec = 0;
float anguloMinut = 0;
int hora = 0;
int fpsCount = 0;
float ar;
static const int TASA_FPS = 60;

/**
*	Metodo para dibujar el arco externo del reloj
*/
void createSGExt() {
	glPushMatrix();
		glColor3f(0.34, 0.34, 0.34);
		// 0.1f de espesor
		glutSolidTorus(0.04f, 0.96f, 2, 50);
	glPopMatrix();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.2, 0.0, 0.0);
	glEnd();
}

/**
*	Metodo para dibujar el arco interno del reloj
*/
void createSGInt() {
	glPushMatrix();
		glColor3f(0.50, 0.50, 0.50);
		// 0.1f de espesor
		glutSolidTorus(0.08f, 0.84f, 2, 50);
	
		// Simbolos del arco interior:
		glColor3f(0.0, 0.0, 0.0);
		// Simbolo 1: Una tetera
		glPushMatrix();
			glTranslatef(0.0, 0.84, 0.0); glutSolidTeapot(0.06f);
		glPopMatrix();
		// Simbolo 2: Una esfera
		glPushMatrix();
			glTranslatef(0.84f * cos(60 * M_PI / 180)
				, 0.84f * sin(60 * M_PI / 180), 0.0);
			glutWireSphere(0.06f, 5, 5);
		glPopMatrix();
		// Simbolo 3: Una esfera
		glPushMatrix();
			glTranslatef(0.84f * cos(30 * M_PI / 180)
				, 0.84f * sin(30 * M_PI / 180), 0.0);
			glutWireSphere(0.06f, 10, 10);
		glPopMatrix();
		// Simbolo 4: Un cubo
		glPushMatrix();
			glTranslatef(0.84, 0.0, 0.0); glutSolidCube(0.06f);
		glPopMatrix();
		// Simbolo 5: Un Icosahedron
		glPushMatrix();
			glTranslatef(0.84f * cos(30 * M_PI / 180)
				, -0.84f * sin(30 * M_PI / 180), 0.0);
			glScalef(0.05, 0.05, 0.05); glutSolidIcosahedron();
		glPopMatrix();
		// Simbolo 6: Un Icosahedron
		glPushMatrix();
			glTranslatef(0.84f * cos(60 * M_PI / 180)
				, -0.84f * sin(60 * M_PI / 180), 0.0);
			glScalef(0.05, 0.05, 0.05); glutWireIcosahedron();
		glPopMatrix();
		// Simbolo 7: Un Octahedron
		glPushMatrix();
			glTranslatef(0.0, -0.84, 0.0);
			glScalef(0.05, 0.05, 0.05); glutSolidOctahedron();
		glPopMatrix();
		// Simbolo 8: Un Tetrahedron
		glPushMatrix();
			glTranslatef(-0.84f * cos(60 * M_PI / 180)
				, -0.84f * sin(60 * M_PI / 180), 0.0);
			glScalef(0.05, 0.05, 0.05); glutSolidTetrahedron();
		glPopMatrix();
		// Simbolo 9: Un Tetrahedron
		glPushMatrix();
			glTranslatef(-0.84f * cos(30 * M_PI / 180)
				, -0.84f * sin(30 * M_PI / 180), 0.0);
			glScalef(0.05, 0.05, 0.05); glutWireTetrahedron();
		glPopMatrix();
		// Simbolo 10: Un Dodecahedron
		glPushMatrix();
			glTranslatef(-0.84, 0.0, 0.0);
			glScalef(0.03, 0.03, 0.03); glutSolidDodecahedron();
		glPopMatrix();
		// Simbolo 11: Un Tetrahedron
		glPushMatrix();
			glTranslatef(-0.84f * cos(30 * M_PI / 180)
				, 0.84f * sin(30 * M_PI / 180), 0.0);
			glutWireCone(0.06f, 0.06f, 4, 2);
		glPopMatrix();
		// Simbolo 12: Un Tetrahedron
		glPushMatrix();
			glTranslatef(-0.84f * cos(60 * M_PI / 180)
				, 0.84f * sin(60 * M_PI / 180), 0.0);
			glutWireCone(0.06f, 0.06f, 8, 2);
		glPopMatrix();

		for (int i = 0; i < 12; i++) {
			glPushMatrix();
				glColor3f(0.0, 0.0, 0.0); glRotatef(i*30+15, 0, 0, 1);
				glTranslatef(0.835, 0.0, 0.0); glScalef(1.0, 0.1, 0.3);
				glutSolidCube(0.15f);
			glPopMatrix();
		}
	glPopMatrix();
}

void init() {
	std::cout << WINDOWNAME << std::endl;
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	
	stargateExt = glGenLists(1); // Obtiene el identificador de la lista
	glNewList(stargateExt, GL_COMPILE); // Abre la lista
		createSGExt();
	glEndList();
	
	stargateInt = glGenLists(1); // Obtiene el identificador de la lista
	glNewList(stargateInt, GL_COMPILE); // Abre la lista
		createSGInt();
	glEndList();

	//glColor3f(0.0, 0.0, 1.0);
}

/**
*	Metodo para dibujar strings
*/
void RenderString(float x, float y, void* font, const char* string, 
	const float red, const float green, const float blue) {
	glColor3f(red, green, blue);
	glRasterPos2f(x, y);
	glutBitmapString(font, (unsigned char*) string);
}

/**
*	 Metodo que cuenta los frames por segundo
*/
void FPS() {
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	int ttrans = ahora - antes;
	static int fotogramas = 0;
	fotogramas++;
	if (ttrans >= 1000) {
		// Ponemos los fps en el titulo de la ventana
		stringstream titulo;
		titulo << WINDOWNAME << " | FPS = " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		fotogramas = 0;
		antes = ahora;
	}
}

/**
*	Metodo para actualizar los angulos de minutos, segundos y actualizar la hora
*	para que cada cono cambie de color dependiendo de la hora
*/
void dibujaHoras() {
	if (hora >= 12) hora -= 12;
	if (hora == 11) {
		glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glRotatef(180, 0, 1, 0);
		glutSolidCone(0.76, 0.0, 50, 8);
		glPopMatrix();
	}
	else if (dx == 0) dx = 1;
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		if (hora >= i) glColor3f(1.0, 0.0, 0.0);
		else glColor3f(0.4, 0.0, 0.0);
		glRotatef(-30*i, 0, 0, 1);
		glTranslatef(0.0, 1.0, 0.05); glRotatef(90, 1, 0, 0);
		glutSolidCone(0.1, 0.2, 10, 8);
		glPopMatrix();
	}
}

/**
*	Metodo para el dibujado de cada frame
*/
void display() {
	// Fondo
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(/* Posicion de la camara */ posCamX, posCamY, posCamZ,
		/* Punto de interes */ 0, 0, 0,
		/*vertical de la camara*/ 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Asi aseguramos que se cargue la matriz identidad
	
	glPushMatrix();
		glCallList(stargateExt);
	glPopMatrix();

	glPushMatrix();
		// El aro interno girará junto con los simbolos
		glRotatef(anguloForE, 0, 0, 1); glCallList(stargateInt);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-anguloSec, 0, 0, 1);
		glTranslatef(0.0, 0.0, 0.05);
		glRotatef(-90, 1, 0, 0);
		glColor3f(1.0, 0.0, 0.0); glutWireCone(0.1, 0.2, 10, 8);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-anguloMinut, 0, 0, 1);
		glTranslatef(0.0, 0.3, 0.05);
		glRotatef(-90, 1, 0, 0);
		glColor3f(0.0, 1.0, 0.0); glutWireCone(0.07, 0.3, 10, 8);
	glPopMatrix();

	dibujaHoras();
	FPS();

	// Cambio la perspectiva de la camara para dar la sensación de movimiento del reloj
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(2 * asin(1.0 / sqrt(posCamX * posCamX
		+ posCamY * posCamY + posCamZ * posCamZ)) * 180.0 / M_PI, ar, 1, 100);

	glutSwapBuffers();
}

/**
*	Callback de redimensionamiento
*/
void reshape(int width, int height) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Cambiamos el marco de dibujo al de la ventana
	glViewport(0, 0, width, height);
	// Relacion de aspecto:
	ar = (float)width / height;

	// Seleccionar tipo de camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Camara perspectiva: Plano cercano es estrictamente positivo
	gluPerspective(2 * asin(1.0 / sqrt(posCamX * posCamX
		+ posCamY * posCamY + posCamZ * posCamZ)) * 180.0 / M_PI, ar, 1, 100);
	// fovy es arcoseno del radio de la esfera dividido la distancia de
	// la camara al cengtro de cooredenadas (esta en radianes, se pasa a grados)
}

void onIdle() {
	// Actualizacion de variables temporales
	time_t aux = time(NULL);
	char aux2[26];
	ctime_s(aux2, sizeof aux2 ,&aux);
	// tiempo.substr(3,5) desde la posicion 3 cuenta 5 caracteres
	// segundos string(aux2).substr(17, 2)
	// minutos string(aux2).substr(14, 2)
	// horas string(aux2).substr(11, 2)
	string tiempo = string(aux2);
	// Variables temporales para horas:
	hora = stoi(tiempo.substr(11, 2));
	// Variables temporales para minutos:
	static int min_antes = stoi(tiempo.substr(14,2));
	int min_ahora = stoi(tiempo.substr(14,2));
	int min_trans = min_ahora - min_antes;
	anguloMinut = (float) min_ahora * 360.0 / 60.0;
	// Variables temporales para segundos:
	int sec_ahora = stoi(tiempo.substr(17, 2));
	anguloSec = (float) sec_ahora * 360.0 / 60.0;
	// Si ha pasado un minuto:
	if (min_trans >= 1) {
		dx *= -1;
		min_antes = min_ahora;
	}
	anguloForE += dx;
	posCamX += ((float) dx)/70.0;
	if (posCamX >= 8.0) posCamX = 8.0;
	if (posCamX <= -8.0) posCamX = -8.0;
	// Encolar evento de dibujo
	glutPostRedisplay();
}

void onTimer(int tiempo) {
	glutTimerFunc(tiempo, onTimer, tiempo);
	onIdle();
}

int main(int argc, char** argv) {
	// Inicializar glut
	glutInit(&argc, argv);

	// Describir los buffers, con GLUT_DEPTH se usa el z_buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Definir y crear la ventana de dibujo
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(WINDOWNAME);

	init(); // Se ejecuta una vez

	// Registrar las callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	// Limito los fps
	glutTimerFunc(1000/TASA_FPS, onTimer, 1000/TASA_FPS);

	// Bucle de atencion a eventos
	glutMainLoop();
}