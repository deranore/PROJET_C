//Ecrite le 13/12/2021
//cslasse abstraite de porte non ET 2 entrée
//Brian Martinez

#ifndef NAND_1_H
#define NAND_1_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "COMB.h"


using namespace std;

class NAND1 : public Comb {

  private :

  public :
    //Constructeur
    NNAND1(string _nom,vector<string> _input,string _output,unsigned int _delay=0);
    ~NAND1();

    //Fonction virtuelle pure
    bool calcul_output(map<string,Net> input);
    void afficher();
};
#endif
