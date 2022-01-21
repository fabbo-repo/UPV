/*!
\file pract9.cpp
\brief Videojuego OpenGL

Practica 9.

\author yuuri <lissu>
\date 2021
*/

#define PROYECTO "Interfaz de conducci�n"
#define _USE_MATH_DEFINES

// Cabeceras
#include <iostream>
#include <GL/freeglut.h>
#include <Utilidades.h>
#include <sstream>
#include <cmath>

#define PI 3.1415926
#define tasaFPS 60

// Variables globales
static enum { SOLIDO, ALAMBRICO } modo;
static enum { FRONTAL, PLANTA } vista;
static float angulo = 180 + 45;
static float speed = 0, giroX = sin(angulo * PI / 180), giroZ = -1;
static float distX = 0, distY = 1, distZ = 0;  // Posicion inicial de la camara
static float avance = 0.0;
static bool isDiurnal = true, isFog = false, turnLeft = false, turnRight = false;

float floorX1 = -150; float floorX2 = 150;
float floorZ1 = 150; float floorZ2 = -150;

GLuint road, roadLarge, landscapeDay, landscapeNight, 
	suelo, ad, ad2, motoF, motoIzq, motoDer, motoArriba;

using namespace std;


//! Callback del menu de pop-up
void onMenu(int opcion)
{
	if (opcion == 0) modo = ALAMBRICO;
	else modo = SOLIDO;

	glutPostRedisplay();
}

void cargarTexturas() {
	glGenTextures(1, &road);
	glBindTexture(GL_TEXTURE_2D, road);
	loadImageFile((char*)"road2.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &roadLarge);
	glBindTexture(GL_TEXTURE_2D, roadLarge);
	loadImageFile((char*)"road2Largo.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &landscapeDay);
	glBindTexture(GL_TEXTURE_2D, landscapeDay);
	loadImageFile((char*)"paisaje2diurno.jpg");

	glGenTextures(1, &landscapeNight);
	glBindTexture(GL_TEXTURE_2D, landscapeNight);
	loadImageFile((char*)"paisaje2nocturno.jpg");

	glGenTextures(1, &suelo);
	glBindTexture(GL_TEXTURE_2D, suelo);
	loadImageFile((char*)"field2diurno.jpg");

	glGenTextures(1, &ad);
	glBindTexture(GL_TEXTURE_2D, ad);
	loadImageFile((char*)"ad1.jpg");

	glGenTextures(1, &ad2);
	glBindTexture(GL_TEXTURE_2D, ad2);
	loadImageFile((char*)"ad2.png");

	glGenTextures(1, &motoF);
	glBindTexture(GL_TEXTURE_2D, motoF);
	loadImageFile((char*)"motoFPV.png");

	glGenTextures(1, &motoIzq);
	glBindTexture(GL_TEXTURE_2D, motoIzq);
	loadImageFile((char*)"motoFPVizq.png");

	glGenTextures(1, &motoDer);
	glBindTexture(GL_TEXTURE_2D, motoDer);
	loadImageFile((char*)"motoFPVder.png");

	glGenTextures(1, &motoArriba);
	glBindTexture(GL_TEXTURE_2D, motoArriba);
	loadImageFile((char*)"motoArriba.png");
}

void cargarLuces() {
	// Luz luna

	GLfloat Al0[] = { 0.05, 0.05, 0.05 };
	GLfloat Dl0[] = { 0.05, 0.05, 0.05 };
	GLfloat Sl0[] = { 0.0, 0.0, 0.0 };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);


	// Luz faro vehiculo

	GLfloat Al1[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat Dl1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Sl1[] = { 0.3, 0.3, 0.3, 1.0 };


	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Al1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Dl1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Sl1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);


	// Farolas

	GLfloat Alx[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat Dlx[] = { 0.5, 0.5, 0.2, 1.0 };
	GLfloat Slx[] = { 0.0, 0.0, 0.0, 1.0 };

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Alx);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Dlx);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Slx);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);

	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, Alx);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Dlx);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Slx);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);

	glEnable(GL_LIGHT4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, Alx);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Dlx);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Slx);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);

	glEnable(GL_LIGHT5);
	glLightfv(GL_LIGHT5, GL_AMBIENT, Alx);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Dlx);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Slx);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);


	// Materiales

	GLfloat Dmx[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat Smx[] = { 0.3, 0.3, 0.3, 1.0 };

	//glEnable(GL_COLOR_MATERIAL); // con esta opcion, con glColor3fv podemos cambiar el color difuso
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Dmx);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Smx);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
}

