#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>


#ifndef VIBORITA_H
#define VIBORITA_H

struct parte_de_la_vibora{
	int x,y;
	parte_de_la_vibora(int columnas,int filas);
	parte_de_la_vibora();
};

class Vibora{
	int puntos,retardo,ancho_maximo,altura_maxima;
	char direccion,caracter_de_parte,caracter_del_borde_de_la_pantalla,caracter_de_la_comida;
	bool consiguio_comida;
	parte_de_la_vibora comida;
	std::vector<parte_de_la_vibora> vibora_completa;
	
	void colocar_comida();
	bool colision_con_algo();
	void mover_vibora();
public:
	Vibora();
	~Vibora();
	void iniciar();
	
};

#endif


