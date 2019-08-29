#include "Symulacja.h"

//konstruktor; symulowany program '_program'
Symulacja::Symulacja(Program* _program) : program(_program) {}

//zmienia wykonywany program
void Symulacja::setProgram(Program* var) {
	program = var;
}

//wykonuje symulacje funkcji o numerze 'nr' (-1 symuluje ostatni¹) z prêdkoœci¹ 'predkosc' razy szybsz¹ (0 pomija pauzy (default)); quiet wycisza komunikaty (default); zwraca kod b³êdu
char Symulacja::wykonajFunkcje(int nr, bool quiet, float predkosc) {
	int currentId = program->getFunction(nr).id;
	int ret = 0;
	switch (currentId) {
	case 10:
		ret = functionId10(program->getFunction(nr).t, predkosc, quiet);
		break;
	case 11:
		ret = functionId11(quiet);
		break;
	case 12:
		ret = functionId12(quiet);
		break;
	case 8:
		ret = functionId8(quiet);
		break;
	case 9:
		ret = functionId9(quiet);
		break;
	case 7:
		ret = functionId7(program->getFunction(nr).T, quiet);
		break;
	case 6:
		ret = functionId6(program->getFunction(nr).f, quiet);
		break;
	case 5:
		ret = functionId5(quiet);
		break;
	default:
		return -4; //b³¹d w programie - nierozpoznane id
	}
	return ret;
}

//wykonuje symulacje ca³ego programu prania z prêdkoœci¹ 'predkosc' razy szybsz¹ (0 pomija pauzy (default)); quiet wycisza komunikaty (default); zwraca kod b³êdu
char Symulacja::wykonajCalosc(bool quiet, float predkosc) {
	int rozmiar = program->getSize();
	char ret;
	for (int i = 0; i < rozmiar; i++) {
		ret = wykonajFunkcje(i, quiet, predkosc);
		if (ret < 0) //je¿eli wyst¹pi³ b³¹d
			return ret;
	}
	//kontrola stanu koñcowego
	return checkDefault();
}

