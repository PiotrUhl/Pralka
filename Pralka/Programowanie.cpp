#include "Programowanie.h"

//interpretuje polecenie 'command' i wywo³uje odpowiedni¹ funkcjê
void Programowanie::interpretCommand(const std::vector<std::string> &command) {
	if (command.size() < 1)
		;
	else if (command[0] == "exit" || command[0] == "quit")
		cmd_exit(command);
	else if (command[0] == "help")
		cmd_help(command);
	else if (command[0] == "list")
		cmd_list(command);
	else if (command[0] == "active" || command[0] == "select")
		cmd_active(command);
	else if (command[0] == "new")
		cmd_new(command);
	else if (command[0] == "delete")
		cmd_delete(command);
	else if (command[0] == "copy")
		cmd_copy(command);
	else if (command[0] == "rename")
		cmd_rename(command);
	else if (command[0] == "add")
		cmd_add(command);
	else if (command[0] == "remove")
		cmd_remove(command);
	else if (command[0] == "show")
		cmd_show(command);
	else if (command[0] == "simulation")
		cmd_simulation(command);
	else if (command[0] == "export")
		cmd_export(command);
	else if (command[0] == "import")
		cmd_import(command);
	else
		unknowncmd();
}

//konstruktor
Programowanie::Programowanie(int _memorySize) : memorySize(_memorySize), exit(false), ret(0), active(-1) {
	memory = new Program*[memorySize];
	simulation = new Symulacja*[memorySize];
	if (memory == nullptr || simulation == nullptr)
		appCrash(-20); //nie mo¿na zaalokowaæ pamiêci
	for (unsigned int i = 0; i < memorySize; i++) {
		memory[i] = nullptr;
		simulation[i] = nullptr;
	}
}
//destruktor
Programowanie::~Programowanie() {
	for (unsigned int i = 0; i < memorySize; i++) {
		if (memory[i] != nullptr) {
			delete memory[i];
		}
		if (simulation[i] != nullptr) {
			delete simulation[i];
		}
	}
	delete[] memory;
	delete[] simulation;
}

//pobiera polecenie od u¿ytkownika
std::string Programowanie::getCommand() {
	using namespace std;
	string command;
	if (active != -1) //wyœwietla wybrany element przed znakiem zachêty
		cout << '[' << active << ']';
	cout << "> "; //wypisuje znak zachêty
	getline(cin, command);
	return command;
}
//dzieli pobrane polecenie 'command' na poszczególne s³owa - polecenie i argumenty
std::vector<std::string> Programowanie::cutCommand(std::string command) {
	using namespace std;
	vector<string> tab; //tablica sk³adowych polecenia (polecenie + argumenty)
	size_t pos = 0;
	while (pos != string::npos) {
		size_t found = command.find(' ', pos);
		if (found == string::npos) {
			if (pos != command.size())
				tab.push_back(command.substr(pos, string::npos));
			pos = string::npos;
		}
		else if (found == pos)
			pos++;
		else {
			tab.push_back(command.substr(pos, found - pos));
			pos = found + 1;
		}
	}
	return tab;
}

