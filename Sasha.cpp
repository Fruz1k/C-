#include<iostream>
#include<string>
#include<fstream>
using namespace std;
const double procent = 0.55;

struct SOsoba{
string imie;
string nazwisko;
double kapital;
bool wczytaj_osobe(istream&fin=cin);
bool wyswietl_osobe(ostream&fout=cout);
bool dodaj_pieniedzy(double& pieniedzy);
double podatek(const double&procent);
};

bool SOsoba::wczytaj_osobe(istream&fin){
if(!fin){
    cerr<<"Blad otwarcia pliku";
    fin.ignore();
    fin.clear();
return false;
}
fin>>imie;
if(!fin.good()){
    cerr<<"Blad z imiem";
    fin.ignore();
    fin.clear();
    return false;
}
fin>>nazwisko;
if(!fin.good()){
    cerr<<"Blad z nazwiskiem";
    fin.ignore();
    fin.clear();
    return false;
}
fin>>kapital;
if(!fin.good()){
    cerr<<"Blad z kapitalem";
    fin.ignore();
    fin.clear();
    return false;
}
return true;
}


bool SOsoba::wyswietl_osobe(ostream&fout){
if(!fout){
    cerr<<"Blad otwarcia pliku";
    fout.clear();
return false;
}
fout<<imie<<endl;
if(!fout.good()){
    cerr<<"Blad z imiem";
    fout.clear();
    return false;
}
fout<<nazwisko<<endl;
if(!fout.good()){
    cerr<<"Blad z nazwisko";
    fout.clear();
    return false;
}
fout<<kapital<<endl;
if(!fout.good()){
    cerr<<"Blad z kapital";
    fout.clear();
    return false;
}
return true;
}

bool SOsoba::dodaj_pieniedzy(double& pieniedzy){
kapital+=pieniedzy;
return true;
}

double SOsoba::podatek(const double& procent){
return kapital*procent;
}


struct SMiasto{
string nazwa_miasta;
double podatki;
unsigned int liczba_ludzi;
SOsoba* ludzi;
bool wczytaj_miasto(istream&fin=cin);
bool wyswietl_miasto(const bool pokaz_ludzi);
bool zapisz_miasto(ostream&fout);
bool policz_dochod();
bool dodaj_osobe(const string&imie,const string&nazwisko,const double&kapital);
};

bool SMiasto::wczytaj_miasto(istream&fin){
if(!fin){
    cerr<<"Blad otwarcia pliku";
    fin.ignore();
    fin.clear();
return false;
}
fin>>nazwa_miasta;
if(!fin.good()){
    cerr<<"Blad z nazwa miasta";
    fin.ignore();
    fin.clear();
    return false;
}
fin>>liczba_ludzi;
if(!fin.good()){
    cerr<<"Blad z nazwa miasta";
    fin.ignore();
    fin.clear();
    return false;
}
if(liczba_ludzi>0){
ludzi=new SOsoba[liczba_ludzi];
for(unsigned int i=0; i<liczba_ludzi; i++)
ludzi[i].wczytaj_osobe(fin);
}
return true;
}


bool SMiasto::wyswietl_miasto(const bool pokaz_ludzi){
cout<<"nazwa miasta: "<<nazwa_miasta<<endl;
cout<<"liczba ludzi: "<<liczba_ludzi<<endl;
cout<<"podatki: "<<podatki<<endl;
if(pokaz_ludzi){
for(unsigned int i=0; i<liczba_ludzi;i++){
cout<<"imie: "<<ludzi[i].imie<<endl;
cout<<"nazwisko: "<<ludzi[i].nazwisko<<endl;
cout<<"kapital: "<<ludzi[i].kapital<<endl;
    }
}
return true;
}

bool SMiasto::zapisz_miasto(ostream&fout){
if(!fout){
    cerr<<"Blad otwarcia pliku";
    fout.clear();
return false;
}
fout<<nazwa_miasta<<endl;
if(!fout.good()){
    cerr<<"Blad z nazwa_miasta";
    fout.clear();
    return false;
}
fout<<liczba_ludzi<<endl;
if(!fout.good()){
    cerr<<"Blad z liczba_ludzi";
    fout.clear();
    return false;
}
if(liczba_ludzi>0){
for(unsigned int i=0; i<liczba_ludzi;i++){
fout<<ludzi[i].imie<<" "<<ludzi[i].nazwisko<<" "<<ludzi[i].kapital<<endl;
if(!fout.good()){
    cerr<<"Blad z czloweliem "<<i;
    fout.clear();
    return false;
}
}
}
return true;
}

bool SMiasto::policz_dochod(){
double summa=0;
if(liczba_ludzi>0){
for(unsigned int i=0; i<liczba_ludzi;i++)
summa+=ludzi[i].podatek(procent);
}
podatki=summa;
return true;
}


bool SMiasto::dodaj_osobe(const string&imie,const string&nazwisko,const double&kapital){
SOsoba*nowy = new SOsoba[liczba_ludzi+1];
for(unsigned int i=0;i<liczba_ludzi;i++)
nowy[i]=ludzi[i];
nowy[liczba_ludzi].imie=imie;
nowy[liczba_ludzi].nazwisko=nazwisko;
nowy[liczba_ludzi].kapital=kapital;
liczba_ludzi+=1;
ludzi=nowy;
return true;
}

struct SKraj{
string nazwa_kraju;
double WWP=0;
float HDI;
unsigned int liczba_miast;
SOsoba* president;
SMiasto* miasta;
bool wczytaj_kraj(istream&fin=cin);
bool zapisz_kraj(ostream&fout);
SOsoba* znajdz_lidera(const string&imie,const string&nazwisko);
bool dodaj_miasto(const string&nazwa);
bool usun_miasto(const string&nazwa);
bool policz_wwp();
};

