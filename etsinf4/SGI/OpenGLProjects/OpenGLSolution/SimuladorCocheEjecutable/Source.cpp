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
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

static enum { SOLID_MODE, WIRE_MODE } modo;
static const int TASA_FPS = 60;
static GLuint pista, fondo, suelo, meta, interiorCoche;
static GLuint volante1, volante2, volante3;
static GLuint fondoNocturno, sueloNocturno;
static GLuint anuncio1, anuncio2, anuncio3, anuncio4;

const int LEN_PISTA1 = 96;
float pista1[96][3] = {
	{ -4, 0, 0 }, { 4, 0, 0 }, { 4,0,-18 }, { -4,0,-18 }, // Rectangulo 1
	{ -4, 0, -18 }, { 4, 0 ,-18 }, { 4, 0, -18 }, { 4-5.81, 0, -18-5.5 },
	{ 4-5.81, 0, -18-5.5 }, { 4, 0, -18 }, { 8, 0, -24 }, { 8 - 5.81, 0, -24 - 5.5 },
	{ 8 - 5.81, 0, -24 - 5.5 }, { 8, 0, -24 }, { 8, 0, -24 }, { 8, 0, -32 },
	{ 8, 0, -32 }, { 8, 0, -24 }, { 44, 0, -24 }, { 44, 0, -32 }, // Rectangulo 2
	{ 44, 0, -32 }, { 44, 0, -24 }, { 44, 0, -24 }, { 44 + 5.81, 0, -24 - 5.5 },
	{ 44+5.81, 0, -24-5.5 }, { 44, 0, -24 }, { 48, 0, -18 }, { 48 + 5.81, 0, -18 - 5.5 },
	{ 48+5.81, 0, -18-5.5 }, { 48, 0, -18 }, { 48, 0, -18 }, { 56, 0, -18 },
	{ 56, 0, -18 }, { 48, 0, -18 }, { 48, 0, 46 }, { 56, 0, 46 }, // Rectangulo 3
	{ 56, 0, 46 }, { 48, 0, 46 }, { 48, 0, 46 }, { 48 + 5.81, 0, 46 + 5.5 },
	{ 48+5.81, 0, 46+5.5 }, { 48, 0, 46 }, { 44, 0, 52 }, { 44 + 5.81, 0, 52 + 5.5 },
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

bool lightsON = false; bool fogON = false;
bool ver_pista = false; bool conduciendo = true;
bool tecla_up = false, tecla_down = false;
bool tecla_left = false, tecla_rigth = false;
bool inercia1 = false, inercia2 = false;
bool enMeta = true; bool musicaON = true;
bool enableCI = true;
int puntos = 0;

float incSueloX = 0;
float incSueloZ = 0;
float incSuelo2X = 0;
float incSuelo2Z = 0;

void verPista() {
	glDisable(GL_LIGHT1); glDisable(GL_LIGHT6);
	coche.posCamX = 12.0; coche.posCamY = 110.0; coche.posCamZ = 14.0;
	coche.velocidad = 0; coche.dspeedS = 0.5;
	coche.distancia = 0.0; coche.angulo = 180 - 90;
}

void conducir() {
	glEnable(GL_LIGHT1); glEnable(GL_LIGHT6);
	coche.posCamX = 0.0; coche.posCamY = 1.0; coche.posCamZ = 0.0;
	coche.velocidad = 0; coche.dspeedS = 0.5;
	coche.distancia = 0.0; coche.angulo = 180;
}

void loadIluminacion() {
	// Habilitar luces
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
	GLfloat ambiental1[4] = {0.2, 0.2, 0.2, 1.0};
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

	//GLfloat difusoM[4] = {0.8, 0.8, 0.8, 1.0};
	//GLfloat especularM[4] = { 0.3, 0.3, 0.3, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difusoM);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especularM);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
}

/**
*	Metodo para cargar texturas
*/
void loadTexturas() {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &interiorCoche); glBindTexture(GL_TEXTURE_2D, interiorCoche);
	loadImageFile((char*)"interiorCoche.png");
	glGenTextures(1, &volante1); glBindTexture(GL_TEXTURE_2D, volante1);
	loadImageFile((char*)"volante1.png");
	glGenTextures(1, &volante2); glBindTexture(GL_TEXTURE_2D, volante2);
	loadImageFile((char*)"volante2.png");
	glGenTextures(1, &volante3); glBindTexture(GL_TEXTURE_2D, volante3);
	loadImageFile((char*)"volante3.png");
	glGenTextures(1, &pista); glBindTexture(GL_TEXTURE_2D, pista);
	loadImageFile((char*)"pista.jpg");
	glGenTextures(1, &fondo); glBindTexture(GL_TEXTURE_2D, fondo);
	loadImageFile((char*)"fondo.jpg");
	glGenTextures(1, &fondoNocturno); glBindTexture(GL_TEXTURE_2D, fondoNocturno);
	loadImageFile((char*)"fondoNocturno.jpg");
	glGenTextures(1, &suelo); glBindTexture(GL_TEXTURE_2D, suelo);
	loadImageFile((char*)"suelo.jpg");
	glGenTextures(1, &sueloNocturno); glBindTexture(GL_TEXTURE_2D, sueloNocturno);
	loadImageFile((char*)"sueloNocturno.jpg");
	glGenTextures(1, &meta); glBindTexture(GL_TEXTURE_2D, meta);
	loadImageFile((char*)"meta.png");
	glGenTextures(1, &anuncio1); glBindTexture(GL_TEXTURE_2D, anuncio1);
	loadImageFile((char*)"anuncio1.jpg");
	glGenTextures(1, &anuncio2); glBindTexture(GL_TEXTURE_2D, anuncio2);
	loadImageFile((char*)"anuncio2.jpg");
	glGenTextures(1, &anuncio3); glBindTexture(GL_TEXTURE_2D, anuncio3);
	loadImageFile((char*)"anuncio3.jpg");
	glGenTextures(1, &anuncio4); glBindTexture(GL_TEXTURE_2D, anuncio4);
	loadImageFile((char*)"anuncio4.jpg");
}

