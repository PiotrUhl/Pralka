#ifndef Pralka_h
#define Pralka_h

//pralka "na poziomie sprzêtowym"
class Pralka {
private:
//stan sygna³ów steruj¹cych komponentami pralki
	bool lck; //blokada drzwi
	bool wti; //nalewanie wody do bêbna
	bool wto; //wylewanie wody z bêbna
	bool su1; //pobieranie substancji z przegródki 1
	bool su2; //pobieranie substancji z przegródki 2
	bool su3; //pobieranie substancji z przegródki 3
	char tmp; //zadana temperatura wody w bêbnie [°C]
	double rot; //zadana predkosc obrotow bebna [Hz] (ujemne w lewo)
	//bool brk; //hamulec bêbna
protected:
//metody ustawiaj¹ce sygna³y steruj¹ce komponentami pralki
	//ustawia stan blokady drzwi na 'arg'
	void set_lck(bool arg);
	//ustawia nalewanie wody do bêbna na 'arg'
	void set_wti(bool arg);
	//ustawia wylewanie wody z bêbna na 'arg'
	void set_wto(bool arg);
	//ustawia zadan¹ temeraturê wody na 'arg'
	void set_tmp(char T);
	//ustawia pobieranie substancji z przegródki 1 na 'arg'
	void set_su1(bool arg);
	//ustawia pobieranie substancji z przegródki 2 na 'arg'
	void set_su2(bool arg);
	//ustawia pobieranie substancji z przegródki 3 na 'arg'
	void set_su3(bool arg);
	//ustawia zadan¹ predkosc obrotow na 'arg' [Hz] (ujemne w lewo)
	void set_rot(double arg);
	//ustawia stan hamulca bêbna na 'arg'
	//void set_brk(bool arg);
public:
//metody odczytuj¹ce aktualny stan sygna³ów steruj¹cych oraz wskazania czujników
	//odczytuje informacje z czujnika opn (czy drzwi s¹ otwarte)
	bool chk_opn();
	//odczytuje stan sygna³u lck (blokada drzwi)
	bool get_lck();
	//odczytuje informacje z czujnika lck (czy aktywna jest blokada drzwi)
	//bool chk_lck();
	//odczytuje stan sygna³u wti (nalewanie wody do bêbna)
	bool get_wti();
	//odczytuje informacje z czujnika wti (w bêbnie jest woda (iloœæ maksymalna))
	bool chk_wti();
	//odczytuje stan sygna³u wto (wylewanie wody z bêbna)
	bool get_wto();
	//odczytuje informacje z czujnika wto (z bêbna wylewa siê woda)
	bool chk_wto();
	//odczytuje stan sygna³u tmp (zadana temperatura wody)
	char get_tmp();
	//odczytuje informacje z czujnika tmp (temperatura wody w bêbnie)
	char chk_tmp();
	//odczytuje stan sygna³u su1 (pobieranie substancji z przegródki 1)
	bool get_su1();
	//odczytuje stan sygna³u su2 (pobieranie substancji z przegródki 2)
	bool get_su2();
	//odczytuje stan sygna³u su3 (pobieranie substancji z przegródki 3)
	bool get_su3();
	//odczytuje stan sygna³u rot (zadana prêdkoœæ obrotów bêbna)
	double get_rot();
	//odczytuje informacje z czujnika rot (aktualna prêdkoœæ obrotów bêbna)
	double chk_rot();
	//odczytuje stan sygna³u brk (hamulec bêbna)
	//bool get_brk();
	//odczytuje informacje z czujnika brk (czy aktywny jest hamulec bêbna)
	//bool chk_brk();

	//konstruktor domyœlny
	Pralka();
};

#endif