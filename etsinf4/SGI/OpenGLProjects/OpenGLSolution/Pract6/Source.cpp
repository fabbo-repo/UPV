/**
*	@author: Fabian Scherle
*/

#define WINDOWNAME "Interfaz de conducción"
#define _USE_MATH_DEFINES

// Librerias
#include <iostream>
#include <sstream>
#include <GL/freeglut.h>
#include <Utilidades.h>
#include <math.h>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

static enum { SOLID_MODE, WIRE_MODE } modo;
static const int TASA_FPS = 60;

const int LEN_PISTA1 = 96;
float pista1[96][3] = {
	{ -4, 0, 0 }, { 4, 0, 0 }, { 4,0,-18 }, { -4,0,-18 }, // Rectangulo 1
	{ -4, 0, -18 }, { 4, 0 ,-18 }, { 4, 0, -18 }, { 4 - 5.81, 0, -18 - 5.5 },
	{ 4 - 5.81, 0, -18 - 5.5 }, { 4, 0, -18 }, { 8, 0, -24 }, { 8 - 5.81, 0, -24 - 5.5 },
	{ 8 - 5.81, 0, -24 - 5.5 }, { 8, 0, -24 }, { 8, 0, -24 }, { 8, 0, -32 },
	{ 8, 0, -32 }, { 8, 0, -24 }, { 44, 0, -24 }, { 44, 0, -32 }, // Rectangulo 2
	{ 44, 0, -32 }, { 44, 0, -24 }, { 44, 0, -24 }, { 44 + 5.81, 0, -24 - 5.5 },
	{ 44 + 5.81, 0, -24 - 5.5 }, { 44, 0, -24 }, { 48, 0, -18 }, { 48 + 5.81, 0, -18 - 5.5 },
	{ 48 + 5.81, 0, -18 - 5.5 }, { 48, 0, -18 }, { 48, 0, -18 }, { 56, 0, -18 },
	{ 56, 0, -18 }, { 48, 0, -18 }, { 48, 0, 46 }, { 56, 0, 46 }, // Rectangulo 3
	{ 56, 0, 46 }, { 48, 0, 46 }, { 48, 0, 46 }, { 48 + 5.81, 0, 46 + 5.5 },
	{ 48 + 5.81, 0, 46 + 5.5 }, { 48, 0, 46 }, { 44, 0, 52 }, { 44 + 5.81, 0, 52 + 5.5 },
	{ 44 + 5.81, 0, 52 + 5.5 }, { 44, 0, 52 }, { 44, 0, 52 }, { 44, 0, 60 },
	{ 44, 0, 60 }, { 44, 0, 52 }, { -20, 0, 52 }, { -20, 0, 60 }, // Rectangulo 4
	{ -20,0,60 }, { -20,0,52 }, { -20,0,52 }, { -20 - 5.81,0,52 + 5.5 },
	{ -20 - 5.81,0,52 + 5.5 }, { -20,0,52 }, { -24,0,46 }, { -24 - 5.81,0,46 + 5.5 },
	{ -24 - 5.81,0,46 + 5.5 }, { -24,0,46 }, { -24,0,46 }, { -32,0,46 },
	{ -32,0,46 }, { -24,0,46 }, { -24,0,20 }, { -32,0,20 }, // Rectangulo 5
	{ -32,0,20 }, { -24,0,20 }, { -24,0,20 }, { -24 - 5.81,0,20 - 5.5 },
	{ -24 - 5.81,0,20 - 5.5 }, { -24,0,20 }, { -20,0,12 }, { -20 - 5.81,0,12 - 5.5 },
	{ -20 - 5.81,0,12 - 5.5 }, { -20,0,12 }, { -20,0,12 }, { -20,0,4 },
	{ -20,0,4 }, { -20,0,12 }, { -8,0,12 }, { -8,0,4 }, // Rectangulo 6
	{ -8 + 5.81,0,4 + 5.5 }, { -8,0,4 }, { -8,0,4 }, { -8,0,12 },
	{ -8,0,4 }, { -8 + 5.81,0,4 + 5.5 }, { -4 + 5.81, 0, 0 + 5.5 }, { -4, 0, 0 },
	{ 4, 0, 0 }, { -4, 0, 0 }, { -4, 0, 0 }, { -4 + 5.81, 0, 0 + 5.5 }
};

