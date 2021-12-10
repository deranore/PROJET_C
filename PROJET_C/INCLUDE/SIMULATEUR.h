#ifndef NET_H
  #define NET_H
  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include <map>
  #include "NET.h"
  #include "GATE.h"
  #include "DECOUPAGE.h"

  using namespace std;

  class Simulateur{

  private :
  map<string,*Net> input;
  map<string,*Net> output;
  map<string,*Gate> gate;
  string url_json;
  string url_dot;

  void set_url_json(string url);
  void set_url_dot(string url);

  public :
  Simulateur();
  ~Simulateur();

  void obtain_url();
  bool url_valid();
  string get_url_json();
  string get_url_json();

  *Net get_input(string nom);
  *Net get_output(string nom);
  *Gate get_gate(string nom);
  bool add_input(*Net);
  bool add_output(*Net);
  bool add_gate(*Gate);
  void set_input(unsigned int index);
  void set_output(bool val);

  vector<Decoupage> lexeur();
  int parsseur(vector<Decoupage>);
  void err_parssing(*Decoupage);

  int Kernel();10
  void err_simulation(*Gate,*Net);

  void print();

  };
#endif
