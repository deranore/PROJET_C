//Ecrite le 03/12/2021
//cslasse abstraite de porte ET 2 entrée
//Brian Martinez

#inndef _NOT_1_H_
#define _NOT_1_H_


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <NET.h>
#include "COMB.h"
#include "GATE.h"

using namespace std;

class NOT1 : public Comb {

  private :

  public :
    //Constructeur
    NOT1(string _nom,vector<string> _input,string _output,unsigned int _delay=0);
    ~NOT1();

    //Fonction virtuelle pure
    bool calcul_output(input map(string,net));
    void afficher();
}
