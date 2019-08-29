#include "Pralka.h"

//konstruktor
Pralka::Pralka() : lck(false), wti(false), wto(true), su1(false), su2(false), su3(false), tmp(0), rot(0.0)/*, brk(false)*/ {}

//metody ustawiaj¹ce sygna³y steruj¹ce komponentami pralki

//ustawia stan blokady drzwi na 'arg'
void Pralka::set_lck(bool arg) {
	lck = arg;
}

//ustawia nalewanie wody do bêbna na 'arg'
void Pralka::set_wti(bool arg) {
	wti = arg;
}

//ustawia wylewanie wody z bêbna na 'arg'
void Pralka::set_wto(bool arg) {
	wto = arg;
}

//ustawia zadan¹ temeraturê wody na 'arg'
void Pralka::set_tmp(char arg) {
	tmp = arg;
}

//ustawia pobieranie substancji z przegródki 1 na 'arg'
void Pralka::set_su1(bool arg) {
	su1 = arg;
}

//ustawia pobieranie substancji z przegródki 2 na 'arg'
void Pralka::set_su2(bool arg) {
	su2 = arg;
}

//ustawia pobieranie substancji z przegródki 3 na 'arg'
void Pralka::set_su3(bool arg) {
	su3 = arg;
}

//ustawia zadan¹ predkosc obrotow na 'arg' [Hz] (ujemne w lewo)
void Pralka::set_rot(double arg) {
	rot = arg;
}

//ustawia stan hamulca bêbna na 'arg'
/*void Pralka::set_brk(bool arg) {
	brk = arg;
}*/


//metody odczytuj¹ce aktualny stan sygna³ów steruj¹cych oraz wskazania czujników

//odczytuje informacje z czujnika opn (czy drzwi s¹ otwarte)
bool Pralka::chk_opn() {
	return 0; //na potrzeby symulacji przyjmujemy ¿e drzwi s¹ zawsze zamkniête
}

//odczytuje stan sygna³u lck (blokada drzwi)
bool Pralka::get_lck() {
	return lck;
}

//odczytuje informacje z czujnika lck (czy aktywna jest blokada drzwi)
/*bool Pralka::chk_lck() {
	return lck; //na potrzeby symulacji przyjmujemy ¿e blokada drzwi zawsze dzia³a poprawnie i bez opóŸnieñ
}*/

//odczytuje stan sygna³u wti (nalewanie wody do bêbna)
bool Pralka::get_wti() {
	return wti;
}

//odczytuje informacje z czujnika wti (w bêbnie jest woda (iloœæ maksymalna))
bool Pralka::chk_wti() {
	return wti; //na potrzeby symulacji przyjmujemy ¿e woda wlewa siê natychmiast (opóŸnienie musia³oby byæ realizowane równolegle)
}

//odczytuje stan sygna³u wto (wylewanie wody z bêbna)
bool Pralka::get_wto() {
	return wto;
}

//odczytuje informacje z czujnika wto (z bêbna wylewa siê woda)
bool Pralka::chk_wto() {
	return false; //na potrzeby symulacji przyjmujemy ¿e woda wylewa siê natychmiast (opóŸnienie musia³oby byæ realizowane równolegle)
}

//odczytuje stan sygna³u tmp (zadana temperatura wody)
char Pralka::get_tmp() {
	return tmp;
}

//odczytuje informacje z czujnika tmp (temperatura wody w bêbnie)
char Pralka::chk_tmp() {
	return tmp; //na potrzeby symulacji przyjmujemy ¿e woda nagrzewa siê natychmiast (opóŸnienie musia³oby byæ realizowane równolegle)
}

//odczytuje stan sygna³u su1 (pobieranie substancji z przegródki 1)
bool Pralka::get_su1() {
	return su1;
}
//odczytuje stan sygna³u su2 (pobieranie substancji z przegródki 2)
bool Pralka::get_su2() {
	return su2;
}
//odczytuje stan sygna³u su3 (pobieranie substancji z przegródki 3)
bool Pralka::get_su3() {
	return su3;
}

//odczytuje stan sygna³u rot (zadana prêdkoœæ obrotów bêbna)
double Pralka::get_rot() {
	return rot;
}

//odczytuje informacje z czujnika rot (aktualna prêdkoœæ obrotów bêbna)
double Pralka::chk_rot() {
	return rot; //na potrzeby symulacji przyjmujemy ¿e bêben nie ma bezw³adnoœci - rozkrêca siê i hamuje natychmiast (opóŸnienie musia³oby byæ realizowane równolegle)
}

//odczytuje stan sygna³u brk (hamulec bêbna)
/*bool Pralka::get_brk() {
	return brk;
}*/

//odczytuje informacje z czujnika brk (czy aktywny jest hamulec bêbna)
/*bool Pralka::chk_brk() {
	return brk; //na potrzeby symulacji przyjmujemy ¿e hamulec zawsze dzia³a poprawnie i bez opóŸnieñ
}*/