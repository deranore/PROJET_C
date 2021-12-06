#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "OR1.h"

using namespace std;

//Constructeur
OR1(string _nom,vector<string> _input,string _output,unsigned int _delay=0):Comb(_nom,_input,_output,_delay){
  cout << " Constructeur de porte OR X vers 1" << endl;
}

~OR1(){
  cout << " Destrcteur de porte OR X vers 1 " << endl;
}

//Fonction virtuelle pure
bool calcul_output(input map(string,net)){
  bool output = 0;
  for (vector<string>::iterator index = this->input.begin(); index != this->input.end();index++){
    output |= input[*index];
  }
  return output;
}

void afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << this->get_nom() << endl;
  cout << "Porte OR 1 sortie pour un nombre de sortie de : " << this->input.size() << endl;
  cout << "Net de sortie : " << this->get_output() << endl;
  cout << "Net d'entrée : " << this->get_input() << endl;
  cout << "Delay : " << this->get_delay() << endl;
}
