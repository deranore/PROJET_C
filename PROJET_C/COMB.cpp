//Ecrite le 03/12/2021
//cslasse abstraite de porte combinatoire
//Brian Martinez

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "COMB.h"

Comb::Comb(string _nom,vector<string> _input,string _output,unsigned int _delay):Gate(_nom,_input,_output,_delay){

}
Comb::~Comb(){

}
