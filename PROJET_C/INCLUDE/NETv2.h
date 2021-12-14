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
    bool current_val;
    vector <bool> val;
    unsigned int index_val;

  public:
    Net(){
      name = " " ;
      current_val = 0 ;
      index_val = 0 ;
    }
    Net(string _name,bool _val=0);
    ~Net();

    void add_val(bool new_val);

    string get_name();
    bool get_current_val();
    vector<bool> get_val();
    void set_val(unsigned int index);

    void afficher();
};
#endif
