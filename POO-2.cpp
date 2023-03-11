/*
Cerințe comune: 

--> Toate clasele vor conține obligatoriu constructori de 
inițializare, parametrizați și de copiere; 
destructor; operatorii „=”, „>>”, „<<”
supraîncărcați corespunzător, moșteniri & encapsulare  

--> Clasele derivate trebuie sa contina constructori parametrizati 
(prin care sa se evidentieze transmiterea parametrilor catre 
constructorul din clasa de baza) si destructori. 

--> În fiecare proiect vor fi ilustrate conceptele de upcasting, 
downcasting, funcții virtuale (pure – unde se consideră mai natural)

-->Utilizarea de variabile și de funcții statice

-->Tratarea exceptiilor (try – catch) 

-->Citirea informațiilor complete a n obiecte (de diferite tipuri), 
memorarea și afișarea acestora

--> Meniu interactiv 

--> Rezolvarea corectă a cerințelor suplimentare corespunzatoare 
fiecarei teme 


Tema 4.
Se dau urmatoarele clase: 

- Clasa Persoana(int id,  string nume) 

- Clasa Abonat:Persoana(string nr_telefon) 

- Clasa Abonat_Skype: Abonat (string id_skype) 

- Clasa Abonat_Skype_Romania (string adresa_mail) : Abonat_Skype 

- Clasa Abonat_Skype_Extern(string tara) : Abonat_Skype 

Sa se construiasca clasa Agenda ce contina o lista de abonati si 
sa se supraincarce operatorul [ ](indexare)care returneaza 
abonatul cu numele precizat.

*/


#include<iostream>
#include<vector>
#include<typeinfo>
#include<sstream>

using namespace std;

class Persoana
{
protected:
    int id;
    string nume;
public:
    Persoana(){};
    Persoana(int i, string n)
    {
        id=i;
        nume=n;
    };
    Persoana(const Persoana&);
    Persoana& operator=(Persoana&);
    friend istream& operator>>(istream&, Persoana&);
    friend ostream& operator<<(ostream&, Persoana&);
    virtual void citire();
    virtual void afisare();
    string get_nume(){return nume;}
    virtual ~Persoana();
};

Persoana::~Persoana(){};

istream& operator>>(istream& in, Persoana& P)
{
    in>>P.id>>P.nume;
    return in;
}

ostream& operator<<(ostream& out, Persoana& P)
{
    out<<P.id<<' '<<P.nume<<endl;
    return out;
}

void Persoana::afisare(){cout<<"Id-ul: "<<id<<endl;
                         cout<<"Numele: "<<nume<<endl;}


void Persoana::citire()
{
    int ok=0;

    while(ok==0){
        try{ cout<<"Furnizati id-ul(numar): ";
             cin>>id;
            if(id<0) throw 1;
               else ok=1;}

        catch(int x){cout<<"Id invalid. Reincercati."<<endl;} }

     int ok1=0;
     while(ok1==0)
        {try{
        cout<<"Furnizati numele abonatului: ";
        cin>>nume;
        int val=1;
        for(unsigned int i=0;i<nume.size();i++)
        {
         if(isdigit(nume[i])!=0)
            val=0;
        }
        if(val!=1) throw  1;
            else ok1=1;
        }
        catch(int x) {cout<<"Numele furnizat nu este corect introdus. Reincercati"<<endl;
                    } }
}

Persoana::Persoana(const Persoana& P)
{
    cout<<"merge"<<endl;
    id=P.id;
    nume=P.nume;
    cout<<id<<' '<<nume;
}

Persoana& Persoana::operator=(Persoana& P)
{
    cout<<"da"<<endl;
    if(this!=&P)
        {nume=P.nume;
        id=P.id;
        cout<<nume<<' '<<id<<' ';}
    return *this;
}

class Abonat: public Persoana
{

    string nr_telefon;
public:
    Abonat(){};
    Abonat(int i, string num, string nr):Persoana(i, num){nr_telefon=nr;};
    Abonat(const Abonat&);
    Abonat& operator=(Abonat&);
    friend istream& operator>>(istream&, Abonat&);
    friend ostream& operator<<(ostream&, Abonat&);
    void citire(){Persoana::citire();
                  int ok=0;
                  while(ok==0)
                  {try{
                  cout<<"Furnizati numarul de telefon: ";
                  cin>>nr_telefon;
                  int val=1;
                  for(unsigned int i=0;i<nr_telefon.size();i++)
                    {
                     if(isalpha(nr_telefon[i])!=0)
                        val=0;
                    }
                  if(val!=1) throw  1;
                     else ok=1;
                  }
                  catch(int x) {cout<<"Numarul de telefon este invalid. Reincercati"<<endl;
                                }

                }
                }
    void afisare(){Persoana::afisare();
                   cout<<"Numarul de telefon: "<<nr_telefon<<endl;}
    virtual ~Abonat();

};

Abonat::~Abonat(){};



istream& operator>>(istream& in, Abonat& A)
{
    in>>dynamic_cast<Persoana&>(A);
    in>>A.nr_telefon;
    return in;
}

