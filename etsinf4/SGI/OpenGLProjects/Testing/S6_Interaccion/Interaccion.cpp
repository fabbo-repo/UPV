/*!
	\file		Interaccion.cpp
	\brief		Ejemplo de captura de eventos de teclado y raton

	Dibujar dos objetos que se puedan inspeccionar y seleccionar por separado.

	\author		Roberto Vivo' <rvivo@upv.es>
	\date		2016-2021
 */


#define PROYECTO "ISGI::S6E01::Interaccion"

#include <iostream>			
#include <gl/freeglut.h>
#include <Utilidades.h>

// Globales
static enum {ALAMBRICO,SOLIDO,DOBLE} modo;
static float girox = 0, giroy = 0;
static float giroxTB = 0, giroyTB = 0, giroxTA = 0, giroyTA = 0;
static int xanterior, yanterior;
static GLubyte objeto[1];

using namespace std;

//! Callback del menu de pop-up
void onMenu(int opcion)
{
	if (opcion == 0) modo = ALAMBRICO;
	else if (opcion == 1) modo = SOLIDO;
	else modo = DOBLE;

	glutPostRedisplay();
}

//! Inicializaciones
void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// Crear el menu de popup
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

//! Callback de dibujo
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt( /*posicion de la camara*/ 3, 2, 7,
		/*punto de interes*/ 0, 0, 0,
		/*vertical de la camara*/ 0, 1, 0);

	ejes();

	// Geometria

	// Tetera blanca con hilos rojos
	glPushMatrix();
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glColor3f(1, 0, 0);
		glutWireTeapot(0.51);
	}
	else if (modo == SOLIDO) {
		glColor3f(1, 1, 1);
		glutSolidTeapot(0.5);
	}
	else {
		glColor3f(1, 1, 1);
		glutSolidTeapot(0.5);
		glColor3f(1, 0, 0);
		glutWireTeapot(0.51);
	}
	glPopMatrix();

	// Tetera amarilla con hilos verdes
	glPushMatrix();
	glTranslatef(-1, 0, -1);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glColor3f(0, 1, 0);
		glutWireTeapot(0.51);
	}
	else if (modo == SOLIDO) {
		glColor3f(1, 1, 0);
		glutSolidTeapot(0.5);
	}
	else {
		glColor3f(1, 1, 0);
		glutSolidTeapot(0.5);
		glColor3f(0, 1, 0);
		glutWireTeapot(0.51);
	}
	glPopMatrix();

	glutSwapBuffers();
}

void select()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt( /*posicion de la camara*/ 3, 2, 7,
		/*punto de interes*/ 0, 0, 0,
		/*vertical de la camara*/ 0, 1, 0);

	// Geometria seleccionable

	// Tetera blanca
	glPushMatrix();
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidTeapot(0.5);
	glPopMatrix();

	// Tetera amarilla
	glPushMatrix();
	glTranslatef(-1, 0, -1);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
	glColor3f(1, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();
}

//! Callback de redimensionamiento
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	float ar = (float)w / h;		// relacion de aspecto

	// Seleccionar el tipo de camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Camara perspectiva
	gluPerspective(25, ar, 1, 100);

}

//! Callback de atencion al pulsado de teclas alfanumericas
void onKey(unsigned char tecla, int x, int y)
{
	switch (tecla) {
	case 'a': modo = ALAMBRICO;
		break;
	case 's': modo = SOLIDO;
		break;
	case 'd': modo = DOBLE;
		break;
	case 27: exit(0);
	}

	glutPostRedisplay();
}

//! Callback de atencion al evento de pulsado del boton del raton
void onClick(int boton, int estado, int x, int y)
{
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
	}

	// Ver que valor tiene el pixel en coordenadas del backbuffer (viewport)
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport); // origen, extension
	GLfloat yv = viewport[3] - y;
	// dibujar en el backbuffer los objetos a colores que los identifiquen
	select();
	glReadPixels(x, yv, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, objeto);
}

//! Callback de atencion al arrastre del raton (dragging)
void onDrag(int x, int y)
{
	static const float pixel2grado = 1;
	// al mover el raton hacia la derecha la x aumenta y el giro sera
	// alredor del eje Y positivo
	/// giroy += (x - xanterior) * pixel2grado;
	// al mover el raton hacia abajo la y aumenta y el giro sera alrededor
	// del eje X positivo
	/// girox += (y - yanterior) * pixel2grado;

	if (objeto[0] == 0x00) { //Seleccionada tetera amarilla
		giroyTA += (x - xanterior) * pixel2grado;
		giroxTA += (y - yanterior) * pixel2grado;
	}
	else if (objeto[0] == 0xFF) { //Seleccionada la blanca }
		giroyTB += (x - xanterior) * pixel2grado;
		giroxTB += (y - yanterior) * pixel2grado;
	}

	xanterior = x;
	yanterior = y;

	glutPostRedisplay();
}

//! Programa principal
int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);

	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(onKey);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);

	// Bucle de atencion a eventos
	glutMainLoop();
}