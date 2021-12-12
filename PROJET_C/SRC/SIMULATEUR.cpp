#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "SIMULATEUR.h"

using namespace std;

Simulateur::Simulateur(){
  cout << " Constructeur de simulateur "
}

void Simulateur::obtain_url(){
  cout << endl << "-  url du fichier dot :  ";
  cin >> url_dot;
  cout << endl << endl << "-  url du fichier json :  ";
  cin >> url_json;
}

bool Simulateur::url_valid(){

}

string Simulateur::get_url_json(){
  return url_json;
}
string Simulateur::get_url_json(){
  return url_dot;
}

*Net Simulateur::get_input(string nom){
  if(input.find(nom)==(input.end)){
    cout << " Élement inconnu ";
    return nullptr;
  }
  else{
    return &input[nom];
  }
}

*Net Simulateur::get_output(string nom){
  if(output.find(nom)==(output.end)){
    cout << " Élement inconnu ";
    return nullptr;
  }
  else{
    return &output[nom];
  }
}

*Gate Simulateur::get_gate(string nom){
  if(gate.find(nom)==(gate.end)){
    cout << " Élement inconnu ";
    return nullptr;
  }
  else{
    return &gate[nom];
}

bool Simulateur::add_input(*Net i){
  if(input.find(*i.get_name())!=(input.end)){
    cout << " Élement déja présent ";
    return 0;
  }
  else{
    input[*i.get_name()]=i;
  }
  return 1;
}

bool Simulateur::add_output(*Net o){
  if(input.find(*o.get_name())!=(input.end)){
    cout << " Élement déja présent ";
    return 0;
  }
  else{
    output[*o.get_name()]=o;
  }
  return 1;
}

bool Simulateur::add_gate(*Gate g){
  if(gate.find(*g.get_name())!=(input.end)){
    cout << " Élement déja présent ";
    return 0;
  }
  else{
    gate[*g.get_name()]=i;
  }
  return 1;
}

void Simulateur::set_input(unsigned int index){
  for(map<string,*Net>::iterator it = input.begin(); it != input.end(); ++it){
    if(*(it->first).find("-") == string::npos){
      *(it->second).set_val(index);
    }
  }
}

void Simulateur::set_output(string nom,bool val){
  if(output.find(nom)==(input.end)){
    cout << " Élement inconnu ";
    return 0;
  }
  else{
    output[nom].add_val(val);
  }
  return 1;
}

vector<Decoupage> Simulateur::lexeur_dot ();
int Simulateur::parsseur_dot (vector<Decoupage> dot);
vector<Decoupage> Simulateur::lexeur_json ();
int Simulateur::parsseur_json (vector<Decoupage> json);
void Simulateur::err_parssing_dot(*Decoupage err_w);
void Simulateur::err_parssing_json(*Decoupage err_w);


int Simulateur::Kernel();
void Simulateur::err_simulation(*Gate err_g,*Net err_n);

void Simulateur::print(){
  cout << endl << " ___________________________________________________________ "<< endl;
  cout << "Simulateur : " << endl ;
  cout << " - Adresse : " << this << endl ;
  cout << " - URL du JSON : " << url_json << endl;
  cout << " - URL du DOT : " << url_dot << endl;
  cout << " - Entree : " << endl;
  for(map<string,*Net>::iterator it = input.begin(); it != input.end(); ++it){
    cout <<" [ "<< *(it->second).afficher() <<" ] "<< endl ;
  }
  cout << " - Sortie : " << endl;
  for(map<string,*Net>::iterator it = output.begin(); it != output.end(); ++it){
    cout <<" [ "<< *(it->second).afficher() <<" ] "<< endl ;
  }
  cout << " - Porte : " << endl;
  for(map<string,*Net>::iterator it = gate.begin(); it != gate.end(); ++it){
    cout <<" [ "<< *(it->second).afficher() <<" ] "<< endl ;
  }
  cout << endl << " ___________________________________________________________ "<< endl;
}
