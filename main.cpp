#include <iostream>
#include <string.h>

using namespace std;
class Stedac
{
public:
    void vnesi_podatoci(int br, char *ip, char *adr, long s){
        broj=br; saldo=s;
        strcpy(imeprezime,ip);
        strcpy(adresa,adr);
    }
    void prikazi_podatoci(){
        cout<<"Broj na smetka:"<<broj<<" Ime i prezime: "<<imeprezime<<endl;
        cout<<" Adresa: "<<adresa<<" i saldo: "<<saldo<<endl;
    }
    void uplata(unsigned long i){
        saldo=saldo+i;
    }
    void isplata(unsigned long i){
        if(i<=saldo){
            cout<<"Uspesno";
            saldo=saldo-i;
        }
        else
            cout<<"Nema dovolno sredstva."<<endl;
    }
    int getBroj(){
        return broj;
    }
    long sostojba(){
        return saldo;
    }

private:
    int broj;
    char imeprezime[30], adresa[50];
    long saldo;
};

int main(){
    int izbor=0;
    Stedac pole[100];
    int counter=0,i;
    unsigned long int suma;
    int smetka;

    while(izbor!=6){
        cout<<"(1)Vnesuvanje nov shtedac vo sistemot."<<endl;
        cout<<"(2)Prikaz na podatocite."<<endl;
        cout<<"(3)Uplata na sredstva."<<endl;
        cout<<"(4)Isplata na sredstva."<<endl;
        cout<<"(5)Prikaz na saldo."<<endl<<"(6)Kraj."<<endl;
        cin>>izbor;
        switch(izbor){
        case 1:{
            int br; long sal; char ip[30]; char adr[50];
            cout<<"Vnesi broj na smetka:"<<endl; cin>>br;
            cout<<"Vnesi kolku pari deponirate:"<<endl; cin>>sal;
            cout<<"Vnesi ime prezime:"<<endl; cin>>ip;
            cout<<"Vnesi adresa:"<<endl; cin>>adr;

            pole[counter].vnesi_podatoci(br,ip,adr,sal);
            counter++;
            break;
        }
        case 2:{
            for(i=0;i<counter;i++)
                pole[i].prikazi_podatoci();
            break;
        }
        case 3:{
            cout<<"Suma koja ke ja uplakjate i smetka:"<<endl;
            cin>>suma>>smetka;
            for(i=0;i<counter;i++){
                if(smetka==pole[i].getBroj()){
                    pole[i].uplata(suma);
                }
            }
            break;
        }
        case 4:{
            cout<<"Suma koja ke ja vadite i smetka:"<<endl;
            cin>>suma>>smetka;
            for(i=0;i<counter;i++){
                if(smetka==pole[i].getBroj()){
                    pole[i].isplata(suma);
                }
            }
            break;
        }
        case 5:{
            cout<<"Smetka za prikaz:"<<endl;
            cin>>smetka;
            for(i=0;i<counter;i++){
                if(smetka==pole[i].getBroj()){
                    cout<<"Na vashata smetka ima "<<pole[i].sostojba();
                    }
            }
            break;
        }
        case 6: cout<<"Kraj"; break;
        default: cout<<"Pogresen broj."<<endl;

        }
    }
    return 0;
}