//! Inicializadores
void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(1, 1, 1, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	//PNG
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);

	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);*/
	// Luces (caracteristicas cromaticas)
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, GRISCLARO);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, BLANCO);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, GRISOSCURO);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, GRISCLARO);


	cargarTexturas();
	cargarLuces();

	// Niebla
	glFogfv(GL_FOG_COLOR, BLANCO);
	glFogf(GL_FOG_DENSITY, 0.1);

	// Crear el menu de popup
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void background() {

	glPushMatrix();
	if (isDiurnal) glBindTexture(GL_TEXTURE_2D, landscapeDay);
	else glBindTexture(GL_TEXTURE_2D, landscapeNight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-150 + distX, 150, -150 + distZ);
	glTexCoord2f(1, 1); glVertex3f(150 + distX, 150, -150 + distZ);
	glTexCoord2f(1, 0); glVertex3f(150 + distX, -1, -150 + distZ);
	glTexCoord2f(0, 0); glVertex3f(-150 + distX, -1, -150 + distZ);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(150 + distX, 150, -150 + distZ);
	glTexCoord2f(1, 1); glVertex3f(150 + distX, 150, 150 + distZ);
	glTexCoord2f(1, 0); glVertex3f(150 + distX, -1, 150 + distZ);
	glTexCoord2f(0, 0); glVertex3f(150 + distX, -1, -150 + distZ);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(150 + distX, 150, 150 + distZ);
	glTexCoord2f(1, 1); glVertex3f(-150 + distX, 150, 150 + distZ);
	glTexCoord2f(1, 0); glVertex3f(-150 + distX, -1, 150 + distZ);
	glTexCoord2f(0, 0); glVertex3f(150 + distX, -1, 150 + distZ);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-150 + distX, 150, 150 + distZ);
	glTexCoord2f(1, 1); glVertex3f(-150 + distX, 150, -150 + distZ);
	glTexCoord2f(1, 0); glVertex3f(-150 + distX, -1, -150 + distZ);
	glTexCoord2f(0, 0); glVertex3f(-150 + distX, -1, 150 + distZ);
	glEnd();

	glPopMatrix();
}

void floor() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, suelo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if ((int)distX % 50 > 48 || (int)distX % 50 < -48) {
		floorX1 = distX - 150;
		floorX2 = distX + 150;
	}
	if ((int)distZ % 50 > 48 || (int)distZ % 50 < -48) {
		floorZ1 = distZ + 150;
		floorZ2 = distZ - 150;
	}

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(floorX1, -0.01, floorZ1);
	glTexCoord2f(1, 0); glVertex3f(floorX2, -0.01, floorZ1);
	glTexCoord2f(1, 1); glVertex3f(floorX2, -0.01, floorZ2);
	glTexCoord2f(0, 1); glVertex3f(floorX1, -0.01, floorZ2);
	glEnd();
	glPopMatrix();

}

void postes() {
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCylinder(0.06, 4, 8, 8);
	glPopMatrix();
}

void carteles() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, ad);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-30, 2, -26);
	glTexCoord2f(1, 0); glVertex3f(-24, 2, -26);
	glTexCoord2f(1, 1); glVertex3f(-24, 4, -26);
	glTexCoord2f(0, 1); glVertex3f(-30, 4, -26);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 2, -56);
	glTexCoord2f(1, 0); glVertex3f(0, 2, -50);
	glTexCoord2f(1, 1); glVertex3f(0, 4, -50);
	glTexCoord2f(0, 1); glVertex3f(0, 4, -56);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(30, 2, -26);
	glTexCoord2f(1, 0); glVertex3f(24, 2, -26);
	glTexCoord2f(1, 1); glVertex3f(24, 4, -26);
	glTexCoord2f(0, 1); glVertex3f(30, 4, -26);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 0, -26); postes();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-24, 0, -26); postes();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -56); postes();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -50); postes();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 0, -26); postes();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(24, 0, -26); postes();
	glPopMatrix();
}

