//Ecrite le 03/12/2021
//cslasse abstraite de porte combinatoire
//Brian Martinez

#inndef _COMB_H_
#define _COMB_H_


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <NET.h>
#include <GATE.h>

using namespace std;

class Comb : public Gate {

  private :

  public :
    //constructeur
    Comb(string _nom,vector<string> _input,string _output,unsigned int _delay=0);

    //fonction virtuelle pure
    virtual bool calcul_output(input map(string,net));
    virtual bool afficher();


}
