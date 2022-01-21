/*!
	\file		Animacion.cpp
	\brief		Introduccion del tiempo en la escena

	Programa para generar una animacion de dos objetos con y sin control
	del tiempo transcurrido

	\author		Roberto Vivo' <rvivo@upv.es>
	\date		2016-2021
 */


#define PROYECTO "ISGI::S5E01::Animacion"

#include <iostream>		
#include <sstream>
#include <gl/freeglut.h>

static const int TASAFPS = 20;

// Variables dependientes del tiempo
static float angulo = 0;

using namespace std;

//! Inicializaciones
void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
}

//! Cuenta los frames por segundo
void FPS()
{
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	int ttrans = ahora - antes;
	static int fotogramas = 0;

	fotogramas++;

	if (ttrans >= 1000) {
		// Ponemos los fps en el titulo de la ventana
		stringstream titulo;
		titulo << "FPS= " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		fotogramas = 0;
		antes = ahora;
	}
}

//! Callback de dibujo
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Trabajo con la MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 3, 4, 0, 0, 0, 0, 1, 0);
	
	// Geometria
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glRotatef(angulo, 0, 1, 0);
	glutWireTeapot(0.5);
	glPopMatrix();

	glColor3f(0, 1, 0);
	glTranslatef(-0.5, 0, 0);
	glRotatef(angulo / 2, 0, 1, 0);
	glutWireTeapot(0.5);

	glutSwapBuffers();

	FPS();
}

//! Callback de redimensionamiento
void reshape(GLint w, GLint h)
{
	// Establer el marco (viewport)
	glViewport(0, 0, w, h);

	// Construir la PROJECTION
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, (float)w / h, 0.1, 20);
}
//! Callback de actualizacion
void onIdle()
{
	// Actualizacion de las variables temporales
	//angulo += 0.1;  // sin control de tiempo

	// Controlando el tiempo transcurrido
	static const float vueltasXsegundo = 3;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	float ttrans = (ahora - antes) / 1000.0f;
	angulo += vueltasXsegundo * 360 * ttrans;

	antes = ahora;

	// Encolar el evento de dibujo
	glutPostRedisplay();
}

//! Callback de cuenta atras
void onTimer(int tiempo)
{
	glutTimerFunc(tiempo, onTimer, tiempo);
	onIdle();
}

//! Programa principal
int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(onIdle);
	glutTimerFunc(1000 / TASAFPS, onTimer, 1000 / TASAFPS);

	// Bucle de atencion a eventos
	glutMainLoop();
}