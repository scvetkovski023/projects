#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;
class Datum{
private:
    int den;
    int mesec;
    int godina;
public:
    Datum(int d,int m,int g){
        setDatum(d,m,g);
    }
    void setDatum(int d,int m,int g){
        den=d;
        mesec=m;
        godina=g;
        if(m>0 && m<13){
            mesec=m;
        }
        else{
            mesec=1;
            cout<<"Nema takov mesec. Postaveno e na 1."<<endl;
        }
        if(g<2024){
            godina=g;
        }
        else{
            cout<<"Gresna godina"<<endl;
        }
        den=proveriDen(d,m,g);
    }
    int getden(){ return den; }
    int getmesec(){ return mesec; }
    int getgodina(){ return godina; }
    void print(){
        cout<<den<<"/"<<mesec<<"/"<<godina<<endl;
    }
    int proveriDen( int day , int m,int g)
    {
        static const int denovi[ 13 ] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ( day > 0 && day <= denovi[ m ] )
            return day;
        if ( m == 2 && day == 29 && ( g % 400 == 0 || ( g % 4 == 0 && g % 100 != 0 ) ) )
            return day;
        cout << "Denot " << day << " e greshen. Postaveno na 1."<<endl;
        return 1;
    }
};

class Zivotno{
protected:
    Datum raganje;
    Datum primanje;
    char pol;
    char *ime;
    Datum p_vakcina;
public:
    Zivotno(char *,char,int,int,int,int,int,int,int,int,int);
    void Prikazhi_Podatoci();
    ~Zivotno(){
        delete [] ime;
    }
    virtual int presmetaj_vakcina(Datum p_vakcina){
        time_t t = time(0);
        tm* now=localtime(&t);
        int godina=(now->tm_year+1900);
        int mesec=now->tm_mon+1;
        int den=now->tm_mday;
        Datum *denes= new Datum(den,mesec,godina);
        static const int denovi[ 13 ] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(denovi[denes->getmesec()]-denes->getden()>=7){         // se gleda od 1 do 23 ili 24ti vo mesecot
            if(((p_vakcina.getden())-(denes->getden()))<=7){
                return 1;       // treba da se vakcinira vo slednata nedela
            }
        }
        else{
            if(((denovi[denes->getmesec()]-denes->getden())+p_vakcina.getden())<=7){ // primer denes e 27 od 31 to e 31-27=4 i den na vakcina pomalo od 7 treba da e
                if(denes->getmesec()==12 && p_vakcina.getmesec()==1 && p_vakcina.getgodina()==(denes->getgodina()+1)){ // ova samo za dekemvri
                    return 1;
                }
                if((denes->getmesec()+1)==p_vakcina.getmesec())      // momentalniot mesec + 1 = sledniot
                    return 1;
            }
        }
        return 0;
    }


};

Zivotno::Zivotno(char *i,char mz, int rd,int rm, int rg, int pd,int pm, int pg, int vd,int vm,int vg):
    raganje(rd,rm,rg),primanje(pd,pm,pg),p_vakcina(vd,vm,vg){
    ime = new char[strlen(i)+1];
    strcpy(ime,i);
    pol=mz;
}