//przerywa dzia³anie programu wypisuj¹c komunikat o b³êdzie
void Programowanie::appCrash(char error) {
	ret = error;
	exit = true;
	std::cerr << "A fatal error has occurred. The application will be terminated. Error code: " << error;
	if (error = -20)
		std::cerr << " - cannot allocate memory.";
	std::cerr << "\n";
}
//wypisuje komunikat o nierozpoznanym poleceniu
void Programowanie::unknowncmd() {
	using namespace std;
	cout << "Unknown command. Type \"help\" to get more information." << endl;
}
//wypisuje ca³¹ zawartoœæ pliku 'file' na ekran  (help; * /h)
void Programowanie::coutFile(const std::string &file) {
	using namespace std;
	ifstream helpFile(file);
	if (!helpFile.is_open())
		cout << "Cannot open \"" << file << "\" file. The file may not exist, you may not have permissions to open it, or it may be open in another program." << endl;
	else {
		string helpLine;
		while (getline(helpFile, helpLine))
			cout << helpLine << endl;
		helpFile.close();
	}
}
//szuka wœród parametrów parametru 'arg'; zwraca true jeœli znajdzie
bool Programowanie::searchForArg(const std::vector<std::string> &command, const std::string &arg) {
	for (const std::string &i : command) {
		if (i == ("/"+arg) || i == ("\\"+arg) || i == ("-"+arg) || i == ("--"+arg))
			return true;
	}
	return false;
}
bool Programowanie::searchForArg(const std::vector<std::string> &command, char arg) {
	std::string tmp;
	tmp += arg;
	return searchForArg(command, tmp);
}
//szuka wœród parametrów parametrów "/h", "\h", "-h", "--h", "/help", "\help", "-help", "--help"; zwraca true jeœli znajdzie
inline bool Programowanie::searchForHelp(const std::vector<std::string> &command) { //todo: przerobiæ by u¿ywa³ searchForArg()
	return (searchForArg(command, "h") || searchForArg(command, "help"));
}
//wypisuje zapytanie "str" i œci¹ga od u¿ytkownika odpowiedŸ tak lub nie; 'def' = 0 domyœlnie false, = 1 domyœlnie true, = -1 pyta w pêtli; zwraca odpowiedŸ
bool Programowanie::askBool(const std::string &str, const char &def = -1) {
	using namespace std;
	string input;
	do {
		cout << str;
		cin >> input;
		cin.ignore();
		if (input == "y" || input == "Y" || input == "1" || input == "t" || input == "T" || input == "yes" || input == "Yes" || input == "true" || input == "True")
			return true;
		else if (input == "n" || input == "N" || input == "0" || input == "f" || input == "F" || input == "no" || input == "No" || input == "false" || input == "False")
			return false;
		else if (def != -1)
			return def;
	} while (def == -1);
	return def; //nie powynno siê wywo³aæ, by unikn¹æ warninga
}
//konwertuje argument 'arg' na liczbê ca³kowit¹ dodatni¹; zwraca wynik; w razie niepowodzenia wypisuje odpowiednie komunikaty i zwraca -1
unsigned int Programowanie::argToInt(const std::vector<std::string> &command, unsigned int arg) {
	unsigned int var = -1;
	if (command.size() <= arg) {
		std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
		return -1;
	}
	try {
		var = std::stoi(command[arg]);
	}
	catch (const std::invalid_argument&) {
		std::cout << "Invalid argument: \"" << command[1] << "\" is not a number. Type \"" << command[0] << " -h\" to get more information." << std::endl;
		return -1;
	}
	catch (const std::out_of_range&) {
		std::cout << "Argument: \"" << command[1] << "\" is out of range." << std::endl;
		return -1;
	}
	return var;
}//konwertuje argument 'arg' na liczbê odpowiadaj¹c¹ indeksowi komórki pamiêci; zwraca wynik; w razie niepowodzenia wypisuje odpowiednie komunikaty i zwraca -1
int Programowanie::argToMemIndex(const std::vector<std::string> &command, unsigned int arg) {
	int var = argToInt(command, arg);
	if (var < 0 || var > memorySize - 1) {
		std::cout << "Invalid argument: \"" << var << "\" is not an index in memory. Argument must be in range (0;" << memorySize - 1 << ")." << std::endl;
		return -1;
	}
	return var;
}
//zamienia kropkê na przecinek w ³añcuchu 'str' (separator dzesiêtny)
std::string Programowanie::commaToDotDecimalSeparator(std::string str) {
	using namespace std;
	size_t found = str.find(',');
	if (found != string::npos) {
		str.replace(found, 1, ".");
	}
	return str;
}
//zapisuje obiekt "program" do pliku o œcie¿ce "path"; zwraca kod b³êdu
char Programowanie::exportProgram(Program* program, const std::string &path) {
	using namespace std;
	ofstream ofile(path, ios::out | ios::binary | ios::trunc);
	if (!ofile.is_open())
		return -1;
	string name = program->getName();
	size_t size = program->getSize();
	unsigned int zero = 0;
	ofile.write(reinterpret_cast<char*>(&zero), sizeof(zero)); //rozmiar pamiêci - program wiêc 0 - wartoœæ kontrolna
	ofile.write(reinterpret_cast<char*>(&size), sizeof(size)); //rozmiar programu
	ofile.write(name.c_str(), name.length() + 1); //nazwa
	for (unsigned int i = 0; i < size; i++) {
		function funkcja = program->getFunction(i);
		ofile.write(reinterpret_cast<char*>(&funkcja), sizeof(funkcja)); //program (punkt po punkcie)
	}
	ofile.close();
	return 0;
}
char Programowanie::exportProgram(Program* program, const std::string &path, std::ofstream &ofile) {
	using namespace std;
	if (program == nullptr) {
		size_t size = 0;
		ofile.write(reinterpret_cast<char*>(&size), sizeof(size)); //rozmiar programu
	}
	else {
		string name = program->getName();
		size_t size = program->getSize();
		ofile.write(reinterpret_cast<char*>(&size), sizeof(size)); //rozmiar programu
		if (size != 0) {
			ofile.write(name.c_str(), name.length() + 1); //nazwa
			for (unsigned int i = 0; i < size; i++) {
				function funkcja = program->getFunction(i);
				ofile.write(reinterpret_cast<char*>(&funkcja), sizeof(funkcja)); //program (punkt po punkcie)
			}
		}
	}
	return 0;
}
//zapisuje ca³¹ pamiêæ programu do pliku o œcie¿ce "path"; zwraca kod b³êdu
char Programowanie::exportMemory(const std::string &path) {
	using namespace std;
	ofstream ofile(path, ios::out | ios::binary | ios::trunc);
	if (!ofile.is_open())
		return -1;
	ofile.write(reinterpret_cast<char*>(const_cast<unsigned int*>(&memorySize)), sizeof(memorySize)); //rozmiar pamiêci - wartoœæ kontrolna
	for (unsigned int i = 0; i < memorySize; i++) { //zapisywanie ka¿dego punktu po kolei
		exportProgram(memory[i], path, ofile);
	}
	ofile.close();
	return 0;
}
//odczytuje program z pliku o œcie¿ce "path"; zwraca go, b¹dŸ nullptr w razie b³êdu
Program* Programowanie::importProgram(const std::string &path) {
	using namespace std;
	ifstream ifile(path, ios::in | ios::binary);
	if (!ifile.is_open())
		return nullptr;
	unsigned int zero = 1;
	ifile.read(reinterpret_cast<char*>(&zero), sizeof(zero)); //bit kontrolny
	if (zero != 0)
		return nullptr; //to nie jest poprawny plik z programem
	Program* nowy = new Program;
	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size)); //rozmiar programu
	string name;
	getline(ifile, name, '\0'); //nazwa
	nowy->setName(name);
	for (unsigned int i = 0; i < size; i++) {
		function nowa;
		ifile.read(reinterpret_cast<char*>(&nowa), sizeof(function)); //program (punkt po punkcie)
		nowy->addFunction(-1, nowa);
	}
	ifile.close();
	return nowy;
}
Program* Programowanie::importProgram(const std::string &path, std::ifstream &ifile) {
	using namespace std;
	Program* nowy = nullptr;
	string name;
	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size)); //rozmiar programu
	if (size != 0) {
		nowy = new Program;
		getline(ifile, name, '\0'); //nazwa
		nowy->setName(name);
		for (unsigned int i = 0; i < size; i++) {
			function nowa;
			ifile.read(reinterpret_cast<char*>(&nowa), sizeof(function)); //program (punkt po punkcie)
			nowy->addFunction(-1, nowa);
		}
	}
	return nowy;
}
//odczytuje ca³¹ pamiêæ programu z pliku o œcie¿ce "path"; zwraca kod b³êdu
char Programowanie::importMemory(const std::string &path) {
	using namespace std;
	ifstream ifile(path, ios::in | ios::binary);
	if (!ifile.is_open())
		return -1;
	unsigned int memSize = 0;
	ifile.read(reinterpret_cast<char*>(&memSize), sizeof(memSize)); //rozmiar pamiêci
	if (memSize == 0)
		return -2; //to nie jest poprawny plik z pamiêci¹
	memSize = max(memorySize, memSize);
	for (unsigned int i = 0; i < memSize; i++) {
		memory[i] = importProgram(path, ifile);
	}
	ifile.close();
	return 0;
}


