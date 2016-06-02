#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int a = 0;

struct wezel
{
	char litera;
	int prawdpodobienstwo;
	wezel *rodzic;
	wezel *l_potomek;
	wezel *p_potomek;
};


int **utworzenie_macierzy(int rozmiar1, int rozmiar2)//tworzy tablice dwuwymiarowa
{
	int **tab = nullptr;
	try
	{
		tab = new int*[rozmiar1];
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na utworzenie tablicy";
		cin.ignore();
		getchar();
		exit(0);
	}
	for (int i = 0;i < rozmiar1;i++)
		try
	{
		tab[i] = new int[rozmiar2];
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na utworzenie tablicy";
		cin.ignore();
		getchar();
		exit(0);
	}
	return tab;
}
int *utworzenie_tablicy(int rozmiar)//tworzy tablice
{
	try
	{
		int *tab = new int[rozmiar];
		return tab;
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na utworzenie tablicy";
		cin.ignore();
		getchar();
		exit(0);
	}
}

wezel *utworzenie_tablicy_wezlow(int rozmiar)//tworzy tablice
{
	try
	{
		wezel *tab = new wezel[rozmiar];
		return tab;
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na utworzenie tablicy";
		cin.ignore();
		getchar();
		exit(0);
	}
}

void wypisz_macierz(int **tab, int rozmiar1, int rozmiar2)
{
	for (int i = 1;i < rozmiar1 + 1;i++)
		for (int y = 1;y < rozmiar2 + 1;y++)
		{
			cout << setw(4) << tab[i][y] << " ";
			if (y == rozmiar2)
				cout << endl << endl;
		}
}

int pobierz_ilosc_liter(fstream &plik)//pobiera pojemnosc i ilosc potrzebne do zadeklarowania tablic z pobierz_dane2
{
	plik.seekg(0);
	string a;
	int i = 0;
	while (!plik.eof())
	{
		getline(plik, a);
		i++;
	}
	return i;
}

void pobierz_dane(fstream &plik, wezel *symbol, int rozmiar)//pobiera dane zadania
{
	plik.seekg(0);
	for (int i = 0;i < rozmiar;i++)
	{
		plik >> symbol[i].litera;
		plik >> symbol[i].prawdpodobienstwo;
		// cout << symbol[i].litera<<endl;
		// cout << symbol[i].prawdpodobienstwo<<endl<<endl;
	}
}

void zerowanie_macierzy(int **tab, int rozmiar1, int rozmiar2)
{
	for (int i = 0;i < rozmiar1; i++)
		for (int j = 0;j < rozmiar2;j++)
			tab[i][j] = 0;
}

void usuwanie_macierzy(int **tab, int rozmiar) {
	for (int i = 0; i < rozmiar; ++i)
		delete[] tab[i];
	delete[] tab;
}

char *wczytanie_nazwy_pliku(int max_dlugosc_nazwy)//pobiera nazwe pliku tekstowego
{
	char *nazwa_pliku = new char[max_dlugosc_nazwy + 1];
	cout << "Podaj nazwe pliku" << endl;
	cin >> nazwa_pliku;
	nazwa_pliku[max_dlugosc_nazwy] = '\0';
	return nazwa_pliku;
}

void otworzenie_pliku(fstream &plik)//otwiera plik tekstowy
{
	char *nazwa;
	for (int i = 0; i < 3;i++)
	{
		//nazwa = wczytanie_nazwy_pliku(20);
		nazwa = "tekst3.txt";
		if (!nazwa)
		{
			continue;
		}
		plik.open(nazwa, fstream::in);
		if (plik.is_open())
		{
			cout << "Plik zostal pomyslnie otwarty" << endl;
			return;
		}
		else
			cout << "Plik nie zostal otwarty pomyslnie" << endl;
	}
	exit(0);

}
void sortowanie_wezlow(wezel *symbol, int rozmiar)
{
	wezel temp;
	int i = 0;
	while (i < rozmiar - 1)
	{
		if (i<0)
			i = 0;
		cout << i << endl;
		if (symbol[i].prawdpodobienstwo > symbol[i + 1].prawdpodobienstwo)
		{
			temp = symbol[i];
			symbol[i] = symbol[i + 1];
			symbol[i + 1] = temp;
			i--;
		}
		else
			i++;
	}

}

void wypisz(wezel *symbol, int n)
{
	for (int i = 0;i < n;i++)
	{
		cout << symbol[i].litera << "   " << symbol[i].prawdpodobienstwo << endl;
	}
}

wezel *scalanie(wezel *symbol, int *n)
{
	wezel * nowy;
	nowy = (wezel*)malloc(sizeof * nowy);
	nowy->prawdpodobienstwo = 0;
	wezel *tab = utworzenie_tablicy_wezlow(*n - 1);
	for (int i = 1;i < *n;i++)
		tab[i + 1] = symbol[i];
	nowy->prawdpodobienstwo = symbol[0].prawdpodobienstwo + symbol[1].prawdpodobienstwo;
	nowy->l_potomek = &symbol[0];
	nowy->p_potomek = &symbol[1];
	tab = nowy;
	for (int i = 1;i < *n;i++)
		tab[i] = symbol[i + 1];
	*n = *n - 1;
	return tab;
}

void hoffman(wezel *symbol, int n)
{
	int i = n;
	while (i > 1)
	{
		//sortowanie_wezlow(symbol, i);
		scalanie(symbol, &n);
		wypisz(symbol, n);
		i--;
	}
}


int main()
{
	fstream plik;
	otworzenie_pliku(plik);
	int n = pobierz_ilosc_liter(plik);

	wezel *tab = utworzenie_tablicy_wezlow(n);
	pobierz_dane(plik, tab, n);

	//cout << " sortowanie " << endl;

	//sortowanie_wezlow(tab, n);

	//tab = scalanie(tab, &n);

	wypisz(tab, n);

	cout << "hofman?" << endl;
	hoffman(tab, n);

	//wypisz(tab, n);
	plik.close();
	system("pause");
}