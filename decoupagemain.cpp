#include "decoupage.h"
#include <iostream>
#include<algorithm>
#include <list>
using namespace std;

int main()
{
  int nmbline=2;
  string name = "patata";
  string typede = "chaine";
  string recup1;
  string recup2;
  int recup3;
//
      Decoupage first("patata","chaine",2);// on appelle le constructeur pour créer les diff verres


      //recup1=first.getname();
      //recup2=first.gettype();
      //recup3=first.getline();

      //cout <<recup1<< recup2 <<recup3<<endl;

      list<Decoupage> l;
      l.push_back(first) ;
      //l.push_back(Decoupage first("patata","chaine",2)) ;

      list<Decoupage>::iterator itr ;
      for(itr = l.begin() ; itr != l.end() ; ++itr) {
        // déréférencement de l'iterateur
        Decoupage c = *itr ;
        cout<<c.getname()<<endl; ;
        cout<<c.gettype()<<endl; ;
        cout<<c.getline()<<endl; ;

      }

      // while(eau.getVolumeVide()!=eau.contenance)


  return 0;
}
