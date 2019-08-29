#ifndef Pralka_h
#define Pralka_h

//pralka "na poziomie sprz�towym"
class Pralka {
private:
//stan sygna��w steruj�cych komponentami pralki
	bool lck; //blokada drzwi
	bool wti; //nalewanie wody do b�bna
	bool wto; //wylewanie wody z b�bna
	bool su1; //pobieranie substancji z przegr�dki 1
	bool su2; //pobieranie substancji z przegr�dki 2
	bool su3; //pobieranie substancji z przegr�dki 3
	char tmp; //zadana temperatura wody w b�bnie [�C]
	double rot; //zadana predkosc obrotow bebna [Hz] (ujemne w lewo)
	//bool brk; //hamulec b�bna
protected:
//metody ustawiaj�ce sygna�y steruj�ce komponentami pralki
	//ustawia stan blokady drzwi na 'arg'
	void set_lck(bool arg);
	//ustawia nalewanie wody do b�bna na 'arg'
	void set_wti(bool arg);
	//ustawia wylewanie wody z b�bna na 'arg'
	void set_wto(bool arg);
	//ustawia zadan� temeratur� wody na 'arg'
	void set_tmp(char T);
	//ustawia pobieranie substancji z przegr�dki 1 na 'arg'
	void set_su1(bool arg);
	//ustawia pobieranie substancji z przegr�dki 2 na 'arg'
	void set_su2(bool arg);
	//ustawia pobieranie substancji z przegr�dki 3 na 'arg'
	void set_su3(bool arg);
	//ustawia zadan� predkosc obrotow na 'arg' [Hz] (ujemne w lewo)
	void set_rot(double arg);
	//ustawia stan hamulca b�bna na 'arg'
	//void set_brk(bool arg);
public:
//metody odczytuj�ce aktualny stan sygna��w steruj�cych oraz wskazania czujnik�w
	//odczytuje informacje z czujnika opn (czy drzwi s� otwarte)
	bool chk_opn();
	//odczytuje stan sygna�u lck (blokada drzwi)
	bool get_lck();
	//odczytuje informacje z czujnika lck (czy aktywna jest blokada drzwi)
	//bool chk_lck();
	//odczytuje stan sygna�u wti (nalewanie wody do b�bna)
	bool get_wti();
	//odczytuje informacje z czujnika wti (w b�bnie jest woda (ilo�� maksymalna))
	bool chk_wti();
	//odczytuje stan sygna�u wto (wylewanie wody z b�bna)
	bool get_wto();
	//odczytuje informacje z czujnika wto (z b�bna wylewa si� woda)
	bool chk_wto();
	//odczytuje stan sygna�u tmp (zadana temperatura wody)
	char get_tmp();
	//odczytuje informacje z czujnika tmp (temperatura wody w b�bnie)
	char chk_tmp();
	//odczytuje stan sygna�u su1 (pobieranie substancji z przegr�dki 1)
	bool get_su1();
	//odczytuje stan sygna�u su2 (pobieranie substancji z przegr�dki 2)
	bool get_su2();
	//odczytuje stan sygna�u su3 (pobieranie substancji z przegr�dki 3)
	bool get_su3();
	//odczytuje stan sygna�u rot (zadana pr�dko�� obrot�w b�bna)
	double get_rot();
	//odczytuje informacje z czujnika rot (aktualna pr�dko�� obrot�w b�bna)
	double chk_rot();
	//odczytuje stan sygna�u brk (hamulec b�bna)
	//bool get_brk();
	//odczytuje informacje z czujnika brk (czy aktywny jest hamulec b�bna)
	//bool chk_brk();

	//konstruktor domy�lny
	Pralka();
};

#endif