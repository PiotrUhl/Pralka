#ifndef Program_h
#define Program_h

#include "Symulacja.h"

#include <string>
#include <vector>

//struktura przechowuj¹ca dane o pojedynczym punkcie programu (funkcji)
struct function {
	function() : id(0), T(-1), f(0) {}
	int id; //id funkcji 
	char T; //temperatura T (7) lub flagi przegródek (8)
	double f; //czêstotliwoœæ f (6)
	unsigned short t; //czas t (10)
};

class Program {

	std::string name; //nazwa programu
	std::vector<function> program; //tablica z kolejnymi funkcjami programu
	bool finished; //program jest zakoñczony i gotowy do u¿ycia

public:
	//konstruktor
	Program();
	Program(const std::string &_name);
	Program(const Program &_program);
	//zwraca nazwê programu
	std::string getName();
	//ustawia nazwe programu na 'newName'
	void setName(const std::string &newName);
	//dodaje do programu po punkcie numer 'nr' (dla nr == -1 dodaje na koñcu) punkt o id 'id' [z argumentem 'arg1']
	void addFunction(int nr, int id);
	void addFunction(int nr, int id, char arg1);
	void addFunction(int nr, int id, double arg1);
	void addFunction(int nr, int id, unsigned short arg1);
	//dodaje do programu po punkcie numer 'nr' (dla nr == -1 dodaje na koñcu) punkt o x
	void addFunction(int nr, function x);
	//usuwa z programu funkcjê spod numeru 'nr' (dla nr == -1 usuwa ostatni¹) 
	void delFunction(int nr = -1);
	//zwraca funkcjê programu spod numeru 'nr'
	function getFunction(int nr);
	//zwraca iloœæ funkcji w programie
	int getSize();
	//zwraca wartoœæ pola finished
	bool getFinished();
	//ustawia wartoœæ pola finished na 'var'
	bool setFinished(bool var);
};
#endif