/**
*	Metodo para habilitar el blending
*/
void initBlending() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
}

/**
*	Metodo para habilitar el blending
*/
void initFog() {
	glFogfv(GL_FOG_COLOR, BLANCO);
	glFogf(GL_FOG_DENSITY, 0.1);
}

/**
*	Metodo para las inicializaciones
*/
void init() {
	std::cout << WINDOWNAME << std::endl;
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "\nInstrucciones: " << std::endl;
	std::cout << "Flecha izquierda/derecha: giro del vehiculo" << std::endl;
	std::cout << "Flecha arriba/abajo: aumento/disminucion de la velocidad" << std::endl;
	std::cout << "s/S: Modo Solido/Alambrico" << std::endl;
	std::cout << "l/L: Activar/desactivar modo nocturno" << std::endl;
	std::cout << "n/N: Activar/desactivar niebla" << std::endl;
	std::cout << "c/C: Cambia la visibilidad de elementos solidarios a la cámara -HUD- (on/off)" << std::endl;
	std::cout << "v/V: Conducir/Ver pista" << std::endl;
	std::cout << "m/M: Activar/desactivar sonidos" << std::endl;
	
	glEnable(GL_DEPTH_TEST);

	// Cargar iluminacion:
	loadIluminacion();
	loadTexturas();

	// Habilitar blending y fog
	initBlending();
	initFog();

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

void displayFocos() {
	// Unicacion focos del coche
	GLfloat posL1[4] = { 1.0, coche.posCamY, 0, 1 };
	GLfloat posL6[4] = { -1.0, coche.posCamY, 0, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, posL1);
	glLightfv(GL_LIGHT6, GL_POSITION, posL6);
	GLfloat dirL1[] = { 0, -0.2, -0.5 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dirL1);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, dirL1);
}

