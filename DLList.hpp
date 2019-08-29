#ifndef DLList_h
#define DLList_h

#include <iostream>
#include <functional>
#include <string>

template <typename T>
class DLList {

	//struktura w�z�a
	template <typename T>
	struct Node {
		T data; //dane przechowywane w li�cie
		Node* next; //wska�nik na nast�pny w�ze� listy
		Node* prev; //wska�nik na poprzedni w�ze� listy
		Node() : next(nullptr), prev(nullptr) {} //konstruktor
	};

	//wska�niki na list�
	Node<T>* first; //pierwszy w�ze� listy
	Node<T>* last; //ostatni w�ze� listy

	//rozmiar listy
	int size;

	//wypisywanie listy
	std::function<void(T)> printT; //funkcja wypisuj�ca dane

	//w razie gdy funkcja wypisuj�ca jest niezadeklarowana wypisuje b��d i zwraca true
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

	//definiue funkcj� u�ywan� do wypisywania danych
	void definePrint(std::function<void(T)> printF) {
		printT = printF;
	}

	//dodaje w�ze� na pocz�tek listy
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
	//dodaje w�ze� na koniec listy
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

	//usuwa pierwszy w�ze� listy
	void delFirst() {
		if (first == nullptr) //je�eli lista pusta
			return;
		if (first->next == nullptr) { //je�eli to jedyny element listy
			delete first;
			first = last = nullptr;
		}
		else { //je�eli conajmniej dwa elementy listy
			Node<T>* tmp = first->next;
			delete first;
			first = tmp;
			first->prev = nullptr;
		}
		size--;
	}
	//usuwa ostatni w�ze� listy
	void delLast() {
		if (last == nullptr) //je�eli lista pusta
			return;
		if (last->prev == nullptr) { //je�eli to jedyny element listy
			delete last;
			first = last = nullptr;
		}
		else { //je�eli conajmniej dwa elementy listy
			Node<T>* tmp = last->prev;
			delete last;
			last = tmp;
			last->next = nullptr;
		}
		size--;
	}
	//usuwa ca�� list�
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
	//wypisuje ca�� list� z 'separator' mi�dzy elementami
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
	//wypisuje ca�� list� z 'separator' mi�dzy elementami
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

	//konwertuje ca�� list� na tablic�, zwraca wska�nik na tablic�
	T* toTable() {
		T* tab = new T[size];
		Node<T>* current = first;
		for (int i = 0; current != nullptr; i++) {
			tab[i] = current->data;
			current = current->next;
		}
		return tab;
	}
	//konwertuje ca�� list� na tablic� pocz�wszy od elementu ostatniego, zwraca wska�nik na tablic�
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