struct camara {
	GLdouble posCamX = 0.0;
	GLdouble posCamY = 1.0;
	GLdouble posCamZ = 0.0;
	float ar; float velocidad = 0, dspeedS = 0.5;
	float distancia = 0.0; float angulo = 180;
};
camara coche;

struct Luna {
	GLfloat amb[3] = { 0.05, 0.05, 0.05 };
	GLfloat dif[3] = { 0.05, 0.05, 0.05 };
	GLfloat esp[3] = { 0.0, 0.0, 0.0 };
	GLfloat pos[4] = { 0.0, 10.0, 0.0, 0.0 };
};
Luna luna;

bool lightsON = true;
bool ver_pista = false; bool conduciendo = true;
bool tecla_up = false, tecla_down = false;
bool tecla_left = false, tecla_rigth = false;
bool inercia1 = false, inercia2 = false;

void verPista() {
	coche.posCamX = 12.0; coche.posCamY = 110.0; coche.posCamZ = 14.0;
	coche.velocidad = 0; coche.dspeedS = 0.5;
	coche.distancia = 0.0; coche.angulo = 180 - 90;
}

void conducir() {
	coche.posCamX = 0.0; coche.posCamY = 1.0; coche.posCamZ = 0.0;
	coche.velocidad = 0; coche.dspeedS = 0.5;
	coche.distancia = 0.0; coche.angulo = 180;
}

/**
*	Metodo para las inicializaciones
*/
void onMenu(int opcion) {
	switch (opcion) {
	case 0: // Modo conducir
		conduciendo = true; ver_pista = false;
		conducir(); break;
	case 1: // Modo ver pista
		conduciendo = false; ver_pista = true;
		verPista(); break;
	case 3: // Modo apagar luces
		//lightsON ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
		lightsON ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
		lightsON ? glDisable(GL_LIGHT6) : glEnable(GL_LIGHT6);
		lightsON = !lightsON;
		break;
	case 8: modo = SOLID_MODE; break;
	case 9: modo = WIRE_MODE; break;
	case 10: exit(0); break;
	default: break;
	}
	glutPostRedisplay();
}

/**
*	Metodo para las inicializaciones
*/
void init() {
	std::cout << WINDOWNAME << std::endl;
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	// Habilitar luces
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);

	// Iluminación de la luna:
	glLightfv(GL_LIGHT0, GL_AMBIENT, luna.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luna.dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luna.esp);

	// Iluminación faros vehiculo
	GLfloat ambiental1[4] = { 0.2, 0.2, 0.2, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambiental1);
	glLightfv(GL_LIGHT6, GL_AMBIENT, ambiental1);
	GLfloat difusa1[4] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, difusa1);
	GLfloat especular1[4] = { 0.3, 0.3, 0.3, 1.0 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, especular1);
	glLightfv(GL_LIGHT6, GL_SPECULAR, especular1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 25);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 20.0);

	// Iluminación Farolas
	GLfloat ambientalF[] = { 0.0,0.0,0.0,1.0 };
	GLfloat difusaF[] = { 0.5,0.5,0.2,1.0 };
	GLfloat especularF[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientalF);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, difusaF);
	glLightfv(GL_LIGHT2, GL_SPECULAR, especularF);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientalF);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, difusaF);
	glLightfv(GL_LIGHT3, GL_SPECULAR, especularF);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambientalF);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, difusaF);
	glLightfv(GL_LIGHT4, GL_SPECULAR, especularF);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT5, GL_AMBIENT, ambientalF);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, difusaF);
	glLightfv(GL_LIGHT5, GL_SPECULAR, especularF);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT7, GL_AMBIENT, ambientalF);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, difusaF);
	glLightfv(GL_LIGHT7, GL_SPECULAR, especularF);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 10.0);

	// Crear menu de popup
	glutCreateMenu(onMenu);
	glutAddMenuEntry("Conducir", 0);
	glutAddMenuEntry("Ver Pista", 1);
	glutAddMenuEntry("Apagar/Encender luces", 3);
	glutAddMenuEntry("Modo SOLID", 8);
	glutAddMenuEntry("Modo WIRE", 9);
	glutAddMenuEntry("Salir", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	conducir();
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
		titulo << WINDOWNAME << " | " << (int)coche.velocidad << "m/s" << " | FPS = " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		fotogramas = 0;
		antes = ahora;
	}
}