void displayPista1() {
	// Material de la carretera
	glBindTexture(GL_TEXTURE_2D, pista);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	for (int i = 0; i < LEN_PISTA1; i += 4) {
		// glNormal3f(0, 1, 0);
		// glColor3f(0, 0, 0);
		// Para dibujar el quad se requieren 4 puntos
		quadtex(pista1[i], pista1[i + 1], pista1[i + 2], pista1[i + 3], 0, 1, 0, 1, 80, 140);
	}
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void displayFondo() {
	if (!lightsON) glBindTexture(GL_TEXTURE_2D, fondo);
	else glBindTexture(GL_TEXTURE_2D, fondoNocturno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	float puntos[16][3] = {
		{ -200 + coche.posCamX, -10, -200 + coche.posCamZ },
		{ 200 + coche.posCamX, -10, -200 + coche.posCamZ },
		{ 200 + coche.posCamX, 140, -200 + coche.posCamZ },
		{ -200 + coche.posCamX, 140, -200 + coche.posCamZ },
		{ 200 + coche.posCamX, -10, -200 + coche.posCamZ },
		{ 200 + coche.posCamX, -10, 200 + coche.posCamZ },
		{ 200 + coche.posCamX, 140, 200 + coche.posCamZ },
		{ 200 + coche.posCamX, 140, -200 + coche.posCamZ },
		{ 200 + coche.posCamX, -10, 200 + coche.posCamZ },
		{ -200 + coche.posCamX, -10, 200 + coche.posCamZ },
		{ -200 + coche.posCamX, 140, 200 + coche.posCamZ },
		{ 200 + coche.posCamX, 140, 200 + coche.posCamZ },
		{ -200 + coche.posCamX, -10, 200 + coche.posCamZ },
		{ -200 + coche.posCamX, -10, -200 + coche.posCamZ },
		{ -200 + coche.posCamX, 140, -200 + coche.posCamZ },
		{ -200 + coche.posCamX, 140, 200 + coche.posCamZ }
	};
	for (int i = 0; i < 16; i += 4)
		// Para dibujar el quad se requieren 4 puntos
		quadtex(puntos[i], puntos[i + 1], puntos[i + 2], puntos[i + 3], 0, 1, 0, 1, 1, 1);
}

void displaySuelo() {
	if(!lightsON) glBindTexture(GL_TEXTURE_2D, suelo);
	else glBindTexture(GL_TEXTURE_2D, sueloNocturno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	float puntos[4][3] = {
		{ 200 + incSueloX, -0.2, -200 + incSueloZ },
		{ -200 + incSueloX, -0.2, -200 + incSueloZ },
		{ -200 + incSueloX, -0.2, 200 + incSueloZ },
		{ 200 + incSueloX, -0.2, 200 + incSueloZ }
	};
	float puntos2[4][3] = {
		{ 50 + incSuelo2X, -0.1, -50 + incSuelo2Z },
		{ -50 + incSuelo2X, -0.1, -50 + incSuelo2Z },
		{ -50 + incSuelo2X, -0.1, 50 + incSuelo2Z },
		{ 50 + incSuelo2X, -0.1, 50 + incSuelo2Z }
	};
	// Actualizacion del suelo en caso de salir de los limites
	if (coche.posCamX >= incSueloX+100 || coche.posCamX <= incSueloX-100) 
		incSueloX = coche.posCamX;
	if (coche.posCamZ >= incSueloZ + 100 || coche.posCamZ <= incSueloZ - 100)
		incSueloZ = coche.posCamZ;
	if (coche.posCamX >= incSuelo2X + 10 || coche.posCamX <= incSuelo2X - 10)
		incSuelo2X = coche.posCamX;
	if (coche.posCamZ >= incSuelo2Z + 10 || coche.posCamZ <= incSuelo2Z - 10)
		incSuelo2Z = coche.posCamZ;
	quadtex(puntos[0], puntos[1], puntos[2], puntos[3], 0, 1, 0, 1, 1, 1);
	if(conduciendo) quadtex(puntos2[0], puntos2[1], puntos2[2], puntos2[3], 0, 1, 0, 1, 160, 160);
}

void displayMeta() {
	glBindTexture(GL_TEXTURE_2D, meta);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	float puntos[4][3] = {{ -4, 3, 0 }, { 4, 3, 0 }, { 4,7,0 }, { -4,7,0 }};
	quadtex(puntos[0], puntos[1], puntos[2], puntos[3], 0, 1, 0, 1);
}

void displayAnuncios() {
	float puntos1[4][3] = { { -18, 3, 37 }, { -18, 3, 29 }, { -18, 7, 29 }, { -18, 7, 37 } };
	float puntos2[4][3] = { { 22, 3, -18 }, { 30, 3, -18 }, { 30,7,-18 }, { 22,7,-18 }};
	float puntos3[4][3] = { { 42, 3, 6 }, { 42, 3, 14 }, { 42,7,14 }, { 42,7,6 } };
	float puntos4[4][3] = { { 16, 3, 46 }, { 8, 3, 46 }, { 8,7,46 }, { 16,7,46 } };

	// Dibujo aununcio 1:
	glBindTexture(GL_TEXTURE_2D, anuncio1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	quadtex(puntos1[0], puntos1[1], puntos1[2], puntos1[3], 0, 1, 0, 1, 20, 20);
	glPushMatrix();
		glTranslatef(-18, 0, 0);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0); glTranslatef(0, -29, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90, 1, 0, 0); glTranslatef(0, -37, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
	glPopMatrix();

	// Dibujo aununcio 2:
	glBindTexture(GL_TEXTURE_2D, anuncio2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	quadtex(puntos2[0], puntos2[1], puntos2[2], puntos2[3], 0, 1, 0, 1, 20, 20);
	glPushMatrix();
		glTranslatef(0, 0, -18);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(22, 0, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(30, 0, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
	glPopMatrix();

	// Dibujo aununcio 3:
	glBindTexture(GL_TEXTURE_2D, anuncio3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
		glTranslatef(42, 0, 0);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0); glTranslatef(0, -6, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90, 1, 0, 0); glTranslatef(0, -14, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
	glPopMatrix();
	quadtex(puntos3[0], puntos3[1], puntos3[2], puntos3[3], 0, 1, 0, 1, 20, 20);

	// Dibujo aununcio 4:
	glBindTexture(GL_TEXTURE_2D, anuncio4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	quadtex(puntos4[0], puntos4[1], puntos4[2], puntos4[3], 0, 1, 0, 1, 20, 20);
	glPushMatrix();
		glTranslatef(0, 0, 46);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0); glTranslatef(8, 0, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90, 1, 0, 0); glTranslatef(16, 0, 0);
			glutSolidCylinder(0.2, 7, 5, 5);
		glPopMatrix();
	glPopMatrix();
}

void displayFarolas() {
	// Ubicacion farolas
	GLfloat dirF[] = {0.0, -1.0, -0.0};
	GLfloat posFL2[] = { 0, 8, -9, 1 };
	GLfloat posFL3[] = { 26, 8, -28, 1 };
	GLfloat posFL4[] = { 52, 8, 10, 1 };
	GLfloat posFL5[] = { 12, 8, 56, 1 };
	GLfloat posFL7[] = { -28, 8, 33, 1 };
	glPushMatrix();
		glRotatef(-90, 1, 0, 0); glTranslatef(0, 9, 5);
		glutSolidCone(0.5, 0.5, 10, 6);
	glPopMatrix();
	glPushMatrix();
		glRotatef(-90, 1, 0, 0); glTranslatef(26, 28, 5);
		glutSolidCone(0.5, 0.5, 10, 6);
	glPopMatrix();
	glPushMatrix();
		glRotatef(-90, 1, 0, 0); glTranslatef(52, -10, 5);
		glutSolidCone(0.5, 0.5, 10, 6);
	glPopMatrix();
	glPushMatrix();
		glRotatef(-90, 1, 0, 0); glTranslatef(12, -56, 5);
		glutSolidCone(0.5, 0.5, 10, 6);
	glPopMatrix();
	glPushMatrix();
		glRotatef(-90, 1, 0, 0); glTranslatef(-28, -33, 5);
		glutSolidCone(0.5, 0.5, 10, 6);
	glPopMatrix();
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
}

void displayVelocidad() {
	if (lightsON) glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDepthMask(GL_FALSE);
	
	if (coche.velocidad <= 10) glColor4f(0, 1, 0, 0.3);
	else if (coche.velocidad <= 20) glColor4f(1, 1, 0, 0.3);
	else glColor4f(1, 0, 0, 0.3);
	
	
	glPushMatrix();
	glTranslatef(-0.055, -0.51, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1, 0.014 * abs(coche.velocidad));
	
	
	glutSolidCylinder(0.037, 0.2, 4, 4);
	glPopMatrix();
	glDepthMask(GL_TRUE);
	glPopAttrib();
	if (lightsON) glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void displayPuntos() {
	if (lightsON) glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDepthMask(GL_FALSE);
	glColor4f(0, 0, 1, 0.3);
	for (int i = 0; i < puntos; i++) {
		glPushMatrix();
		glTranslatef(0.2 + i/10.0, -0.8, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCylinder(0.025, 0.2, 4, 4);
		glPopMatrix();
	}
	glDepthMask(GL_TRUE);
	glPopAttrib();
	if (lightsON) glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void displayCocheInt() {
	glEnable(GL_CULL_FACE);

	gluLookAt(2, 2, 3, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity(); glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D, interiorCoche);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDepthMask(GL_FALSE);
	GLfloat c0[] = { -1,-1,-0.1 }; GLfloat c1[] = { 1,-1,-0.1 };
	GLfloat c2[] = { 1,1,-0.1 }; GLfloat c3[] = { -1,1,-0.1 };
	quadtex(c0, c1, c2, c3, 0, 1, 0, 1);
	
	if (tecla_rigth) glBindTexture(GL_TEXTURE_2D, volante3);
	else if (tecla_left) glBindTexture(GL_TEXTURE_2D, volante2);
	else glBindTexture(GL_TEXTURE_2D, volante1);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDepthMask(GL_FALSE);
	GLfloat v0[] = { -0.65, -0.7, 0 }; GLfloat v1[] = { -0.2, -0.7, 0 };
	GLfloat v2[] = { -0.2, 0, 0 }; GLfloat v3[] = { -0.65, 0, 0 };
	quadtex(v0, v1, v2, v3, 0, 1, 0, 1);

	// Dibujar puntos en el interior del coche
	if (modo == SOLID_MODE) displayPuntos();
	// Dibujar medidor de velocidad en el interior del coche
	if (modo == SOLID_MODE) displayVelocidad();

	glPopMatrix(); glMatrixMode(GL_PROJECTION);
	glPopMatrix(); glDepthMask(GL_TRUE);
	
	glDisable(GL_CULL_FACE);
}

/**
*	Metodo para comprobar si el coche ha pasado por la meta
*/
bool pasaMeta() {
	if (coche.posCamX > -4 && coche.posCamX < 4)
		if (coche.posCamZ >= -0.2 && coche.posCamZ <= 0.2)
			return true;
	return false;
}

/**
*	Metodo para el dibujado de cada frame
*/
void display() {
	// Fondo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(lightsON && modo == SOLID_MODE) glClearColor(0.15, 0.15, 0.15, 1.0);
	else if (modo == SOLID_MODE) glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Asi aseguramos que se cargue la matriz identidad
	
	// Brillo incorporado en la textura
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	
	if (lightsON) displayFocos();

	gluLookAt(/* Posicion de la camara */ coche.posCamX, coche.posCamY, coche.posCamZ,
		/* Punto de interes */ coche.posCamX + sin(coche.angulo * PI / 180), 1,
		coche.posCamZ + cos(coche.angulo * PI / 180),
		/* Vertical de la camara */ 0, 1, 0);

	FPS();

	if (modo == WIRE_MODE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// Dibujo la Pista 1
	displayPista1();

	// Dibujo el fondo
	displayFondo();

	// Dibujo el suelo
	displaySuelo();

	// Dibujo de anuncios
	displayAnuncios();

	// Ubicacion iluminación Luna
	if (lightsON) glLightfv(GL_LIGHT0, GL_POSITION, luna.pos);

	// Dibujado de las farolas
	if (lightsON) displayFarolas();

	// Dibujo la meta
	displayMeta();

	// Gestion de puntos
	if (pasaMeta() && !enMeta) { 
		puntos++;  enMeta = true;
	}
	else if (!pasaMeta() && enMeta) enMeta = false;
	if (puntos >= 5) puntos = 0;

	// Dibujar interior del coche en primera persona
	if (conduciendo && enableCI) displayCocheInt();

	glutSwapBuffers();
	glFlush();
}

/**
*	Callback de redimensionamiento
*/
void reshape(int width, int height) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Cambiamos el marco de dibujo al de la ventana
	glViewport(0, 0, width, height);
	// Relacion de aspecto:
	coche.ar = (float) width / height;

	// Seleccionar tipo de camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Camara perspectiva: Plano cercano es estrictamente positivo
	gluPerspective(45, coche.ar, 1, 500);
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
	case 'v': case 'V':
		if (conduciendo) {
			conduciendo = false; ver_pista = true;
			verPista();
		}
		else {
			conduciendo = true; ver_pista = false;
			conducir();
		}
		break;
	case 'n': case 'N':
		if (modo == SOLID_MODE) {
			fogON ? glDisable(GL_FOG) : glEnable(GL_FOG);
			fogON = !fogON;
			if (lightsON) glFogfv(GL_FOG_COLOR, GRISOSCURO);
			else glFogfv(GL_FOG_COLOR, BLANCO);
		}
		break;
	case 's': case 'S':
		if (modo == WIRE_MODE) {
			if (lightsON) glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			modo = SOLID_MODE;
		}
		else {
			if (lightsON) glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glClearColor(0.0, 0.0, 0.0, 1.0);
			modo = WIRE_MODE;
		}
		break;
	case 'l': case 'L': 
		if (modo == SOLID_MODE) {
			lightsON ? glDisable(GL_LIGHTING) : glEnable(GL_LIGHTING);
			lightsON = !lightsON;
			if (lightsON) glFogfv(GL_FOG_COLOR, GRISOSCURO);
			else glFogfv(GL_FOG_COLOR, BLANCO);
		}
		break;
	case 'm': case 'M':
		musicaON = !musicaON;
		break;
	case 'c': case 'C':
		enableCI = !enableCI;
		break;
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
			if (!tecla_up) {
				PlaySound(NULL, NULL, 0);
				if (musicaON) PlaySound(TEXT("aceleracion.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
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
			coche.velocidad -= 0.3;
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
		PlaySound(NULL, NULL, 0);
		if (musicaON) 
			PlaySound(TEXT("desaceleracion.wav"), NULL, SND_ASYNC);
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
	FreeImage_Initialise();

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

	FreeImage_DeInitialise();
}