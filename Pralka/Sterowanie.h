#ifndef Sterowanie_h
#define Sterowanie_h

#include "Pralka.h"

#include <windows.h>

class Sterowanie : private Pralka {
private:
	//blokuje drzwi pralki; zwraca kod b³êdu (11)
	char zablokujDrzwi();
	//odblokowuje drzwi pralki; zwraca kod b³êdu (12)
	char odblokujDrzwi();
	//wpomowuje czyst¹ wodê do bêbna; zwraca kod b³edu (8)
	inline char wpompujWode();
	//wpompowuje do bêbna wodê wraz z substancjami z substancj¹ z wybranych przegródek; zwraca kod b³êdu (8)
	char wpompujWode(bool substancja1, bool substancja2, bool substancja3);
	//wypompowuje wodê z bêbna; zwraca kod b³êdu (9)
	char wypompujWode();
	//ustawia termostat grza³ki na temperaturê 'T' [°C]; zwraca kod b³êdu (7)
	char termostat(char T);
	//rozkrêca bêbnen do czêstotliwoœci obrotów 'f' [Hz]; zwraca kod b³êdu (6)
	char krecBebnem(double f);
	//zatrzymuje bêben; zwraca kod b³êdu (5)
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
	//sprawdza czy aktualny stan jest stanem domyœlnym; zwraca kod b³êdu
	char checkDefault();
};
#endif