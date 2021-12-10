using namespace std;
#include "decoupage.h"
#include <algorithm>
#include <list>
#include <iostream> // inclusion du header de la librairie C++ iostream (Input Output stream)
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>



int main () {

  ifstream monFlux("and_xor.dot");
  stringstream key;
  int l=0;
  char fleche1 ='-';
  char fleche2 ='>';
  char endline =';';
  char returnline ='\n';
  char space = ' ';
  //char tab = '0x09';
  //cout << "Tapez un chemin : "; cin >> chemin;
  monFlux.seekg(0, ios::end);
  int taille = monFlux.tellg();
  cout << taille <<endl;
  monFlux.seekg(0, ios::beg);
  vector<string> v(2); // def du vecteur de sortie pour le .dot
  vector<Decoupage> v1;
  char buffer1[300]; // rempli de la saisie
  int b=0;




  Type mot;




  int i=0;
  int ligne = 1;
  int erreurlexeur=0;
  bool end=0;
  monFlux.get(buffer1[i]);

  do {

    //monFlux.get(buffer1[i]);
    if (isalpha(buffer1[i]) || buffer1[i]== '"')// si c'esrt un alpha num
    {

      key<<buffer1[i];
      //v.push_back(key.str());
      i++;
      monFlux.get(buffer1[i]);

      while(isalpha(buffer1[i])|| buffer1[i]== '"'|| buffer1[i]== '_')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);
      }
      while(buffer1[i]=='"')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);
      }
      while(isdigit(buffer1[i])|| buffer1[i]== '"')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);
      }
      mot = CHAINE;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }

    if (buffer1[i]== ' ')
    {
      //cout << "jai vu un espace" <<endl;
      i++;
      monFlux.get(buffer1[i]);/////
      mot = ESPACE;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }

    if (buffer1[i]== '{')
    {
      key<<buffer1[i];
      i++;
      //ligne++;
      monFlux.get(buffer1[i]);////
      mot = ACCOLADEO;
      //v.push_back(key.str());
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      key.str("");//reinit
      key.clear();
    }

    if (buffer1[i]== '-')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);
      if (buffer1[i]== '>')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);////////
        //v.push_back(key.str());
        mot = FLECHE;
        Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
        v1.push_back(first);
        key.str("");//reinit
        key.clear();
      }
      else
      {
        cout << "erreur: caractère - non valide sans l'ajout > ligne" <<ligne <<endl;
        i++;
        monFlux.get(buffer1[i]);/////
        //v.push_back(key.str());
        mot = DUMP;
        Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
        v1.push_back(first);
        key.str("");//reinit
        key.clear();
      }

    }

    if (buffer1[i]== ';')
    {
      //ligne++;
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);////////
      mot = POINTV;
      //v.push_back(key.str());
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      key.str("");//reinit
      key.clear();
    }

    if (buffer1[i]== '[')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);//////
      mot = CROCHET0;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }
    if (buffer1[i]== ']')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);///////
      mot = CROCHETC;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }

    if (buffer1[i]== '=')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);//////
      mot = EQUAL;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }

    if (buffer1[i]== '$')
    {
      cout << "erreur: caratctère $ non valide ligne "<< ligne<<endl;
      i++;
      monFlux.get(buffer1[i]);////////
      mot = DUMP;
      erreurlexeur=2;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();

    }
    if (buffer1[i]== '\n')
    {
      cout << "saut ligne"<<endl;
      ligne++;
      i++;
      monFlux.get(buffer1[i]);////////
    }
    if (buffer1[i]== '}')
    {
      cout <<"this is the end"<< endl;
      key<<buffer1[i];
      i++;
      //ligne++;
      monFlux.get(buffer1[i]);//////
      mot = ACCOLADEC;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
      end=1;
    }

    if (buffer1[i]== '\t')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);//////
      mot = TAB;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
      end=1;
    }



  } while(i<taille);

        vector<Decoupage>::iterator itr ;
        for(itr = v1.begin() ; itr != v1.end() ; ++itr)
        {
          // déréférencement de l'iterateur
          Decoupage c = *itr;
          cout<<c.getname()<<endl;
          cout<<c.gettype()<<endl;
          cout<<c.getline()<<endl;

        //switch(erreurlexeur){
          //case 1 :cout << "erreur 1: caractère - non valide sans l'ajout > ligne" <<ligne <<endl;<< "erreur 1:"; // prints "1"
            // break;       // and exits the switch
          //case 2 : cout << '2';
            // break;



            //switch(c.gettype())
            //{
              //case 0: cout <<"c'est une chaine"<<endl;
                      //if (c.getname()=="digraph")
                      //{
                        //cout<< "bingo bg" <<endl;
                      //}
                      //else {cout<< "c'est un nom"<<endl;}
                      //break;

              //case 2: cout <<"c'est une accolade ouvrante"<<endl;
                      //break;
              //case 2: cout <<"c'est une accolade ouvrante"<<endl;
                      //break;
              //case 3: cout <<"c'est une accolade fermante"<<endl;
                      //break;
              //case 1 :cout << "erreur 1: caractère - non valide sans l'ajout > ligne" <<ligne <<endl;<< "erreur 1:"; // prints "1"
                // break;       // and exits the switch
              //case 2 : cout << '2';
                // break;

            }


    }

  //cout << i << endl;
  //for(int v=0; v<300; ++v) // reinit du tab buffer2
  //{
  //  buffer1[v]= ' ';
  //}








  // int i = 0;
  // do {
  //   cout << i << "\n";
  //   i++;
  // }
  // while (i < 5);