void Zivotno::Prikazhi_Podatoci(){
    cout<<"Ime: "<<ime;
    cout<<" Pol: "<<pol;
    cout<<" Datum na raganje:";
    raganje.print();
    cout<<"Datum na primanje:";
    primanje.print();
    cout<<" Datum na posledna vakcina: ";
    p_vakcina.print();
}
class Vlekac:public Zivotno{
protected:
    Datum sledna;
    static int br_v;
public:
    Vlekac(char *,char,int,int,int,int,int,int,int,int,int,int,int,int);
    ~Vlekac(){
        --br_v;
    }
    int get_broj(){
        return br_v;
    }
    Datum getSledna(){
        return sledna;
    }
    int presmetaj_vakcina(Datum sledna){
        time_t t = time(0);
        tm* now=localtime(&t);
        int godina=(now->tm_year+1900);
        int mesec=now->tm_mon+1;
        int den=now->tm_mday;
        Datum *denes= new Datum(den,mesec,godina);
        static const int denovi[ 13 ] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(denovi[denes->getmesec()]-denes->getden()>=7){         // se gleda od 1 do 23 ili 24ti vo mesecot
            if(((sledna.getden())-(denes->getden()))<=7){
                return 1;       // treba da se vakcinira vo slednata nedela
            }
        }
        else{
            if(((denovi[denes->getmesec()]-denes->getden())+sledna.getden())<=7){ // primer denes e 27 od 31 to e 31-27=4 i den na vakcina pomalo od 7 treba da e
                if(denes->getmesec()==12 && sledna.getmesec()==1 && sledna.getgodina()==(denes->getgodina()+1)){ // ova samo za dekemvri
                    return 1;
                }
                if((denes->getmesec()+1)==sledna.getmesec())      // momentalniot mesec + 1 = sledniot
                    return 1;
            }
        }
        return 0;
    }
    void print_Vlekac();
};
int Vlekac::br_v=0;
Vlekac::Vlekac(char *i,char mz, int rd,int rm, int rg, int pd,int pm, int pg, int vd,int vm,int vg,int sd,int sm,int sg):
    sledna(sd,sm,sg),Zivotno(i,mz,rd,rm,rg,pd,pm,pg,vd,vm,vg){
    ++br_v;
}
void Vlekac::print_Vlekac(){
    Prikazhi_Podatoci();
    cout<<"Datum na sledna vakcina";
    sledna.print();
}

class Ptica:public Zivotno{
protected:
    char letac;
    static int br_p;
public:
    Ptica(char *,char,int,int,int,int,int,int,int,int,int,char);
    ~Ptica(){
        --br_p;
    }
    int get_broj(){
        return br_p;
    }
    void print_Ptica();
    int presmetaj_vakcina(Datum p_vakcina){
        time_t t = time(0);
        tm* now=localtime(&t);
        int godina=(now->tm_year+1900);
        int mesec=now->tm_mon+1;
        int den=now->tm_mday;
        Datum *denes= new Datum(den,mesec,godina);
        static const int denovi[ 13 ] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(denovi[denes->getmesec()]-denes->getden()>=7){         // se gleda od 1 do 23 ili 24ti vo mesecot
            if((p_vakcina.getden()-(denes->getden()))<=7 &&(p_vakcina.getden()-(denes->getden()))>=0){
                if((p_vakcina.getmesec()+6)==denes->getmesec() && (p_vakcina.getgodina()==denes->getgodina()))    // ist da e mesec a godinata za 1 razlika
                    return 1;       // treba da se vakcinira vo slednata nedela
                if((p_vakcina.getgodina()+1)==denes->getgodina() && (13-p_vakcina.getmesec()+denes->getmesec())==6) // deka na 6 meseci e
                    return 1;   // ova e za mesecite 1,2,3,4,5 bidejki pred 6 meseci ke e 8,9,10,11,12
            }
        }
        else{
            if(((denovi[denes->getmesec()]-denes->getden())+p_vakcina.getden())<=7){ // primer denes e 27 od 31 to e 31-27=4 i den na vakcina pomalo od 7 treba da e
                if((denes->getmesec()-6)==p_vakcina.getmesec() && p_vakcina.getgodina()==denes->getgodina()){ // ako sme 12 mesec - 6 meseci
                    return 1;   // ako sme 12 mesec tocno e -6 meseci, a godinata e ista
                }
            }
        }
        return 0;
    }

};

