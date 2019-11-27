#ifndef LIBFILES_H
#define LIBFILES_H

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;
namespace MyRuntimeExceptions {
	class FileOpenException : public runtime_error {
	public:
		FileOpenException(string msg) : runtime_error(msg.c_str()) {}
	};
	class CreateTabelException : public runtime_error {
	public:
		CreateTabelException(string msg) : runtime_error(msg.c_str()) {}
	};
}
namespace funkcje_Rafal {
	//
	class CTablica {
	public:
		int l_porownan = 0, l_przestawien=0;
		// funkcja sortuje tablice -> tab[ile] metoda babelkowa za pomoca wariantu wahadlowego i zlicza liczbe porownan i przestawien
		void f_sort_babelkowe(int *tab, int ile, int &l_porownan, int &l_przestawien);
		// funkcja sortuje tablice -> tab metoda Qiucksort za pomoca algorytmu podzialu Hoare'a i zlicza liczbe porownan i przestawien 
		void f_sort_szybkie_Hoarea(int *tab, int p, int q, int &l_porownan, int &l_przestawien);
		// funkcja sortuje tablice -> tab metoda Qiucksort za pomoca algorytmu podzialu Lumoto i zlicza liczbe porownan i przestawien 
		void f_sort_szybkie_Lomuto(int *tab, int p, int q, int &l_porownan, int &l_przestawien);
		// funkcja metoda sortowania przez kopcowanie sortuje tablice -> tab  i zlicza liczbe porownan i przestawien   ile->rozmiar tablicy
		void f_sort_przez_kopcowanie(int *tab, int ile, int &l_porownan, int &l_przestawien);
		// funkcja pomocnicza do sortowania przez kopcowanie
		// segreguje kopiec (jako tablice tab[ile]) w celu znalezienia watosci jego korzenia (maksymalnego elementu)
		void f_max_ele_kopca(int *tab, int ile, int parentIndex, int &l_porownan, int &l_przestawien);
	};
	//
	class CSortTablica {
	public:
		// funkcja zwraca tablice liczb wprowadzonych przez uzytkownika   ile->rozmiar tablicy
		int *f_wprowadzenie_danych(int ile);
		// funkcja za pomoca LINIOWEJ METODY KONGRUENCYJNEJ zwraca tablice losowych liczb z zakresu <1, ile) o rozmiarze tablicy [ile] 
		int *f_liczby_pseudolosowe_LMK(int ile);
		// funkcja pelni role menu na podstawie ktorego uzytkownik dopiera metody i rodzaje danych do sortowania
		void f_wybor_metody_sortowania_i_rodzaju_danych();
		// funkcja zapisuje do pliku tabele wynikow metod sortujacych i wnioski porownujac liczbe porownan i przestawien
		void f_zapis_rozwiazania(int rozmiar, int rodzaj, int metoda, int l_porownan, int l_przestawien, ofstream &plik);
	};
	// otwiera plik o podanej nazwie
	void f_otworz_plik(ifstream &plik, string nazwa);
	// tworzy plik o podanej nazwie na dysku
	void f_utworz_plik(ofstream &plik, string nazwa);
	// tworzy tablice o zadanej liczbie elementow
	int *f_utworz_tablice_1(int rozmiar);
	// funkcja tworzy tablice dwuwymiarowa o w wierszach i k kolumnach
	int **f_utworz_tablice_2(int w, int k);
}

#endif
#pragma once
