#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

using namespace std;

struct SPracownik {
	string imie;
	string nazwisko;
	int liczba_projektow;
};

struct SFirma {
	string nazwa_firmy;
	int liczba_pracownikow;
	SPracownik* pracownik;

	static bool wczytaj(ifstream& fin, SFirma& firma);
	static bool zapisz(ofstream& fout, const SFirma& firma);
	static bool zapisz(ofstream& fout, const SFirma& firma, bool wyswietl);
	static double obliczSredniaProjektow(const SFirma& firma);
	static void wyswietl(const SFirma& firma, ofstream& fout, bool wyswietl = true);
	static void wyswietl(const SFirma& firma, bool wyswietl = true);
	static bool porownajLiczbeProjektow(const SPracownik&, const SPracownik&);
	static void sortuj(const SFirma& firma, bool (*porownaj)(const SPracownik&, const SPracownik&));
};


bool SFirma::wczytaj(ifstream& fin, SFirma& firma) {
	if (!fin) {
		cerr << "Blad otwarcia pliku!" << endl;
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}

	fin >> firma.nazwa_firmy;
	if (!fin.good()) {
		cerr << "Blad strumienia: nazwa";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	fin >> firma.liczba_pracownikow;
	if (!fin.good()) {
		cerr << "Blad strumienia: liczbaPracownikow";
		fin.ignore();
		fin.clear();
		fin.close();
		return false;
	}
	if (firma.liczba_pracownikow > 0) {
		firma.pracownik = new SPracownik[firma.liczba_pracownikow];
		for (int i = 0; i < firma.liczba_pracownikow; ++i) {

			fin >> firma.pracownik[i].imie;
			if (!fin.good()) {
				cerr << "Blad strumienia: pracownicy[i].imie;\n";
				delete[] firma.pracownik; // Dodane czyszczenie pamięci
				fin.ignore();
				fin.clear();
				fin.close();
				return false;
			}
			fin >> firma.pracownik[i].nazwisko;
			if (!fin.good()) {
				cerr << "Blad strumienia: pracownicy[i].nazwisko;\n";
				delete[] firma.pracownik; //czyszczenie pamięci jesli zły plik wej.
				fin.ignore();
				fin.clear();
				fin.close();
				return false;
			}
			fin >> firma.pracownik[i].liczba_projektow;
			if (!fin.good() && !fin.eof()) {
				cerr << "Blad strumienia: pracownicy[i].liczbaProjektow;\n";
				delete[] firma.pracownik; // czyszczenie pamięci jesli zły plik wej.
				fin.ignore();
				fin.clear();
				fin.close();
				return false;
			}
			
		}
	}
	return true;
}

bool SFirma::zapisz(ofstream& fout, const SFirma& firma) {
	if (!fout.good()) {
		cerr << "Błąd strumienia pliku przy zapisywaniu danych." << endl;
		fout.clear();
		fout.close();
		return false;
	}
	SFirma::wyswietl(firma, fout, true);
	fout << firma.nazwa_firmy << endl;
	if (!fout.good()) {
		cerr << "Błąd strumienia pliku przy zapisywaniu danych." << endl;
		fout.clear();
		fout.close();
		return false;
	}
	fout << " - srednia liczba projektow: " << obliczSredniaProjektow(firma) << endl;
	if (!fout.good()) {
		cerr << "Błąd strumienia pliku przy zapisywaniu danych." << endl;
		fout.clear();
		fout.close();
		return false;
	}

	return true;
}

bool SFirma::zapisz(ofstream& fout, const SFirma& firma, bool wyswietl) {
	if (!fout.good()) {
		cerr << "Błąd strumienia pliku przy zapisywaniu danych." << endl;
		return false;
	}

	fout << firma.nazwa_firmy << endl;
	if (!fout.good()) {
		cerr << "Błąd strumienia pliku przy zapisywaniu danych." << endl;
		fout.clear();
		fout.close();
		return false;
	}

	fout << " - srednia liczba projektow: " << obliczSredniaProjektow(firma);
	if (!fout.good()) {
		cerr << "Błąd strumienia pliku przy zapisywaniu danych." << endl;
		fout.clear();
		fout.close();
		return false;
	}

	if (!fout.good()) {
		cerr << "Błąd strumienia pliku po zapisaniu danych." << endl;
		fout.clear();
		fout.close();
		return false;
	}

	if (wyswietl) {
		cout << firma.nazwa_firmy << " - srednia liczba projektow: " << obliczSredniaProjektow(firma) << endl;
	}

	return true;
}


double SFirma::obliczSredniaProjektow(const SFirma& firma) {
	double ilosc = 0;
	double suma = 0;
	for (int i = 0; i < firma.liczba_pracownikow; i++)
	{
		suma += firma.pracownik[i].liczba_projektow;
	}
	ilosc = suma / firma.liczba_pracownikow;
	return ilosc;
}


void SFirma::wyswietl(const SFirma& firma, ofstream& fout, bool wyswietl) {
	if (!fout) {
		cerr << "Blad otwarcie pliku wyjczewego" << endl;
		fout.clear();
		fout.close();

	}
	fout << "Nazwa firmy: " << firma.nazwa_firmy << endl;
	if (!fout.good()) {
		cerr << "Blad strumenia nazwa firmy" << endl;
		fout.clear();
		fout.close();

	}
	fout << "Liczba pracownikow: " << firma.liczba_pracownikow << endl;
	if (!fout.good()) {
		cerr << "Blad strumenia liczba pracownikow" << endl;
		fout.clear();
		fout.close();

	}
	SFirma::sortuj(firma, porownajLiczbeProjektow);
	for (int i = 0; i < firma.liczba_pracownikow; i++)
	{
		fout << firma.pracownik[i].imie << " " << firma.pracownik[i].nazwisko << " " << firma.pracownik[i].liczba_projektow << endl;
		if (!fout.good()) {
			cerr << "Blad strumenia" << endl;
			fout.clear();
			fout.close();

		}
	}
	if (wyswietl) {
		cout << "Informacje o firmie zostaly zapisane do pliku." << endl;

	}
}


void SFirma::wyswietl(const SFirma& firma, bool wyswietl) {
	cout << "Nazwa firmy: " << firma.nazwa_firmy << endl;
	cout << "Ilos osob w firmie: " << firma.liczba_pracownikow<<endl;
	SFirma::sortuj(firma, porownajLiczbeProjektow);
	for (int i = 0; i < firma.liczba_pracownikow; i++)
	{
		cout << firma.pracownik[i].imie << " " << firma.pracownik[i].nazwisko << " " << firma.pracownik[i].liczba_projektow << endl;
	}
	cout << "Srednia Projektow" << obliczSredniaProjektow(firma) << endl;
	if (wyswietl) {
		cout << "Informacje o firmie zostaly zapisane do pliku." << endl;
	}
}

bool SFirma::porownajLiczbeProjektow(const SPracownik& pracownik1, const SPracownik& pracowwnik2) {
	return pracownik1.liczba_projektow < pracowwnik2.liczba_projektow;

}


void SFirma::sortuj(const SFirma& firma, bool (*porownaj)(const SPracownik&, const SPracownik&)) {
	SPracownik temp;
	for (int i = 0; i < firma.liczba_pracownikow - 1; i++) {
		for (int j = 0; j < firma.liczba_pracownikow - i - 1; j++) {
			if (porownaj(firma.pracownik[j], firma.pracownik[j + 1])) {
				temp = firma.pracownik[j];
				firma.pracownik[j] = firma.pracownik[j + 1];
				firma.pracownik[j + 1] = temp;
			}
		}
	}

}

bool wczytaj(const string& fin, SFirma*& firmy, int& liczbaFirm) {
	ifstream fini;
	fini.open(fin);
	if (!fini) {
		cerr << "Blad pliku wyjce" << endl;
		fini.ignore();
		fini.clear();
		fini.close();
		return false;
	}
	fini >> liczbaFirm;
	firmy = new SFirma[liczbaFirm];
	for (int i = 0; i < liczbaFirm; i++) {
		if (!SFirma::wczytaj(fini, firmy[i])) {
			return false;
		}

	}


	fini.close();
	return true;

}

bool zapisz(const string& fout, SFirma* firmy, int liczbaFirm) {
	ofstream fouti(fout);
	if (!fouti.is_open()) {
		return false;
	}
	

	for (int i = 0; i < liczbaFirm; i++) {
		SFirma::zapisz(fouti, firmy[i]);
	}
	

	fouti.close();
	return true;
}

void usun(SFirma* firmy, int liczbaFirm) {
	for (int i = 0; i < liczbaFirm; i++) {
		delete[] firmy[i].pracownik;
	}
	delete[] firmy;
}



int main(int argc, char** argv) {
	if (argc != 3) {
		cerr << "Nie prawidlowa liczba argumentow" << endl;
		return 100;
	}
	string plik_wyj = argv[1];
	string plik_wej = argv[2];
	SFirma* firma;
	int liczbaFirm;
	if (wczytaj(plik_wyj, firma, liczbaFirm)) {
		for (int i = 0; i < liczbaFirm; i++) {
			firma[i].sortuj(firma[i], SFirma::porownajLiczbeProjektow);
			SFirma::wyswietl(firma[i], true);
		}
		zapisz(plik_wej, firma, liczbaFirm);
		usun(firma, liczbaFirm);
	}
	else {
		cout << "Blad wczytywania danych." << endl;
	}

	return 0;
}
