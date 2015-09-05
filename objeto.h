#ifndef OBJETO2D_H
#define OBJETO2D_H 

#include "imagen/imagen.h"
#include "geometria.h"
#include "gl2.h"

namespace _2D{
	class Objeto{
		public:
			virtual bool colisiona(Objeto*)const = 0;
			virtual bool colisiona(const Rectangulo<double>&) const= 0;
			virtual void dibujar() const = 0;	
			
	};

	class ObjetoInmovil:public Objeto{
	public:
		Rectangulo<double> posicion;
		Imagen * render;  
		Color fondo;

		ObjetoInmovil(const Rectangulo<double>& pos, Imagen * r, Color f = Color::negro):posicion(pos), fondo(f){
			render = r;
		}

		virtual bool colisiona(const Rectangulo<double>& r)const{
			return posicion.colision(r);
		}

		virtual bool colisiona(Objeto* o) const{
			return o->colisiona(posicion);
		}

		virtual void dibujar()const{
			glDrawPixels(render,posicion.inicio,fondo);
		}	

		virtual void moverA(const Punto<double>& pos){
			posicion = Rectangulo<double>(pos, posicion.base(), posicion.altura());
		}

	};

	class ObjetoMovil:public ObjetoInmovil{
	public:
		Punto<double> aceleracion;
		Punto<double> velocidad;
		Punto<double> posicionAnterior;

		ObjetoMovil(const Rectangulo<double>& pos, Imagen * r, Color f = Color::negro , const Punto<double> v = Punto<double>(), 
			   const Punto<double> a = Punto<double>()):ObjetoInmovil(pos,r,f), aceleracion(a), velocidad(v){
		}

		virtual void iterar(){
			posicionAnterior = posicion.inicio;
			posicion+=velocidad;
			velocidad+=aceleracion;
		}

		virtual Linea<double> desplazamiento(){
			return Linea<double>(posicionAnterior, posicion.inicio);
		}

		virtual Linea<double> desplazamientoSuperior(){
			return Linea<double>(posicionAnterior, posicion.inicio)+(posicion.fin-posicion.inicio);
		}

		virtual void limitar(const Rectangulo<double>& limite){
			Punto<double> ajuste;
			if(posicion.inicio.x < limite.inicio.x){	
				ajuste.x -= posicion.inicio.x - limite.inicio.x;
				velocidad.x = 0;
			}
			if(posicion.inicio.y < limite.inicio.y){	
				ajuste.y -= posicion.inicio.y - limite.inicio.y;
				velocidad.y = 0;
			}
			if(posicion.fin.x > limite.fin.x){	
				ajuste.x -= posicion.fin.x - limite.fin.x;
				velocidad.x = 0;
			}
			if(posicion.fin.y > limite.fin.y){	
				ajuste.y -= posicion.fin.y - limite.fin.y;
				velocidad.y = 0;
			}
			posicion+=ajuste;
		} 

		virtual void aplicarFriccion(const Punto<double>& f){
			velocidad.x*=f.x;
			velocidad.y*=f.y;
		}

		virtual bool colisiona(const Rectangulo<double>& r){
			return ObjetoInmovil::colisiona(r);
		}
		