/**
*	Metodo para el dibujado de cada frame
*/
void display() {
	// Fondo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Asi aseguramos que se cargue la matriz identidad

	// Unicacion focos del coche
	GLfloat posL1[4] = { 1.0, coche.posCamY - 0.3, 0, 1 };
	GLfloat posL6[4] = { -1.0, coche.posCamY - 0.3, 0, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, posL1);
	glLightfv(GL_LIGHT6, GL_POSITION, posL6);
	GLfloat dirL1[] = { 0, -0.4, -0.45 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dirL1);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, dirL1);

	gluLookAt(/* Posicion de la camara */ coche.posCamX, coche.posCamY, coche.posCamZ,
		/* Punto de interes */ coche.posCamX + sin(coche.angulo * PI / 180), 1,
		coche.posCamZ + cos(coche.angulo * PI / 180),
		/* Vertical de la camara */ 0, 1, 0);

	FPS();

	if (modo == WIRE_MODE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// Dibujo la Pista 1
	// Material de la carretera
	//glEnable(GL_COLOR_MATERIAL);
	GLfloat difusoM[4] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat especularM[4] = { 0.3, 0.3, 0.3, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difusoM);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especularM);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	for (int i = 0; i < LEN_PISTA1; i += 4) {
		glNormal3f(0, 1, 0);
		glColor3f(0, 0, 0);
		// Para dibujar el quad se requieren 4 puntos
		quad(pista1[i], pista1[i + 1], pista1[i + 2], pista1[i + 3], 40, 70);
	}

	// Ubicacion iluminación Luna
	glLightfv(GL_LIGHT0, GL_POSITION, luna.pos);

	// Ubicacion farolas
	GLfloat dirF[] = { 0.0, -1.0, 0.0 };
	GLfloat posFL2[] = { 0, 8, -9, 1 };
	GLfloat posFL3[] = { 18 + 8, 8, -24 - 4, 1 };
	GLfloat posFL4[] = { 48 + 4, 8, 10, 1 };
	GLfloat posFL5[] = { 12, 8, 52 + 4, 1 };
	GLfloat posFL7[] = { -28, 8, 33, 1 };
	glLightfv(GL_LIGHT2, GL_POSITION, posFL2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dirF);
	glLightfv(GL_LIGHT3, GL_POSITION, posFL3);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dirF);
	glLightfv(GL_LIGHT4, GL_POSITION, posFL4);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dirF);
	glLightfv(GL_LIGHT5, GL_POSITION, posFL5);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dirF);
	glLightfv(GL_LIGHT7, GL_POSITION, posFL7);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, dirF);

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
	coche.ar = (float)width / height;

	// Seleccionar tipo de camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Camara perspectiva: Plano cercano es estrictamente positivo
	gluPerspective(45, coche.ar, 1, 120);
	// fovy es arcoseno del radio de la esfera dividido la distancia de
	// la camara al cengtro de cooredenadas (esta en radianes, se pasa a grados)
}

void update()
{
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;
	// Calculo de la distancia como tiempo * velocidad
	coche.distancia = tiempo_transcurrido * coche.velocidad;
	antes = ahora;

	coche.posCamX += coche.distancia * sin(coche.angulo * PI / 180);
	coche.posCamZ += coche.distancia * cos(coche.angulo * PI / 180);

	if (inercia1) {
		if (coche.velocidad > 0)
			coche.velocidad -= 0.02;
		else {
			coche.velocidad = 0;
			inercia1 = false;
		}
	}
	else if (inercia2) {
		if (coche.velocidad < 0)
			coche.velocidad += 0.02;
		else {
			coche.velocidad = 0;
			inercia2 = false;
		}
	}

	glutPostRedisplay();
}

