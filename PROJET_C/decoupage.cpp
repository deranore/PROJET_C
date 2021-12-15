#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include "DECOUPAGE.h"

using namespace std;
//enum TOTE {CHAINE, NOMBRE, ACCOLADEO, ACCOLADEC, CROCHET0, CROCHETC, ESPACE, FLECHE, POINTV, EQUAL, DUMP, TAB} ;




//Verre::Verre() {// Ceci est un constructeur
//  cout << "Cstr par défaut d'un verre "<<endl;
//  this->contenance = 20; // this pointe l'objet qui est en train d'être construit (créé)
//  this->quantite = 0;
//}

Decoupage::Decoupage (string name,Type poss,int nmbline) // constructeur pour encaspulation
{
  this->nom = name;
  this->type = poss;
  this->line =nmbline;
}

string Decoupage::getname() const
{
  //cout<<"il reste"<<this->contenance-this->quantite<<"de libre dans le verre"<<endl;
  return this->nom;
}

Type Decoupage::gettype() const
{
  //cout<<"il reste"<<this->contenance-this->quantite<<"de libre dans le verre"<<endl;
  return this->type;
}

int Decoupage::getline() const
{
  //cout<<"il reste"<<this->contenance-this->quantite<<"de libre dans le verre"<<endl;
  return this->line;
}



Decoupage::~Decoupage() {//ceci est un desctructeurs
  //cout << "Destructeur actif "<<endl;
  // Dans ce destructeur, si besoin, on pourrait fermer un fichier, nettoyer des choses.
}