		virtual bool colisiona(Objeto* o){
			return ObjetoInmovil::colisiona(o);
		}

	};

	
	int ladoColision(const ObjetoMovil*o, const Rectangulo<double>& rec){
		double prof_x = std::min(o->posicion.fin.x,rec.fin.x) - std::max(o->posicion.inicio.x,rec.inicio.x);
		double prof_y = std::min(o->posicion.fin.y,rec.fin.y) - std::max(o->posicion.inicio.y,rec.inicio.y);
		
		bool izquierda = o->posicion.fin.x < rec.fin.x;
		bool abajo =  o->posicion.fin.y < rec.fin.y;

		if(prof_x < 0 or prof_y < 0){
			return -1;
		}


		if(o->posicion.inicio.x >= rec.inicio.x and o->posicion.fin.x <= rec.fin.x){
			return (abajo ? 3 : 1);
		}
		if(o->posicion.inicio.y >= rec.inicio.y and o->posicion.fin.y <= rec.fin.y){
			return (izquierda ? 4 : 2);
		}
		
		if(izquierda){
			if(abajo){
				if(o->velocidad.x < 0){
					return 3;
				}else if(o->velocidad.y < 0){
					return 4;
				}
			}else{
				if(o->velocidad.x < 0){
					return 1;
				}else if(o->velocidad.y > 0){
					return 4;
				}
			}
		}else{
			if(abajo){
				if(o->velocidad.x > 0){
					return 3;
				}else if(o->velocidad.y < 0){
					return 2;
				}
			}else{
				if(o->velocidad.x > 0){
					return 1;
				}else if(o->velocidad.y > 0){
					return 2;
				}
			}
		}
		Linea<double> lado;
		if(o->velocidad.x > 0){
			if(o->velocidad.y > 0){
				lado = Linea<double>(o->posicionAnterior,o->posicion.fin);
				return lado.colisiona(rec.lado4())?4:3;
			}else if(o->velocidad.y < 0){
				lado = Linea<double>(Punto<double>(o->posicionAnterior.x,o->posicionAnterior.y+o->posicion.altura()),Punto<double>(o->posicion.fin.x,o->posicion.inicio.y));
				return lado.colisiona(rec.lado4())?4:1;
			}
		}else if(o->velocidad.x < 0){ 
			if(o->velocidad.y > 0){
				lado = Linea<double>(Punto<double>(o->posicionAnterior.x+o->posicion.base(),o->posicionAnterior.y),Punto<double>(o->posicion.inicio.x,o->posicion.fin.y));				
				return lado.colisiona(rec.lado2())?2:3;
			}else if(o->velocidad.y < 0){
				std::cout<<":v"<<std::endl;
				lado = Linea<double>(Punto<double>(o->posicionAnterior.x+o->posicion.base(),o->posicionAnterior.y+o->posicion.altura()),o->posicion.inicio);				
				return lado.colisiona(rec.lado2())?2:1;
			}
		}
		return -1;

	}
	
	class Scroll{
	public:
		_2D::Rectangulo<double> area;
		_2D::Rectangulo<double> posicion;

		Scroll(double mx, double my, double px, double py):area(Punto<double>(),mx,my), posicion(Punto<double>(),px,py){

		}

		void limitar(){
			Punto<double> ajuste;
			if(posicion.inicio.x < area.inicio.x){	
				ajuste.x -= posicion.inicio.x - area.inicio.x;
			}
			if(posicion.inicio.y < area.inicio.y){	
				ajuste.y -= posicion.inicio.y - area.inicio.y;
			}
			if(posicion.fin.x > area.fin.x){	
				ajuste.x -= posicion.fin.x - area.fin.x;
			}
			if(posicion.fin.y > area.fin.y){	
				ajuste.y -= posicion.fin.y - area.fin.y;
			}
			posicion+=ajuste;
		} 

		bool enPantalla(Objeto* o){
			return o->colisiona(posicion);
		}

		void moverX(double x){
			posicion.inicio.x+=x;
			posicion.fin.x+=x;
			limitar();
		}

		void moverY(double y){
			posicion.inicio.y+=y;
			posicion.fin.y+=y;
			limitar();
		}

		void ponerEn(const _2D::Punto<double>& p){
			double h = posicion.altura();
			double b = posicion.base();
			posicion.inicio = posicion.fin = p;
			posicion.fin.x+=b;
			posicion.fin.y+=h;
			limitar();
		}

		void colocaCamaraOGL(){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D (posicion.inicio.x, posicion.fin.x, posicion.inicio.y, posicion.fin.y);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

	};

}



#endif
