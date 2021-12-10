#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "XOR1.h"

using namespace std;

//Constructeur
XOR1::XOR1(string _nom,vector<string> _input,string _output,unsigned int _delay):Comb(_nom,_input,_output,_delay){
  cout << " Constructeur de porte XOR X vers 1 " << endl;
}

XOR1::~XOR1(){
  cout << " Destrcteur de porte XOR X vers 1 " << endl;
}

//Fonction virtuelle pure
bool XOR1::calcul_output(map<string,Net> input){
  bool output = 0;
  unsigned int i=0;
  for (vector<string>::iterator index = get_input().begin(); index != get_input().end();index++,i++){
    output ^= input[get_input()[i]].get_val();
  }
  return output;
}

void XOR1::afficher(){
  cout << "Addresse : " << this << endl;
  cout << "Nom : " << get_name() << endl;
//  cout << "Porte XOR 1 sortie pour un nombre de sortie de : " << input.size() << endl;
  cout << "Net de sortie : " << get_output() << endl;
//  cout << "Net d'entrée : " << get_input() << endl;
  cout << "Delay : " << get_delay() << endl;
}
