#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "OR1.h"

using namespace std;

//Constructeur
OR1::OR1(string _nom,vector<string> _input,string _output,unsigned int _delay):Comb(_nom,_input,_output,_delay){
  cout << " Constructeur de porte OR X vers 1" << endl;
}

OR1::~OR1(){
  cout << " Destrcteur de porte OR X vers 1 " << endl;
}

//Fonction virtuelle pure
bool OR1::calcul_output(map<string,Net> input){
  bool output = 0;
  unsigned int i = 0;
  for (vector<string>::iterator index = get_input().begin(); index != get_input().end();index++,i++){
    output |= input[get_input()[i]].get_current_val();
  }
  return output;
}

void OR1::afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << this->get_name() << endl;
  //cout << "Porte OR 1 sortie pour un nombre de sortie de : " << this->input.size() << endl;
  cout << "Net de sortie : " << this->get_output() << endl;
  //cout << "Net d'entrée : " << this->get_input() << endl;
  cout << "Delay : " << this->get_delay() << endl;
}
