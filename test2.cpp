#include <iostream>
#include<string>
#include<fstream>

using namespace std;

struct SStudent {
    string imie;
    string nazwisko;
    int numer_indeksu;
    int liczba_ocen_poz;
    float* kursy;


    bool wczytaj(ifstream&);
    bool wypisz(ostream& out = cout);
};

bool SStudent::wczytaj(ifstream& fin) {
    if (!fin) {
        cerr << "Blad otwercia pliku wejciewego" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    if (!(fin >> imie)) {
        cerr << "Blad wcytania strumenia Imie" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    if (!(fin >> nazwisko)) {
        cerr << "Blad wcytania strumenia Nazwisko" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    if (!(fin >> numer_indeksu)) {
        cerr << "Blad wcytania strumenia Numer Indeksu" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    return true;
}

bool SStudent::wypisz(ostream& out) {
    out << "Imie: " << imie << endl;
    out << "Nazwisko: " << nazwisko << endl;
    out << "Numer indeksu: " << numer_indeksu << endl;
    for (int i = 0; i < liczba_ocen_poz; i++)
    {
        out << "Kursy: " << kursy[i] << endl;
    }
    return true;
}


struct SLista {
    string nazwa_listy;
    int liczba_student;
    SStudent* student;

    bool wczytaj(ifstream&);
    bool wypisz(ostream& out = cout);
    double srednia();
};

bool SLista::wczytaj(ifstream& fin){
    if (!fin) {
        cerr << "Blad pliku wejciewego" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    if (!(fin>>nazwa_listy)) {
        cerr << "Blad strumenia Nazwa Listy" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    if (!(fin >> liczba_student)) {
        cerr << "Blad strumenia Nazwa Listy" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    if (liczba_student > 0) {
        student = new SStudent[liczba_student];
        for (int i = 0; i < liczba_student; i++)
        {
            if (!(student[i].wczytaj(fin))) {
                cerr << "Blad fun wczytaj" << endl;
                delete[] student;
                student = nullptr;
                fin.ignore();
                fin.clear();
                fin.close();
                return false;
                
            }
        }
    }


    return true;
}

bool SLista::wypisz(ostream& out){
    out << "Nazwa Listy: " << nazwa_listy << endl;
    out << "Liczba Studentow: " << liczba_student << endl;
    for (int i = 0; i < liczba_student; i++)
    {
        out << student[i].wypisz(out) << endl;
    }
    return true;
}

double SLista::srednia() {
    return student->liczba_ocen_poz/liczba_student;
}

int main(int argv,char** argc)
{
    if (argv != 3) {
        cerr << "Nie prawidlowa liczba arg" << endl;
        return 1;
    }
    ifstream fin;
    fin.open(argc[1]);
    ofstream fout;
    fout.open(argc[2]);
    SLista lista;
    if (!lista.wczytaj(fin)) {
        cerr << "" << endl;
        return 2;
    }
    cout << lista.srednia() << endl;
    if (lista.wypisz(fout)) {
        cout << "Jest zapisano" << endl;
    }
    return 0;
}

