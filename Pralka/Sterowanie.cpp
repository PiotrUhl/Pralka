#include "Sterowanie.h"

//blokuje drzwi pralki; zwraca kod b��du
char Sterowanie::zablokujDrzwi() {
	if (chk_opn())
		return -112; //nie mo�na zablokowa� drzwi - drzwi otwarte
	if (get_lck())
		return 111; //drzwi ju� zablokowane
	set_lck(true);
	return 110; //pomy�lnie zablokowano drzwi
}

//odblokowuje drzwi pralki; zwraca kod b��du
char Sterowanie::odblokujDrzwi() {
	if (!get_lck())
		return 128; //drzwi nie s� zablokowane
	if (chk_rot()) {
		if (get_rot())
			return -121; //nie mo�na odblokowa� drzwi - b�ben si� kr�ci (zadana pr�dko��)
		return -122; //nie mo�na odblokowa� drzwi - b�ben si� kr�ci (zadany stop)
	}
	if (chk_wti()) {
		if (get_wti())
			return -123; //nie mo�na odblokowa� drzwi - w b�bnie jest woda (w��czone nalewanie)
		if (!get_wto())
			return -124; //nie mo�na odblokowa� drzwi - w b�bnie jest woda (wy��czone nalewanie i wylewanie)
		return -125; //nie mo�na odblokowa� drzwi - w b�bnie jest woda (trwa wylewanie - pe�no wody)
	}
	if (chk_wto())
		return -126; //nie mo�na odblokowa� drzwi - w b�bnie jest woda (trwa wylewanie)
	if (!get_wto())
		return -127; //nie mo�na odblokowa� drzwi - zablokowany odp�yw wody - w b�bnie mo�e by� woda
	set_lck(false);
	return 120; //pomy�lnie odblokowano drzwi
}

//wpomowuje czyst� wod� do b�bna; zwraca kod b�edu
inline char Sterowanie::wpompujWode() {
	return wpompujWode(false, false, false);
}

//wpompowuje do b�bna wod� wraz z substancjami z substancj� z wybranych przegr�dek; zwraca kod b��du
char Sterowanie::wpompujWode(bool substancja1, bool substancja2, bool substancja3) {
	if (!get_lck()) {
		if (chk_opn()) {
			return -82; //nie mo�na wpompowa� wody - drzwi s� otwarte
		}
		return -83; //nie mo�na wpompowa� wody - drzwi nie sa zablokowane
	}
	if (get_wti()) {
		return 81; //nalewanie wody ju� trwa
	}
	if (substancja1)
		set_su1(true);
	if (substancja2)
		set_su2(true);
	if (substancja3)
		set_su3(true);
	set_wto(false);
	set_wti(true);
	return 80; //pomy�lnie rozpocz�to nalewanie wody
}

//wypompowuje wod� z b�bna; zwraca kod b��du
char Sterowanie::wypompujWode() {
	set_tmp(0);
	set_wti(false);
	set_su1(false);
	set_su2(false);
	set_su3(false);
	if (get_wto() == true)
		return 91; //odp�yw wody jest ju� otwarty
	set_wto(true);
	return 90; //pomy�lnie otwarto odp�yw wody
}

//ustawia termostat grza�ki na temperatur� 'T' [�C]; zwraca kod b��du
char Sterowanie::termostat(char T) {
	if (!get_lck()) {
		if (chk_opn()) {
			return -72; //nie mo�na w��czy� grza�ki - drzwi s� otwarte
		}
		return -73; //nie mo�na w��czy� grza�ki - drzwi nie sa zablokowane
	}
	if (get_wto()) {
		return -71; //nie mo�na w��czy� grza�ki - otwarty jest odp�yw wody
	}
	set_tmp(T);
	return 70; //pomy�lnie ustawiono temperatur� grza�ki
}

//rozkr�ca b�bnen do cz�stotliwo�ci obrot�w 'f' [Hz]; zwraca kod b��du
char Sterowanie::krecBebnem(double f) {
	if (!get_lck()) {
		if (chk_opn()) {
			return -61; //nie mo�na kr�ci� b�bnem - drzwi s� otwarte
		}
		return -62; //nie mo�na kr�ci� b�bnem - drzwi nie sa zablokowane
	}
	set_rot(f);
	return 60; //pomy�lnie ustawiono pr�dko�� b�bna
}

//zatrzymuje b�ben; zwraca kod b��du
inline char Sterowanie::zatrzymajBeben() {
	if (get_rot() == 0)
		return 51; //b�ben si� nie kr�ci
	krecBebnem(0);
	return 50;
}

//czeka przez czas 't' [s]
void Sterowanie::czekaj(unsigned short t) {
	Sleep(t);
}

//wykonuje funkcje o numerze 'id' (11, 12, 8, 9, 5)
char Sterowanie::funkcja(char id) {
	switch (id) {
	case 11:
		return zablokujDrzwi();
	case 12:
		return odblokujDrzwi();
	case 8:
		return wpompujWode();
	case 9:
		return wypompujWode();
	case 5:
		return zatrzymajBeben();
	default:
		return -1; //b��dne wywo�anie funkcji (0-arg)
	}
}
//wykonuje funkcje o numerze 'id' z argumentem 'arg1' (7 6)
char Sterowanie::funkcja(char id, char arg1) {
	if (id == 7) {
		return termostat(arg1);
	}
	if (id == 6) { //gdyby wybrana zosta�a niew�a�ciwa funkcja
		return funkcja(id, (double)arg1);
	}
	return -2;
}
char Sterowanie::funkcja(char id, double arg1) {
	if (id == 6) {
		return krecBebnem(arg1);
	}
	if (id == 7) { //gdyby wybrana zosta�a niew�a�ciwa funkcja - prawdopodobnie zb�dne, ale przy poprawnym dzia�aniu nie wyst�puje, wi�c nie zaszkodzi
		return funkcja(id, (char)arg1);
	}
	return -3;
}
//wykonuje funkcje o numerze 'id' z argumentem 'arg1', 'arg2', 'arg3' (8)
char Sterowanie::funkcja(char id, bool arg1, bool arg2, bool arg3) {
	if (id == 8) {
		return wpompujWode(arg1, arg2, arg3);
	}
	return -5;
}
//sprawdza czy aktualny stan jest stanem domy�lnym; zwraca kod b��du
char Sterowanie::checkDefault() {
	if (get_lck())
		return 11; //drzwi s� zablokowane
	if (get_wti())
		return 8; //woda jest nalewana
	if (!get_wto())
		return 9; //odp�yw wody jest zamkni�ty
	if (get_tmp() != 0)
		return 7; //grza�ka nie jest wy��czona
	if (get_rot() != 0)
		return 6; //b�ben si� kr�ci
	return 0; //stan domy�lny
}