//g³ówna pêtla programu (wiersz poleceñ)
int Programowanie::cmd() {
	while (!exit) {
		interpretCommand(cutCommand(getCommand()));
	}
	return ret;
}

//wychodzi z programu
inline void Programowanie::cmd_exit(const std::vector<std::string> &command) {
	exit = true;
}
//wypisuje pomoc dla u¿ytkownika
inline void Programowanie::cmd_help(const std::vector<std::string> &command) {
	coutFile("help/help.txt");
}
//wypisuje zawartoœæ pamiêci wewnêtrznej pralki (nazwy programów)
void Programowanie::cmd_list(const std::vector<std::string> &command) {
	using namespace std;
	for (unsigned int i = 0; i < memorySize; i++) {
		if (active == i)
			cout << "->";
		else
			cout << ' ';
		cout << '[' << i << "]\t";
		if (memory[i] != nullptr) {
			cout << memory[i]->getName();
			if (memory[i]->getFinished() == false)
				cout << " *";
		}
		cout << endl;
	}
}
//wybiera aktywny element pamiêci
void Programowanie::cmd_active(const std::vector<std::string> &command) {
	if (searchForHelp(command))
		coutFile("help/active.txt");
	else if (command.size() < 2)
		std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
	else if (command[1] == "none")
		active = -1;
	else {
		int var = argToMemIndex(command, 1);
		if (var != -1) {
			active = var;
			//po zmianie
			if (memory[active] == nullptr)
				std::cout << "Memory cell [" << active << "] is empty. Type \"new <name>\" to create new washing program." << std::endl;
			else {
				if (memory[active]->getSize() == 0)
					std::cout << "Program " << memory[active]->getName() << " is empty. Add function to program using \"add\" command." << std::endl;
				else if (memory[active]->getFinished() == true)
					std::cout << "Program " << memory[active]->getName() << " is finished and ready to use." << std::endl;
				else {
					std::cout << "Program " << memory[active]->getName() << " isn't finished and cannot be used yet." << std::endl;
					//todo: wypisz co jest nieukoñczone
				}
			}
		}
	}
}
//tworzy nowy program prania w aktywnej komórce pamiêci
void Programowanie::cmd_new(const std::vector<std::string> &command) {
	using namespace std;
	if (searchForHelp(command))
		coutFile("help/new.txt");
	else if (active == -1)
		cout << "Select memory cell using \"active <index>\" command." << endl;
	else if (memory[active] != nullptr)
		cout << "This memory cell is not empty! Use other cell or delete existing washing program with command \"delete\"." << endl;
	else {
		//pobieranie nazwy
		string newName;
		if (command.size() > 1)
			newName = command[1];
		while (newName == "") {
			cout << "Enter new washing program name: ";
			getline(cin, newName);
			if (newName == "") {
				cout << "Program name cannot be empty!" << endl;
			}
		}
		//tworzenie programu
		memory[active] = new Program(newName);
		if (memory[active] == nullptr) {
			appCrash(-21); //nie mo¿na zaalokowaæ pamiêci
		}
		else {
			simulation[active] = new Symulacja(memory[active]);
			if (simulation[active] == nullptr) {
				appCrash(-21); //nie mo¿na zaalokowaæ pamiêci
			}
		}
		cout << "Washing program \"" << memory[active]->getName() << "\" created successfully in memory cell [" << active << "]." << endl;
	}
}
//usuwa program prania z aktywnej komórki pamiêci
void Programowanie::cmd_delete(const std::vector<std::string> &command) {
	if (searchForHelp(command))
		coutFile("help/delete.txt");
	else if (active == -1)
		std::cout << "Select memory cell using \"active <index>\" command." << std::endl;
	else if (memory[active] == nullptr && !searchForArg(command, "q") && !searchForArg(command, "Q"))
		std::cout << "This memory cell is already empty." << std::endl;
	else {
		if (!searchForArg(command, "q") && !searchForArg(command, "Q")) {
			if (askBool("Are you sure you want to delete this program? This operation cannot be undone! [y/N]", 0) == false)
				return;
		}
		delete memory[active];
		memory[active] = nullptr;
		delete simulation[active];
		simulation[active] = nullptr;
		std::cout << "Program successfully deleted." << std::endl;
	}
}
//kopiuje program z innej komórki do aktywnej komórki pamiêci
void Programowanie::cmd_copy(const std::vector<std::string> &command) {
	using namespace std;
	if (searchForHelp(command))
		coutFile("help/copy.txt");
	else if (active == -1)
		cout << "Select memory cell using \"active <index>\" command." << endl;
	else if (memory[active] != nullptr)
		cout << "This memory cell is not empty! Use other cell or delete existing washing program with command \"delete\"." << endl;
	else {
		int source = argToMemIndex(command, 1);
		if (source != -1) {
			if (memory[source] == nullptr)
				cout << "Source cell [" << source << "] is empty! Nothing to copy." << endl;
			else {
				memory[active] = new Program(*memory[source]);
				if (memory[active] == nullptr) {
					appCrash(-22); //nie mo¿na zaalokowaæ pamiêci
				}
				else {
					simulation[active] = new Symulacja(*simulation[source]);
					if (simulation[active] == nullptr) {
						appCrash(-22); //nie mo¿na zaalokowaæ pamiêci
					}
					simulation[active]->setProgram(memory[active]);
				}
				cout << "Washing program \"" << memory[active]->getName() << "\" created successfully in memory cell [" << active << "] as a copy of cell [" << source << "]." << endl;
			}
		}
	}
}
//zmienia nazwê programu w aktywnej komórce
void Programowanie::cmd_rename(const std::vector<std::string> &command) {
	if (searchForHelp(command))
		coutFile("help/rename.txt");
	else if (active == -1)
		std::cout << "Select memory cell using \"active <index>\" command." << std::endl;
	else if (memory[active] == nullptr)
		std::cout << "Active memory cell is empty." << std::endl;
	else if (command.size() < 2)
		std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
	else {
		memory[active]->setName(command[1]);
		std::cout << "Program successfully renamed." << std::endl;
	}
}
//dodaje punkt do programu prania
void Programowanie::cmd_add(const std::vector<std::string> &command) {
	if (searchForHelp(command)) {
		coutFile("help/add.txt");
		return;
	}
	else if (active == -1) {
		std::cout << "Select memory cell using \"active <index>\" command." << std::endl;
		return;
	}
	else if (memory[active] == nullptr) {
		std::cout << "This memory cell is empty. Create a washing program using \"new\" command." << std::endl;
		return;
	}
	else if (command.size() < 2) {
		std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
		return;
	}
	else {
		int var = argToInt(command, 1);
		if (var < 5 || var > 12) {
			std::cout << "Invalid argument: \"" << command[1] << "\". Type \"" << command[0] << " -h\" to get more information." << std::endl;
			return;
		}
		//dodawanie funkcji
		unsigned short pause = 0;
		if (var == 7) {
			if (command.size() < 3) {
				std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
				return;
			}
			char arg = argToInt(command, 2);
			if (arg < 0 || arg > 100) {
				std::cout << "Invalid argument: \"" << command[2] << "\" - argument must be in range (0; 100). Type \"" << command[0] << " -h\" to get more information." << std::endl;
				return;
			}
			else {
				memory[active]->addFunction(-1, var, arg);
			}
		}
		else if (var == 8) {
			if (command.size() > 2) {
				char args = 0;
 				char arg1 = argToInt(command, 2);
				if (arg1 == -1)
					return;
				if (command.size() > 3) {
					char arg2 = argToInt(command, 3);
					if (arg2 == -1)
						return;
					if (command.size() > 4) {
						char arg3 = argToInt(command, 4);
						if (arg3 == -1)
							return;
						else {
							if (arg1 == 1 || arg2 == 1 || arg3 == 1)
								args += 1;
							if (arg1 == 2 || arg2 == 2 || arg3 == 2)
								args += 2;
							if (arg1 == 3 || arg2 == 3 || arg3 == 3)
								args += 4;
						} //3-arg
					}
					else {
						if (arg1 == 1 || arg2 == 1)
							args += 1;
						if (arg1 == 2 || arg2 == 2)
							args += 2;
						if (arg1 == 3 || arg2 == 3)
							args += 4;
					} //2-arg
				}
				else {
					if (arg1 == 1)
						args += 1;
					if (arg1 == 2)
						args += 2;
					if (arg1 == 3)
						args += 4;
				} //1-arg
				memory[active]->addFunction(-1, var, args);
			}
			else { //0-arg
				memory[active]->addFunction(-1, var);
			}
		}
		else if (var == 6) {
			if (command.size() < 4) {
				std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
				return;
			}
			else {
				bool error = false;
				//konwersja argumentu double arg1
				double arg1;
				try {
					arg1 = std::stod(commaToDotDecimalSeparator(command[2]));
				}
				catch (const std::invalid_argument&) {
					std::cout << "Invalid argument: \"" << command[2] << "\" is not a number. Type \"" << command[0] << " -h\" to get more information." << std::endl;
					return;
				}
				catch (const std::out_of_range&) {
					std::cout << "Argument: \"" << command[2] << "\" is out of range." << std::endl;
					return;
				}
				//konwersja argumentu unsigned short arg2
				unsigned short arg2 = argToInt(command, 3);
				if (arg2 < 0) {
					std::cout << "Invalid argument: \"" << command[3] << "\". Type \"" << command[0] << " -h\" to get more information." << std::endl;
					return;
				}
				else {
					//dodanie funkcji
					pause = arg2;
					memory[active]->addFunction(-1, var, arg1);
				}
			}
		}
		else if (var == 10) {
			if (command.size() < 3) {
				std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
				return;
			}
			unsigned short arg = argToInt(command, 2);
			if (arg < 0) {
				std::cout << "Invalid argument: \"" << command[2] << "\" - argument must be in range (0; 100). Type \"" << command[0] << " -h\" to get more information." << std::endl;
				return;
			}
			else {
				memory[active]->addFunction(-1, var, arg);
			}
		}
		else {
			memory[active]->addFunction(-1, var);
		}
		//symulacja
		char simRet = simulation[active]->wykonajFunkcje(memory[active]->getSize() - 1, true);
		if (simRet < 0) {
			memory[active]->delFunction();
			std::cout << "An error occured (" << +simRet << "). Function hasn't been added to program." << std::endl;
		}
		else {
			if ((simRet % 10) == 0) {
				std::cout << "Function successfully added to program." << std::endl;
				if (pause != 0) { //pauza
					memory[active]->addFunction(-1, 10, pause);
					if (var == 6)
						memory[active]->addFunction(-1, 5);
					simulation[active]->wykonajFunkcje(memory[active]->getSize() - 1, true);
				}
			}
			else if (simRet == 111) {
				memory[active]->delFunction();
				std::cout << "The door is already locked." << std::endl;
			}
			else if (simRet == 81) {
				memory[active]->delFunction();
				std::cout << "Water is already beeing pumped in." << std::endl;
			}
			else if (simRet == 91) {
				memory[active]->delFunction();
				std::cout << "The water drain is already open." << std::endl;
			}
			else if (simRet == 128) {
				memory[active]->delFunction();
				std::cout << "The door isn't locked." << std::endl;
			}
			else if (simRet == 51) {
				memory[active]->delFunction();
				std::cout << "The drum isn't rotating." << std::endl;
			}
			if ((memory[active]->setFinished(simulation[active]->zakonczona())) == true) {
				std::cout << "Program " << memory[active]->getName() << " is finished and ready to use." << std::endl;
			}
		}
	}
}
//usuwa ostatni punkt programu prania
void Programowanie::cmd_remove(const std::vector<std::string> &command) {
	if (searchForHelp(command))
		coutFile("help/remove.txt");
	else if (active == -1)
		std::cout << "Select memory cell using \"active <index>\" command." << std::endl;
	else if (memory[active] == nullptr)
		std::cout << "This memory cell is empty. Nothing to remove." << std::endl;
	else if (memory[active]->getSize() == 0)
		std::cout << "This program is empty. Nothing to remove." << std::endl;
	else {
		memory[active]->delFunction();
		delete simulation[active];
		simulation[active] = new Symulacja(memory[active]);
		simulation[active]->wykonajCalosc();
		memory[active]->setFinished(simulation[active]->zakonczona());
	}
}
//wyœwietla na ekranie zawartoœæ aktywnego programu
void Programowanie::cmd_show(const std::vector<std::string> &command) {
	using namespace std;
	if (searchForHelp(command))
		coutFile("help/show.txt");
	else if (active == -1)
		cout << "Select memory cell using \"active\" command." << endl;
	else if (memory[active] == nullptr)
		cout << "This memory cell is empty. Create a washing program using \"new\" command." << endl;
	else if (memory[active]->getSize() == 0) {
		cout << "Washing program \"" << memory[active]->getName() << "\" is empty." << endl;
	}
	else {
		cout << "Washing program \"" << memory[active]->getName() << "\" from memory slot [" << active << "]:" << endl;
		int tabSize = memory[active]->getSize();
		for (int i = 0; i < tabSize; i++) {
			int id = memory[active]->getFunction(i).id;
			cout << "  " << i + 1 << ". ";
			cout.width(2);
			cout << id;
			switch (id) {
			case 11:
				cout << " - lock door" << endl;
				break;
			case 12:
				cout << " - unlock door" << endl;
				break;
			case 8:
				cout << " - pump water in";
				if (memory[active]->getFunction(i).T != -1) {
					cout << " with substance from";
					std::bitset<3> args(memory[active]->getFunction(i).T);
					if (args[0])
						cout << " 1";
					if (args[1])
						cout << " 2";
					if (args[2])
						cout << " 3";
				}
				cout << endl;
				break;
			case 9:
				cout << " - pump water out" << endl;
				break;
			case 7:
				cout << " - set temperature to " << +memory[active]->getFunction(i).T << endl;
				break;
			case 6:
				cout << " - rotate drum " << [](const double &x)->string {
					if (x > 0)
						return "right";
					else
						return "left";
				}(memory[active]->getFunction(i).f) << " with frequency " << abs(memory[active]->getFunction(i).f) << endl; //wyra¿enie lambda
				break;
			case 5:
				cout << " - stop drum" << endl;
				break;
			case 10:
				cout << " - wait " << memory[active]->getFunction(i).t << " seconds" << endl;
			}
		}
	}
}
//symuluje dzia³anie wybranego programu prania
void Programowanie::cmd_simulation(const std::vector<std::string> &command) {
	using namespace std;
	if (searchForHelp(command))
		coutFile("help/simulation.txt");
	else if (command.size() < 2)
		std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
	else if (active == -1)
		cout << "Select memory cell using \"active\" command." << endl;
	else if (memory[active] == nullptr)
		cout << "This memory cell is empty. Create a washing program using \"new\" command." << endl;
	else if (memory[active]->getSize() == 0) {
		cout << "Washing program \"" << memory[active]->getName() << "\" is empty." << endl;
	}
	else {
		if (memory[active]->getFinished() == false) {
			cout << "Washing program \"" << memory[active]->getName() << "\" is not finished.";
			if (!askBool(" Do you want to continue ? [y / N]", 0))
				return;
		}
		float arg;
		try {
			arg = std::stof(commaToDotDecimalSeparator(command[1]));
		}
		catch (const std::invalid_argument&) {
			std::cout << "Invalid argument: \"" << command[1] << "\" is not a number. Type \"" << command[0] << " -h\" to get more information." << std::endl;
			return;
		}
		catch (const std::out_of_range&) {
			std::cout << "Argument: \"" << command[1] << "\" is out of range." << std::endl;
			return;
		}
		cout << "Simulating program \"" << memory[active]->getName() << "\" with speed x" << arg << endl;
		char ret = simulation[active]->wykonajCalosc(false, arg);
		if ((ret % 10) == 0)
			cout << "Simulation ended successfully." << endl;
		else {
			cout << "Simulation ended with error (" << ret << ")." << endl;
		}
	}
}
//eksportuje aktywny program do pliku
void Programowanie::cmd_export(const std::vector<std::string> &command) {
	if (searchForHelp(command))
		coutFile("help/export.txt");
	else if (command.size() < 2)
		std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
	else if (active == -1) {
		bool allEmpty = true;
		for (unsigned int i = 0; i < memorySize; i++) {
			if (memory[i] != nullptr) {
				allEmpty = false;
				break;
			}
		}
		if (allEmpty) {
			std::cout << "Memory is empty! Nothing to export." << std::endl;
			return;
		}
		else {
			if (exportMemory(command[1]) < 0)
				std::cout << "An error has occurred while opening file \"" << command[1] << "\"" << std::endl;
			else
				std::cout << "Memory successfuflly saved to file \"" << command[1] << "\"" << std::endl;
		}
	}
	else if (memory[active] == nullptr)
		std::cout << "This memory cell is empty. Create a washing program using \"new\" command." << std::endl;
	else if (memory[active]->getSize() == 0) {
		std::cout << "Washing program \"" << memory[active]->getName() << "\" is empty." << std::endl;
	}
	else {
		if (exportProgram(memory[active], command[1]) == -1)
			std::cout << "An error has occurred while opening file \"" << command[1] << "\"" << std::endl;
		else
			std::cout << "Program \"" << memory[active]->getName() << "\" successfuflly saved to file \"" << command[1] << "\"" << std::endl;
	}
}
//importuje program z pliku do aktywnego slotu pamiêci
void Programowanie::cmd_import(const std::vector<std::string> &command) {
	if (searchForHelp(command))
		coutFile("help/import.txt");
	else if (command.size() < 2)
		std::cout << "Invalid syntax. Type \"" << command[0] << " -h\" to get more information." << std::endl;
	else if (active == -1) {
		bool allEmpty = true;
		for (unsigned int i = 0; i < memorySize; i++) {
			if (memory[i] != nullptr) {
				allEmpty = false;
				break;
			}
		}
		if (!allEmpty) {
			std::cout << "Memory is not empty! Delete existing programs first." << std::endl;
			return;
		}
		else {
			if (importMemory(command[1]) < 0)
				std::cout << "An error has occurred while opening file \"" << command[1] << "\"" << std::endl;
			else {
				for (unsigned int i = 0; i < memorySize; i++) {
					if (memory[i] != nullptr) {
						simulation[i] = new Symulacja(memory[i]);
						simulation[i]->wykonajCalosc();
						memory[i]->setFinished(simulation[i]->zakonczona());
					}
				}
				std::cout << "Memory successfuflly imported from file \"" << command[1] << "\"" << std::endl;
			}
		}
	}
	else if (memory[active] != nullptr)
		std::cout << "This memory cell is not empty. Delete existing program using \"remove\" commamd or select other memory cell." << std::endl;
	else {
		memory[active] = importProgram(command[1]);
		if (memory[active] == nullptr)
			std::cout << "An error has occurred while opening file \"" << command[1] << "\"" << std::endl;
		else {
			simulation[active] = new Symulacja(memory[active]);
			simulation[active]->wykonajCalosc();
			memory[active]->setFinished(simulation[active]->zakonczona());
			std::cout << "Program \"" << memory[active]->getName() << "\" successfuflly imported from file \"" << command[1] << "\"" << std::endl;
		}
	}
}