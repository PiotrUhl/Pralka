#include "Program.h"

//konstruktor
Program::Program() {}
Program::Program(const std::string &_name) : name(_name) {}
Program::Program(const Program &_program) {
	name = _program.name;
	program = _program.program;
	finished = _program.finished;
}

//zwraca nazw� programu
std::string Program::getName() {
	return name;
}

//ustawia nazwe programu na 'newName'
void Program::setName(const std::string &newName) {
	name = newName;
}

//dodaje do programu po punkcie numer 'nr' (dla nr == -1 dodaje na ko�cu) punkt o id 'id' [z argumentem 'arg1']
void Program::addFunction(int nr, int id) {
	function nowa;
	nowa.id = id;
	//dodawanie
	if (nr == -1) {
		program.push_back(nowa);
	}
	else if (nr <= getSize() && nr >= 0)
		program.insert(program.begin() + nr, nowa);
}
void Program::addFunction(int nr, int id, char arg1) {
	function nowa;
	nowa.id = id;
	nowa.T = arg1;
	//dodawanie
	if (nr == -1)
		program.push_back(nowa);
	else if (nr <= getSize() && nr >= 0)
		program.insert(program.begin() + nr, nowa);
}
void Program::addFunction(int nr, int id, double arg1) {
	function nowa;
	nowa.id = id;
	nowa.f = arg1;
	//dodawanie
	if (nr == -1)
		program.push_back(nowa);
	else if (nr <= getSize() && nr >= 0)
		program.insert(program.begin() + nr, nowa);
}

void Program::addFunction(int nr, int id, unsigned short arg1) {
	function nowa;
	nowa.id = id;
	nowa.t = arg1;
	//dodawanie
	if (nr == -1)
		program.push_back(nowa);
	else if (nr <= getSize() && nr >= 0)
		program.insert(program.begin() + nr, nowa);
}

//dodaje do programu po punkcie numer 'nr' (dla nr == -1 dodaje na ko�cu) punkt o x
void Program::addFunction(int nr, function nowa) {
	if (nr == -1)
		program.push_back(nowa);
	else if (nr <= getSize() && nr >= 0)
		program.insert(program.begin() + nr, nowa);
}

//usuwa z programu funkcj� spod numeru 'nr' (dla nr == -1 usuwa ostatni�) 
void Program::delFunction(int nr) {
	if (nr == -1)
		program.pop_back();
	else if (nr >= 0 && nr <= getSize())
		program.erase(program.begin() + nr);
}

//zwraca funkcj� programu spod numeru 'nr'
function Program::getFunction(int nr) {
	return program[nr];
}

//zwraca ilo�� funkcji w programie
int Program::getSize() {
	return program.size();
}

//zwraca warto�� pola finished
bool Program::getFinished() {
	return finished;
}
//ustawia warto�� pola finished na 'var'
bool Program::setFinished(bool var) {
	finished = var;
	return var;
}