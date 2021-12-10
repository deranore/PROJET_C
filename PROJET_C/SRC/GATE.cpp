//Ecrite le 03/12/2021
//cslasse abstraite de porte
//Brian Martinez

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "GATE.h"

Gate::Gate(string _nom,vector<string> _input,string _output,unsigned int _delay):name(_nom),input(_input),output(_output),delay(_delay){

}
Gate::~Gate(){
  
}
//accesseur
string Gate::get_name(){
  return name;
}
string Gate::get_output(){
  return output;
}
unsigned int Gate::get_delay(){
  return delay;
}
vector<string> Gate::get_input(){
  return input;
}