//symulacja wykonania funkcji o konkretnym id; 'quiet' nie wypisuje komunikatów o powodzeniu; zwraca kod b³êdu
char Symulacja::functionId11(bool quiet) { //zablokujDrzwi()
	if (!quiet)
		std::cout << "Locking door: ";
	char ret = funkcja(11);
	if (ret == -112)
		//if (!quiet)
			std::cout << "ERROR (-112 - door is open)" << std::endl;
	if (ret == 111)
		if (!quiet)
			std::cout << "OK (111 - door already locked)" << std::endl;
	if (ret == 110)
		if (!quiet)
			std::cout << "OK (110)" << std::endl;
	return ret;
}
char Symulacja::functionId12(bool quiet) { //odblokujDrzwi()
	if (!quiet)
		std::cout << "Unlocking door: ";
	char ret = funkcja(12);
	if (ret == 120)
		if (!quiet)
			std::cout << "OK (120)" << std::endl;
	else if (ret == -121)
		//if (!quiet
			std::cout << "ERROR (-121 - drum is rotating)" << std::endl;
	else if (ret == -122)
		//if (!quiet)
			std::cout << "ERROR (-122 - drum is rotating)" << std::endl;
	else if (ret == -123)
		//if (!quiet)
			std::cout << "ERROR (-123 - water in drum)" << std::endl;
	else if (ret == -124)
		//if (!quiet)
			std::cout << "ERROR (-124 - water in drum)" << std::endl;
	else if (ret == -125)
		//if (!quiet)
			std::cout << "ERROR (-125 - water in drum)" << std::endl;
	else if (ret == -126)
		//if (!quiet)
			std::cout << "ERROR (-126 - water in drum)" << std::endl;
	else if (ret == -127)
		//if (!quiet)
			std::cout << "ERROR (-127 - water drain is closed)" << std::endl;
	return ret;
}
char Symulacja::functionId8(bool quiet) { //wpompujWode()
	if (!quiet)
		std::cout << "Pumping water in: ";
	char ret = funkcja(8);
	if (ret == 80)
		if (!quiet)
			std::cout << "OK (80)" << std::endl;
	else if (ret == -82)
		//if (!quiet)
			std::cout << "ERROR (-82 - door is open)" << std::endl;
	else if (ret == -83)
		//if (!quiet)
			std::cout << "ERROR (-83 - door isn't locked)" << std::endl;
	else if (ret == 81)
		if (!quiet)
			std::cout << "OK (81 - Water is already beeing pumped in)" << std::endl;
	return ret;
}
char Symulacja::functionId8(char T, bool quiet) { //wpompujWode()
	if (!quiet)
		std::cout << "Pumping water in: ";
	std::bitset<3> args(T);
	char ret = funkcja(8, args[0], args[1], args[2]);
	if (ret == 80)
		if (!quiet)
			std::cout << "OK (80)" << std::endl;
		else if (ret == -82)
			//if (!quiet)
			std::cout << "ERROR (-82 - door is open)" << std::endl;
		else if (ret == -83)
			//if (!quiet)
			std::cout << "ERROR (-83 - door isn't locked)" << std::endl;
		else if (ret == 81)
			if (!quiet)
				std::cout << "OK (81 - Water is already beeing pumped in)" << std::endl;
	return ret;
}
char Symulacja::functionId9(bool quiet) { //wypompujWode()
	if (!quiet)
		std::cout << "Pumping water out: ";
	char ret = funkcja(9);
	if (ret == 90)
		if (!quiet)
			std::cout << "OK (90)" << std::endl;
	return ret;
}
char Symulacja::functionId7(char T, bool quiet) { //termostat()
	if (!quiet)
		std::cout << "Setting temperature: ";
	char ret = funkcja(7, T);
	if (ret == 70)
		if (!quiet)
			std::cout << T << " OK (70)" << std::endl;
	else if (ret == -71)
		//if (!quiet)
			std::cout << T << " ERROR (-71 - water drain is open)" << std::endl;
	else if (ret == -72)
		//if (!quiet)
			std::cout << T << " ERROR (-72 - door is open)" << std::endl;
	else if (ret == -73)
		//if (!quiet)
			std::cout << T << " ERROR (-73 - door isn't locked)" << std::endl;
	return ret;
}
char Symulacja::functionId6(double f, bool quiet) { //krecBebnem()
	if (!quiet)
		std::cout << "Rotating the drum: ";
	char ret = funkcja(6, f);
	if (ret == 60)
		if (!quiet)
			std::cout << f << " OK (60)" << std::endl;
	else if (ret == -61)
		//if (!quiet)
			std::cout << f << " ERROR (-72 - door is open)" << std::endl;
	else if (ret == -62)
		//if (!quiet)
			std::cout << f << " ERROR (-73 - door isn't locked)" << std::endl;
	return ret;
}
char Symulacja::functionId5(bool quiet) { //zatrzymajBeben()
	if (!quiet)
		std::cout << "Stopping the drum: ";
	char ret = funkcja(5);
	if (ret == 50)
		if (!quiet)
			std::cout << "OK (50)" << std::endl;
	return ret;
}

//symulacja wykonania funkcji czekaj przez 'czas', 'predkosc' razy szybciej (0 pomija pauzy)
char Symulacja::functionId10(unsigned short czas, float predkosc, bool quiet) {
	if (!quiet)
		std::cout << "Waiting: " << czas << '/' << predkosc << ' = ' << static_cast<unsigned short>(czas/predkosc) << "...";
	if (predkosc != 0)
		czekaj(static_cast<unsigned short>(static_cast<float>(czas * 1000) / predkosc));
	if (!quiet)
		std::cout << std::endl;
	return 100;
}

//sprawdza czy aktualna symulacja jest zakonczona
bool Symulacja::zakonczona() {
	if (checkDefault() == 0)
		return true;
	else
		return false;
}