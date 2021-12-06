//Ecrite le 03/12/2021
//cslasse abstraite de porte ET 2 entrée
//Brian Martinez

#inndef _MUX_1_H_
#define _MUX_1_H_


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <NET.h>
#include "COMB.h"
#include "GATE.h"

using namespace std;

class MUX1 : public Comb {

  private :
    string slect;
  public :
    //Constructeur
    MUX1(string _nom,vector<string> _input,string _output,string _slect,unsigned int _delay=0);
    ~MUX1();

    //Accesseur
    string get_slect();
    //Fonction virtuelle pure
    bool calcul_output(input map(string,net));
    void afficher();
}
