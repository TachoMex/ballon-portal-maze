#ifndef TEMPORIZADOR
#define TEMPORIZADOR 
#include <chrono>

class Temporizador{
private:
	std::chrono::system_clock::time_point marca;

public:
	Temporizador(){
		marca = std::chrono::system_clock::now();
	}

	void reiniciar(){
		marca = std::chrono::system_clock::now();
	}

	unsigned msegundos(){
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-marca).count();
	}

	unsigned segundos(){
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-marca).count();
	}

};
#endif