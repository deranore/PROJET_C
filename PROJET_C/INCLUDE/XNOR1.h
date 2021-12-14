//Ecrite le 03/12/2021
//cslasse abstraite de porte ET 2 entrée
//Brian Martinez

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "COMB.h"

using namespace std;

class XNOR1 : public Comb {

  private :

  public :
    //Constructeur
    XNOR1(string _nom,vector<string> _input,string _output,unsigned int _delay=0);
    ~XNOR1();

    //Fonction virtuelle pure
    bool calcul_output(map<string,Net> input);
    void afficher();
};
