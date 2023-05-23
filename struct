#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Transakcje {
    double kwota;
    string opis;
};

struct SKonto {
    string numer_konta;
    double saldo;
    unsigned int liczba_transakcji;
    Transakcje* transakcje;

    SKonto() : numer_konta(""), saldo(1000000), liczba_transakcji(0), transakcje(nullptr) {
        //cout << "Konstruktor SKonto()\n";
    }
    
    void skopiuj(const SKonto& konto) {
        if (this != &konto) {
            numer_konta = konto.numer_konta;
            saldo = konto.saldo;
            liczba_transakcji = konto.liczba_transakcji;
            delete [] transakcje;
            transakcje = new Transakcje[liczba_transakcji];
            for (unsigned i = 0; i < liczba_transakcji; ++i) {
                transakcje[i] = konto.transakcje[i];
            }
        }
    }

    ~SKonto() {
            if (transakcje) {
                delete[] transakcje;
                transakcje = nullptr;
            }
            //cout << "Destruktor SKonto()\n";
        }

    bool wczytaj_konto(istream& fin = cin);
    bool wyswietl_konto(bool pokaz_transakcje);
    bool dodaj_transakcje(double kwota, const string& opis);
};

struct SKlient {
    string imie;
    string nazwisko;
    SKonto* konto;

    SKlient() : imie(""), nazwisko(""), konto(nullptr) {
        //cout << "Konstruktor SKlient()\n";
    }

    void skopiuj(const SKlient& klient) {
        //cout << "Operator=\n";
        if(this != &klient) {
            imie = klient.imie;
            nazwisko = klient.nazwisko;
            delete konto;
            if (!klient.konto) {
                konto = nullptr;
            } else {
                konto = new SKonto();
                konto->skopiuj(*klient.konto);
            }
        }
    }

    ~SKlient() {
            if (konto) {
                delete konto;
                konto = nullptr;
            }
            //cout << "Destruktor SKlient()\n";
        }

    bool wczytaj_dane_klienta(istream& fin = cin);
    bool wypisz_klienta(ostream& out = cout);
    bool wplata(double kwota);
    bool wyplata(double kwota);
};

 struct SBank {
    string nazwa_banku;
    unsigned int liczba_klientow;
    SKlient* klient;

    SBank() : nazwa_banku(""), liczba_klientow(0), klient(nullptr) {
        //cout << "Konstruktor SBank()\n";
    }

    ~SBank() {
            if (klient) {
                delete[] klient;
                klient = nullptr;
            }
            //cout << "Destruktor SBank()\n";
        }

    bool wczytaj_bank(istream& fin = cin);
    bool wyswietl_bank(ostream& out = cout);
    bool dodaj_konto(const string& nazwa_wlasciciela);
    bool losuj_nr_konta(string& wygenerowany_numer);
    bool usun_konto(const string& numer_konta);
    SKonto* znajdz_konto(const string& numer_konta);
};

void sortuj_transakcje(SKlient* klient, unsigned int liczba_klientow, bool (*porownaj)(const SKlient&, const SKlient&));
bool porownaj(const SKlient& a, const SKlient& b);

