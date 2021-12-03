//Ecrite le 03/12/2021
//cslasse abstraite de porte
//Brian Martinez

#inndef _GATE_H_
#define _GATE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <NET.h>

using namespace std;

class Gate {

  private :
    string name = " " ;
    vector<string> input ;
    string output = " " ;
    unsigned int delay = 0 ;

  public :
    //constructeur
    Gate(string _nom,vector<string> _input,string _output,unsigned int _delay=0);

    //accesseur
    string get_nom(){
      return nom;
    }
    string get_output(){
      return output;
    }
    unsigned int get_delay(){
      return delay;
    }
    vector<string> get_input(){
      return input;
    }

    //fonction virtuelle pure
    virtual bool calcul_output(input map(string,net))=0;
    virtual bool afficher()=0;


}
