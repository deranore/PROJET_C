#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "MUX1.h"

using namespace std;

//Constructeur
MUX1(string _nom,vector<string> _input,string _output,string _select,unsigned int _delay=0):Comb(_nom,_input,_output,_delay),select(_select){
  cout << " Constructeur de porte MUX X vers 1" << endl;
}

~MUX1(){
  cout << " Destrcteur de porte MUX X vers 1 " << endl;
}

//Accesseur
string get_slect(){
  return select;
}
//Fonction virtuelle pure
bool calcul_output(input map(string,net)){
  bool output = 1;
  for (vector<string>::iterator index = this->input.begin(); index != this->input.end();index++){
    output &= input[*index];
  }
  return output;
}

void afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << this->get_nom() << endl;
  cout << "Porte MUX 1 sortie pour un nombre de sortie de : " << this->input.size() << endl;
  cout << "Net de sortie : " << this->get_output() << endl;
  cout << "Net d'entrée : " << this->get_input() << endl;
  cout << "Delay : " << this->get_delay() << endl;
}