int Ptica::br_p=0;
Ptica::Ptica(char *i,char mz, int rd,int rm, int rg, int pd,int pm, int pg, int vd,int vm,int vg,char l):
    Zivotno(i,mz,rd,rm,rg,pd,pm,pg,vd,vm,vg){
    letac=l;
    ++br_p;
}
void Ptica::print_Ptica(){
    Prikazhi_Podatoci();
    cout<<"Letac:"<<letac<<endl;
}
class Cicac:public Zivotno{
protected:
    char prezivar;
    static int br_c;
public:
    Cicac(char *i,char mz, int rd,int rm, int rg, int pd,int pm, int pg, int vd,int vm,int vg,char c);
    ~Cicac(){
        --br_c;
    }
    int get_broj(){
        return br_c;
    }
    void print_Cicac();
    int presmetaj_vakcina(Datum p_vakcina){
        time_t t = time(0);
        tm* now=localtime(&t);
        int godina=(now->tm_year+1900);
        int mesec=now->tm_mon+1;
        int den=now->tm_mday;
        Datum *denes= new Datum(den,mesec,godina);
        static const int denovi[ 13 ] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(denovi[denes->getmesec()]-denes->getden()>=7){         // se gleda od 1 do 23 ili 24ti vo mesecot
            if((p_vakcina.getden()-(denes->getden()))<=7 &&(p_vakcina.getden()-(denes->getden()))>=0){
                if(p_vakcina.getmesec()==denes->getmesec() && (p_vakcina.getgodina()+1)==denes->getgodina())    // ist da e mesec a godinata za 1 razlika
                    return 1;       // treba da se vakcinira vo slednata nedela
            }
        }
        else{
            if(((denovi[denes->getmesec()]-denes->getden())+p_vakcina.getden())<=7){ // primer denes e 27 od 31 to e 31-27=4 i den na vakcina pomalo od 7 treba da e
                if(denes->getmesec()==12 && p_vakcina.getmesec()==1 && (p_vakcina.getgodina()+1)==denes->getgodina()){ // ova samo za dekemvri
                    return 1;
                }
            }
        }
        return 0;
    }
};
int Cicac::br_c=0;

Cicac::Cicac(char *i,char mz, int rd,int rm, int rg, int pd,int pm, int pg, int vd,int vm,int vg,char c):
    Zivotno(i,mz,rd,rm,rg,pd,pm,pg,vd,vm,vg){
    prezivar=c;
    ++br_c;
}
void Cicac::print_Cicac(){
    Prikazhi_Podatoci();
    cout<<"Prezivar:"<<prezivar<<endl;
}

