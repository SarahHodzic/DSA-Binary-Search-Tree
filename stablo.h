#ifndef STABLO_H
#define STABLO_H
#include <utility>
#include<vector>
#include<iostream>
using namespace std;

template <typename Tip>
class Stablo {
    public:
    struct Cvor {
        Tip element;
        Cvor *ld, *dd, *rod;
        int brElemenataLijevoPodstablo;
        Cvor(Tip el, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr):element(el), rod(rod), ld(ld), dd(dd), brElemenataLijevoPodstablo(0){}
    };

    private:
    int n;
    Cvor *korijen;
    void Ispis(Cvor*) const;
    void InOrder(Cvor*) const;
    int Visina(Cvor*) const;

    public:
    //const iterator
    class Const_Iterator{
        protected:
            Cvor* trenutni;
            Const_Iterator(Cvor* cvor):trenutni(cvor){}
            Cvor* sljedbenik(Cvor* cvor){
                if(cvor->dd != nullptr) {
                    Cvor *trenutni = cvor->dd;
                    while(trenutni->ld != nullptr)
                        trenutni = trenutni->ld;
                    return trenutni;
                }
                Cvor* trenutni = cvor;
                while(trenutni->rod != nullptr) {
                    if(trenutni->rod->ld == trenutni)
                        return trenutni->rod;
                    if(trenutni->rod->dd == trenutni)
                        trenutni = trenutni->rod;
                }

                return nullptr;
            }
            Cvor* prethodnik(Cvor* cvor){
                if (cvor->ld != nullptr) {
                    Cvor* trenutni = cvor->ld;
                    while (trenutni->dd != nullptr)
                        trenutni = trenutni->dd;
                    return trenutni;
                }

                Cvor* trenutni = cvor;

                while (trenutni->rod != nullptr) {
                    if (trenutni->rod->dd == trenutni)
                        return trenutni->rod;
                    if (trenutni->rod->ld == trenutni)
                        trenutni = trenutni->rod;
                }

                return nullptr;
            }
        public:
            Const_Iterator(){trenutni = nullptr;}
            Tip operator*(){return trenutni->element;}
            Const_Iterator operator++(){
                Const_Iterator pok = trenutni;
                trenutni = sljedbenik(trenutni);
                return pok;
            }
            Const_Iterator operator++(int){
                trenutni = sljedbenik(trenutni);
                return trenutni;
            }
            Const_Iterator operator--(){
                Const_Iterator pok = trenutni;
                trenutni = prethodnik(trenutni);
                return pok;
            }
            Const_Iterator operator--(int){
                trenutni = prethodnik(trenutni);
                return trenutni;
            }
            friend bool operator == (Const_Iterator it1, Const_Iterator it2){
                return it1.trenutni == it2.trenutni;
            }
            friend bool operator != (Const_Iterator it1, Const_Iterator it2){
                return it1.trenutni != it2.trenutni;
            }
            friend class Stablo<Tip>;
    };

    //Iterator
    class Iterator: public Const_Iterator{
        Iterator(Cvor* cvor):Const_Iterator(cvor){}


    public:
        Iterator(){this->trenutni = nullptr;}
        Tip& operator*(){return this->trenutni->element;}
        Iterator operator++(){
            Iterator pok = this->trenutni;
            this->trenutni = this->sljedbenik(this->trenutni);
            return pok;
        }
        Iterator operator++(int){
            this->trenutni = this->sljedbenik(this->trenutni);
            return this->trenutni;
        }
        Iterator operator--(){
            Iterator pok = this->trenutni;
            this->trenutni = this->prethodnik(this->trenutni);
            return pok;
        }
        Iterator operator--(int){
            this->trenutni = this->prethodnik(this->trenutni);
            return this->trenutni;
        }

        friend class Stablo<Tip>;

    };
    //Reverse iterator

    class Reverse_iterator: public Const_Iterator{
        Reverse_iterator(Cvor* cvor):Const_Iterator(cvor){}

    public:
        Reverse_iterator(){this->trenutni = nullptr;}
        Tip& operator*(){return this->trenutni->element;}
        Reverse_iterator operator++(){
            Reverse_iterator pok = this->trenutni;
            this->trenutni = this->prethodnik(this->trenutni);
            return pok;
        }
        Reverse_iterator operator++(int){
            this->trenutni = this->prethodnik(this->trenutni);
            return this->trenutni;
        }
        Reverse_iterator operator--(){
            Reverse_iterator pok = this->trenutni;
            this->trenutni = this->sljedbenik(this->trenutni);
            return pok;
        }
        Reverse_iterator operator--(int){
            this->trenutni = this->sljedbenik(this->trenutni);
            return this->trenutni;
        }

        friend class Stablo<Tip>;

    };
        Stablo():n(0),korijen(nullptr){}
        int Size() { return n;}
        bool Empty() { return n == 0; }
        Cvor* Find(const Tip vrijednost) const;
        pair<Cvor*, bool> Insert(const Tip vrijednost);
        void Erase(const Tip vrijednost);
        void Ispis() const { Ispis(korijen); } //za testiranje
        void InOrder() const { InOrder(korijen); }
        int Visina() const { return Visina(korijen); }
        Cvor* Pocetak() const;
        Cvor* Kraj() const;
        Cvor* Sljedbenik(Cvor* cvor) const;
        Cvor* Prethodnik(Cvor* cvor) const;
        Const_Iterator Begin()const {return Pocetak();}
        Const_Iterator End() const {return nullptr;}
        Const_Iterator Zadnji() const {return Kraj();}
        Reverse_iterator RBegin(){return Kraj();}
        Reverse_iterator REnd(){return nullptr;}
        Iterator Begin(){return Pocetak();}
        Iterator End(){return nullptr;}
        Tip Korijen() {return korijen->element;}
        Tip operator[](int k)const;
        friend bool JePodskup(Stablo<Tip>& stablo1, Stablo<Tip>& stablo2){
            vector<Tip> prvoStablo;
            vector<Tip> drugoStablo;
            int prvoStabloSize = stablo1.Size();

            int drugoStabloSize = stablo2.Size();

            for(auto it = stablo1.Begin(); it != stablo1.End(); it++)
                prvoStablo.push_back(*it);

            for(auto it2 = stablo2.Begin(); it2 != stablo2.End(); it2++)
                drugoStablo.push_back(*it2);
            int manjeStablo = min(prvoStabloSize, drugoStabloSize);

            int j = 0;
            if(manjeStablo == prvoStabloSize)
            {
                for(int i = 0; i < prvoStabloSize; i++)
                {
                    if(prvoStablo[i] != drugoStablo[j])
                    {
                        j++;
                    }
                    else {i--; j++;}

                    if (j == drugoStabloSize && i < prvoStabloSize)
                    {
                        return false;
                        break;
                    }
                }
                return true;
            }
            else
            {
                for(int i = 0; i < drugoStabloSize; i++)
                {
                    if(drugoStablo[i] != prvoStablo[j])
                    {
                        j++;
                    }

                    else {i--; j++;}

                    if (j == prvoStabloSize && i < drugoStabloSize)
                    {

                        return false;
                        break;
                    }
                }

                return true;
            }
        }
};

#include "stablo.cpp"

#endif // STABLO_H
