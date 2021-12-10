#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NET.h"


Net::Net(string _name,bool _val):name(_name),val(_val){
  //cout << " Constrcteur de NET " << endl ;
}
Net::~Net(){
  //cout<< " Destructeur de NET " << endl ;
}
string Net::get_name(){
  return name;
}
bool Net::get_val(){
  return val;
}
void Net::set_val(bool valeur){
  val=valeur;
}

void Net::afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << this->get_name() << endl;
  cout << "Valeur : " << this->get_val() << endl;
}