bool SKraj::wczytaj_kraj(istream&fin){
if(!fin){
    cerr<<"Blad otwarcia pliku";
    fin.ignore();
    fin.clear();
return false;
}
fin>>nazwa_kraju;
if(!fin.good()){
    cerr<<"Blad z nazwa kraju";
    fin.ignore();
    fin.clear();
    return false;
}
fin>>HDI;
if(!fin.good()){
    cerr<<"Blad z HDI";
    fin.ignore();
    fin.clear();
    return false;
}
string imie;
string nazwisko;
fin>>imie;
fin>>nazwisko;
if(!fin.good()){
    cerr<<"Blad z president";
    fin.ignore();
    fin.clear();
    return false;
}
fin>>liczba_miast;
if(!fin.good()){
    cerr<<"Blad z liczba miast";
    fin.ignore();
    fin.clear();
    return false;
}

if(liczba_miast>0){
miasta=new SMiasto[liczba_miast];
for(unsigned int i=0; i<liczba_miast; i++)
miasta[i].wczytaj_miasto(fin);
}
president=znajdz_lidera(imie,nazwisko);
return true;
}


bool SKraj::zapisz_kraj(ostream&fout){
if(!fout){
    cerr<<"Blad otwarcia pliku";
    fout.clear();
return false;
}
fout<<nazwa_kraju<<endl;
if(!fout.good()){
    cerr<<"Blad z nazwa_kraju";
    fout.clear();
    return false;
}
fout<<liczba_miast<<endl;
if(!fout.good()){
    cerr<<"Blad z liczba_miast";
    fout.clear();
    return false;
}
if (liczba_miast>0){
for(unsigned int i=0; i<liczba_miast;i++){
        miasta[i].zapisz_miasto(fout);
        if(!fout.good()){
            cerr<<"Blad z czloweliem "<<i;
            fout.clear();
            return false;
            }
        }
    }
return true;
}

SOsoba* SKraj::znajdz_lidera(const string&imie,const string&nazwisko){
int indi=0;
int indj=0;
for(unsigned int i = 0; i<liczba_miast;i++){
    for(unsigned int j = 0; j<miasta[i].liczba_ludzi;j++){
        if(miasta[i].ludzi[j].imie==imie&&miasta[i].ludzi[j].nazwisko==nazwisko){
            indi=i;
            indj=j;
        }
    }
}
return &miasta[indi].ludzi[indj];
}

bool SKraj::dodaj_miasto(const string&nazwa){
SMiasto*nowy=new SMiasto[liczba_miast+1];
for(unsigned int i = 0; i<liczba_miast; i++)
nowy[i]=miasta[i];
nowy[liczba_miast].nazwa_miasta=nazwa;
liczba_miast+=1;
miasta=nowy;
return true;
}

bool SKraj::usun_miasto(const string&nazwa){
SMiasto*nowy=new SMiasto[liczba_miast-1];
for(unsigned int i = 0; i<liczba_miast; i++){
if(miasta[i].nazwa_miasta!=nazwa)
nowy[i]=miasta[i];
else
delete[] miasta[i].ludzi;
}
liczba_miast-=1;
miasta=nowy;
return true;
}

bool SKraj::policz_wwp(){
WWP=0;
for(unsigned int i=0; i<liczba_miast;i++)
WWP+=miasta[i].podatki;
return true;
}

bool wczytaj(const string&file_in,int&ilosc_kraje,SKraj*&kraje){
ifstream fin(file_in);
if(!fin){
    cerr<<"Blad otwarcia pliku";
    fin.ignore();
    fin.clear();
    fin.close();
return false;
}
fin>>ilosc_kraje;
if(!fin.good()){
    cerr<<"Blad ilosc kraje";
    fin.ignore();
    fin.clear();
    fin.close();
return false;
}
kraje=new SKraj[ilosc_kraje];
for(int i=0; i<ilosc_kraje ; i++){
kraje[i].wczytaj_kraj(fin);
if(!fin.good()){
    cerr<<"Blad kraj "<<i;
    fin.ignore();
    fin.clear();
    fin.close();
return false;
}
}
return true;
}

bool zapisz(const string&file_out,int&ilosc_kraje,SKraj*&kraje){
ofstream fout(file_out);
if(!fout){
    cerr<<"Blad otwarcia pliku";
    fout.clear();
    fout.close();
return false;
}
for(int i=0; i<ilosc_kraje ; i++){
kraje[i].zapisz_kraj(fout);
if(!fout){
    cerr<<"Blad zapis kraja";
    fout.clear();
    fout.close();
return false;
}
}
return true;
}
void usun(int ilosc_kraje,SKraj*&kraje){
for(int i = 0; i<ilosc_kraje; i++){
    for(unsigned j=0; j<kraje[i].liczba_miast; j++){
        delete[] kraje[i].miasta[j].ludzi;
        kraje[i].miasta[j].ludzi=nullptr;
    }
    delete[] kraje[i].miasta;
    kraje[i].miasta=nullptr;
}
delete[] kraje;
}

int main(int argc, char**argv){
	if(argc!=3){
		cerr<<"Nieprawidlowa liczba elementow"<<endl;
		cout<<"Wymagane argumenty to ./nazwa, nazwę pliku wejs , nazwę pliku wyjs"<<endl;
		return 100;
	}
int ilosc_kraje;
SKraj* kraje;
wczytaj(argv[1],ilosc_kraje,kraje);
zapisz(argv[2],ilosc_kraje,kraje);
usun(ilosc_kraje,kraje);
return 0;
}
