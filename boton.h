#ifndef BOTON_H
#define BOTON_H 

#include "muro.h"
#include "puerta.h"

class Boton: public Muro{
private:
	Puerta* puerta;
public:	
	void colisionConGlobero(Globero* g);
	void colisionConPiedra(Piedra *p);
	virtual void dibujar();
	Boton(const _2D::Rectangulo<double>& r, Puerta*p):Muro(r){
		puerta = p;
	}
};
void Boton::colisionConGlobero(Globero* g){
	Muro::colisionConGlobero(g);
}

void Boton::colisionConPiedra(Piedra *p){
	Muro::colisionConPiedra(p);
	puerta->abierta^=true;
}


void Boton::dibujar(){
	glColor(ColorBoton);
	glDraw(this->posicion, true);
}


#endif