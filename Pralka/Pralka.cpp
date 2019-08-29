#include "Pralka.h"

//konstruktor
Pralka::Pralka() : lck(false), wti(false), wto(true), su1(false), su2(false), su3(false), tmp(0), rot(0.0)/*, brk(false)*/ {}

//metody ustawiaj�ce sygna�y steruj�ce komponentami pralki

//ustawia stan blokady drzwi na 'arg'
void Pralka::set_lck(bool arg) {
	lck = arg;
}

//ustawia nalewanie wody do b�bna na 'arg'
void Pralka::set_wti(bool arg) {
	wti = arg;
}

//ustawia wylewanie wody z b�bna na 'arg'
void Pralka::set_wto(bool arg) {
	wto = arg;
}

//ustawia zadan� temeratur� wody na 'arg'
void Pralka::set_tmp(char arg) {
	tmp = arg;
}

//ustawia pobieranie substancji z przegr�dki 1 na 'arg'
void Pralka::set_su1(bool arg) {
	su1 = arg;
}

//ustawia pobieranie substancji z przegr�dki 2 na 'arg'
void Pralka::set_su2(bool arg) {
	su2 = arg;
}

//ustawia pobieranie substancji z przegr�dki 3 na 'arg'
void Pralka::set_su3(bool arg) {
	su3 = arg;
}

//ustawia zadan� predkosc obrotow na 'arg' [Hz] (ujemne w lewo)
void Pralka::set_rot(double arg) {
	rot = arg;
}

//ustawia stan hamulca b�bna na 'arg'
/*void Pralka::set_brk(bool arg) {
	brk = arg;
}*/


//metody odczytuj�ce aktualny stan sygna��w steruj�cych oraz wskazania czujnik�w

//odczytuje informacje z czujnika opn (czy drzwi s� otwarte)
bool Pralka::chk_opn() {
	return 0; //na potrzeby symulacji przyjmujemy �e drzwi s� zawsze zamkni�te
}

//odczytuje stan sygna�u lck (blokada drzwi)
bool Pralka::get_lck() {
	return lck;
}

//odczytuje informacje z czujnika lck (czy aktywna jest blokada drzwi)
/*bool Pralka::chk_lck() {
	return lck; //na potrzeby symulacji przyjmujemy �e blokada drzwi zawsze dzia�a poprawnie i bez op�nie�
}*/

//odczytuje stan sygna�u wti (nalewanie wody do b�bna)
bool Pralka::get_wti() {
	return wti;
}

//odczytuje informacje z czujnika wti (w b�bnie jest woda (ilo�� maksymalna))
bool Pralka::chk_wti() {
	return wti; //na potrzeby symulacji przyjmujemy �e woda wlewa si� natychmiast (op�nienie musia�oby by� realizowane r�wnolegle)
}

//odczytuje stan sygna�u wto (wylewanie wody z b�bna)
bool Pralka::get_wto() {
	return wto;
}

//odczytuje informacje z czujnika wto (z b�bna wylewa si� woda)
bool Pralka::chk_wto() {
	return false; //na potrzeby symulacji przyjmujemy �e woda wylewa si� natychmiast (op�nienie musia�oby by� realizowane r�wnolegle)
}

//odczytuje stan sygna�u tmp (zadana temperatura wody)
char Pralka::get_tmp() {
	return tmp;
}

//odczytuje informacje z czujnika tmp (temperatura wody w b�bnie)
char Pralka::chk_tmp() {
	return tmp; //na potrzeby symulacji przyjmujemy �e woda nagrzewa si� natychmiast (op�nienie musia�oby by� realizowane r�wnolegle)
}

//odczytuje stan sygna�u su1 (pobieranie substancji z przegr�dki 1)
bool Pralka::get_su1() {
	return su1;
}
//odczytuje stan sygna�u su2 (pobieranie substancji z przegr�dki 2)
bool Pralka::get_su2() {
	return su2;
}
//odczytuje stan sygna�u su3 (pobieranie substancji z przegr�dki 3)
bool Pralka::get_su3() {
	return su3;
}

//odczytuje stan sygna�u rot (zadana pr�dko�� obrot�w b�bna)
double Pralka::get_rot() {
	return rot;
}

//odczytuje informacje z czujnika rot (aktualna pr�dko�� obrot�w b�bna)
double Pralka::chk_rot() {
	return rot; //na potrzeby symulacji przyjmujemy �e b�ben nie ma bezw�adno�ci - rozkr�ca si� i hamuje natychmiast (op�nienie musia�oby by� realizowane r�wnolegle)
}

//odczytuje stan sygna�u brk (hamulec b�bna)
/*bool Pralka::get_brk() {
	return brk;
}*/

//odczytuje informacje z czujnika brk (czy aktywny jest hamulec b�bna)
/*bool Pralka::chk_brk() {
	return brk; //na potrzeby symulacji przyjmujemy �e hamulec zawsze dzia�a poprawnie i bez op�nie�
}*/