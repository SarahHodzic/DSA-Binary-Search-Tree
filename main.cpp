#include <iostream>
#include "stablo.h"
using namespace std;

int main() {

    Stablo<int> s;
    s.Insert(20);
    s.Insert(50);
    s.Insert(10);
    s.Insert(30);
    s.Insert(40);
    s.Insert(0);
    s.Insert(60);
    s.Insert(35);
    s.Insert(15);
    s.Insert(17);
    s.Insert(32);

    Stablo<int> s1;
    s1.Insert(20);
    s1.Insert(17);
    s1.Insert(40);
    cout<<"Da li je podskup: ";
    cout<<JePodskup(s,s1)<<endl;

    for(int i = 0; i < s.Size(); i++){

        cout<<s[i]<<" ";
    }
    cout<<endl;


    cout<<"Ispis sa iteratorima: "<<endl;
    for(Stablo<int>::Iterator it = s.Begin(); it != s.End(); ++it)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

    for(Stablo<int>::Reverse_iterator it = s.RBegin(); it != s.REnd(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

    s.Erase(20);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;

    s.Erase(30);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;

    s.Erase(10);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(40);
    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(17);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(35);

    for(int i = 0; i < s.Size(); i++){

        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(50);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(15);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(0);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(60);

    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(50);
    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;

    s.Insert(100);
    for(int i = 0; i < s.Size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s.Erase(32);

    for(int i = 0; i < s.Size(); i++){

        cout<<s[i]<<" ";
    }
    cout<<endl;


}
