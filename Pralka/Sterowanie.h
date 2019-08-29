#ifndef Sterowanie_h
#define Sterowanie_h

#include "Pralka.h"

#include <windows.h>

class Sterowanie : private Pralka {
private:
	//blokuje drzwi pralki; zwraca kod b��du (11)
	char zablokujDrzwi();
	//odblokowuje drzwi pralki; zwraca kod b��du (12)
	char odblokujDrzwi();
	//wpomowuje czyst� wod� do b�bna; zwraca kod b�edu (8)
	inline char wpompujWode();
	//wpompowuje do b�bna wod� wraz z substancjami z substancj� z wybranych przegr�dek; zwraca kod b��du (8)
	char wpompujWode(bool substancja1, bool substancja2, bool substancja3);
	//wypompowuje wod� z b�bna; zwraca kod b��du (9)
	char wypompujWode();
	//ustawia termostat grza�ki na temperatur� 'T' [�C]; zwraca kod b��du (7)
	char termostat(char T);
	//rozkr�ca b�bnen do cz�stotliwo�ci obrot�w 'f' [Hz]; zwraca kod b��du (6)
	char krecBebnem(double f);
	//zatrzymuje b�ben; zwraca kod b��du (5)
	inline char zatrzymajBeben();
protected:
	//czeka przez czas 't' [s]
	void czekaj(unsigned short t);
	//wykonuje funkcje o numerze 'id' (11, 12, 8, 9, 5)
	char funkcja(char id);
	//wykonuje funkcje o numerze 'id' z argumentem 'arg1' (7 6)
	char funkcja(char id, char arg1);
	char funkcja(char id, double arg1);
	//wykonuje funkcje o numerze 'id' z argumentem 'arg1', 'arg2', 'arg3' (8)
	char funkcja(char id, bool arg1, bool arg2, bool arg3);
	//sprawdza czy aktualny stan jest stanem domy�lnym; zwraca kod b��du
	char checkDefault();
};
#endif