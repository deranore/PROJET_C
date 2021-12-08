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

class MUX1 : public Comb {

  private :
    vector<string> select;
  public :
    //Constructeur
    MUX1(string _nom,vector<string> _input,string _output,vector<string> _slect,unsigned int _delay=0);
    ~MUX1();

    //Accesseur
    vector<string> get_select();
    //Fonction virtuelle pure
    bool calcul_output(map<string,Net> input);
    void afficher();
};
