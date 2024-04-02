#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
using namespace std;
class Vraboten{
protected:
    char *ime;
    char *prezime;
    int godina_na_vrabotuvanje;
public:
    Vraboten(const char *i,const char *p,int g){
        ime= new char[strlen(i)+1];
        strcpy(ime,i);
        prezime= new char[strlen(p)+1];
        strcpy(prezime,p);
        godina_na_vrabotuvanje=g;
    }
    ~Vraboten(){
        delete [] ime;
        delete [] prezime;
    }
    void prikazi_vraboten(){
        cout<<"Ime i prezime:"<<ime<<" "<<prezime;
        cout<<" so godina na vrabotuvanje:"<<godina_na_vrabotuvanje<<endl;
    }
};
class Profesor: public Vraboten{
protected:
    char *ime; char *prezime; int godina_na_vrabotuvanje;
    char *zvanje; char *oblast; int br_predmeti;
public:
    Profesor(const char *i,const char *p,int g,const char *z,const char *o, int br_p):Vraboten(i,p,g){
        zvanje= new char[strlen(z)+1];
        strcpy(zvanje,z);
        oblast= new char[strlen(o)+1];
        strcpy(oblast,o);
        br_predmeti=br_p;
    }
    ~Profesor(){
        delete [] zvanje;
        delete [] oblast;
    }
    void prikazi_profesor(){
        prikazi_vraboten();
        cout<<"So zvanje "<<zvanje<<" vo oblast "<<oblast<<" i br na predmeti "<<br_predmeti<<endl;
    }
};
class Asistent: public Vraboten{
protected:
    char *ime; char *prezime; int godina_na_vrabotuvanje;
    char *zvanje; char *mentor; int br_predmeti;
public:
    Asistent(const char *i,const char *p,int g,const char *z,const char *o, int br_p):Vraboten(i,p,g){
        zvanje= new char[strlen(z)+1];
        strcpy(zvanje,z);
        mentor= new char[strlen(o)+1];
        strcpy(mentor,o);
        br_predmeti=br_p;
    }
    ~Asistent(){
        delete [] zvanje;
        delete [] mentor;
    }
    void prikazi_asistent(){
        prikazi_vraboten();
        cout<<"So zvanje "<<zvanje<<" so mentor "<<mentor<<" i br na predmeti "<<br_predmeti<<endl;
    }
};
class Demonstrator:public Vraboten{
protected:
    char *ime; char *prezime; int godina_na_vrabotuvanje;
    int od_rab,do_rab;
public:
    Demonstrator(const char *i,const char *p,int g,int od,int d):Vraboten(i,p,g){
        od_rab=od; do_rab=d;
    }
    void prikazi_demonstrator(){
        prikazi_vraboten();
        cout<<"So rabotno vreme od "<<od_rab<<" do "<<do_rab<<endl;
    }
};
int main()
{
    int izbor=0;
    Asistent **asistenti;
    asistenti=(Asistent**)malloc(10*sizeof(Asistent*));
    Profesor **profesori;
    profesori=(Profesor**)malloc(10*sizeof(Profesor*));
    Demonstrator **dem;
    dem=(Demonstrator**)malloc(20*sizeof(Demonstrator*));
    int pr=0,as=0,de=0; // broj na profesori,asistenti i demonstratori
    char k;
    while(izbor!=3){
        cout<<"(1)Dodavanje na nov vraboten:"<<endl;
        cout<<"(2)Prikazi na lista."<<endl;
        cout<<"(3)Kraj."<<endl;
        cin>>izbor;
        switch(izbor){
        case 1:{
            cout<<"Dali ste profesor,asistent ili demonstrator:(p,a,d)"<<endl;
            cin>>k;
            switch(k){
            case 'p':{
                cout<<"Vnesi ime prezime, godina, zvanje,oblast,predmeti"<<endl;
                const char *i,*p,*z,*o;
                int g,pred;
                string vlez[6];
                for(int i=0;i<6;i++){
                    cin>>vlez[i];
                }
                i=vlez[0].c_str(); p=vlez[1].c_str(); z=vlez[3].c_str(); o=vlez[4].c_str();
                g=stoi(vlez[2],0,10);
                pred=stoi(vlez[5],0,10);
                profesori[pr]=new Profesor (i,p,g,z,o,pred);
                pr++;
                break;
            }
            case 'a':{
                cout<<"Vnesi ime prezime, godina, zvanje,mentor,predmeti"<<endl;
                const char *i,*p,*z,*m;
                int g,pred;
                string vlez[6];
                for(int i=0;i<6;i++){
                    cin>>vlez[i];
                }
                i=vlez[0].c_str(); p=vlez[1].c_str(); z=vlez[3].c_str(); m=vlez[4].c_str();
                g=stoi(vlez[2],0,10);
                pred=stoi(vlez[5],0,10);
                asistenti[as]=new Asistent (i,p,g,z,m,pred);as++;
                break;
            }
            case 'd':{
                cout<<"Vnesi ime prezime, godina, rabotno vreme od i do"<<endl;
                const char *i,*p;
                int od,doo,g;
                string vlez[5];
                for(int i=0;i<5;i++){
                    cin>>vlez[i];
                }
                i=vlez[0].c_str(); p=vlez[1].c_str();
                g=stoi(vlez[2],0,10);
                od=stoi(vlez[3],0,10);
                doo=stoi(vlez[4],0,10);
                dem[de]= new Demonstrator(i,p,g,od,doo); de++;
                break;
            }
            default: cout<<"Greska!"<<endl;
            }
            break;
        }
        case 2:{
            int i;
            for(i=0;i<pr;i++){           // gi pechati site profesori
                profesori[i]->prikazi_profesor();
            }
            for(i=0;i<as;i++){
                asistenti[i]->prikazi_asistent();       // site asistenti
            }
            for(i=0;i<de;i++){
                dem[i]->prikazi_demonstrator();     // site demonstratori
            }
            break;
        }
        case 3: cout<<"Kraj."<<endl; break;
        default: cout<<"Greska!"<<endl;

        }
    }
    int i;
    for(i=0;i<pr;i++){
        delete [] profesori[i];
    }
    for(i=0;i<as;i++){
        delete []asistenti[i];
    }
    for(i=0;i<de;i++){
        delete [] dem[i];
    }
    return 0;
}
