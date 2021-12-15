#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NET.h"


Net::Net(string _name,bool _val):name(_name),current_val(_val){
  //cout << " Constrcteur de NET " << endl ;
  index_val=0;
}
Net::~Net(){
  //cout<< " Destructeur de NET " << endl ;
}

void Net::add_val(bool new_val){
  val.push_back(new_val);
}

string Net::get_name(){
  return name;
}
vector <bool> Net::get_val(){
  return val;
}
bool Net::get_current_val(){
  return current_val;
}
void Net::set_val(unsigned int index){
  current_val=val[index];
}

void Net::afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << this->get_name() << endl;
  cout << "Index courrante : " << this->index_val << endl;
  cout << "Valeur courante : " << this->get_current_val() << endl;
  cout << "Valeur possible : " << " print (val) " << endl;
}
