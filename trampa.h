#ifndef TRAMPA_H
#define TRAMPA_H 

#include "muro.h"


const Color ColorTrampa = Color::naranja;


class Trampa: public Muro{
public:
	Trampa(const _2D::Rectangulo<double>& r):Muro(r){

	}
	void colisionConGlobero(Globero* g);
	virtual void dibujar();
};

void Trampa::colisionConGlobero(Globero* g){
	g->colisionado = true;
}

void Trampa::dibujar(){
	glColor(ColorTrampa);
	glDraw(this->posicion, true);
}



#endif
