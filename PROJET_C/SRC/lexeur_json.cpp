using namespace std;
#include "decoupage.h"
#include <algorithm>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main () {



  ifstream Fichier2("Inputs.json");// ouverture du flux du Fichier2
  stringstream save2;
  ////////////////////////////////detection de la taille du Fichier2
  Fichier2.seekg(0, ios::end);
  int taille2 = Fichier2.tellg();
  cout << taille2 <<endl;
  Fichier2.seekg(0, ios::beg);
  ///////////////////////////////curseur remis au debut du Fichier2
  vector<Decoupage> v2; // def du vecteur de sortie pour le .dot
  char buffer2[1000]; // rempli de la saisie
  Type etiquette2; // creation de l'etiquette (chaine, nombre,accoladeo...)
  int i2=0; // increment du buffer2
  int ligne2 = 1;// increment de la ligne
  int erreur2;
  Fichier2.get(buffer2[i2]);

  do {

    if (buffer2[i2]== '\'')// si le caractère commence par des guillemets
    {
      save2<<buffer2[i2];// on enregistre le caractere actuel dans le stringstream
      i2++; // on incremente
      Fichier2.get(buffer2[i2]); // on observe le caractère suivant

      while(isalpha(buffer2[i2])|| buffer2[i2]== '_') // tant qu'on a des lettres ou des guillemets  ou des tiret du bas on continue a scrutter
      {
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        while(isdigit(buffer2[i2])|| buffer2[i2]=='\'')//tant que c'est un nombre ou une entrecote de fin
        {
          save2<<buffer2[i2];
          i2++;
          Fichier2.get(buffer2[i2]);
        }
        etiquette2 = NOM;
      }


      while(isdigit(buffer2[i2])|| buffer2[i2]=='\''|| buffer2[i2]=='.')
      {
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = NOMBRE;
      }
      Decoupage morceau2(save2.str(),etiquette2,ligne2);// on appelle le constructeur pour un morceau à partir d'un nom, d'un type(chaine) et d'une ligne
      v2.push_back(morceau2); // on stocke notre objet "morceau" dans un vecteur
      save2.str("");//reinitialisation de streamstring save --> on le vide pour réccuperer le prochain etiquette
      save2.clear();// on le clear
    }



    if (isalpha(buffer2[i2]))// si le caractère est un alpha num
    {
      save2<<buffer2[i2];// on enregistre le caractere actuel dans le stringstream
      i2++; // on incremente
      Fichier2.get(buffer2[i2]); // on observe le caractère suivant

      while(isalpha(buffer2[i2])|| buffer2[i2]== '_') // tant qu'on a des lettres ou des guillemets  ou des tiret du bas on continue a scrutter
      {
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
      }
      cout << "chaine"<<endl;
      etiquette2 = CHAINE; // tout ces cas correspondent à des chaines
      Decoupage morceau2(save2.str(),etiquette2,ligne2);// on appelle le constructeur pour un morceau à partir d'un nom, d'un type(chaine) et d'une ligne
      v2.push_back(morceau2); // on stocke notre objet "morceau" dans un vecteur
      save2.str("");//reinitialisation de streamstring save --> on le vide pour réccuperer le prochain etiquette
      save2.clear();// on le clear
    }



    if (buffer2[i2]== ' ')// detection d'un espace
    {
      cout << "space"<<endl;
      //save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = ESPACE;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '{')// detection de l'accoladeo
    {
      cout << "accoo"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = ACCOLADEO;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== ',')
    {
      cout << "virg"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = VIRGULE;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '[')
    {
      cout << "crocheto"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = CROCHET0;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }
    if (buffer2[i2]== ']')
    {
      cout << "crochetc"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = CROCHETC;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== ':')
    {
      cout << "pointpoint"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = POINTPOINT;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '\n')
    {
      cout << "return"<<endl;
      ligne2++;
      i2++;
      Fichier2.get(buffer2[i2]);
    }

    if (buffer2[i2]== '}')
    {
      cout << "crochetc"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = ACCOLADEC;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '\t')
    {
      cout << "tab"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = TAB;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }
  } while(i2<100);

/////////////////////////////////////////////partie test pour l'affichage du nom, du type et de la ligne de chaque morceau
  vector<Decoupage>::iterator itr2 ;
  for(itr2 = v2.begin() ; itr2 != v2.end() ; ++itr2)
  {
    Decoupage c2 = *itr2;// déréférencement de l'iterateur
    cout<<c2.getname()<<endl;
    cout<<c2.gettype()<<endl;
    cout<<c2.getline()<<endl;
  }
