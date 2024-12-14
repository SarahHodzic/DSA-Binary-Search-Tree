#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include <iostream>
#include <vector>

using namespace std;
template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Find(const Tip vrijednost) const {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
       if(trenutni->element == vrijednost)
         return trenutni;
       if(vrijednost < trenutni->element)
            trenutni = trenutni->ld;
       else trenutni = trenutni->dd;
    }
    return nullptr;
}

template <typename Tip>
pair<typename Stablo<Tip>::Cvor*, bool> Stablo<Tip>::Insert(const Tip vrijednost) {

    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr) {
       if(trenutni->element == vrijednost)
         return {trenutni, false};
       prethodni = trenutni;
       if(vrijednost < trenutni->element){
            trenutni->brElemenataLijevoPodstablo+=1;
            trenutni = trenutni->ld;
       }
       else trenutni = trenutni->dd;
    }

    Cvor *novi = new Cvor(vrijednost, prethodni);
    if(korijen == nullptr) {
        korijen = novi;
    }
    else {
        if(prethodni ->element < novi->element)
            prethodni->dd = novi;
        else prethodni->ld = novi;
    }
    n++;
    return {novi, true};
}

template <typename Tip>
void Stablo<Tip>::Ispis(Cvor* cvor) const {
    cout<<"Vrijednost: "<<cvor->element;
    if(cvor->ld != nullptr)
        cout<<" Lijevo dijete: "<<cvor->ld->element;
    if(cvor->dd != nullptr)
        cout<<" Desno dijete: "<<cvor->dd->element;
    cout<<endl;
    if(cvor->ld != nullptr)
        Ispis(cvor->ld);
    if(cvor->dd != nullptr)
        Ispis(cvor->dd);
}

template <typename Tip>
void Stablo<Tip>::InOrder(Cvor* cvor) const {
   if(cvor == nullptr) return;
   InOrder(cvor->ld);
   cout<<cvor->element<<" ";
   InOrder(cvor->dd);
}

template <typename Tip>
int Stablo<Tip>::Visina(Cvor* cvor) const {
    if(cvor == nullptr)
        return -1;
    return max(Visina(cvor->ld), Visina(cvor->dd)) + 1;

}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Pocetak() const {
    if(korijen == nullptr)
        return korijen;
    Cvor *trenutni = korijen;
    while(trenutni->ld != nullptr)
        trenutni = trenutni->ld;
    return trenutni;

}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Kraj() const{
    if(korijen == nullptr)
        return korijen;
    Cvor *trenutni = korijen;
    while(trenutni->dd != nullptr)
        trenutni = trenutni->dd;
    return trenutni;

}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Sljedbenik(Stablo<Tip>::Cvor* cvor) const {
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

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Prethodnik(Stablo<Tip>::Cvor* cvor) const {
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


template <typename Tip>
void Stablo<Tip>::Erase(const Tip vrijednost) {
    Cvor* cvor = Find(vrijednost);
    Cvor* pomocni = cvor;
    if(cvor == nullptr) return;

    if(cvor->ld == nullptr && cvor->dd == nullptr) { //ako je list
        if(cvor->rod == nullptr) //ako je korijen
           korijen = nullptr;
        else {
            //Cvor* pomocni = cvor;
            while(pomocni->rod != nullptr){

            if(pomocni->rod->ld == pomocni)
                {
                    pomocni->rod->brElemenataLijevoPodstablo--;
                }
            pomocni = pomocni->rod;
            }
            if(cvor->rod->ld == cvor){
                cvor->rod->ld = nullptr;
            }
            else cvor->rod->dd = nullptr;


        }

    }
    else if(cvor->ld == nullptr) { //ako nema lijevo dijete
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) //ako je korijen
           korijen = cvor->dd;
        else {
                while(pomocni->rod != nullptr){

            if(pomocni->rod->ld == pomocni)
                {
                    pomocni->rod->brElemenataLijevoPodstablo--;
                }
            pomocni = pomocni->rod;
            }
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }
    else if(cvor->dd == nullptr) { //ako nema desno dijete
        cvor->ld->rod = cvor->rod;
        if(cvor->rod == nullptr) //ako je korijen
           korijen = cvor->ld;
        else {
                while(pomocni->rod != nullptr){

            if(pomocni->rod->ld == pomocni)
                {
                    pomocni->rod->brElemenataLijevoPodstablo--;
                }
            pomocni = pomocni->rod;
            }
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->ld;
            else cvor->rod->dd = cvor->ld;
        }
    }
    else { //ako ima oba djeteta
        Cvor* sljedbenik = Sljedbenik(cvor);
        Cvor* pomocni1 = sljedbenik;
        sljedbenik->ld = cvor->ld;
        cvor->ld->rod = sljedbenik;
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr){ //ako je korijen
           korijen = cvor->dd;
           sljedbenik->brElemenataLijevoPodstablo+=pomocni->brElemenataLijevoPodstablo;

           while(pomocni1->rod != nullptr){
            if(pomocni1->rod->ld == pomocni1)
                {
                    pomocni1->rod->brElemenataLijevoPodstablo+=cvor->dd->brElemenataLijevoPodstablo;
                }

            pomocni1 = pomocni1->rod;
            }
        }
        else {
                bool iznad_obrisanog = false;
    sljedbenik->brElemenataLijevoPodstablo+=pomocni->brElemenataLijevoPodstablo;
    if(cvor->rod->ld == cvor){

                cvor->rod->ld = cvor->dd;
                }
            else cvor->rod->dd = cvor->dd;
        while(pomocni1->rod != nullptr){

            if(pomocni->rod == pomocni1->rod) iznad_obrisanog = true;

            if(pomocni1->rod->ld == pomocni1 && !iznad_obrisanog)
                {

                    pomocni1->rod->brElemenataLijevoPodstablo+=pomocni->brElemenataLijevoPodstablo;
                }
                else if(pomocni1->rod->ld == pomocni1 && iznad_obrisanog)
                    {
                    pomocni1->rod->brElemenataLijevoPodstablo--;
                }
            pomocni1 = pomocni1->rod;
            }


        }


    }


    delete cvor;
    n--;
}

template <typename Tip>
Tip Stablo<Tip>::operator[](int k) const {
    if(korijen == nullptr)
        return 0;
    Cvor* cvor = korijen;
    int count1 = cvor->brElemenataLijevoPodstablo;
    while(cvor != nullptr)
    {

        if(k == count1)
            return cvor->element;
        else if(k < count1)
            cvor = cvor->ld;
        else
        {
            k = k - count1 - 1;
            cvor = cvor->dd;
        }
        count1 = cvor->brElemenataLijevoPodstablo;
    }

}


#endif // STABLO_CPP
