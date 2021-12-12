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


  ifstream Fichier("and_xor.dot");// ouverture du flux du fichier
  stringstream save;
  ////////////////////////////////detection de la taille du fichier
  Fichier.seekg(0, ios::end);
  int taille = Fichier.tellg();
  cout << taille <<endl;
  Fichier.seekg(0, ios::beg);
  ///////////////////////////////curseur remis au debut du fichier
  vector<Decoupage> v1; // def du vecteur de sortie pour le .dot
  char buffer1[1000]; // rempli de la saisie
  Type etiquette; // creation de l'etiquette (chaine, nombre,accoladeo...)
  int i=0; // increment du buffer1
  int ligne = 1;// increment de la ligne
  Fichier.get(buffer1[i]);

  do {

    //Fichier.get(buffer1[i]);
    if (isalpha(buffer1[i]) || buffer1[i]== '"')// si le caractère est un alpha num ou commence avec des guillemets
    {
      save<<buffer1[i];// on enregistre le caractere actuel dans le stringstream
      i++; // on incremente
      Fichier.get(buffer1[i]); // on observe le caractère suivant

      while(isalpha(buffer1[i])|| buffer1[i]== '"'|| buffer1[i]== '_') // tant qu'on a des lettres ou des guillemets  ou des tiret du bas on continue a scrutter
      {
        save<<buffer1[i];
        i++;
        Fichier.get(buffer1[i]);
      }
      while(buffer1[i]=='"')
      {
        save<<buffer1[i];
        i++;
        Fichier.get(buffer1[i]);
      }
      while(isdigit(buffer1[i])|| buffer1[i]== '"')
      {
        save<<buffer1[i];
        i++;
        Fichier.get(buffer1[i]);
      }
      etiquette = CHAINE; // tout ces cas correspondent à des chaines
      Decoupage morceau(save.str(),etiquette,ligne);// on appelle le constructeur pour un morceau à partir d'un nom, d'un type(chaine) et d'une ligne
      v1.push_back(morceau); // on stocke notre objet "morceau" dans un vecteur
      save.str("");//reinitialisation de streamstring save --> on le vide pour réccuperer le prochain etiquette
      save.clear();// on le clear
    }

    if (buffer1[i]== ' ')// detection d'un espace
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = ESPACE;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }

    if (buffer1[i]== '{')// detection de l'accoladeo
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = ACCOLADEO;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }

    if (buffer1[i]== '-')// detection de tiret du 6
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      if (buffer1[i]== '>') // detection de la fleche
      {
        save<<buffer1[i];
        i++;
        Fichier.get(buffer1[i]);
        etiquette = FLECHE;
        Decoupage morceau(save.str(),etiquette,ligne);
        v1.push_back(morceau);
        save.str("");
        save.clear();
      }
      else
      {
        cout << "erreur: caractère - non valide sans l'ajout > ligne" <<ligne <<endl;
        i++;
        Fichier.get(buffer1[i]);
        etiquette = DUMP;
        Decoupage morceau(save.str(),etiquette,ligne);
        v1.push_back(morceau);
        save.str("");
        save.clear();
      }

    }

    if (buffer1[i]== ';')
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = POINTV;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }

    if (buffer1[i]== '[')
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = CROCHET0;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }
    if (buffer1[i]== ']')
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = CROCHETC;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }

    if (buffer1[i]== '=')
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = EQUAL;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }

    if (buffer1[i]== '$')
    {
      cout << "erreur: caratctère $ non valide ligne "<< ligne<<endl;
      i++;
      Fichier.get(buffer1[i]);
      etiquette = DUMP;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();

    }
    if (buffer1[i]== '\n')
    {
      cout << "saut ligne"<<endl;
      ligne++;
      i++;
      Fichier.get(buffer1[i]);
    }
    if (buffer1[i]== '}')
    {
      cout <<"this is the end"<< endl;
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = ACCOLADEC;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }

    if (buffer1[i]== '\t')
    {
      save<<buffer1[i];
      i++;
      Fichier.get(buffer1[i]);
      etiquette = TAB;
      Decoupage morceau(save.str(),etiquette,ligne);
      v1.push_back(morceau);
      save.str("");
      save.clear();
    }
  } while(i<taille);

/////////////////////////////////////////////partie test pour l'affichage du nom, du type et de la ligne de chaque morceau
  vector<Decoupage>::iterator itr ;
  for(itr = v1.begin() ; itr != v1.end() ; ++itr)
  {
    Decoupage c = *itr;// déréférencement de l'iterateur
    cout<<c.getname()<<endl;
    cout<<c.gettype()<<endl;
    cout<<c.getline()<<endl;
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