ostream& operator<<(ostream& out, Abonat& A)
{
    out<<dynamic_cast<Persoana&>(A);
    out<<A.nr_telefon<<' ';
    return out;
}

Abonat& Abonat::operator=(Abonat& a)
{
    if(this!=&a)
    {
        this->Persoana::operator=(a);
        nr_telefon=a.nr_telefon;
    }
    return *this;
}

Abonat::Abonat(const Abonat& A):Persoana(A)
{
    nr_telefon=A.nr_telefon;
}


class Abonat_Skype:public Abonat
{
    string id_skype;
public:
    Abonat_Skype(){};
    Abonat_Skype(int i, string num, string nr, string id):Abonat(i, num, nr)
    {id_skype=id;}
    Abonat_Skype(const Abonat_Skype&);
    Abonat_Skype& operator=(Abonat_Skype&);
    friend istream& operator>>(istream&, Abonat_Skype&);
    friend ostream& operator<<(ostream&, Abonat_Skype&);
    void citire(){Abonat::citire();
                  cout<<"Furnizati skype id-ul: ";
                  cin>>id_skype;
                }
    void afisare(){Abonat::afisare();
                    cout<<"Skype id-ul: "<<id_skype<<endl;}
    virtual ~Abonat_Skype();



};

Abonat_Skype::~Abonat_Skype(){};

istream& operator>>(istream& in, Abonat_Skype& AS)
{
    in>>dynamic_cast<Abonat&>(AS);
    in>>AS.id_skype;
    return in;
}

ostream& operator<<(ostream& out, Abonat_Skype& AS)
{
    out<<dynamic_cast<Abonat&>(AS);
    out<<AS.id_skype<<' ';
    return out;
}

Abonat_Skype& Abonat_Skype::operator=(Abonat_Skype& AS)
{
    if(this!=&AS)
    {
        this->Abonat::operator=(AS);
        id_skype=AS.id_skype;
    }
    return *this;
}

Abonat_Skype::Abonat_Skype(const Abonat_Skype& AS):Abonat(AS)
{
    id_skype=AS.id_skype;
}


class Abonat_Skype_Romania: public Abonat_Skype
{
    string adresa_mail;
public:
    Abonat_Skype_Romania(){};
    Abonat_Skype_Romania(int i, string num, string nr, string id, string adresa):Abonat_Skype(i, num, nr, id)
    {adresa_mail=adresa;};
    Abonat_Skype_Romania(const Abonat_Skype_Romania&);
    friend istream& operator>>(istream&, Abonat_Skype_Romania&);
    friend ostream& operator<<(ostream&, Abonat_Skype_Romania&);
    void citire(){Abonat_Skype::citire();
                  cout<<"Furnizati adresa de mail: ";
                  cin>>adresa_mail;}
    void afisare(){Abonat_Skype::afisare();
                  cout<<"Adresa de mail: "<<adresa_mail<<endl;}
    ~Abonat_Skype_Romania();

};

Abonat_Skype_Romania::~Abonat_Skype_Romania(){};

istream& operator>>(istream& in, Abonat_Skype_Romania& ASR)
{
    in>>dynamic_cast<Abonat_Skype&>(ASR);
    in>>ASR.adresa_mail;
    return in;
}

ostream& operator<<(ostream& out, Abonat_Skype_Romania& ASR)
{
    out<<dynamic_cast<Abonat_Skype&>(ASR);
    out<<ASR.adresa_mail<<' ';
    return out;
}

Abonat_Skype_Romania::Abonat_Skype_Romania(const Abonat_Skype_Romania& ASR):Abonat_Skype(ASR)
{
    adresa_mail=ASR.adresa_mail;
}


class Abonat_Skype_Extern: public Abonat_Skype
{
    string tara;
public:
    Abonat_Skype_Extern(){};
    Abonat_Skype_Extern(int i, string num, string nr, string id, string s):Abonat_Skype(i, num, nr, id)
    {tara=s;};
    Abonat_Skype_Extern(const Abonat_Skype_Extern&);
    Abonat_Skype_Extern& operator=(Abonat_Skype_Extern&);
    friend istream& operator>>(istream&, Abonat_Skype_Extern&);
    friend ostream& operator<<(ostream&, Abonat_Skype_Extern&);
    void citire(){Abonat_Skype::citire();
                  int ok=0;
                  while(ok==0)
                  {try{
                   cout<<"Furnizati tara de apartanenta a abonatului: ";
                  cin>>tara;
                  int val=1;
                  for(unsigned int i=0;i<tara.size();i++)
                    {
                     if(isdigit(tara[i])!=0)
                        val=0;
                    }
                  if(val!=1) throw  1;
                     else ok=1;
                  }
                  catch(int x) {cout<<"Tara furnizata nu este corect introdusa. Reincercati"<<endl;
                                }

                }
                }


    void afisare(){Abonat_Skype::afisare();
                   cout<<"Tara: "<<tara<<endl;}
    ~Abonat_Skype_Extern();

};

