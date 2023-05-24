#include <iostream>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;

struct Transakcje {
    double kwota;
    string opis;
};

struct SKonto {
    string numer_konta;
    double saldo_konta;
    int liczba_transakcij;
    Transakcje* transakcje;

    bool wczytaj_konto(istream& fin = cin);
    bool wyswietl_konto(bool pokaz_transakcje);
    bool dodaj_transakcje(double kwota, const string& opis);
};

bool SKonto::wczytaj_konto(istream& fin) {
    if (!fin) {
        cerr << "Blad otwercia pliku wejciewego" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (!(fin >> numer_konta)) {
        cerr << "blad wczytania Numer Konta" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (!(fin >> saldo_konta)) {
        cerr << "blad wczytania Saldo Konta" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (!(fin >> liczba_transakcij)) {
        cerr << "blad wczytania Liczba Transakcij" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (liczba_transakcij > 0) {
        transakcje = new Transakcje[liczba_transakcij];
        for (int i = 0; i < liczba_transakcij; i++)
        {
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

    }
    return true;
}

bool SKonto::wyswietl_konto(bool pokaz_transakcje) {
    cout << "Numer Konta: " << numer_konta << endl;
    cout << "Saldo konta: " << saldo_konta << endl;
    if (pokaz_transakcje) {
        cout << "Liczba transakcij: " << liczba_transakcij << endl;
        for (int i = 0; i < liczba_transakcij; i++)
        {
            cout << "Liczba transakcij: " << i + 1 << endl;
            cout << "/Kwota: " << transakcje[i].kwota << endl;
            cout << "/Opis: " << transakcje[i].opis << endl;
        }
    }



    return true;
}

bool SKonto::dodaj_transakcje(double kwota, const string& opis) {
    Transakcje* nowa_transakcje = new Transakcje[liczba_transakcij + 1];
    for (int i = 0; i < liczba_transakcij; i++)
    {
        nowa_transakcje[i] = transakcje[i];
    }
    nowa_transakcje[liczba_transakcij].kwota = kwota;
    nowa_transakcje[liczba_transakcij].opis = opis;
    delete[] transakcje;
    liczba_transakcij++;
    transakcje = nowa_transakcje;
    return true;
}

struct SKlient {
    string imie;
    string nazwisko;
    SKonto* konto;

    bool wczytaj_dane_klienta(istream& fin = cin);
    bool wypisz_klienta(ostream& out = cout);
    bool wplata(double kwota);
    bool wyplata(double kwota);

};

bool SKlient::wczytaj_dane_klienta(istream& fin) {
    if (!fin) {
        cerr << "Blad otwercia pliku wejciewego" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (!(fin >> imie)) {
        cerr << "blad wczytania Imie" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (!(fin >> nazwisko)) {
        cerr << "blad wczytania Nazwisko" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    konto = new SKonto;
    if (!(konto->wczytaj_konto(fin))) {
        delete[] konto;
        konto = nullptr;
        fin.ignore();
        fin.clear();
        return false;
    }

    return true;
}

bool SKlient::wypisz_klienta(ostream& out) {
    //if (!out) {
    //    cerr << "Blad otwercia pliku wyjcewego" << endl;
    //    out.clear();
    //    return false;
    //}
    //if (!(out << imie)) {
    //    cerr << "Blad wyswitlenia Imie" << endl;
    //    out.clear();
    //    return false;
    //}
    //if (!(out << nazwisko)) {
    //    cerr << "Blad wyswitlenia Nazwisko" << endl;
    //    out.clear();
    //    return false;
    //}
    ////konto = new SKonto;
    //if (!(out << konto->numer_konta)) {
    //    cerr << "Blad wyswitlenia Numer Konta" << endl;
    //    delete[] konto;
    //    konto = nullptr;
    //    out.clear();
    //    return false;
    //}
    //if (!(out << konto->saldo_konta)) {
    //    cerr << "Blad wyswitlenia Saldo Konta" << endl;
    //    delete[] konto;
    //    konto = nullptr;
    //    out.clear();
    //    return false;
    //}
    //if (!(out << konto->liczba_transakcij)) {
    //    cerr << "Blad wyswitlenia Liczba transakcj" << endl;
    //    delete[] konto;
    //    konto = nullptr;
    //    out.clear();
    //    return false;
    //}
    //if (konto->liczba_transakcij > 0) {
    //    for (int i = 0; i < konto->liczba_transakcij; i++)
    //    {
    //        if (!(out << konto->transakcje[i].kwota)) {
    //            cerr << "Blad wyswitlenia Kwota" << endl;
    //            delete[] konto;
    //            konto = nullptr;
    //            out.clear();
    //            return false;
    //        }
    //        if (!(out << konto->transakcje[i].opis)) {
    //            cerr << "Blad wyswitlenia Opis" << endl;
    //            delete[] konto;
    //            konto = nullptr;
    //            out.clear();
    //            return false;
    //        }
    //    }


    //}

    //return true;

    out << "Imię: " << imie << "\n";
    out<< "Nazwisko: " << nazwisko << "\n";
    if (konto != nullptr) {
        out << "Numer konta: " << konto->numer_konta << "\n";
        out << "Saldo: " << konto->saldo_konta << "\n";
        out<< "Liczba transakcji: " << konto->liczba_transakcij << "\n";
        if (konto->liczba_transakcij > 0) {
            out << "Transakcje:\n";
            for (unsigned int i = 0; i < konto->liczba_transakcij; ++i) {
                out << "Transakcja " << i + 1 << ":\n"
                    << "Kwota: " << konto->transakcje[i].kwota << "\n"
                    << "Opis: " << konto->transakcje[i].opis << "\n";
            }
        }
    }
    else {
        out << "Klient nie ma konta.\n";
    }
    if (out.fail()) {
        cerr << "Błąd: nie można wypisać danych klienta." << endl;
        return false;
    }
    return true;
}

bool SKlient::wplata(double kwota) {
    konto->saldo_konta = konto->saldo_konta + kwota;
    return true;
}

bool SKlient::wyplata(double kwota) {
    konto->saldo_konta = konto->saldo_konta - kwota;
    return true;
}

struct SBank {
    string nazwa_banku;
    int liczba_klientow;
    SKlient* klient;

    bool wczytaj_bank(istream& fin = cin);
    bool wyswietl_bank(ostream& out = cout);
    bool dodaj_konto(const string& nazwa_wlasciciela);
    bool losuj_nr_konta(string& wygenerowany_numer);
    bool usun_konto(const string& numer_konta);
    SKonto* znajdz_konto(const string& numer_konta);
};

bool SBank::wczytaj_bank(istream& fin) {
    if (!fin) {
        cerr << "Blad otwercia pliku wejciewego" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (!(fin >> nazwa_banku)) {
        cerr << "blad wczytania Nazwa Banku" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (!(fin >> liczba_klientow)) {
        cerr << "blad wczytania Liczba Klientow" << endl;
        fin.ignore();
        fin.clear();
        return false;
    }
    if (liczba_klientow > 0) {
        klient = new SKlient[liczba_klientow];
        for (int i = 0; i < liczba_klientow; i++)
        {
            if (!(klient[i].wczytaj_dane_klienta(fin))) {
                cerr << "blad wczytania Klienta" << endl;
                delete[] klient;
                klient = nullptr;
                fin.ignore();
                fin.clear();
                return false;
            }
        }

    }
    return true;
}

bool SBank::wyswietl_bank(ostream& out) {
    out << "Nazwa banku: " << nazwa_banku << endl;
    out << "Liczba klientow: " << liczba_klientow << endl;
    for (int i = 0; i < liczba_klientow; i++)
    {
        out << "Klient: " << i + 1 << endl;
        out << "Imie: " << klient[i].imie << endl;
        out << "Nazwisko: " << klient[i].nazwisko << endl;
        if (klient[i].konto != nullptr) {
            out << "Numer Konta: " << klient[i].konto->numer_konta << endl;
            out << "Saldo: " << klient[i].konto->saldo_konta << endl;
            out << "Liczba transakcj: " << klient[i].konto->liczba_transakcij << endl;
            if (klient[i].konto->liczba_transakcij > 0) {
                for (int j = 0; j < klient[i].konto->liczba_transakcij; j++)
                {
                    out << "Kwota: " << klient[i].konto->transakcje[j].kwota << endl;
                    out << "Opis: " << klient[i].konto->transakcje[j].opis << endl;
                }
            }

        }
    }
    return true;
}

bool SBank::losuj_nr_konta(string& wygenerowany_numer) {
    wygenerowany_numer = "";
    for (int i = 0; i < 10; ++i) {
        wygenerowany_numer += to_string(rand() % 10);
    }
    return true;

}


bool SBank::dodaj_konto(const string& nazwa_wlasciciela) {
    string wygenerowany_numer;
    SKlient* nowy_klient = new SKlient[liczba_klientow + 1];
    for (int i = 0; i < liczba_klientow; i++)
    {
        nowy_klient[i] = klient[i];
    }
    nowy_klient[liczba_klientow].konto->numer_konta = losuj_nr_konta(wygenerowany_numer);
    liczba_klientow++;
    klient = nowy_klient;
    return true;
}

bool SBank::usun_konto(const string& numer_konta) {
    SKlient* nowy_klient = new SKlient[liczba_klientow - 1];
    for (int i = 0; i < liczba_klientow; i++)
    {
        if (klient[i].konto->numer_konta == numer_konta) {
            delete klient[i].konto;
            klient[i].konto = nullptr;
            return true;
        }
    }
    cout << "Nie znaleziono konta o numerze: " << numer_konta << endl;
    return false;
}

SKonto* SBank::znajdz_konto(const string& numer_konta) {
    for (int i = 0; i < liczba_klientow; i++)
    {
        if (klient[i].konto->numer_konta == numer_konta) {
            return klient[i].konto;
        }
    }
    return nullptr;
}

void usun(SBank& bank) {
    for (int i = 0; i < bank.liczba_klientow; i++)
    {
        delete[] bank.klient[i].konto[0].transakcje;
        bank.klient[i].konto[0].transakcje = nullptr;
        delete[] bank.klient[i].konto;
        bank.klient[i].konto = nullptr;
    }
    delete[] bank.klient;
    bank.klient = nullptr;

}


int main(int argc, char** argv)
{
    srand(time(NULL));
    if (argc != 3) {
        cerr << "Za malo arg" << endl;
        return 100;
    }
    ifstream plik_wej(argv[1]);
    ofstream plik_wyj(argv[2]);

    SBank bank;
    if (!bank.wczytaj_bank(plik_wej)) {
        cerr << "Błąd: Nie udało się wczytać danych banku." << endl;
        return 1;
    }
    plik_wej.close();
    bank.wyswietl_bank(plik_wyj);
    plik_wyj.close();

    return 0;
}
