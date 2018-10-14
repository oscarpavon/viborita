#include "viborita.h"

parte_de_la_vibora::parte_de_la_vibora(int columnas, int filas)
{
	x=columnas;
	y=filas;

}

parte_de_la_vibora::parte_de_la_vibora()
{

	x=0;
	y=0;
}


Vibora::Vibora()
{
	//Todo esto es de ncurses
	initscr(); //ncurses
	nodelay(stdscr,true); // el programa no espera hasta que se precione una tecla
	keypad(stdscr,true);
	noecho();
	curs_set(0);
	//getmaxyx(stdscr,ancho_maximo,altura_maxima);
	ancho_maximo = 76;
	altura_maxima = 25;
	//incializar variables
	caracter_de_parte='x';
	caracter_del_borde_de_la_pantalla=(char)219;
	caracter_de_la_comida='*';

	puntos = 0;
	retardo = 100000;
	consiguio_comida=false;
	direccion='i';
	srand(time(0));
	colocar_comida();

	for(int i=0;i<ancho_maximo-1;i++)
	{
		move(0,i);
		addch(caracter_del_borde_de_la_pantalla);
	}

	for(int i=0;i<ancho_maximo-1;i++)
	{
		move(altura_maxima,i);
		addch(caracter_del_borde_de_la_pantalla);
	
	}
	
	for (int i=0;i<altura_maxima;i++){
		move(i,0);
		addch(caracter_del_borde_de_la_pantalla);
		move(i,ancho_maximo-1);
		addch(caracter_del_borde_de_la_pantalla);
	}

	for(int i=0;i<10;i++){
		vibora_completa.push_back(parte_de_la_vibora(40+i,10));
	}

	for (int i=0;i<vibora_completa.size();i++)
	{
	move(vibora_completa[i].y,
	     vibora_completa[i].x);
	addch(caracter_de_parte);
	}	
	
	move(altura_maxima+1,0);
	printw("Puntaje: %d",puntos); //imprimir puntaje
	
	refresh();

}
Vibora::~Vibora(){
	nodelay(stdscr,false);
	getch();
	endwin();


}

bool Vibora::colision_con_algo()
{

	if(vibora_completa[0].x == comida.x && vibora_completa[0].y == comida.y)
	{
		consiguio_comida = true;
		colocar_comida();
		puntos += 10;
	}
	//colision con su propio cuerpo
	for (int i = 2; i < vibora_completa.size();i++){
		if(vibora_completa[0].x == vibora_completa[i].x && vibora_completa[i].y == vibora_completa[0].y){
		
			move(altura_maxima+2,0);
			printw("Colisiono con cuerpo");	
			return true;
		}
			
	}

	if(vibora_completa[0].x == 1 || vibora_completa[0].x == ancho_maximo-1 || vibora_completa[0].y == 0 || vibora_completa[0].y == altura_maxima){
		return true;
	}else{
		return false;
	}
	
	

}

void Vibora::mover_vibora(){
	int numero_de_la_tecla_presionada = getch();
	

	if (!consiguio_comida){
		int posicion_de_la_parte_a_borrar = vibora_completa.size()-1;
		move(vibora_completa[posicion_de_la_parte_a_borrar].y,
		     vibora_completa[posicion_de_la_parte_a_borrar].x);
		addch(' ');
		vibora_completa.pop_back();
	}
	switch(numero_de_la_tecla_presionada)
	{

		case KEY_LEFT:
			if(direccion!='d')
				direccion='i';
			break;
		case KEY_RIGHT:
			if(direccion!='i')
				direccion='d';
			break;
		case KEY_UP:
			if(direccion!='b')
				direccion='a';
			break;
		case KEY_DOWN:
			if(direccion!='a')
				direccion='b';		
			break;
	}
	if (direccion=='d')
		vibora_completa.insert(vibora_completa.begin(),parte_de_la_vibora(vibora_completa[0].x+1,vibora_completa[0].y));
	if (direccion=='a')
		vibora_completa.insert(vibora_completa.begin(),parte_de_la_vibora(vibora_completa[0].x,vibora_completa[0].y-1));
	if (direccion=='i')
		vibora_completa.insert(vibora_completa.begin(),parte_de_la_vibora(vibora_completa[0].x-1,vibora_completa[0].y));
	if (direccion=='b')
		vibora_completa.insert(vibora_completa.begin(),parte_de_la_vibora(vibora_completa[0].x,vibora_completa[0].y+1));




	move(vibora_completa[0].y,vibora_completa[0].x);
	addch(caracter_de_parte);
	refresh();
	
	consiguio_comida = false; //en caso de que la vibora comio la comida y se vuelva a borrar la cola
}

void Vibora::iniciar(){
	int caracter_general;
	int numero;
	while(direccion!=27)
	{
		
		move(0,altura_maxima+3);
		printw("%d",numero);
		numero++;
		if(colision_con_algo()){
			move(0,altura_maxima+3);
			printw("termino el juego");
			break;
			
		}	
	mover_vibora();
	usleep(retardo);
	}
	std::cin.ignore().get();
}
void Vibora::colocar_comida(){
	while(1){

	int posicionX = rand()%ancho_maximo+1;
	int posicionY = rand()%altura_maxima+1;


	for(int i=0;i<vibora_completa.size();i++)
	{
		if (vibora_completa[i].x == posicionX && vibora_completa[i].y == posicionY)
			continue;
		
	}
	if(posicionX >= ancho_maximo-2 || posicionY >= altura_maxima-1)
		continue;
	
	comida.x = posicionX;
	comida.y = posicionY;
	break;


	}
	move(comida.y,comida.x);
	addch(caracter_de_la_comida);
	refresh();	
	
}
