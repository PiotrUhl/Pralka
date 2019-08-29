#ifndef DLList_h
#define DLList_h

#include <iostream>
#include <functional>
#include <string>

template <typename T>
class DLList {

	//struktura wêz³a
	template <typename T>
	struct Node {
		T data; //dane przechowywane w liœcie
		Node* next; //wskaŸnik na nastêpny wêze³ listy
		Node* prev; //wskaŸnik na poprzedni wêze³ listy
		Node() : next(nullptr), prev(nullptr) {} //konstruktor
	};

	//wskaŸniki na listê
	Node<T>* first; //pierwszy wêze³ listy
	Node<T>* last; //ostatni wêze³ listy

	//rozmiar listy
	int size;

	//wypisywanie listy
	std::function<void(T)> printT; //funkcja wypisuj¹ca dane

	//w razie gdy funkcja wypisuj¹ca jest niezadeklarowana wypisuje b³¹d i zwraca true
	bool printDefinedError() {
		if (!printT) {
			std::cerr << "Undefined prining function for your data: use \'definePrint()\' method!";
			return true;
		}
		return false;
	}

public:
	//konstruktor
	DLList() : first(nullptr), last(nullptr), size(0), printT(nullptr) {}
	//destruktor
	~DLList() {
		delAll();
	}

	//definiue funkcjê u¿ywan¹ do wypisywania danych
	void definePrint(std::function<void(T)> printF) {
		printT = printF;
	}

	//dodaje wêze³ na pocz¹tek listy
	void addFirst(T newData) {
		Node<T>* newNode = new Node<T>;
		newNode->data = newData;
		if (first == nullptr)
			first = last = newNode;
		else {
			newNode->next = first;
			first->prev = newNode;
			first = newNode;
		}
		size++;
	}
	//dodaje wêze³ na koniec listy
	void addLast(T newData) {
		Node<T>* newNode = new Node<T>;
		newNode->data = newData;
		if (last == nullptr)
			last = first = newNode;
		else {
			newNode->prev = last;
			last->next = newNode;
			last = newNode;
		}
		size++;
	}

	//usuwa pierwszy wêze³ listy
	void delFirst() {
		if (first == nullptr) //je¿eli lista pusta
			return;
		if (first->next == nullptr) { //je¿eli to jedyny element listy
			delete first;
			first = last = nullptr;
		}
		else { //je¿eli conajmniej dwa elementy listy
			Node<T>* tmp = first->next;
			delete first;
			first = tmp;
			first->prev = nullptr;
		}
		size--;
	}
	//usuwa ostatni wêze³ listy
	void delLast() {
		if (last == nullptr) //je¿eli lista pusta
			return;
		if (last->prev == nullptr) { //je¿eli to jedyny element listy
			delete last;
			first = last = nullptr;
		}
		else { //je¿eli conajmniej dwa elementy listy
			Node<T>* tmp = last->prev;
			delete last;
			last = tmp;
			last->next = nullptr;
		}
		size--;
	}
	//usuwa ca³¹ listê
	void delAll() {
		while (first != nullptr)
			delFirst();
	}

	//zwraca rozmiar listy
	int getSize() {
		return size;
	}

	//wypisuje pierwszy element listy
	void printFirst(std::function<void(T)> printF) {
		printF(first->data);
	}
	//wypisuje pierwszy element listy
	void printFirst() {
		if (printDefinedError())
			return;
		printT(first->data);
	}
	//wypisuje ostatni element listy
	void printLast(std::function<void(T)> printF) {
		printF(last->data);
	}
	//wypisuje ostatni element listy
	void printLast() {
		if (printDefinedError())
			return;
		printT(last->data);
	}
	//wypisuje ca³¹ listê z 'separator' miêdzy elementami
	void printAll(std::function<void(T)> printF, std::string separator = "") {
		Node<T>* current = first;
		while (current != last) {
			printF(current->data);
			std::cout << separator;
			current = current->next;
		}
		if (current != nullptr)
			printF(current->data);
	}
	//wypisuje ca³¹ listê z 'separator' miêdzy elementami
	void printAll(std::string separator = "") {
		if (printDefinedError())
			return;
		Node<T>* current = first;
		while (current != last) {
			printT(current->data);
			std::cout << separator;
			current = current->next;
		}
		if (current != nullptr)
			printT(current->data);
	}

	//konwertuje ca³¹ listê na tablicê, zwraca wskaŸnik na tablicê
	T* toTable() {
		T* tab = new T[size];
		Node<T>* current = first;
		for (int i = 0; current != nullptr; i++) {
			tab[i] = current->data;
			current = current->next;
		}
		return tab;
	}
	//konwertuje ca³¹ listê na tablicê pocz¹wszy od elementu ostatniego, zwraca wskaŸnik na tablicê
	T* toTableR() {
		T* tab = new T[size];
		Node<T>* current = last;
		for (int i = 0; current != nullptr; i++) {
			tab[i] = current->data;
			current = current->prev;
		}
		return tab;
	}
};

#endif