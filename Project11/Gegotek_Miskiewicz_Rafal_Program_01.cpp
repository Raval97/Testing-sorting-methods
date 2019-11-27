//zadanie 12
#include "libFiles.h"
using namespace std;
using namespace funkcje_Rafal;


int main()
{
	// utworzenie obiektu klasy
	CSortTablica sortowanie;
	// wywolanie funkcji pozwalajacej poruszanie sie po programie i tworzenie rozwiazania na podstawie algorytmow sortujacych
	sortowanie.f_wybor_metody_sortowania_i_rodzaju_danych(); 

	getchar();
	cin.ignore();
	return 0;
}