bool SKonto::wczytaj_konto(istream& fin) {
    if (!fin) {
        cerr << "Błąd: nie można odczytać strumienia wejściowego." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    if (!(fin >> numer_konta)) {
        cerr << "Błąd: nie można wczytać numeru konta." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    if (!(fin >> saldo)) {
        cerr << "Błąd: nie można wczytać salda." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    if (!(fin >> liczba_transakcji)) {
        cerr << "Błąd: nie można wczytać liczby transakcji." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    transakcje = new Transakcje[liczba_transakcji];

    for (unsigned int i = 0; i < liczba_transakcji; ++i) {
            if (!(fin >> transakcje[i].kwota)) {
                cerr << "Błąd: nie można wczytać kwoty transakcji." << endl;
                fin.ignore();
                fin.clear();
                delete[] transakcje;
                transakcje = nullptr;
                return false;
            }
            fin.ignore();
            //Zjada reszte linii z kwota
            fin.get();
            getline(fin, transakcje[i].opis);
            cout << transakcje[i].opis << endl;
        }

        return true;
    }

bool SKonto::wyswietl_konto(bool pokaz_transakcje) {
    cout << "Numer konta: " << numer_konta << endl;
    cout << "Saldo: " << saldo << endl;
    if (pokaz_transakcje) {
        cout << "Liczba transakcji: " << liczba_transakcji << endl;
        for (unsigned int i = 0; i < liczba_transakcji; ++i) {
            cout << "Transakcja " << i+1 << ":" << endl;
            cout << "Kwota: " << transakcje[i].kwota << endl;
            cout << "Opis: " << transakcje[i].opis << endl;
        }
    }
    return true;
}


bool SKonto::dodaj_transakcje(double kwota, const string& opis) {
    Transakcje* nowa_tablica_transakcji = new Transakcje[liczba_transakcji + 1];

    for (unsigned int i = 0; i < liczba_transakcji; ++i) {
        nowa_tablica_transakcji[i] = transakcje[i];
    }
    nowa_tablica_transakcji[liczba_transakcji].kwota = kwota;
    nowa_tablica_transakcji[liczba_transakcji].opis = opis;

    delete[] transakcje;
    transakcje = nowa_tablica_transakcji;
    liczba_transakcji++;

    return true;
}

bool SKlient::wczytaj_dane_klienta(istream& fin) {
    if (!fin) {
        cerr << "Błąd: nie można odczytać strumienia wejściowego." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    if (!(fin >> imie)) {
        cerr << "Błąd: nie można wczytać imienia." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    if (!(fin >> nazwisko)) {
        cerr << "Błąd: nie można wczytać nazwiska." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    konto = new SKonto;

    if (!konto->wczytaj_konto(fin)) {
        delete konto;
        konto = nullptr;
        return false;
    }

    return true;
  }

bool SKlient::wypisz_klienta(ostream& out) {
    out << "Imię: " << imie << "\n"
        << "Nazwisko: " << nazwisko << "\n";
    if (konto != nullptr) {
        out << "Numer konta: " << konto->numer_konta << "\n"
            << "Saldo: " << konto->saldo << "\n"
            << "Liczba transakcji: " << konto->liczba_transakcji << "\n";
        if (konto->liczba_transakcji > 0) {
            out << "Transakcje:\n";
            for (unsigned int i = 0; i < konto->liczba_transakcji; ++i) {
                out << "Transakcja " << i + 1 << ":\n"
                    << "Kwota: " << konto->transakcje[i].kwota << "\n"
                    << "Opis: " << konto->transakcje[i].opis << "\n";
            }
        }
    } else {
        out << "Klient nie ma konta.\n";
    }
    if (out.fail()) {
        cerr << "Błąd: nie można wypisać danych klienta." << endl;
        return false;
    }
    return true;
}


bool SBank::wczytaj_bank(istream& fin) {
    if (!fin) {
        cerr << "Błąd: nie można odczytać strumienia wejściowego." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    if (!(fin >> nazwa_banku)) {
        cerr << "Błąd: nie można wczytać nazwy banku." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    if (!(fin >> liczba_klientow)) {
        cerr << "Błąd: nie można wczytać liczby klientów." << endl;
        fin.ignore();
        fin.clear();
        return false;
    }

    klient = new SKlient[liczba_klientow];

    for (unsigned int i = 0; i < liczba_klientow; ++i) {
        if (!klient[i].wczytaj_dane_klienta(fin)) {
                cerr << "Błąd: nie można wczytać danych klienta." << endl;
                fin.ignore();
                fin.clear();
                delete[] klient;
                klient = nullptr;
                return false;
            }
        }

        return true;
    }

bool SBank::wyswietl_bank(ostream& out) {
    out << "Nazwa banku: " << nazwa_banku << endl;
    out << "Liczba klientów: " << liczba_klientow << endl;

    for (unsigned int i = 0; i < liczba_klientow; ++i) {
        out << "Klient " << i + 1 << ":" << endl;
        out << "Imię: " << klient[i].imie << endl;
        out << "Nazwisko: " << klient[i].nazwisko << endl;

        if (klient[i].konto != nullptr) {
            out << "Konto:" << endl;
            out << "Numer konta: " << klient[i].konto->numer_konta << endl;
            out << "Saldo: " << klient[i].konto->saldo << endl;

            if (klient[i].konto->liczba_transakcji > 0) {
                out << "Transakcje:" << endl;
                for (unsigned int j = 0; j < klient[i].konto->liczba_transakcji; ++j) {
                    out << "Transakcja " << j + 1 << ":" << endl;
                    out << "Kwota: " << klient[i].konto->transakcje[j].kwota << endl;
                    out << "Opis: " << klient[i].konto->transakcje[j].opis << endl;
                }
            } else {
                out << "Brak transakcji." << endl;
            }
        } else {
            out << "Brak konta." << endl;
        }

        out << endl;
    }

    if (out.fail()) {
        cerr << "Błąd: nie można wypisać danych bankowych." << endl;
        return false;
    }

    return true;
}


bool SBank::losuj_nr_konta(string& wygenerowany_numer) {
// Sprawdzanie, czy bank ma jakiekolwiek konta
if (liczba_klientow == 0) {
    cerr << "Błąd: Bank nie ma żadnych kont." << endl;
    return false;
}
// Inicjalizacja generatora liczb losowych
srand(time(nullptr));

bool unikalny_numer = false;

while (!unikalny_numer) {
    wygenerowany_numer = "";
    // Generowanie losowego numeru konta
    for (int i = 0; i < 10; ++i) {
        wygenerowany_numer += to_string(rand() % 10);
    }
    unikalny_numer = true;
    // Sprawdzenie, czy numer jest unikalny dla wszystkich kont w banku
    for (unsigned int i = 0; i < liczba_klientow; ++i) {
        if (klient[i].konto->numer_konta == wygenerowany_numer) {
            unikalny_numer = false;
            break;
        }
    }
}

return true;
}

bool SBank::dodaj_konto(const string& nazwa_wlasciciela) {
    //cout << "Dodaj_konto begin\n";
    // Generowanie unikalnego numeru konta
    string wygenerowany_numer;
    if (!losuj_nr_konta(wygenerowany_numer)) {
    return false;
    }
    // Tworzenie nowego konta
    SKonto* nowe_konto =  new SKonto;
    nowe_konto->numer_konta = wygenerowany_numer;
    // Powiększenie tablicy klientów o nowego klienta
    liczba_klientow++;
    SKlient* nowa_tablica_klientow = new SKlient[liczba_klientow];
    for (unsigned int i = 0; i < liczba_klientow - 1; ++i) {
        nowa_tablica_klientow[i].skopiuj(klient[i]);
    }
    nowa_tablica_klientow[liczba_klientow - 1].imie = nazwa_wlasciciela;
    nowa_tablica_klientow[liczba_klientow - 1].konto = nowe_konto;
    // Zwalnianie pamięci po starych danych
    if(klient){
        delete[] klient;
        klient =nullptr;
    }
    // Przypisanie nowej tablicy klientów do banku
    klient = nowa_tablica_klientow;
    //cout << "Dodaj_konto end\n";

return true;
}

bool SKlient::wplata(double kwota) {
    if (konto != nullptr) {
        konto->saldo += kwota;
        konto->dodaj_transakcje(kwota, "Wpłata");
        return true;
    }
    return false;
}

bool SKlient::wyplata(double kwota) {
    if (konto != nullptr) {
        if (konto->saldo >= kwota) {
            konto->saldo -= kwota;
            konto->dodaj_transakcje(-kwota, "Wypłata");
            return true;
        }
        return false;
    }
    return false;
}

SKonto* SBank::znajdz_konto(const string& numer_konta) {
    for (unsigned int i = 0; i < liczba_klientow; ++i) {
        if (klient[i].konto != nullptr && klient[i].konto->numer_konta == numer_konta) {
            return klient[i].konto;
        }
    }
    return nullptr;
}

bool SBank::usun_konto(const string& numer_konta) {
    if (klient == nullptr || liczba_klientow == 0) {
        cout << "Brak klientów w banku." << endl;
        return false;
    }
// dopisac zmiane rozmiaru konta po uzunieciu konta.
    for (unsigned int i = 0; i < liczba_klientow; ++i) {
        if (klient[i].konto != nullptr && klient[i].konto->numer_konta == numer_konta) {
            delete klient[i].konto;
            klient[i].konto = nullptr;
            return true;
        }
    }

    cout << "Nie znaleziono konta o numerze: " << numer_konta << endl;
    return false;
}
bool porownaj(const SKlient& a, const SKlient& b) {
    if (a.nazwisko != b.nazwisko) {
        return a.nazwisko < b.nazwisko;
    } else {
        return a.imie < b.imie;
    }
}

void sortuj_transakcje(SKlient* klient, unsigned int liczba_klientow, bool (*porownaj)(const SKlient&, const SKlient&)) {
    SKlient temp;
    for (unsigned int i = 0; i < liczba_klientow; ++i) {
        for (unsigned int j = 0; j < liczba_klientow - 1; ++j) {
            if (porownaj(klient[j], klient[j+1]))
            {
                temp = klient[i];
                klient[i] = klient[j+1];
                klient[j+1]=temp;
            }
        }
    }
}

int main(int argc, char** argv) {
    if(argc!= 3 ){
        cerr<<"malo arg";
        cout<<"/nazwa in.txt, out.txt";
    }
    ifstream plik_wejsciowy(argv[1]);
    if (!plik_wejsciowy) {
        cerr << "Błąd: Nie można otworzyć pliku wejściowego." << endl;
        return 1;
    }

    ofstream plik_wyjsciowy(argv[2]);
    if (!plik_wyjsciowy) {
        cerr << "Błąd: Nie można otworzyć pliku wyjściowego." << endl;
        return 1;
    }

    SBank bank;
    // Wczytanie danych banku
    if (!bank.wczytaj_bank(plik_wejsciowy)) {
        cerr << "Błąd: Nie udało się wczytać danych banku." << endl;
        return 1;
    }
    plik_wejsciowy.close();
    // Wyświetlenie informacji o banku
    bank.wyswietl_bank(plik_wyjsciowy);
    // Przykładowe operacje na banku i klientach
    bank.dodaj_konto("Jan Kowalski");
    bank.dodaj_konto("Anna Nowak");
    cout << "Znajdz_konto\n";
    SKonto* konto = bank.znajdz_konto("Konto123");
    if (konto) {
        cout << "Konto123\n";
        konto->dodaj_transakcje(500.0, "Wpłata");
        konto->wyswietl_konto(true);
    }
    konto = bank.znajdz_konto("Konto456");
    if (konto) {
        cout << "Konto456\n";
        konto->dodaj_transakcje(-200.0, "Wypłata");
        konto->wyswietl_konto(true);
    }
    cout << "Usun_kont\n";
    // Usunięcie konta
    bank.usun_konto("Konto123");
    // Wypisanie informacji o banku po operacjach
    bank.wyswietl_bank(plik_wyjsciowy);
    // Sortowanie klientów według nazwiska i imienia
    sortuj_transakcje(bank.klient, bank.liczba_klientow, porownaj);
    // Wypisanie do pliku posortowanych klientów
    plik_wyjsciowy << "Klienci po sortowaniu: " << endl;
    for (unsigned int i = 0; i < bank.liczba_klientow; ++i) {
        bank.klient[i].wypisz_klienta(plik_wyjsciowy);
        plik_wyjsciowy << endl;
    }

    plik_wyjsciowy.close();

    return 0;
}
