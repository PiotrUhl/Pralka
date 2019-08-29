#ifndef Symulacja_h
#define Symulacja_h

#include "Sterowanie.h"
#include "Program.h"

#include <iostream>
#include <bitset>

class Symulacja : private Sterowanie {
private:
	class Program* program; //symulowany program //nie chcia�o si� kompilowa� bez tego class, nie wiem czemu

	//symulacja wykonania funkcji o konkretnym id; 'quiet' nie wypisuje komunikat�w o powodzeniu; zwraca kod b��du
	char functionId11(bool quiet);
	char functionId12(bool quiet);
	char functionId8(bool quiet);
	char functionId8(char T, bool quiet);
	char functionId9(bool quiet);
	char functionId7(char T, bool quiet);
	char functionId6(double f, bool quiet);
	char functionId5(bool quiet);
	//symulacja wykonania funkcji czekaj przez 'czas', 'predkosc' razy szybciej (0 pomija pauzy)
	char functionId10(unsigned short czas, float predkosc, bool quiet);

public:
	//konstruktor; symulowany program '_program'
	Symulacja(Program* _program);
	//zmienia wykonywany program
	void setProgram(Program* var);

	//wykonuje symulacje funkcji o numerze 'nr' (-1 symuluje ostatni�) z pr�dko�ci� 'predkosc' razy szybsz� (0 pomija pauzy (default)); quiet wycisza komunikaty (default); zwraca kod b��du
	char wykonajFunkcje(int nr = -1, bool quiet = true, float predkosc = 0);
	//wykonuje symulacje ca�ego programu prania z pr�dko�ci� 'predkosc' razy szybsz� (0 pomija pauzy (default)); quiet wycisza komunikaty (default); zwraca kod b��du
	char wykonajCalosc(bool quiet = true, float predkosc = 0);

	//sprawdza czy aktualna symulacja jest zakonczona
	bool zakonczona();
};
#endif