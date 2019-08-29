#ifndef Programowanie_h
#define Programowanie_h

#include "Program.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

//interfejs u¿ytkownika - program do tworzenia w³asnych programów prania
class Programowanie {

	const unsigned int memorySize; //rozmiar wewnêtrznej pamiêci pralki (zale¿na od modelu)
	Program** memory; //wewnêtrzna pamiêæ pralki

	bool exit; //wydano polecenie wyjœcia z programu
	int ret; //wartoœæ zwracana przez program
	int active; //obecnie wybrany element pamieci wewnêtrznej (-1 - nie wybrano)
	Symulacja** simulation; //tablica z symulacjami poszczególnych programów

private:
	//pobiera polecenie od u¿ytkownika
	std::string getCommand();
	//dzieli pobrane polecenie 'command' na poszczególne s³owa - polecenie i argumenty
	std::vector<std::string> cutCommand(std::string command);
	//interpretuje polecenie 'command' i wywo³uje odpowiedni¹ funkcjê
	void interpretCommand(const std::vector<std::string> &command);


//lista dostêpnych poleceñ
	//wychodzi z programu
	void cmd_exit(const std::vector<std::string> &command);
	//wypisuje pomoc dla u¿ytkownika
	void cmd_help(const std::vector<std::string> &command);
	//wypisuje tablicê pamiêci pralki na programy
	void cmd_list(const std::vector<std::string> &command);
	//wybiera aktywny element pamiêci
	void cmd_active(const std::vector<std::string> &command);
	//tworzy nowy program prania w aktywnej komórce pamiêci
	void cmd_new(const std::vector<std::string> &command);
	//usuwa program prania z aktywnej komórki pamiêci
	void cmd_delete(const std::vector<std::string> &command);
	//kopiuje program z innej komórki do aktywnej komórki pamiêci
	void cmd_copy(const std::vector<std::string> &command);
	//zmienia nazwê programu w aktywnej komórce
	void cmd_rename(const std::vector<std::string> &command);
	//dodaje punkt do programu prania
	void cmd_add(const std::vector<std::string> &command);
	//usuwa ostatni punkt programu prania
	void cmd_remove(const std::vector<std::string> &command);
	//wyœwietla na ekranie zawartoœæ aktywnego programu
	void cmd_show(const std::vector<std::string> &command);
	//symuluje dzia³anie wybranego programu prania
	void cmd_simulation(const std::vector<std::string> &command);
	//eksportuje aktywny program do pliku
	void cmd_export(const std::vector<std::string> &command);
	//importuje program z pliku do aktywnego slotu pamiêci
	void cmd_import(const std::vector<std::string> &command);


//metody pomocnicze
	//przerywa dzia³anie programu wypisuj¹c komunikat o b³êdzie
	void appCrash(char error);
	//wypisuje komunikat o nierozpoznanym poleceniu
	void unknowncmd();
	//wypisuje ca³¹ zawartoœæ pliku o nazwie 'file' na ekran (help; * /h)
	void coutFile(const std::string &file);
	//szuka wœród parametrów parametru 'arg'; zwraca true jeœli znajdzie
	bool searchForArg(const std::vector<std::string> &command, const std::string &arg);
	bool searchForArg(const std::vector<std::string> &command, char arg);
	//szuka wœród parametrów parametrów "/h", "\h", "-h", "--h", "/help", "\help", "-help", "--help"; zwraca true jeœli znajdzie
	bool searchForHelp(const std::vector<std::string> &command);
	//konwertuje argument 'arg' na liczbê ca³kowit¹ dodatni¹; zwraca wynik; [z zakresu <x, y>]; w razie niepowodzenia wypisuje odpowiednie komunikaty i zwraca -1
	//wypisuje zapytanie "str" i œci¹ga od u¿ytkownika odpowiedŸ tak lub nie; 'def' = 0 domyœlnie false, = 1 domyœlnie true, = -1 pyta w pêtli; zwraca odpowiedŸ
	bool askBool(const std::string &str, const char &def);
	unsigned int argToInt(const std::vector<std::string> &command, unsigned int arg);
	//konwertuje argument 'arg' na liczbê odpowiadaj¹c¹ indeksowi komórki pamiêci; zwraca wynik; w razie niepowodzenia wypisuje odpowiednie komunikaty i zwraca -1
	int argToMemIndex(const std::vector<std::string> &command, unsigned int arg);
	//zamienia kropkê na przecinek w ³añcuchu 'str' (separator dzesiêtny)
	std::string commaToDotDecimalSeparator(std::string str); //nie przez referencje celowo!
	//zapisuje obiekt "program" do pliku o œcie¿ce "path"; zwraca kod b³êdu
	char exportProgram(Program* program, const std::string &path);
	char exportProgram(Program* program, const std::string &path, std::ofstream &ofile);
	//odczytuje program z pliku o œcie¿ce "path"; zwraca go, b¹dŸ nullptr w razie b³êdu
	Program* importProgram(const std::string &path);
	Program* importProgram(const std::string &path, std::ifstream &ifile);
	//zapisuje ca³¹ pamiêæ programu do pliku o œcie¿ce "path"; zwraca kod b³êdu
	char exportMemory(const std::string &path);
	//odczytuje ca³¹ pamiêæ programu z pliku o œcie¿ce "path"; zwraca kod b³êdu
	char importMemory(const std::string &path);

public:
	//konstruktor
	Programowanie(int _memorySize);
	//destruktor
	~Programowanie();
	//g³ówna pêtla programu (wiersz poleceñ)
	int cmd();
};

#endif