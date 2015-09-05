#ifndef META_H
#define META_H 

#include "muro.h"

class Meta: public Muro{
public:
	bool esSalida;
	Meta(const _2D::Rectangulo<double>& r, bool s=false): Muro(r){
		esSalida = s;
	}
	void colisionConGlobero(Globero * g);
	void dibujar();
};

void Meta::colisionConGlobero(Globero * g){
	g->meta |= esSalida;
	Muro::colisionConGlobero(g);
}

void Meta::dibujar(){
	glColor(ColorMeta);
	glDraw(this->posicion, true);
}

#endif
