//Ecrite le 03/12/2021
//cslasse abstraite de porte ET 2 entrée
//Brian Martinez

#inndef _AND_1_H_
#define _AND_1_H_


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <NET.h>
#include "COMB.h"
#include "GATE.h"

using namespace std;

class AND1 : public Comb {

  private :

  public :
    //Constructeur
    AND1(string _nom,vector<string> _input,string _output,unsigned int _delay=0);
    ~AND1();

    //Fonction virtuelle pure
    bool calcul_output(input map(string,net));
    void afficher();
}
