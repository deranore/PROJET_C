#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NOT1.h"

using namespace std;

//Constructeur
NOT1::NOT1(string _nom,vector<string> _input,string _output,unsigned int _delay):Comb(_nom,_input,_output,_delay){
  cout << " Constructeur de porte NOT 1 vers 1" << endl;
}

NOT1::~NOT1(){
  cout << " Destrcteur de porte NOT 1 vers 1 " << endl;
}

//Fonction virtuelle pure
bool NOT1::calcul_output(map<string,Net> input){
  bool output = 1;
  unsigned int i=0;
  for (vector<string>::iterator index = get_input().begin(); index != get_input().end();index++,i++){
    output ^= input[get_input()[i]].get_val();
  }
  return output;
}

void NOT1::afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << this->get_name() << endl;
  cout << "Porte NOT 1 sortie pour un nombre de sortie de : 1 "<< endl;
  cout << "Net de sortie : " << this->get_output() << endl;
  //cout << "Net d'entrée : " << this->get_input() << endl;
  cout << "Delay : " << this->get_delay() << endl;
}
