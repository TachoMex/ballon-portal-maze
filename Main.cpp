#include "imagen/gestor.h"
#include "juego.h"
#include "constantes.h"
#include <vector>
#include "temporizador.h"


using namespace std;
using namespace _2D;




Juego *juego;

void renderFunction(){
	juego->iterar();
	glutTimerFunc(delay, (void(*)(int))renderFunction,0);
}

void eventoClick(int b , int e, int x, int y){
}

void eventoArrastre(int x, int y){

}

void eventoTeclado(unsigned char k, int x, int y){ 
	juego->evento(k);
}



int main(int argc, char** argv){ 
	juego = new Juego();
	juego->inicializaJuego(SCREEN_X*4, SCREEN_Y);

	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(SCREEN_X,SCREEN_Y); 
	glutInitWindowPosition(0,0); 
	glutCreateWindow(WINDOW_NAME); 
	glClearColor(0, 0,0, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glClear(GL_COLOR_BUFFER_BIT); 
	gluOrtho2D(0, SCREEN_X, 0, SCREEN_Y); 
	glFlush(); 
	glutMouseFunc(eventoClick); 
	glutMotionFunc(eventoArrastre); 
	glutDisplayFunc(renderFunction); 
	glutKeyboardFunc(eventoTeclado); 
	glutMainLoop(); 
	return 0; 
} 