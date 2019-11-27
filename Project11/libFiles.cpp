#include "libFiles.h"

namespace funkcje_Rafal {

// Funkcje kalsy CsortTablica:

	// funkcja sortuje tablice -> tab[ile] metoda babelkowa za pomoca wariantu wahadlowego i zlicza liczbe porownan i przestawien
	void CTablica::f_sort_babelkowe(int *tab, int ile, int &l_porownan, int &l_przestawien)
	{
		// a,b->zmienne pomocnicze okreslajace dlugosc wykonania sie petli;  bufor->zmienna pomocnicza przy zamianie wartosci
		int a = 0, b = ile - 1, bufor;
		// petla wykona sie polowie ilosci danych w tablicy (poniewaz w jednym przejsciu elementy zostana porownane w przod i w tyl)
		for (int i = 0; i < (ile / 2); i++)
		{
			// porownanie elementow tablicy poruszajac sie do przodu
			for (int j = a; j < b; j++)
			{
				if (tab[j] > tab[j + 1])
				{
					// zamiana elementow
					bufor = tab[j];
					tab[j] = tab[j + 1];
					tab[j + 1] = bufor;
					// zliczenie ilosci przestawien 
					l_przestawien++;
				}
				// zliczenie ilosci porownan
				l_porownan++;;
			}
			// dzieki temu ostatno badany element tablicy (od konca)nie bedzie juz porownywany
			b--;
			// porownanie elementow tablicy poruszajac sie do tylu
			for (int j = b; j > a; j--)
			{
				if (tab[j] < tab[j - 1])
				{
					bufor = tab[j];
					tab[j] = tab[j - 1];
					tab[j - 1] = bufor;
					l_przestawien++;
				}
				l_porownan++;
			}
			// dzieki temu ostatno badany element tablicy (od poczatku) nie bedzie juz porownywany
			a++;
		}
	}
	// funkcja sortuje tablice -> tab metoda Qiucksort za pomoca algorytmu podzialu Hoare'a i zlicza liczbe porownan i przestawien 
	void CTablica::f_sort_szybkie_Hoarea(int *tab, int p, int q, int &l_porownan, int &l_przestawien)
	{
		// x->zmienna pomocnicza przy wyborze przy osi oraz zamianie wartosci piwot->oœ (poczatkowy element porownawczy)
		int x = (p + q) / 2;
		// piwot->oœ (poczatkowy element porownawczy)  p,q->zmienne pomocnicze wskazujace na odpowiedni element tablicy (wskazniki)
		int piwot = tab[x], i = p, j = q;
		while (i <= j)
		{
			// szukamy elemntu mniejszego od pivota i zliczamy liczbe elemntow do jego napotkania
			while (tab[i] < piwot) {
				i++;
				l_porownan++;
			}
			// szukamy elemntu wiekszego od pivota i zliczamy liczbe elemntow do jego napotkania
			while (tab[j] > piwot) {
				j--;
				l_porownan++;
			}
			// jezeli zmienne i oraz j nie wskazywa³y tych samych elementow w pewnym momencie to zostanie dokonana zamiana
			if (i <= j)
			{
				x = tab[i];
				tab[i] = tab[j];
				tab[j] = x;
				i++; j--;
				l_przestawien++;
			}
			l_porownan++;
		}
		// jezeli wskaznik a nie dotarl do konca tablicy to zostanie wywolana funkcja od poczatku do jego aktualnej wartosci 
		if (j > p)
			CTablica::f_sort_szybkie_Hoarea(tab, p, j, l_porownan, l_przestawien);
		// jezeli wskaznik a nie dotarl do poczatku tablicy to zostanie wywolana funkcja od jego aktualnej wartosci do konca
		if (i < q)
			CTablica::f_sort_szybkie_Hoarea(tab, i, q, l_porownan, l_przestawien);
	}
	// funkcja sortuje tablice -> tab metoda Qiucksort za pomoca algorytmu podzialu Lumoto i zlicza liczbe porownan i przestawien 
	void CTablica::f_sort_szybkie_Lomuto(int *tab, int p, int q, int &l_porownan, int &l_przestawien)
	{
		// bufor->zmienna pomocnicza przy zamianie wartosci  p,q->zmienne pomocnicze wskazujace na odpowiedni element tablicy (wskazniki)
		int i = p - 1, bufor;
		// piwot->oœ (poczatkowy element porownawczy)
		int pivot = tab[q];
		// pettla wykonuje sie od poczatku obszaru sortowania do konca
		for (int j = p; j < q; j++)
		{
			// jezeli element porownawczy jest mniejszy od aktualnie badanego to zostana zamienione
			if (tab[j] < pivot)
			{
				bufor = tab[i];
				tab[i] = tab[j];
				tab[j] = bufor;
				i++;
				l_przestawien++;
			}
			l_porownan++;
		}
		// jezeli nie wykonala sie zadna zamiana w petli u gory to ostatni z perwszym element obszaru do sortowania sie zamienia
		if (i < p)
		{
			bufor = tab[p];
			tab[p] = tab[q];
			tab[q] = bufor;
			i++;
			l_przestawien++;
		}
		l_porownan++;
		// funkcja sortuje obszar od badanego elementu w dul
		if (p < i) f_sort_szybkie_Lomuto(tab, p, i, l_porownan, l_przestawien);
		// funkcja sortuje obszar od badanego elementu w gore
		if (q > i + 2) f_sort_szybkie_Lomuto(tab, i + 1, q, l_porownan, l_przestawien);
	}
	// funkcja metoda sortowania przez kopcowanie sortuje tablice -> tab  i zlicza liczbe porownan i przestawien   ile->rozmiar tablicy
	void CTablica::f_sort_przez_kopcowanie(int *tab, int ile, int &l_porownan, int &l_przestawien)
	{
		// bufor->zmienna pomocnicza przy zamianie wartosci
		int bufor;
		// petla ustawia wartosc korzenie przy pomocy funkcji szukajacej max elementu kopca (petla zaczyna sie od ostatniego rodzica=ile/2 -1)
		for (int i = ile / 2 - 1; i >= 0; i--)
			CTablica::f_max_ele_kopca(tab, ile, i, l_porownan, l_przestawien);
		// w petli zamieniane jest maksymalny elementy kopca z ostatnim jego wyrazem
		for (int i = ile - 1; i > 0; i--)
		{
			bufor = tab[0];
			tab[0] = tab[i]; 
			tab[i] = bufor;
			--ile; l_przestawien++;
			// nastepnie znowu wykonywana jet procedura segragacji kopca i znalezienie jego maksymalnego elementu
			CTablica::f_max_ele_kopca(tab, ile, 0, l_porownan, l_przestawien);
		}
	}
	// funkcja pomocnicza do sortowania przez kopcowanie
	// segreguje kopiec (jako tablice tab[ile]) w celu znalezienia watosci jego korzenia (maksymalnego elementu)
	void CTablica::f_max_ele_kopca(int *tab, int ile, int parentIndex, int &l_porownan, int &l_przestawien) 
	{
		// bufor->zmienna pomocnicza przy zamianie wartosci
		int bufor;
		// wprowadzenie zmiennych oznaczajacych elementy kopca i przypisanie im indeksow tablicy
		int maxIndex = parentIndex;
		int leftChild = parentIndex * 2 + 1;
		int rightChild = parentIndex * 2 + 2;
		// jezeli lewy potomek jest wiekszy od rodzica to nastapi ich zamiana
		if (leftChild < ile && tab[leftChild] > tab[maxIndex])
		{
			maxIndex = leftChild; l_porownan++;
		}
		// jezeli prawy potomek jest wiekszy od rodzica to nastapi ich zamiana
		if (rightChild < ile && tab[rightChild] > tab[maxIndex])
		{
			maxIndex = rightChild; l_porownan++;
		}
		// jezeli ktorys z potomkow byl inny od rodzica to na podstawie zmiennych indeksowych elementy kopca zostana zamienione
		if (maxIndex != parentIndex) 
		{
			l_porownan++; l_przestawien++;
			bufor = tab[maxIndex];
			tab[maxIndex] = tab[parentIndex];
			tab[parentIndex] =bufor;
			// rekursja dzieki ktorej otrzymamy maksymalny element kopca
			CTablica::f_max_ele_kopca(tab, ile, maxIndex, l_porownan, l_przestawien);
		}
	}

//#####################################################################################################################################
// Funkcje kalsy CsortTablica:

