//Ecrite le 07/12/2021
//cslasse de net
//Brian Martinez

#ifndef NET_H
#define NET_H
  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include <map>

using namespace std;

class Net{

  private :
    string name;
    bool val;

  public:
    Net(){
      name = " " ;
      val = 0 ;
    }
    Net(string _name,bool _val=0);
    ~Net();

    string get_name();
    bool get_val();
    void set_val(bool valeur);

    void afficher();
};
#endif
