#ifndef Programowanie_h
#define Programowanie_h

#include "Program.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

//interfejs u�ytkownika - program do tworzenia w�asnych program�w prania
class Programowanie {

	const unsigned int memorySize; //rozmiar wewn�trznej pami�ci pralki (zale�na od modelu)
	Program** memory; //wewn�trzna pami�� pralki

	bool exit; //wydano polecenie wyj�cia z programu
	int ret; //warto�� zwracana przez program
	int active; //obecnie wybrany element pamieci wewn�trznej (-1 - nie wybrano)
	Symulacja** simulation; //tablica z symulacjami poszczeg�lnych program�w

private:
	//pobiera polecenie od u�ytkownika
	std::string getCommand();
	//dzieli pobrane polecenie 'command' na poszczeg�lne s�owa - polecenie i argumenty
	std::vector<std::string> cutCommand(std::string command);
	//interpretuje polecenie 'command' i wywo�uje odpowiedni� funkcj�
	void interpretCommand(const std::vector<std::string> &command);


//lista dost�pnych polece�
	//wychodzi z programu
	void cmd_exit(const std::vector<std::string> &command);
	//wypisuje pomoc dla u�ytkownika
	void cmd_help(const std::vector<std::string> &command);
	//wypisuje tablic� pami�ci pralki na programy
	void cmd_list(const std::vector<std::string> &command);
	//wybiera aktywny element pami�ci
	void cmd_active(const std::vector<std::string> &command);
	//tworzy nowy program prania w aktywnej kom�rce pami�ci
	void cmd_new(const std::vector<std::string> &command);
	//usuwa program prania z aktywnej kom�rki pami�ci
	void cmd_delete(const std::vector<std::string> &command);
	//kopiuje program z innej kom�rki do aktywnej kom�rki pami�ci
	void cmd_copy(const std::vector<std::string> &command);
	//zmienia nazw� programu w aktywnej kom�rce
	void cmd_rename(const std::vector<std::string> &command);
	//dodaje punkt do programu prania
	void cmd_add(const std::vector<std::string> &command);
	//usuwa ostatni punkt programu prania
	void cmd_remove(const std::vector<std::string> &command);
	//wy�wietla na ekranie zawarto�� aktywnego programu
	void cmd_show(const std::vector<std::string> &command);
	//symuluje dzia�anie wybranego programu prania
	void cmd_simulation(const std::vector<std::string> &command);
	//eksportuje aktywny program do pliku
	void cmd_export(const std::vector<std::string> &command);
	//importuje program z pliku do aktywnego slotu pami�ci
	void cmd_import(const std::vector<std::string> &command);


//metody pomocnicze
	//przerywa dzia�anie programu wypisuj�c komunikat o b��dzie
	void appCrash(char error);
	//wypisuje komunikat o nierozpoznanym poleceniu
	void unknowncmd();
	//wypisuje ca�� zawarto�� pliku o nazwie 'file' na ekran (help; * /h)
	void coutFile(const std::string &file);
	//szuka w�r�d parametr�w parametru 'arg'; zwraca true je�li znajdzie
	bool searchForArg(const std::vector<std::string> &command, const std::string &arg);
	bool searchForArg(const std::vector<std::string> &command, char arg);
	//szuka w�r�d parametr�w parametr�w "/h", "\h", "-h", "--h", "/help", "\help", "-help", "--help"; zwraca true je�li znajdzie
	bool searchForHelp(const std::vector<std::string> &command);
	//konwertuje argument 'arg' na liczb� ca�kowit� dodatni�; zwraca wynik; [z zakresu <x, y>]; w razie niepowodzenia wypisuje odpowiednie komunikaty i zwraca -1
	//wypisuje zapytanie "str" i �ci�ga od u�ytkownika odpowied� tak lub nie; 'def' = 0 domy�lnie false, = 1 domy�lnie true, = -1 pyta w p�tli; zwraca odpowied�
	bool askBool(const std::string &str, const char &def);
	unsigned int argToInt(const std::vector<std::string> &command, unsigned int arg);
	//konwertuje argument 'arg' na liczb� odpowiadaj�c� indeksowi kom�rki pami�ci; zwraca wynik; w razie niepowodzenia wypisuje odpowiednie komunikaty i zwraca -1
	int argToMemIndex(const std::vector<std::string> &command, unsigned int arg);
	//zamienia kropk� na przecinek w �a�cuchu 'str' (separator dzesi�tny)
	std::string commaToDotDecimalSeparator(std::string str); //nie przez referencje celowo!
	//zapisuje obiekt "program" do pliku o �cie�ce "path"; zwraca kod b��du
	char exportProgram(Program* program, const std::string &path);
	char exportProgram(Program* program, const std::string &path, std::ofstream &ofile);
	//odczytuje program z pliku o �cie�ce "path"; zwraca go, b�d� nullptr w razie b��du
	Program* importProgram(const std::string &path);
	Program* importProgram(const std::string &path, std::ifstream &ifile);
	//zapisuje ca�� pami�� programu do pliku o �cie�ce "path"; zwraca kod b��du
	char exportMemory(const std::string &path);
	//odczytuje ca�� pami�� programu z pliku o �cie�ce "path"; zwraca kod b��du
	char importMemory(const std::string &path);

public:
	//konstruktor
	Programowanie(int _memorySize);
	//destruktor
	~Programowanie();
	//g��wna p�tla programu (wiersz polece�)
	int cmd();
};

#endif