	// funkcja zwraca tablice liczb wprowadzonych przez uzytkownika   ile->rozmiar tablicy
	int *CSortTablica::f_wprowadzenie_danych(int ile)
	{
		int *T = nullptr;
		T = f_utworz_tablice_1(ile);
		for (int i = 0; i < ile; i++)
		{
			cout << "\nPodaj " << i + 1 << " liczbe: ";
			cin >> T[i];
		}
		return T;
	}
	// funkcja za pomoca LINIOWEJ METODY KONGRUENCYJNEJ zwraca tablice losowych liczb z zakresu <0, ile) o rozmiarze tablicy [ile] 
	int *CSortTablica::f_liczby_pseudolosowe_LMK(int ile)
	{
		// x->wygenerowana liczba   Xo->wartosc poczzatkowa (ziarno);   
		// a->mnoznik  m->modul;  c->przyrost; 
		int x, m = ile + 1, a = 0, c = 0, *t = nullptr, Xo = 6;
		t = f_utworz_tablice_1(ile);
		// wyliczenie c (przyrostu) ktory jest wzglednie peirwszy z m   i->zmienna pomocnicza
		int i = m;
		do {
			c++;
			int j;
			while (c)
			{
				j = c;
				c = i % c;
				i = j;
			}
		} while (i != 1);
		// wyliczenie a (mnoznika) za pomoca zaleznosci  (a^y) mod m=1
		// p=a^y     t2->tablica dwuwymiarowa: 1 kolumna->mnozniki a;  2 kolumna->lambda y  
		// max_y->najwieksza wartosc lambdy (y);  max_a->maksymalne a dla ktorego lambda=max_y 
		int **t2 = nullptr, max_y = 0;
		t2 = f_utworz_tablice_2((ile - 1), 2);
		for (long long int i = 0; i < ile - 1; i++)
		{
			// y->lambda
			long long int y = 1, p;
			do
			{
				p = pow(i + 2, y);
				if (p < 0)
					p = (-1)*p;
				if ((p % m) == 1)
				{
					t2[i][0] = i;
					t2[i][1] = y;
					if (y > max_y)
						max_y = y;
				}
				y++;
			} while (((p % m) != 1) && (y<20));
		}
		for (int i = 0; i < ile - 2; i++)
		{
			if (t2[i][1] == max_y)
			{
				if ((m % 4 == 0) && (((i + 2) - 1) % 4 == 0))
				{
					a = i + 2; break;
				}
				else if (i + 2 > a)
					a = i + 2;
			}
		}
		// wylosowanie licb i przypisanie rozwiazania
		for (int i = 0; i < ile; i++)
		{
			if (i == 0)
				t[i] = (a*Xo + c) % m;
			else
				t[i] = (a*t[i - 1] + c) % m;
		}
		return t;
	}
	// funkcja pelni role menu na podstawie ktorego uzytkownik dopiera metody i rodzaje danych do sortowania
	void CSortTablica::f_wybor_metody_sortowania_i_rodzaju_danych()
	{
		ofstream plik;
		f_utworz_plik(plik, "out.txt");
		// tab->tablica liczb do sortowania;  ile->rozmiar tablicy;  i->zmienna pomocnicza (ile razy wykonuje sie glowna petla do while)
		int *tab=nullptr, ile, i = 0;
		// utworzenie obiektow klas
		CTablica sortowanie;
		CSortTablica obiekt;
		// odp->zmienna wskazjujaca na to czy uzytkownik chce kontynuowac program
		char odp;
		// zmienne wyboru w menu na podstawie ktorych okreslany jest sposob sortowania
		int rozmiar, rodzaj, metoda;
		do {
			sortowanie.l_porownan = 0; sortowanie.l_przestawien = 0;
			// ok->zmienna pomocnicza, przyjmuje wartosc FALSE jezeli uzytkownik zle wprowadzil dane
			bool ok;
			cout << "Program porownuje dzialania 4 algorytmow sortujacych:\n"
				<< "i przedstawia ich wyniki w tabeli.\n";
			cout << "\n\nSortowanie nr: " << i+1;
			// w petli dokonywany jest wybor rozmiaru tablicy do sortowania
			do {
				ok = true;
				cout << "\n\n#Podaj dlugosc tablicy liczb do sortowania:\n1. 100\n2. 1000\n3. 1000000"
					<< "\nPodaj numer odpowiadajacy dlugosci (1/2/3): ";
				cin >> rozmiar;
				switch (rozmiar)
				{
				case 1: ile =100; tab = f_utworz_tablice_1(ile); break; 
				case 2: ile=1000; tab = f_utworz_tablice_1(ile); break;
				case 3: ile=100000000; tab = f_utworz_tablice_1(ile); break;
				default: cout << "\nZly numer! Podaj jeszcze raz."; ok = false; break;
				}
			}while (ok != true);
			// w petli dokonywany jest wybor rodzaju ulozonie liczb w tablicy do sortowania
			do {
				ok = true;
				cout << "\n#Podaj jak maja wygladac liczby w tablicy:\n1. losowe\n2. uporzadkowane\n3. odwrotnie uporzadkowane"
					<< "\n4. prawie posortowane (10% elementow na zlych miejscach)\nPodaj numer odpowiadajacy rodzajowi liczb (1/2/3/4): ";
				cin >> rodzaj;
				switch (rodzaj)
				{
				// liczby losowe (metoda LMK lub wprowadzane recznie)
				case 1: {
					cout << " *Jezeli chcesz wprowadzic liczby recznie nacisnit 'T' lub 't'. Innaczej zostana one wylosowane. Wybor: ";
					cin >> odp;
					if ((odp == 't') || (odp == 'T'))
						tab = obiekt.f_wprowadzenie_danych(ile);
					else
						tab = obiekt.f_liczby_pseudolosowe_LMK(ile);
					//for (int i = 0; i < ile; i++)
						//cout << endl << i << ". " << tab[i]; 
					break; }
				// liczby posortowane
				case 2: {
					tab = obiekt.f_liczby_pseudolosowe_LMK(ile);
					list<int> sort_tab;
					for (int i = 0; i < ile; i++)
						sort_tab.push_front(tab[i]); 
					sort_tab.sort();
					for (int i = 0; i < ile; i++)
					{
						tab[i] = *sort_tab.begin();
						sort_tab.pop_front();
					}
					//for (int i = 0; i < ile; i++)
						//cout << endl << i << ". " << tab[i];
					break; }
				// liczby odwrotnie posortowane
				case 3: {
					tab = obiekt.f_liczby_pseudolosowe_LMK(ile);
					list<int> sort_tab;
					for (int i = 0; i < ile; i++)
						sort_tab.push_front(tab[i]);
					sort_tab.sort();
					sort_tab.reverse();
					for (int i = 0; i < ile; i++)
					{
						tab[i] = *sort_tab.begin();
						sort_tab.pop_front();
					}
					//for (int i = 0; i < ile; i++)
						//cout << endl << i << ". " << tab[i];
					break; }
				// liczb prawie posortowane (10% elementow na zlych miejscach)
				case 4: {
					tab = obiekt.f_liczby_pseudolosowe_LMK(ile);
					list<int> sort_tab;
					for (int i = 0; i < ile; i++)
						sort_tab.push_front(tab[i]);
					sort_tab.sort();
					for (int i = 0; i < ile; i++)
					{
						tab[i] = *sort_tab.begin();
						sort_tab.pop_front();
						if ((((i + 1) % 20) == 0) && (i != 0))
						{
							int x = tab[i];
							tab[i] = tab[i - 10];
							tab[i - 10] = x;
						}
					}
					//for (int i = 0; i < ile; i++)
						//cout << endl << i+1 << ". " << tab[i];
					break; }
				default: cout << "\nZly numer! Podaj jeszcze raz."; ok = false; break;
				}
			// w petli dokonywany jest wybor metody sortowania
			} while (ok != true);
			do {
				ok = true;
				cout << "\n#Podaj metode sortowania:\n1.Sortowanie babelkowe\n2.Sortowanie szybkie z algorytmem podzialu Hore'a\n"
					<<"3.Sortowanie szybkie z algorytmem podzialu Lomuto\n4.Sortowanie prze kopcowanie\nPodaj numer metody (1/2/3/4): ";
				cin >> metoda;
				switch (metoda)
				{
				case 1: sortowanie.f_sort_babelkowe(tab, ile, sortowanie.l_porownan, sortowanie.l_przestawien); break;
				case 2: sortowanie.f_sort_szybkie_Hoarea(tab, 0, ile-1, sortowanie.l_porownan, sortowanie.l_przestawien); break;
				case 3: sortowanie.f_sort_szybkie_Lomuto(tab, 0, ile - 1, sortowanie.l_porownan, sortowanie.l_przestawien); break;
				case 4: sortowanie.f_sort_przez_kopcowanie(tab, ile, sortowanie.l_porownan, sortowanie.l_przestawien); break;
				default: cout << "\nZly numer! Podaj jeszcze raz."; ok = false; break;
				}
			} while (ok != true);
			// zapis rozwiazania w formie tabeli do pliku
			if(i==0)
				plik << "Nazwa metody sortowania \t|Dlugosc tablicy|Rodzaj uporzadkowania tablicy|Liczba porownan|Liczba przestawien";
			obiekt.f_zapis_rozwiazania(rozmiar, rodzaj, metoda, sortowanie.l_porownan, sortowanie.l_przestawien, plik);
			i++;
			cout << "\n\nCzy chcesz przejsc do kolejnego sortowania? [T/N]: ";
			cin >> odp;
			if ((odp == 'n') || (odp == 'N'))
				break;
			system("cls");
		} while (i != 32);
		plik << "\n\nWNIOSKI:\n"
			<< "1.Sortowanie babelkowe metoda wahadlowa: jest zdcydowanie najwolniejsza metoda sortowania\n"
			<< "  z posrod wykorzystanych (gdyz ogolnie jest prawie dwa razy szybsza od podstawowej poniewaz\n"
			<< "  sprawdza elementy w dwie strony), glownie dlatego ze porownujeze soba wszystkie elementy\n"
			<< "  tablicy totez ma najwieksza liczbe porownan i przestawien (wyjatek tablica uszeregowana,\n"
			<< "  gdzie nieprzestawia zadnej wartosci)\n"
			<< "2.Sortowanie szybkie za pomoca algorytmu podzialu Hoare'a: jest zdecydowanie najszybsza\n"
			<< "  metod sortowaniawykorzystuje metode dziel i zwyciezej dzieki czemu robi najmniej porownan,\n"
			<< "  a co za tym idzie ma najmniejsza liczbe przestawien\n"
			<< "3.Sortowanie szybkie za pomoca algorytmu podzialu Lomuto : rownie szybka metoda co poprzednia\n"
			<< "  opierajaca sie na  tej samej zasadzie,lecz w przeciwienstwie do algorytmu Hore'a wykonuje\n"
			<< "  znacznie wieksza liczbe porownan gdyz do podzielenie jednego segmentu funkcja porownuje elementy\n"
			<< "  w jednym kierunku podczas gdy 'wskazniki' w drugiej metodzie przesuwaja sie od krawedzi do\n"
			<< "  srodka, skutkuje to rowniez wieksza iloscia przestawien\n"
			<< "4.Sortowanie przez kopcowanie: metoda srednio efektywna, obiektywnie wykonuje nie duzo liczbe\n"
			<< "  porownan w stosunku do metody BubbleSort i QiuckSort Lomuto lecz w porownaniu z ta druga ma\n"
			<< "  wieksza liczbe przestawien, wynika to z faktu iz w metodzie kpocowania przy jednym przejsciu kopca\n"
			<< "  znajdujemy jeden element najwiekszy, natomiast QuickSort z kazdym krokiem zmniejsza tablice so\n"
			<< "  sortowania nawet o polowe, przez co tak duza liczba porownan jak wystepuje w metodzie Lomuto nie\n"
			<< "  skutkuje znacznymwzrostem liczby porownan jak ma miejsce chcoiazby w metodzie babelkowej\n";
		plik.close();
		delete[] tab;
	}
	// funkcja zapisuje do pliku tabele wynikow metod sortujacych i wnioski porownujac liczbe porownan i przestawien
	void CSortTablica::f_zapis_rozwiazania(int rozmiar, int rodzaj, int metoda, int l_porownan, int l_przestawien, ofstream &plik)
	{
		plik<< "\n--------------------------------------------|-----------------------|----------------------------------------------|-------------------------|-------------------------------\n";
		switch (metoda){
		case 1: plik<<  "sortowanie babelkowe  \t|"; break;
		case 2: plik<<  "sortowanie szybkie Hore'a      |"; break;
		case 3: plik << "sortowanie szybkie Lomuto     |"; break;
		case 4: plik << "sortowanie przez kopcowanie|"; break;
		}
		switch (rozmiar) {
		case 1: plik << "          100           |"; break;
		case 2: plik << "         1000          |"; break;
		case 3: plik << "       1000000     |"; break;
		}
		switch (rodzaj) {
		case 1: plik << " liczby losowe                              |"; break;
		case 2: plik << " liczby uporzadkowane               |"; break;
		case 3: plik << " l. odwrotnie uporzadkowane    |"; break;
		case 4: plik << " l. czesciwo uporzadkowane     |"; break;
		}
		plik << l_porownan << "                     |" << l_przestawien;
	}

//#################################################################################################################################
// Podstawowe funkcje wraz z obsluga bledow:

