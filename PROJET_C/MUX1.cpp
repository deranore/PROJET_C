#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "MUX1.h"

using namespace std;

//Constructeur
MUX1::MUX1(string _nom,vector<string> _input,string _output,vector<string> _select,unsigned int _delay):Comb(_nom,_input,_output,_delay),select(_select){
  cout << " Constructeur de porte MUX X vers 1" << endl;
}

MUX1::~MUX1(){
  cout << " Destrcteur de porte MUX X vers 1 " << endl;
}

//Accesseur
vector<string> MUX1::get_select(){
  return this->select;
}
//Fonction virtuelle pure
bool MUX1::calcul_output(map<string,Net> input){
  bool output = 1;
  unsigned int selector=0;
  int i=0;

  for (vector<string>::iterator index = this->select.begin(); index != this->select.end();index++){
    selector=input[*index].get_current_val()<<i;
    i++;
  }
  output = input[get_input()[selector]].get_current_val();

  return output;
}

void MUX1::afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << this->get_name() << endl;
  //cout << "Porte MUX 1 sortie pour un nombre d'entrée de : " << this->input.size() << endl;
  cout << "Net de sortie : " << this->get_output() << endl;
  //cout << "Net d'entrée : " << this->get_input() << endl;
  cout << "Delay : " << this->get_delay() << endl;
}