Abonat_Skype_Extern::~Abonat_Skype_Extern(){};

istream& operator>>(istream& in, Abonat_Skype_Extern& ASE)
{
    in>>dynamic_cast<Abonat_Skype&>(ASE);
    in>>ASE.tara;
    return in;
}

ostream& operator<<(ostream& out, Abonat_Skype_Extern& ASE)
{
    out<<dynamic_cast<Abonat_Skype&>(ASE);
    out<<ASE.tara<<' ';
    return out;
}

Abonat_Skype_Extern& Abonat_Skype_Extern::operator=(Abonat_Skype_Extern& ASE)
{
    if(this!=&ASE)
    {
        this->Abonat_Skype::operator=(ASE);
        tara=ASE.tara;
    }
    return *this;

}

Abonat_Skype_Extern::Abonat_Skype_Extern(const Abonat_Skype_Extern& ASE):Abonat_Skype(ASE)
{
    tara=ASE.tara;
}


class Agenda:public Abonat
{
    int nr_abonati;
    vector<Abonat*> v;
public:
    Agenda(){};
    void creare_lista();
    string& operator[](string);
    void destruct();
    void afisare_lista();
    ~Agenda();
};

Agenda::~Agenda(){};

string &Agenda::operator[](string nume)
{
    try{
        if(v.empty()==true) throw 1;
        else
   {
       vector<Abonat*>::iterator p;
    int ok=0;
    for(p=v.begin();p!=v.end();p++)
        {
         if((**p).get_nume()==nume)
          {(**p).afisare();
          ok=1;}
        }
    if(ok==0) cout<<"Abonatul nu exista."<<endl;
   } }
  catch(int x){cout<<"Agenda de abonati nu contine niciun abonat. Va rugam adaugati persoane in agenda."<<endl;}


}



void Agenda::creare_lista()
{   cout<<"Furnizati numarul de abonati pe care doriti sa ii adaugati in agenda"<<endl;
    cin>>nr_abonati;
  for(int i=1;i<=nr_abonati;i++)
    {cout<<"Selectati tipul de persoana de adaugat in Agenda."<<endl;
    cout<<"1-Abonat 2-Abonat Skype 3- Abonat Skype din Romania 4-Abonat Skype din strainatate"<<endl;
    int op;
    cin>>op;
    switch(op)
    {
        case 1: {Abonat *A = new Abonat();
                 A->citire();
                 v.push_back(A);
                 break;
                 }
        case 2: {Abonat_Skype *AS = new Abonat_Skype();
                 (*AS).citire();
                 v.push_back(AS);
                 break;
                 }
        case 3: {Abonat_Skype_Romania *ASR = new Abonat_Skype_Romania();
                 ASR->citire();
                 v.push_back(ASR);
                 break;
                 }
        case 4: {Abonat_Skype_Extern *ASE = new Abonat_Skype_Extern();
                 ASE->citire();
                 v.push_back(ASE);
                 break;
                 }
    }

    }
    cout<<endl;

}

void Agenda::afisare_lista()
{   try{
        if(v.empty()==true) throw 1;
        else{ cout<<"Lista contine: ";
            vector<Abonat*>::iterator p;
            for(p=v.begin();p!=v.end();p++)
                (**p).afisare();
            }}
     catch(int x){cout<<"Agenda de abonati nu contine niciun abonat. Va rugam adaugati persoane in agenda."<<endl;}
}

void Agenda::destruct()
{
    if(v.empty()!=true)
       { vector<Abonat*>::iterator p;
         for(p=v.begin();p!=v.end();p++)
                delete (*p);
        }
}


int main()
{
  Agenda a;
  int optiune=0;
  while (true)
  {
      if(optiune==0)
      {
          cout<<"Selectati optiunea dorita!"<<endl;
          cout<<"1. Adaugare abonati"<<endl;
          cout<<"2. Afisare abonati"<<endl;
          cout<<"3. Gasire abonat dupa nume"<<endl;
          cout<<"4. Sfarsit program"<<endl;
          cout<<"Optiune: ";
          cin>>optiune;
      }

      if(optiune==1)
      {
          a.creare_lista();
          cout<<"Pentru revenire la meniu, apasati 0. Pentru adaugarea unor noi abonati, apasati 1."<<endl;
          cout<<"Optiune: ";
          cin>>optiune;
      }

      if(optiune==2)
      {
          a.afisare_lista();
          cout<<"Pentru revenire la meniu, apasati 0. Pentru adaugarea abonatilor, apasati 1."<<endl;
          cout<<"Optiune: ";
          cin>>optiune;
      }

      if(optiune==3)
      {
          cout<<"Furnizati numele abonatului: ";
          string s;
          cin>>s;
          a.operator[](s);
          cout<<"Pentru revenire la meniu, apasati 0. Pentru gasirea unui  nou abonat, apasati 3."<<endl;
          cin>>optiune;
      }

      if(optiune==4)
      {
          a.destruct();
          break;
      }
  }
}