	// otwiera plik o podanej nazwie z dysku
	void f_otworz_plik(ifstream &plik, string nazwa)
	{
		try {
			plik.open(nazwa.c_str());
			if (!plik.good())
				throw MyRuntimeExceptions::FileOpenException("Nie mozna otworzyc pliku wejsciowego");
		}
		catch (std::exception &e) {
			cerr << e.what();
		}
	}
	// tworzy plik o podanej nazwie na dysku
	void f_utworz_plik(ofstream &plik, string nazwa)
	{
		try {
			plik.open(nazwa.c_str());
			if (!plik.good())
				throw MyRuntimeExceptions::FileOpenException("Nie mozna utworzyc pliku wyjsciowego");
		}
		catch (std::exception &e) {
			cerr << e.what();
		}
	}
	// tworzy tablice o zadanej liczbie elementow
	int *f_utworz_tablice_1(int rozmiar)
	{
		int *T = NULL;
		try {
			T = new int[rozmiar];
			if (!T)
				throw MyRuntimeExceptions::CreateTabelException("Brak miejsca na utworzenie tablicy");
		}
		catch (std::exception &e) {
			cerr << e.what();
		}
		return T;
	}
	// funkcja tworzy tablice dwuwymiarowa o w wierszach i k kolumnach
	int **f_utworz_tablice_2(int w, int k)
	{
		int **T = NULL;
		try {
			T = new int*[w];
			if (!T)
				throw MyRuntimeExceptions::CreateTabelException("Brak miejsca na utworzenie tablicy");
		}
		catch (std::exception &e) {
			cerr << e.what();
		}
		for (int i = 0; i < w; i++)
		{
			try
			{
				T[i] = new int[k];
				if (!T[i])
					throw MyRuntimeExceptions::CreateTabelException("Brak miejsca na utworzenie tablicy");
			}
			catch (std::exception &e) {
				cerr << e.what();
			}
		}
		return T;
	}
}