void onIdle() {
	update();
	// Encolar evento de dibujo
	glutPostRedisplay();
}

void onTimer(int tiempo) {
	glutTimerFunc(tiempo, onTimer, tiempo);
	onIdle();
}

void onKey(unsigned char tecla, int x, int y) {
	switch (tecla)
	{
	case 'w': case 'W': modo = WIRE_MODE; break;
	case 's': case 'S': modo = SOLID_MODE; break;
	case 27: exit(0);
	default: break;
	}
	glutPostRedisplay();
}

void onArrowPress(int tecla, int x, int y)
{
	if (coche.dspeedS <= 5.0f && (tecla == GLUT_KEY_LEFT || tecla == GLUT_KEY_RIGHT))
		coche.dspeedS += 0.2f;
	// Solo se movera la camara si esta en modo conduccion
	if (conduciendo) {
		switch (tecla) {
		case GLUT_KEY_UP:
			tecla_up = true;
			break;
		case GLUT_KEY_DOWN:
			tecla_down = true;
			break;
		case GLUT_KEY_LEFT:
			tecla_left = true;
			break;
		case GLUT_KEY_RIGHT:
			tecla_rigth = true;
			break;
		}
		// Aumentar la velocidad en 0.2 m/sg
		if (tecla_up) {
			if (coche.velocidad > 0) inercia2 = false;
			inercia1 = false;
			// Limite de velocidad 120 km/h
			if (coche.velocidad < 33.33)
				coche.velocidad += 0.1f;
			if (coche.velocidad > 33.33)
				coche.velocidad = 33.33;
		}
		// Disminuir la velocidad en 0.1 m/sg
		if (tecla_down) {
			inercia2 = false;
			if (coche.velocidad < 0) inercia1 = false;
			coche.velocidad -= 0.1;
			if (coche.velocidad > -0.1f && coche.velocidad < 0.1f) coche.velocidad = 0;
			if (coche.velocidad < -2.0f) coche.velocidad = -2.0f;
		}
		// Girar medio grado respecto al eje Y
		if (tecla_left) {
			if (coche.velocidad > 0) coche.angulo += coche.dspeedS;
			if (coche.velocidad < 0) coche.angulo -= coche.dspeedS;
		}
		// Girar medio grado respecto al eje Y
		if (tecla_rigth) {
			if (coche.velocidad > 0) coche.angulo -= coche.dspeedS;
			if (coche.velocidad < 0) coche.angulo += coche.dspeedS;
		}
	}
	glutPostRedisplay();
}

void onArrowRelease(int tecla, int x, int y)
{
	if (tecla == GLUT_KEY_LEFT || tecla == GLUT_KEY_RIGHT)
		coche.dspeedS = 0.5f;
	switch (tecla) {
	case GLUT_KEY_UP:
		inercia1 = true;
		tecla_up = false;
		break;
	case GLUT_KEY_DOWN:
		inercia2 = true;
		tecla_down = false;
		break;
	case GLUT_KEY_LEFT:
		tecla_left = false;
		break;
	case GLUT_KEY_RIGHT:
		tecla_rigth = false;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	// Inicializar glut
	glutInit(&argc, argv);

	// Describir los buffers, con GLUT_DEPTH se usa el z_buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Definir y crear la ventana de dibujo
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(WINDOWNAME);

	init(); // Se ejecuta una vez

	// Registrar las callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(onKey);
	// Con las siguientes dos funciones permito que se puedan usar dos teclas a la vez
	glutSpecialFunc(onArrowPress);
	glutSpecialUpFunc(onArrowRelease);
	// Limito los fps
	glutTimerFunc(1000 / TASA_FPS, onTimer, 1000 / TASA_FPS);

	// Bucle de atencion a eventos
	glutMainLoop();
}