int main()
{

    Vlekac **vlekaci;
    vlekaci=(Vlekac**)malloc(50*sizeof(Vlekac*));
    Cicac **cicaci;
    cicaci=(Cicac**)malloc(50*sizeof(Cicac*));
    Ptica **ptici;
    ptici=(Ptica**)malloc(50*sizeof(Ptica*));
    int counter=0;
    int izbor=0,ci=0,vl=0,pt=0;
    char izbor1;
    while(izbor!=6){
        cout<<"(1) Dodavanje na zivotno:"<<endl;
        cout<<"(2) Prikazuvanje na brojna sostojba"<<endl;
        cout<<"(3) Prikazuvanje na grupa."<<endl;
        cout<<"(4) Cela lista."<<endl;
        cout<<"(5) Zivotni za vakcina za edna nedela."<<endl;
        cout<<"(6) Izlez."<<endl;
        cin>>izbor;
        switch(izbor){
        case 1:{
            cout<<"Kakov tip na zivotno e:(v,c,p)"<<endl;
            cin>>izbor1;
            switch(izbor1){
            case 'c':{
                char p,c;
                char i[10];
                int rd,rm,rg,pd,pm,pg,vd,vm,vg;
                cout<<"Vnesi ime"<<endl;
                cin>>i;
                cout<<"Vnesi pol"<<endl; cin>>p;
                cout<<"Vnesi datum na raganje"<<endl;
                cin>>rd>>rm>>rg;
                cout<<"Vnesi datum na primanje"<<endl;
                cin>>pd>>pm>>pg;
                cout<<"Vnesi datum na posledna vakcina"<<endl;
                cin>>vd>>vm>>vg;
                cout<<"Vnesi dali e prezivar"<<endl;
                cin>>c;
                cicaci[ci]= new Cicac(i,p,rd,rm,rg,pd,pm,pg,vd,vm,vg,c);ci++;
                break;
            }
            case 'v':{
                char p;
                char i[10];
                int rd,rm,rg,pd,pm,pg,vd,vm,vg,sd,sm,sg;
                cout<<"Vnesi ime"<<endl;
                cin>>i;
                cout<<"Vnesi pol"<<endl; cin>>p;
                cout<<"Vnesi datum na raganje"<<endl;
                cin>>rd>>rm>>rg;
                cout<<"Vnesi datum na primanje"<<endl;
                cin>>pd>>pm>>pg;
                cout<<"Vnesi datum na posledna vakcina"<<endl;
                cin>>vd>>vm>>vg;
                cout<<"Vnesi sledna vakcina"<<endl;
                cin>>sd>>sm>>sg;
                vlekaci[vl]= new Vlekac(i,p,rd,rm,rg,pd,pm,pg,vd,vm,vg,sd,sm,sg);vl++;
                break;
            }
            case 'p':{
                char p,c;
                char i[10];
                int rd,rm,rg,pd,pm,pg,vd,vm,vg,sd,sm,sg;
                cout<<"Vnesi ime"<<endl;
                cin>>i;
                cout<<"Vnesi pol"<<endl; cin>>p;
                cout<<"Vnesi datum na raganje"<<endl;
                cin>>rd>>rm>>rg;
                cout<<"Vnesi datum na primanje"<<endl;
                cin>>pd>>pm>>pg;
                cout<<"Vnesi datum na posledna vakcina"<<endl;
                cin>>vd>>vm>>vg;
                cout<<"Vnesi dali e letac"<<endl;
                cin>>c;
                ptici[pt]= new Ptica(i,p,rd,rm,rg,pd,pm,pg,vd,vm,vg,c);pt++;
                break;
            }
            default:cout<<"Pogresen tip na zivotno"<<endl;
            }
            break;
        }
        case 2:{
            cout<<"Ima:"<<endl;
            cout<<cicaci[0]->get_broj()<<" cicaci."<<endl;
            cout<<ptici[0]->get_broj()<<" ptici."<<endl;
            cout<<vlekaci[0]->get_broj()<<" vlekaci."<<endl;
            break;
        }
        case 3:{
            cout<<"Vnesi za shto sakas informacii:"<<endl;
            cin>>izbor1;
            switch(izbor1){
            case 'c':{
                for(int i=0;i<cicaci[i]->get_broj();i++){
                    cicaci[i]->print_Cicac();
                }
                break;
            }
            case 'v':{
                for(int i=0;i<vlekaci[0]->get_broj();i++){
                    vlekaci[i]->print_Vlekac();
                }
                break;
            }
            case 'p':{
                for(int i=0;i<ptici[0]->get_broj();i++){
                    ptici[i]->print_Ptica();
                }
                break;
            }
            }
            break;
        }
        case 4:{
            for(int i=0;i<ci;i++){
                cout<<"Cicac:"<<endl;
                cicaci[i]->print_Cicac();
            }
            for(int i=0;i<vl;i++){
                cout<<"Vlekac:"<<endl;
                vlekaci[i]->print_Vlekac();
            }
            for(int i=0;i<pt;i++){
                cout<<"Ptica:"<<endl;
                ptici[i]->print_Ptica();
            }
            break;
        }
        case 5:{
            for(int i=0;i<vlekaci[0]->get_broj();i++){
                Datum pom=vlekaci[i]->getSledna();
                if(vlekaci[i]->presmetaj_vakcina(pom))
                    vlekaci[i]->print_Vlekac();
            }
            break;
        }
        case 6:{
            cout<<"Kraj."<<endl; break;
        }
        default:cout<<"Pogresen broj."<<endl;
        }
    }
    for(int i=0;i<ci;i++){
        delete [] cicaci[i];
    }
    for(int i=0;i<vl;i++){
        delete [] vlekaci[i];
    }
    for(int i=0;i<pt;i++){
        delete [] ptici[i];
    }
    return 0;
}
