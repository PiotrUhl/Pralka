#ifndef Program_h
#define Program_h

#include "Symulacja.h"

#include <string>
#include <vector>

//struktura przechowuj�ca dane o pojedynczym punkcie programu (funkcji)
struct function {
	function() : id(0), T(-1), f(0) {}
	int id; //id funkcji 
	char T; //temperatura T (7) lub flagi przegr�dek (8)
	double f; //cz�stotliwo�� f (6)
	unsigned short t; //czas t (10)
};

class Program {

	std::string name; //nazwa programu
	std::vector<function> program; //tablica z kolejnymi funkcjami programu
	bool finished; //program jest zako�czony i gotowy do u�ycia

public:
	//konstruktor
	Program();
	Program(const std::string &_name);
	Program(const Program &_program);
	//zwraca nazw� programu
	std::string getName();
	//ustawia nazwe programu na 'newName'
	void setName(const std::string &newName);
	//dodaje do programu po punkcie numer 'nr' (dla nr == -1 dodaje na ko�cu) punkt o id 'id' [z argumentem 'arg1']
	void addFunction(int nr, int id);
	void addFunction(int nr, int id, char arg1);
	void addFunction(int nr, int id, double arg1);
	void addFunction(int nr, int id, unsigned short arg1);
	//dodaje do programu po punkcie numer 'nr' (dla nr == -1 dodaje na ko�cu) punkt o x
	void addFunction(int nr, function x);
	//usuwa z programu funkcj� spod numeru 'nr' (dla nr == -1 usuwa ostatni�) 
	void delFunction(int nr = -1);
	//zwraca funkcj� programu spod numeru 'nr'
	function getFunction(int nr);
	//zwraca ilo�� funkcji w programie
	int getSize();
	//zwraca warto�� pola finished
	bool getFinished();
	//ustawia warto�� pola finished na 'var'
	bool setFinished(bool var);
};
#endif