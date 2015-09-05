#ifndef CONSTANTES_H
#define CONSTANTES_H 
#include "geometria.h"
#include "gl2.h"
#include <string>
#include "imagen/gestor.h"

const int jugador_x = 16;
const int jugador_y = 24;

const std::string BFAireIzq = "ballon2.bmp";
const std::string BFParadoIzq = "ballon5.bmp";
const std::string BFPasoIzq = "ballon6.bmp";
const std::string BFPasoDer = "ballon8.bmp";
const std::string BFParadoDer = "ballon7.bmp";
const std::string BFAireDer = "ballon4.bmp";
const std::string BFSaltoIzq = "ballon1.bmp";
const std::string BFSaltoDer = "ballon3.bmp";
const std::string piedrarender = "piedra.bmp";

const Color fondo_renders = Color::blanco;

const _2D::Punto<double> v_mov(3,0);
const _2D::Punto<double> v_salto(0,5);
const _2D::Punto<double> v_grav(0,-1);
const _2D::Punto<double> v_friccion(0.7,0.7);
const _2D::Punto<double> v_piedrai(-10,0);
const _2D::Punto<double> v_piedrad(10,0);

const Color ColorMuros = Color::blanco;
const Color ColorPuertasAbierta = Color::cafe;
const Color ColorPuertasCerrada = Color::gris(100);
const Color ColorBoton = Color::rojo;
const Color ColorHelices = Color::azul;
const Color ColorPortal = Color::verde;
const Color ColorPortalGrande = Color::magenta;
const Color ColorMeta = Color::amarillo;

const int delay = 40;
const int delayPiedra = 350;
const int IZQUIERDA  = 0;
const int DERECHA = 1;

const int SCREEN_X = 400;
const int SCREEN_Y = 300;
const char * WINDOW_NAME = "Ballon Fight";

GestorImagenes renders = GestorImagenes();
#endif