#include "Sterowanie.h"

//blokuje drzwi pralki; zwraca kod b³êdu
char Sterowanie::zablokujDrzwi() {
	if (chk_opn())
		return -112; //nie mo¿na zablokowaæ drzwi - drzwi otwarte
	if (get_lck())
		return 111; //drzwi ju¿ zablokowane
	set_lck(true);
	return 110; //pomyœlnie zablokowano drzwi
}

//odblokowuje drzwi pralki; zwraca kod b³êdu
char Sterowanie::odblokujDrzwi() {
	if (!get_lck())
		return 128; //drzwi nie s¹ zablokowane
	if (chk_rot()) {
		if (get_rot())
			return -121; //nie mo¿na odblokowaæ drzwi - bêben siê krêci (zadana prêdkoœæ)
		return -122; //nie mo¿na odblokowaæ drzwi - bêben siê krêci (zadany stop)
	}
	if (chk_wti()) {
		if (get_wti())
			return -123; //nie mo¿na odblokowaæ drzwi - w bêbnie jest woda (w³¹czone nalewanie)
		if (!get_wto())
			return -124; //nie mo¿na odblokowaæ drzwi - w bêbnie jest woda (wy³¹czone nalewanie i wylewanie)
		return -125; //nie mo¿na odblokowaæ drzwi - w bêbnie jest woda (trwa wylewanie - pe³no wody)
	}
	if (chk_wto())
		return -126; //nie mo¿na odblokowaæ drzwi - w bêbnie jest woda (trwa wylewanie)
	if (!get_wto())
		return -127; //nie mo¿na odblokowaæ drzwi - zablokowany odp³yw wody - w bêbnie mo¿e byæ woda
	set_lck(false);
	return 120; //pomyœlnie odblokowano drzwi
}

//wpomowuje czyst¹ wodê do bêbna; zwraca kod b³edu
inline char Sterowanie::wpompujWode() {
	return wpompujWode(false, false, false);
}

//wpompowuje do bêbna wodê wraz z substancjami z substancj¹ z wybranych przegródek; zwraca kod b³êdu
char Sterowanie::wpompujWode(bool substancja1, bool substancja2, bool substancja3) {
	if (!get_lck()) {
		if (chk_opn()) {
			return -82; //nie mo¿na wpompowaæ wody - drzwi s¹ otwarte
		}
		return -83; //nie mo¿na wpompowaæ wody - drzwi nie sa zablokowane
	}
	if (get_wti()) {
		return 81; //nalewanie wody ju¿ trwa
	}
	if (substancja1)
		set_su1(true);
	if (substancja2)
		set_su2(true);
	if (substancja3)
		set_su3(true);
	set_wto(false);
	set_wti(true);
	return 80; //pomyœlnie rozpoczêto nalewanie wody
}

//wypompowuje wodê z bêbna; zwraca kod b³êdu
char Sterowanie::wypompujWode() {
	set_tmp(0);
	set_wti(false);
	set_su1(false);
	set_su2(false);
	set_su3(false);
	if (get_wto() == true)
		return 91; //odp³yw wody jest ju¿ otwarty
	set_wto(true);
	return 90; //pomyœlnie otwarto odp³yw wody
}

//ustawia termostat grza³ki na temperaturê 'T' [°C]; zwraca kod b³êdu
char Sterowanie::termostat(char T) {
	if (!get_lck()) {
		if (chk_opn()) {
			return -72; //nie mo¿na w³¹czyæ grza³ki - drzwi s¹ otwarte
		}
		return -73; //nie mo¿na w³¹czyæ grza³ki - drzwi nie sa zablokowane
	}
	if (get_wto()) {
		return -71; //nie mo¿na w³¹czyæ grza³ki - otwarty jest odp³yw wody
	}
	set_tmp(T);
	return 70; //pomyœlnie ustawiono temperaturê grza³ki
}

//rozkrêca bêbnen do czêstotliwoœci obrotów 'f' [Hz]; zwraca kod b³êdu
char Sterowanie::krecBebnem(double f) {
	if (!get_lck()) {
		if (chk_opn()) {
			return -61; //nie mo¿na krêciæ bêbnem - drzwi s¹ otwarte
		}
		return -62; //nie mo¿na krêciæ bêbnem - drzwi nie sa zablokowane
	}
	set_rot(f);
	return 60; //pomyœlnie ustawiono prêdkoœæ bêbna
}

//zatrzymuje bêben; zwraca kod b³êdu
inline char Sterowanie::zatrzymajBeben() {
	if (get_rot() == 0)
		return 51; //bêben siê nie krêci
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
		return -1; //b³êdne wywo³anie funkcji (0-arg)
	}
}
//wykonuje funkcje o numerze 'id' z argumentem 'arg1' (7 6)
char Sterowanie::funkcja(char id, char arg1) {
	if (id == 7) {
		return termostat(arg1);
	}
	if (id == 6) { //gdyby wybrana zosta³a niew³aœciwa funkcja
		return funkcja(id, (double)arg1);
	}
	return -2;
}
char Sterowanie::funkcja(char id, double arg1) {
	if (id == 6) {
		return krecBebnem(arg1);
	}
	if (id == 7) { //gdyby wybrana zosta³a niew³aœciwa funkcja - prawdopodobnie zbêdne, ale przy poprawnym dzia³aniu nie wystêpuje, wiêc nie zaszkodzi
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
//sprawdza czy aktualny stan jest stanem domyœlnym; zwraca kod b³êdu
char Sterowanie::checkDefault() {
	if (get_lck())
		return 11; //drzwi s¹ zablokowane
	if (get_wti())
		return 8; //woda jest nalewana
	if (!get_wto())
		return 9; //odp³yw wody jest zamkniêty
	if (get_tmp() != 0)
		return 7; //grza³ka nie jest wy³¹czona
	if (get_rot() != 0)
		return 6; //bêben siê krêci
	return 0; //stan domyœlny
}