#ifndef JUEGO_H
#define JUEGO_H 

#include "globero.h"
#include "piedra.h"
#include "gadget.h"
#include "muro.h"
#include "portal.h"
#include "meta.h"
#include "trampa.h"
#include "boton.h"
#include "rehilete.h"
#include "puerta.h"
#include "temporizador.h"
#include "meta.h"
#include <vector>




class Juego{
public:
	Globero * jugador;
	_2D::Scroll * scroll;
	Temporizador cronometro;
	Temporizador cronometroPiedras;
	std::vector<Piedra*> piedras;
	std::vector<Gadget*> gadgets;
	_2D::Rectangulo<double> pos_ventana;
	void evento(unsigned char);
	void iterar();
	void inicializaJuego(int , int );
};


void Juego::evento(unsigned char e){
	switch(e){
		case 'w':
			jugador->salto();
			break;
		case 'a':
			jugador->izquierda();
			break;
		case 'd':
			jugador->derecha();
			break;
		case ' ':
			if(cronometroPiedras.msegundos() >= delayPiedra){	
				piedras.push_back(new Piedra(jugador->posicion.inicio+_2D::Punto<double>(jugador_x/2,jugador_y/2), (jugador->orientacion()==IZQUIERDA?v_piedrai:v_piedrad)));
				cronometroPiedras.reiniciar();
			}
			break;
	} 
	scroll->ponerEn(_2D::Punto<double>(jugador->posicion.inicio.x-SCREEN_X/2, jugador->posicion.inicio.y-SCREEN_Y/2));
}

void Juego::iterar(){
	if(cronometro.msegundos() >= delay){	
		std::cout<<scroll->posicion.toString()<<std::endl;
		glClear(GL_COLOR_BUFFER_BIT); 
		if(jugador->meta){
			std::cout<<"Ya gano :P"<<std::endl;
			//Evento de terminacion de nivel
		}
		if(jugador->colisionado){
			std::cout<<"Ya perdio :v"<<std::endl;
			//Evento de reiniciar nivel y gestion de vidas
		}
		for(Gadget* g:gadgets){
			//if(scroll->enPantalla(g)){
				g->dibujar();
		//	}
		}
		jugador->dibujar();
		jugador->iterar();
		jugador->limitar(pos_ventana);
		jugador->aplicarFriccion(v_friccion);

		for(Gadget* g : gadgets){
			if(g->colisiona(jugador)){
				g->colisionConGlobero(jugador);
			}
			for(Piedra * p : piedras){
				if(g->colisiona(p)){
					g->colisionConPiedra(p);
				}
			}
		}

		for(int i=0;i<piedras.size();i++){
			if(!pos_ventana.colision(piedras[i]->posicion) or piedras[i]->colisionado){	
				delete piedras[i];
				piedras.erase(piedras.begin()+i--);
			}
		}

		for(auto p: piedras){
			p->dibujar();
			p->iterar();
			//p->aplicarFriccion(v_friccion);
		}
		glFlush();
		glutSwapBuffers();
		scroll->colocaCamaraOGL(); 
		cronometro.reiniciar();
	}
}

void Juego::inicializaJuego(int mapax, int mapay){
	pos_ventana = _2D::Rectangulo<double>(_2D::Punto<double>(), mapax, mapay);
	scroll = new _2D::Scroll(mapax, mapay, SCREEN_X, SCREEN_Y);
	gadgets.push_back(new Muro(_2D::Rectangulo<double>(_2D::Punto<double>(100,100),100, 100)));
	gadgets.push_back(new Puerta(_2D::Rectangulo<double>(_2D::Punto<double>(100,0),20, 100)));
	gadgets.push_back(new Boton(_2D::Rectangulo<double>(_2D::Punto<double>(250,200),20,20), (Puerta*)gadgets.back()));
	gadgets.push_back(new Rehilete(_2D::Punto<double>(300,150), 0, 0, 1,0, 10,70));
	Portal * p1;
	Portal * p2;

	Meta *meta = new Meta(_2D::Rectangulo<double>(_2D::Punto<double>(),30,10), false);

	gadgets.push_back(meta);
	jugador = new Globero(_2D::Rectangulo<double>(_2D::Punto<double>(meta->posicion.inicio.x+5,meta->posicion.fin.y), jugador_x, jugador_y), renders[BFSaltoIzq], fondo_renders, _2D::Punto<double>(),v_grav );
	gadgets.push_back(new Meta(_2D::Rectangulo<double>(_2D::Punto<double>(890,0),30,10), true));
	/*p1 = new Portal(_2D::Rectangulo<double>(_2D::Punto<double>(0,250),20, 40),2); //
	p2 = new Portal(_2D::Rectangulo<double>(_2D::Punto<double>(380,250),20, 40),4);//
	p1->salida = p2;
	p2->salida = p1;
	gadgets.push_back(p1);
	gadgets.push_back(p2);

	p1 = new Portal(_2D::Rectangulo<double>(_2D::Punto<double>(150,0),40,20),1);
	p2 = new Portal(_2D::Rectangulo<double>(_2D::Punto<double>(200,280),40,20),3);
	p1->salida = p2;
	p2->salida = p1;
	gadgets.push_back(p1);
	gadgets.push_back(p2);

	PortalGrande * pg1;
	PortalGrande * pg2;

	pg1 = new PortalGrande(_2D::Rectangulo<double>(_2D::Punto<double>(50,0), 80, 40), 1);
	pg2 = new PortalGrande(_2D::Rectangulo<double>(_2D::Punto<double>(320,0), 80, 40), 1);

	pg1 -> salida = pg2;
	pg2 -> salida = pg1;

	gadgets.push_back(pg1);
	gadgets.push_back(pg2);*/

}

#endif