void carteles2() {
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	carteles();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, ad2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTranslatef(-5, 6, 0);
	glutSolidCylinder(0.06, 4, 8, 8);
	glPopMatrix();
}

void lucesLunaYFarolas() {

	GLfloat posicionL0[] = { 0.0, 10.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicionL0);

	GLfloat dir_farola[] = { 0.0, -1.0, 0.0 };
	GLfloat posicionL2[] = { -27, 5, 26, 1 };
	glLightfv(GL_LIGHT2, GL_POSITION, posicionL2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_farola);
	GLfloat posicionL3[] = { 27, 5, 26, 1 };
	glLightfv(GL_LIGHT3, GL_POSITION, posicionL3);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_farola);
	GLfloat posicionL4[] = { -27, 5, -26, 1 };
	glLightfv(GL_LIGHT4, GL_POSITION, posicionL4);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_farola);
	GLfloat posicionL5[] = { 27, 5, -26, 1 };
	glLightfv(GL_LIGHT5, GL_POSITION, posicionL5);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_farola);
}

void moto() {
	gluLookAt(2, 2, 3, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity(); glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//glBindTexture(GL_TEXTURE_2D, interiorCoche);

	if (turnLeft) glBindTexture(GL_TEXTURE_2D, motoIzq);
	else if (turnRight) glBindTexture(GL_TEXTURE_2D, motoDer);
	else glBindTexture(GL_TEXTURE_2D, motoF);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDepthMask(GL_FALSE);
	GLfloat v0[] = { -1, -1, 0 }; GLfloat v1[] = { 1, -1, 0 };
	GLfloat v2[] = { 1, 1, 0 }; GLfloat v3[] = { -1, 1, 0 };
	quadtex(v0, v1, v2, v3, 0, 1, 0, 1);

	// Dibujar puntos en el interior del coche
	//displayPuntos();
	// Dibujar medidor de velocidad en el interior del coche
	//displayVelocidad();

	glPopMatrix(); glMatrixMode(GL_PROJECTION);
	glPopMatrix(); glDepthMask(GL_TRUE);;
}

void motoUp() {
	gluLookAt(2, 2, 3, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity(); glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D, motoArriba);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDepthMask(GL_FALSE);
	GLfloat v0[] = { -0.2, -0.2, 0 }; GLfloat v1[] = { 0.2, -0.2, 0 };
	GLfloat v2[] = { 0.2, 0.2, 0 }; GLfloat v3[] = { -0.2, 0.2, 0 };
	quadtex(v0, v1, v2, v3, 0, 1, 0, 1);

	// Dibujar puntos en el interior del coche
	//displayPuntos();
	// Dibujar medidor de velocidad en el interior del coche
	//displayVelocidad();

	glPopMatrix(); glMatrixMode(GL_PROJECTION);
	glPopMatrix(); glDepthMask(GL_TRUE);;
}

//!	Callback de dibujo
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Fondo fijo
	/*glBindTexture(GL_TEXTURE_2D, landscape);
	texturarFondo();*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Luz de los focos de la moto
	if (vista == FRONTAL) {
		GLfloat dir_L1[] = { 0.0, -0.5, -0.7 };
		GLfloat posicionL1[] = { 0, 0.7, 0,1 };
		glLightfv(GL_LIGHT1, GL_POSITION, posicionL1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_L1);
	}

	if (vista == PLANTA) {
		gluLookAt(distX, 70, distZ,
			distX + giroX, 1, distZ + giroZ,
			0, 1, 0);
	}
	else {
		gluLookAt(distX, distY, distZ,
			distX + giroX, 1, distZ + giroZ,
			0, 1, 0);
	}

	if (modo == ALAMBRICO) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	// -------------- Texturas ---------------
	background();
	floor();
	carteles();
	carteles2();

	//Textura carretera
	glBindTexture(GL_TEXTURE_2D, road);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // No toma iluminacion de la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// -------------- Carretera en forma de ocho ----------

	// base 
	GLfloat v0[3] = { 6,0,56 }, v1[3] = { -6,0,56 }, v2[3] = { -6,0,50 }, v3[3] = { 6,0,50 };
	quad(v1, v0, v3, v2, 100, 60);

	// carretera izquierda inferior
	GLfloat v8[3] = { -24,0,32 }, v9[3] = { -30,0,32 }, v10[3] = { -30,0,20 }, v11[3] = { -24,0,20 };
	quad(v9, v8, v11, v10, 60, 100);

	// carretera derecha inferior
	GLfloat v12[3] = { 30,0,32 }, v13[3] = { 24,0,32 }, v14[3] = { 24,0,20 }, v15[3] = { 30,0,20 };
	quad(v13, v12, v15, v14, 60, 100);

	// carretera izquierda superior
	GLfloat v16[3] = { -24,0,-20 }, v17[3] = { -30,0,-20 }, v18[3] = { -30,0,-32 }, v19[3] = { -24,0,-32 };
	quad(v17, v16, v19, v18, 60, 100);

	// carretera derecha superior
	GLfloat v20[3] = { 30,0,-20 }, v21[3] = { 24,0,-20 }, v22[3] = { 24,0,-32 }, v23[3] = { 30, 0, -32 };
	quad(v21, v20, v23, v22, 60, 100);

	// techo 
	GLfloat v24[3] = { 6,0,-50 }, v25[3] = { -6,0,-50 }, v26[3] = { -6,0,-56 }, v27[3] = { 6,0,-56 };
	quad(v25, v24, v27, v26, 100, 60);

	// Union base e izq inferior
	GLfloat v36[3] = { -6,0,50 }, v37[3] = { -6,0,56 }, v38[3] = { -30,0,32 }, v39[3] = { -24,0,32 };
	quad(v37, v36, v39, v38, 50, 130);

	// Union base y der inferior
	GLfloat v40[3] = { 6,0,56 }, v41[3] = { 6,0,50 }, v42[3] = { 24,0,32 }, v43[3] = { 30,0,32 };
	quad(v41, v40, v43, v42, 50, 130);

	// Union izq superior y techo
	GLfloat v44[3] = { -24,0,-32 }, v45[3] = { -30,0,-32 }, v46[3] = { -6,0,-56 }, v47[3] = { -6,0,-50 };
	quad(v45, v44, v47, v46, 50, 130);

	// Union der superior y techo
	GLfloat v48[3] = { 30,0,-32 }, v49[3] = { 24,0,-32 }, v50[3] = { 6,0,-50 }, v51[3] = { 6,0,-56 };
	quad(v49, v48, v51, v50, 50, 130);

	glBindTexture(GL_TEXTURE_2D, roadLarge);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // No toma iluminacion de la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Union izq inferior y der superior, dividida en 2
	//GLfloat v28[3] = { -24,0,20 }, v29[3] = { -30,0,20 }, v30[3] = { 24,0,-20 }, v31[3] = { 30,0,-20 };
	//quad(v29, v28, v31, v30, 40, 250);
	GLfloat v281[3] = { -24,0,20 }, v291[3] = { -30,0,20 }, v301[3] = { -3.02,0,0 }, v311[3] = { 0,0,2.23 };
	quad(v291, v281, v311, v301, 40, 300);
	GLfloat v282[3] = { 3.02,0,0 }, v292[3] = { 0,0,-2.23 }, v302[3] = { 24,0,-20 }, v312[3] = { 30,0,-20 };
	quad(v292, v282, v312, v302, 40, 300);

	// Union der inferior e izq superior
	GLfloat v32[3] = { 30,0,20 }, v33[3] = { 24,0,20 }, v34[3] = { -30,0,-20 }, v35[3] = { -24,0,-20 };
	quad(v33, v32, v35, v34, 60, 450);



	//------- Luces ---------
	lucesLunaYFarolas();

	// Textura moto
	if (vista == FRONTAL) moto();
	else motoUp();

	glutSwapBuffers(); // Intercambiar buffer trasero con el frontal
}

void reshape(GLint width, GLint height)
{
	// Cuando hago resize, el objeto siempre queda en el centro de la pantalla y no se deforma
	glViewport(0, 0, width, height); // Mi area de dibujo ocupa todo el marco
	float ar = (float)width / height;  // Relacion de aspecto de mi marco

	// Seleccionar el tipo de camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Camara perspectiva --- Por defecto, la camara est� en el origen de coordenadas mirando hacia -Z. Sufre efectos de distancia
	gluPerspective(45, ar, 1, 500); // De 1m a 500m desde la camara, a 45�.  

}

void update()
{
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;
	avance = tiempo_transcurrido * speed;
	antes = ahora;

	distX += avance * giroX;
	distZ += avance * giroZ;


	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	// Sirve para re-arrancar el reloj de cuenta atras
	glutTimerFunc(tiempo, onTimer, tiempo);
	update();
}

void onArrow(int tecla, int x, int y)
{
	switch (tecla) {
	case GLUT_KEY_UP:
		// Flecha arriba: Aumenta el m�dulo de la velocidad en 0.1 m/s
		if (speed < 30) speed += 0.1;
		break;
	case GLUT_KEY_DOWN:
		// Flecha abajo: Disminuye el m�dulo de la velocidad en 0.1 m/s
		if (speed > 0.1) speed -= 0.1;
		else speed = 0;
		break;
	case GLUT_KEY_LEFT:
		// Flecha izquierda: El vector director de la velocidad gira � de grado respecto al eje Y
		angulo += 1; //0.25
		turnLeft = true;
		break;
	case GLUT_KEY_RIGHT:
		// Flecha derecha: El vector director de la velocidad gira � de grado respecto al eje Y
		angulo -= 1; //0.25
		turnRight = true;
		break;
	}

	giroX = sin(angulo * PI / 180);
	giroZ = cos(angulo * PI / 180);

	stringstream title;
	title << "Interfaz de conducci�n " << speed << "m/s";
	glutSetWindowTitle(title.str().c_str());

	glutPostRedisplay();
}

void onArrowRelease(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_LEFT:
		turnLeft = false;
		break;
	case GLUT_KEY_RIGHT:
		turnRight = false;
		break;
	}
}

//! Callback de atencion al pulsado de teclas alfanumericas
void onKey(unsigned char tecla, int x, int y)
{
	switch (tecla) {
	case 's':
		glDisable(GL_TEXTURE_2D);
		if (modo == SOLIDO) modo = ALAMBRICO;
		else modo = SOLIDO;
		break;
	case 'v':
		if (vista == PLANTA) vista = FRONTAL;
		else vista = PLANTA;
		break;
	case 'l':
		if (isDiurnal) { isDiurnal = false; glEnable(GL_LIGHTING); }
		else { isDiurnal = true; glDisable(GL_LIGHTING); }
		break;
	case 'n':
		if (isFog) { glDisable(GL_FOG); isFog = false; }
		else { glEnable(GL_FOG); isFog = true; }
		break;
	case 27: exit(0);
	}

	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	FreeImage_Initialise();

	// Inicializar glut
	glutInit(&argc, argv);

	// Describir los buffers
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Definir y crear la ventana de dibujo
	glutInitWindowSize(1280, 720);
	glutCreateWindow(PROYECTO);

	init();

	std::cout << PROYECTO << " running" << std::endl; // Mensaje por consola

	// Registrar las callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);
	glutSpecialFunc(onArrow);
	glutSpecialUpFunc(onArrowRelease);
	glutKeyboardFunc(onKey);

	// Bucle de atenci�n a eventos
	glutMainLoop();
}