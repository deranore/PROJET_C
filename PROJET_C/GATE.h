//Ecrite le 03/12/2021
//cslasse abstraite de porte
//Brian Martinez
#ifndef GATE_H
#define GATE_H
  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include <map>
  #include "NET.h"

using namespace std;

class Gate {

  private :
    string name;
    vector<string> input ;
    string output;
    unsigned int delay;

  public :
    //constructeur
    Gate(string _nom,vector<string> _input,string _output,unsigned int _delay=0);
    virtual ~Gate();
    //accesseur
    string get_name();
    string get_output();
    unsigned int get_delay();
    vector<string> get_input();

    //fonction virtuelle pure
    virtual bool calcul_output(map<string,Net> input)=0;
    virtual void afficher()=0;
};
#endif
