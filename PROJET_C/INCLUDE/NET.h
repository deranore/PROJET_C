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
